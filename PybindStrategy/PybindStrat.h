#pragma once

#ifndef _STRATEGY_STUDIO_LIB_EXAMPLES_PYBIND_STRATEGY_H_
#define _STRATEGY_STUDIO_LIB_EXAMPLES_PYBIND_STRATEGY_H_

#ifdef _WIN32
    #define _STRATEGY_EXPORTS __declspec(dllexport)
#else
    #ifndef _STRATEGY_EXPORTS
    #define _STRATEGY_EXPORTS
    #endif
#endif

#include <Strategy.h>
#include <Analytics/ScalarRollingWindow.h>
#include <Analytics/InhomogeneousOperators.h>
#include <Analytics/IncrementalEstimation.h>
#include <MarketModels/Instrument.h>
#include <Utilities/ParseConfig.h>
#include <iostream>
#include <stdlib.h>
#include <functional>

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>
#include "DataTypes.h"
#include "MarketModels/MarketCenterTypes.h"
#include "OrderParams.h"
#include <vector>
#include <mutex>
#include <string>

#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "pybind11/functional.h"
#include "pybind11/stl.h"
#include "pybind11/pytypes.h"
// #include "pybind11/stl_bind.h"
// #include "pybind11/complex.h"


using namespace RCM::StrategyStudio;
using namespace std;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;


class PybindStrategy : public Strategy {
    public:
        PybindStrategy(StrategyID strategyID, const std::string& strategyName, const std::string& groupName);
        ~PybindStrategy();
        
        struct StrategyActions {
            StrategyActions(PybindStrategy* s) : strategy(s) {}

            // const StrategyParamCollection& params() const {
            //     return strategy->params();
            // }

            const IPortfolioTracker& portfolio() const {
                return strategy->portfolio();
            }
            
            const IOrderTracker& orders() const {
                return strategy->orders();
            }

            // const IFillTracker& fills() const {
            //     return strategy->fills();
            // }

            const ITradeTracker& trades() const {
                return strategy->trades();
            }

            // const IRiskProfile& risk_profile() const {
            //     return strategy->risk_profile();
            // }

            const AccountFees& account_fees() const {
                return strategy->account_fees();
            }

            StrategyTradeActions* trade_actions() const {
                return strategy->trade_actions();
            }

            size_t SymbolCount() const {
                return strategy->SymbolCount();
            }

            // Iterators

            py::iterator symbols() const {
                return py::make_iterator(strategy->symbols_begin(), strategy->symbols_end());
            }

            py::iterator instruments() const {
                return py::make_iterator(strategy->instrument_begin(), strategy->instrument_end());
            }

            py::iterator instrument_find(const std::string& symbol) const {
                return py::make_iterator(strategy->instrument_find(symbol), strategy->instrument_end());
            }

            // Flags
            bool CheckEnabledTradingForMarketState() const {
                return strategy->CheckEnabledTradingForMarketState();
            }

            bool enabled_post_close_data_flag() const {
                return strategy->enabled_post_close_data_flag();
            }

            void set_enabled_post_close_data_flag(bool flag) {
                strategy->set_enabled_post_close_data_flag(flag);
            }

            bool enabled_post_close_trade_flag() const {
                return strategy->enabled_post_close_trade_flag();
            }

            void set_enabled_post_close_trade_flag(bool flag) {
                strategy->set_enabled_post_close_trade_flag(flag);
            }

            bool enabled_pre_open_data_flag() const {
                return strategy->enabled_pre_open_data_flag();
            }

            void set_enabled_pre_open_data_flag(bool flag) {
                strategy->set_enabled_pre_open_data_flag(flag);
            }

            bool enabled_pre_open_trade_flag() const {
                return strategy->enabled_pre_open_trade_flag();
            }

            void set_enabled_pre_open_trade_flag(bool flag) {
                strategy->set_enabled_pre_open_trade_flag(flag);
            }

            bool enabled_cancel_on_stop_flag() const {
                return strategy->enabled_cancel_on_stop_flag();
            }

            void set_enabled_cancel_on_stop_flag(bool flag) {
                strategy->set_enabled_cancel_on_stop_flag(flag);
            }

            private:
                PybindStrategy* strategy;
        };

    public: /* from IEventCallback */

    /**
     * This event triggers whenever trade message arrives from a market data source.
     */ 
    virtual void OnTrade(const TradeDataEventMsg& msg);

    /**
     * This event triggers whenever aggregate volume at best price changes, based 
     * on the best available source of liquidity information for the instrument.
     *
     * If the quote datasource only provides ticks that change the NBBO, top quote will be set to NBBO
     */ 
    virtual void OnTopQuote(const QuoteEventMsg& msg);
    
    /**
     * This event triggers whenever a new quote for a market center arrives from a consolidate or direct quote feed,
     * or when the market center's best price from a depth of book feed changes.
     *
     * User can check if quote is from consolidated or direct, or derived from a depth feed. This will not fire if
     * the data source only provides quotes that affect the official NBBO, as this is not enough information to accurately
     * mantain the state of each market center's quote.
     */ 
    virtual void OnQuote(const QuoteEventMsg& msg);
    
    /**
     * This event triggers whenever a order book message arrives. This will be the first thing that
     * triggers if an order book entry impacts the exchange's DirectQuote or Strategy Studio's TopQuote calculation.
     */ 
    virtual void OnDepth(const MarketDepthEventMsg& msg);

    /**
     * This event triggers whenever a Bar interval completes for an instrument
     */ 
    virtual void OnBar(const BarEventMsg& msg);

    /**
     * This event contains alerts about the state of the market
     */

     /**
     * This event contains alerts about the state of the market
     */
    virtual void OnMarketState(const MarketStateEventMsg& msg){};

    /**
     * This event triggers whenever new information arrives about a strategy's orders
     */ 
    virtual void OnOrderUpdate(const OrderUpdateEventMsg& msg);

    /**
     * This event contains strategy control commands arriving from the Strategy Studio client application (eg Strategy Manager)
     */ 
    virtual void OnStrategyControl(const StrategyStateControlEventMsg& msg){}
    
    /**
     *  Perform additional reset for strategy state 
     */
    void OnResetStrategyState();

    /**
     * This event contains alerts about the status of a market data source
     */ 
    void OnDataSubscription(const DataSubscriptionEventMsg& msg){}


    
    /**
     * This event triggers whenever a custom strategy command is sent from the client
     */ 
    void OnStrategyCommand(const StrategyCommandEventMsg& msg);

    /**
     * Notifies strategy for every succesfull change in the value of a strategy parameter.
     *
     * Will be called any time a new parameter value passes validation, including during strategy initialization when default parameter values
     * are set in the call to CreateParam and when any persisted values are loaded. Will also trigger after OnResetStrategyState
     * to remind the strategy of the current parameter values.
     */ 
    void OnParamChanged(StrategyParam& param);

    /**
     * Triggers when news runs 
     * 
    */
    void OnNews(const NewsEventMsg& msg);

    /**
     * Sets up python and runs the abstract functions that would normally 
     * run in a different thread
    */
    void run_init(); 
    
    py::module_ MyStrategy; 
    py::object PybindStrat; 
    
    static std::function<void(py::object)> saved_register_call; 
    static std::function<void(py::object)> saved_define_params_call; 
    static std::function<void(py::object)> saved_define_commands_call; 

private:  
    /* from Strategy */

    virtual void RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate); 
    
    /**
     * Define any params for use by the strategy 
     */     
    virtual void DefineStrategyParams();

    /**
     * Define any strategy commands for use by the strategy
     */ 
    virtual void DefineStrategyCommands();

};  

extern "C" {

    _STRATEGY_EXPORTS const char* GetType()
    {
        return "PybindStrategy";
    }

    _STRATEGY_EXPORTS IStrategy* CreateStrategy(const char* strategyType, 
                                   unsigned strategyID, 
                                   const char* strategyName,
                                   const char* groupName)
    {
        if (strcmp(strategyType,GetType()) == 0) {
            return *(new PybindStrategy(strategyID, strategyName, groupName));
        } else {
            return NULL;
        }
    }

     // must match an existing user within the system 
    _STRATEGY_EXPORTS const char* GetAuthor()
    {
        return "dlariviere";
    }

    // must match an existing trading group within the system 
    _STRATEGY_EXPORTS const char* GetAuthorGroup()
    {
        return "UIUC";
    }

    // used to ensure the strategy was built against a version of the SDK compatible with the server version
    _STRATEGY_EXPORTS const char* GetReleaseVersion()
    {
        return Strategy::release_version();
    }
}

#endif
