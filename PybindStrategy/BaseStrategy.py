from abc import ABC, abstractmethod

'''
This is based off of RCM::StrategyStudio::Strategy
Header file: https://davidl.web.engr.illinois.edu/data/20191030_marketdata/rcm/RCM/StrategyStudio/docs/html/dd/db4/_strategy_8h_source.html
'''
class BaseStrategy(ABC):
    def __init__(self, strategy_actions):
        self.portfolio = strategy_actions.portfolio
        self.orders = strategy_actions.orders
        self.trades = strategy_actions.trades
        self.account_fees = strategy_actions.account_fees
        self.trade_actions = strategy_actions.trade_actions
        self.SymbolCount = strategy_actions.SymbolCount
        
        # Iterators
        self.symbols = strategy_actions.symbols
        self.instruments = strategy_actions.instruments
        self.instrument_find = strategy_actions.instrument_find

        # Flags
        self.CheckEnabledTradingForMarketState = strategy_actions.CheckEnabledTradingForMarketState
        self.enabled_post_close_data_flag = strategy_actions.enabled_post_close_data_flag
        self.set_enabled_post_close_data_flag = strategy_actions.set_enabled_post_close_data_flag
        self.enabled_post_close_trade_flag = strategy_actions.enabled_post_close_trade_flag
        self.set_enabled_post_close_trade_flag = strategy_actions.set_enabled_post_close_trade_flag
        self.enabled_pre_open_data_flag = strategy_actions.enabled_pre_open_data_flag
        self.set_enabled_pre_open_data_flag = strategy_actions.set_enabled_pre_open_data_flag
        self.enabled_pre_open_trade_flag = strategy_actions.enabled_pre_open_trade_flag
        self.set_enabled_pre_open_trade_flag = strategy_actions.set_enabled_pre_open_trade_flag
        self.enabled_cancel_on_stop_flag = strategy_actions.enabled_cancel_on_stop_flag
        self.set_enabled_cancel_on_stop_flag = strategy_actions.set_enabled_cancel_on_stop_flag

    def SetStrategyActions(self, strategy_actions): 
        if strategy_actions is not None: 
            self.trade_actions = strategy_actions.trade_actions
            self.orders = strategy_actions.orders

        else: 
            self.trade_actions = None
            self.orders = None

    """Overridable hooks for events"""
    @abstractmethod
    def RegisterForStrategyEvents(self, eventRegister, currDate):
        pass
    
    @abstractmethod
    def OnResetStrategyState(self):
        pass
    
    # Set flags before the strategy is started
    def SetFlags(self):
        pass

    def OnTrade(self, msg):
        pass
    
    def OnTopQuote(self, msg):
        pass
    
    def OnQuote(self, msg):
        pass
    
    def OnDepth(self, msg):
        pass
    
    def OnImbalance(self, msg):
        pass
    
    def OnWorkup(self, msg):
        pass
    
    def OnInstrumentAlert(self, msg):
        pass
    
    def OnPriceBand(self, msg):
        pass
    
    def OnIndex(self, msg):
        pass
    
    def OnNews(self, msg):
        pass
    
    def OnSentiment(self, msg):
        pass
    
    def OnSentimentActivity(self, msg):
        pass
    
    def OnBar(self, msg):
        pass
    
    def OnOptionsAnalytics(self, msg):
        pass
    
    def OnCorporateAction(self, msg):
        pass
    
    def OnMarketState(self, msg):
        pass
    
    def OnOrderUpdate(self, msg):
        pass
    
    def OnExternalFill(self, msg):
        pass
    
    def OnStrategyCommand(self, msg):
        pass
    
    def OnStrategyControl(self, msg):
        pass
    
    def OnDataSubscription(self, msg):
        pass
    
    def OnAppStateChange(self, msg):
        pass
    
    def OnScheduledEvent(self, msg):
        pass
    
    def OnStrategyMessage(self, msg):
        pass
    
    def OnTopicMessage(self, msg):
        pass
    
    def OnExternalOrder(self, msg):
        pass
    
    def OnParamValidate(self, param):
        return True

