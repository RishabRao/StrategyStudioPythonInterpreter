/*================================================================================                               
*     Source: ../RCM/StrategyStudio/examples/strategies/SimplePairsStrategy/SimplePairsExample.cpp                                                        
*     Last Update: 2010/09/30 13:55:14                                                                            
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) RCM-X, 2011 - 2012.                                                  
*     All rights reserved.                                                                                       
*                                                                                                                
*     This software is part of Licensed material, which is the property of RCM-X ("Company"), 
*     and constitutes Confidential Information of the Company.                                                  
*     Unauthorized use, modification, duplication or distribution is strictly prohibited by Federal law.         
*     No title to or ownership of this software is hereby transferred.                                          
*                                                                                                                
*     The software is provided "as is", and in no event shall the Company or any of its affiliates or successors be liable for any 
*     damages, including any lost profits or other incidental or consequential damages relating to the use of this software.       
*     The Company makes no representations or warranties, express or implied, with regards to this software.                        
/*================================================================================*/   

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "SimpleTwoPairsStrategy.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>

#include <math.h>
#include <iostream>
#include <cassert>

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;

using namespace std;

SimplePairs::SimplePairs(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_spState(),
    m_bars(),
    m_instrumentX(NULL),
    m_instrumentY(NULL),
    m_rollingWindow(15),
    m_zScore(0),
    m_zScoreThreshold(1.5),
    m_tradeSize(100),
    m_nOrdersOutstanding(0),
    m_DebugOn(false)
{
    // note: assume market state is active
    m_spState.marketActive = true;
    //this->set_enabled_pre_open_data_flag(true);
    //this->set_enabled_pre_open_trade_flag(true);
    //this->set_enabled_post_close_data_flag(true);
    //this->set_enabled_post_close_trade_flag(true);
}

SimplePairs::~SimplePairs()
{
}

void SimplePairs::OnResetStrategyState()
{
    m_spState.marketActive = true;
    m_spState.unitsDesired = 0;

    m_rollingWindow.clear();
    m_bars.clear();
}

void SimplePairs::DefineStrategyParams()
{
    CreateStrategyParamArgs arg1("z_score", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_zScoreThreshold);
    params().CreateParam(arg1);

    CreateStrategyParamArgs arg2("trade_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, m_tradeSize);
    params().CreateParam(arg2);

    CreateStrategyParamArgs arg3("debug", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, m_DebugOn);
    params().CreateParam(arg3);
}

void SimplePairs::DefineStrategyGraphs()
{
    graphs().series().add("Mean");
    graphs().series().add("ZScore");
}

void SimplePairs::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    
    int count = 0;

    for (SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        EventInstrumentPair retVal = eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 10);    
        
        if (count == 0) {
            m_instrumentX = retVal.second;
        } else if (count == 1) {
            m_instrumentY = retVal.second;
        }
    
        ++count;
    }
}

void SimplePairs::OnTrade(const TradeDataEventMsg& msg)
{
}

void SimplePairs::OnTopQuote(const QuoteEventMsg& msg)
{x   
}

void SimplePairs::OnBar(const BarEventMsg& msg)
{
     if (m_DebugOn) {
        ostringstream str;
        str << msg.instrument().symbol() << ": "<< msg.bar();
        logger().LogToClient(LOGLEVEL_DEBUG, str.str().c_str());
     }

    // update our bars collection
    m_bars[&msg.instrument()] = msg.bar();

    if (m_bars.size() < 2) {
	    //wait until we have bars for both pairs
        return;
    }

    assert(m_bars.size() == 2);

    double barCloseRatio = 0;
    if (m_bars[m_instrumentY].close() != 0) {
        barCloseRatio = m_bars[m_instrumentX].close() / m_bars[m_instrumentY].close();
        m_bars.clear();
    } else {
        m_bars.clear();
        return;
    }
    
     m_rollingWindow.push_back(barCloseRatio);
   
    // only process when we have a complete rolling window
    if (!m_rollingWindow.full())
        return;

    if (orders().num_working_orders() > 0) 
        return;

    m_zScore = m_rollingWindow.ZScore();

    graphs().series()["Mean"]->push_back(msg.event_time(), m_rollingWindow.Mean());
    graphs().series()["ZScore"]->push_back(msg.event_time(), m_zScore);    
    
    // sell X and buy Y when z widens 
    if (m_zScore > m_zScoreThreshold) {
        m_spState.unitsDesired = -m_tradeSize;
    } else if (m_zScore < -m_zScoreThreshold) {
        m_spState.unitsDesired = m_tradeSize;
    } else {
        m_spState.unitsDesired = 0;
    }

    if (m_spState.marketActive) AdjustPortfolio();
}

void SimplePairs::AdjustPortfolio()
{
    // wait until orders are filled before we send out more orders
    if (orders().num_working_orders() > 0 || portfolio().position(m_instrumentX) != -portfolio().position(m_instrumentY)) {
        return;
    }

    int unitsNeeded = m_spState.unitsDesired - portfolio().position(m_instrumentX);

    if (unitsNeeded > 0) {
        SendBuyOrder(m_instrumentX, unitsNeeded);
        SendSellOrder(m_instrumentY, unitsNeeded);

    } else if (unitsNeeded < 0) {
        SendSellOrder(m_instrumentX, -unitsNeeded);
        SendBuyOrder(m_instrumentY, -unitsNeeded);
    }
}

void SimplePairs::SendBuyOrder(const Instrument* instrument, int unitsNeeded)
{
    if (m_DebugOn) {
        std::stringstream ss;
        ss << "Sending buy order for " << instrument->symbol() << " at price " << instrument->top_quote().ask() << " and quantity " << unitsNeeded;   
        logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
    }

    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().ask() != 0) ? instrument->top_quote().ask() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_BUY,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}
    
void SimplePairs::SendSellOrder(const Instrument* instrument, int unitsNeeded)
{
    if(m_DebugOn) {
        std::stringstream ss;
        ss << "Sending sell order for " << instrument->symbol() << " at price " << instrument->top_quote().bid() << " and quantity " << unitsNeeded;   
        logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
    }

    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().bid() != 0) ? instrument->top_quote().bid() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_SELL,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}

void SimplePairs::OnMarketState(const MarketStateEventMsg& msg)
{
}

void SimplePairs::OnOrderUpdate(const OrderUpdateEventMsg& msg)  
{
}

void SimplePairs::OnAppStateChange(const AppStateEventMsg& msg)
{
}

void SimplePairs::OnParamChanged(StrategyParam& param)
{    
    if (param.param_name() == "z_score") {
        if (!param.Get(&m_zScoreThreshold))
            throw StrategyStudioException("Could not get zscore threshold");
    } else if (param.param_name() == "trade_size") {
        if (!param.Get(&m_tradeSize))
            throw StrategyStudioException("Could not get trade size");
    } else if (param.param_name() == "debug") {
        if (!param.Get(&m_DebugOn))
            throw StrategyStudioException("Could not get trade size");
    }        
}
