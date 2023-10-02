#!/usr/bin/env python
# coding: utf-8

# In[ ]:


from strategy import *
from BaseStrategy import BaseStrategy

class MyStrategy(BaseStrategy):
    def __init__(self, strategy_actions):
        self.small_window = 40
        self.big_window = 100
        self.small_sum = 0.0
        self.big_sum = 0.0
        self.stock_size = 0
        self.revenue = 0.0
        self.capital = 0.0
        self.trade_times = 0
        self.inc = 0
        self.small_set = []
        self.big_set = []

        super().__init__(strategy_actions)

    def OnResetStrategyState(self):
        pass
        
    # Set flags before the strategy is started
    def SetFlags(self):
        pass

    def OnTrade(self, msg):

        instrument = msg.instrument(); 
        mid_price = (instrument.top_quote().ask() + instrument.top_quote().bid()) / 2

        self.small_sum += mid_price
        self.big_sum += mid_price

        self.small_set.append(mid_price)
        self.big_set.append(mid_price)

        if len(self.small_set) > self.small_window: 
            self.small_sum -= self.small_set.pop()
       
        if len(self.big_set) > self.big_window: 
            self.big_sum -= self.big_set.pop()

        small_average = self.small_sum / len(self.small_set)
        big_average = self.big_sum / len(self.big_set)

        if small_average > big_average:
            self.SendOrder(instrument, 100)    
            self.stock_size += 100
            self.revenue -= instrument.top_quote().ask() * 100
            self.trade_times += 1 

        elif small_average < big_average and self.stock_size > 0:
            self.SendOrder(instrument, -100)    
            self.stock_size -= 100
            self.revenue += instrument.top_quote().bid() * 100
            self.trade_times += 1 
        
        self.capital = self.stock_size * instrument.top_quote().bid() + self.revenue

        print("Capital = " + str(self.capital) + " size = " + str(self.stock_size) + " trade times = " + str(self.trade_times))
        
        pass


    def OnTopQuote(self, msg):
        pass
       
    def OnQuote(self, msg): 
        pass
    
    def OnBar(self, msg): 
        pass

    def OnDepth(self, msg):
        pass
    
    def OnResetStrategyState(self): 
        pass

    def OnOrderUpdate(self, msg): 
        pass
    
    def OnResetStrategyState(self): 
        pass

    def RegisterForStrategyEvents(self, eventRegister, currDate):
        print("RegisterForStrategyEvents()")    
        print(currDate)
        pass
    
    def SendOrder(self, instrument, trade_size): 
        price = 0
        action = ""

        if trade_size > 0: # buy 
            price = instrument.top_quote().ask()
            action = "buy"
        else: # sell
            price = instrument.top_quote().bid()
            action = "sell"
        
        params = OrderParams(instrument, abs(trade_size), price, MARKET_CENTER_ID_IEX, (ORDER_SIDE_BUY if trade_size > 0 else ORDER_SIDE_SELL), ORDER_TIF_DAY, ORDER_TYPE_LIMIT)

        print("SendTradeOrder(): about to send new order for size " + str(trade_size) + " at $" + str(price) + " to " + str(action) + " " + instrument.symbol())
        
        self.trade_actions().SendNewOrder(params)
        pass

    def OnNews(self, msg):
        pass  


# # Do All data viz in the cell below

# In[ ]:




