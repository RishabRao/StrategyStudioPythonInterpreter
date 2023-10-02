import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from scipy.interpolate import interp1d
import datetime
import dateutil



def plotPositions():
    df = pd.read_csv("data/fills.csv")

    symbolSet = set(df.Symbol.unique())
    symbolData = dict.fromkeys(symbolSet, [[],0,0,[]]) # time, poslogs, position cnt, position
    numPerBucket = len(df) // 250  # number of fill updates before we log our position

    for index, row in df.iterrows():
        sym = row['Symbol']
        qty = row['Quantity']
        symbolData[sym][1]+=1
        symbolData[sym][2] += qty

        if (symbolData[sym][1] == numPerBucket):
            symbolData[sym][0].append(symbolData[sym][2])
            symbolData[sym][3].append(dateutil.parser.parse(row['TradeTime']))
            symbolData[sym][1] = 0



    if (len(symbolSet) > 6):
        print("We do not support more than 6 symbols for graphing")
        exit()

    symbolSet = list(symbolSet)
    numPlots = min(6,len(symbolSet))
    fig, axs = plt.subplots(numPlots,figsize=(20, 20))
    fig.autofmt_xdate()
    fig.suptitle('Position Tracking')

    xfmt = mdates.DateFormatter('%H:%M:%S')

    if ( numPlots > 1):
        for i,ax in enumerate(axs):
            sym = symbolSet[i]
            ax.set(xlabel='timestamp', ylabel='Position')
            ax.set_title(f'Daily Position for {sym}')
            ax.plot(symbolData[sym][3], symbolData[sym][0])
            ax.set_xticklabels(ax.get_xticks(), rotation=45)
            ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=10))
            ax.xaxis.set_major_formatter( xfmt )
    else:
        sym = symbolSet[0]
        axs.set(xlabel='timestamp', ylabel='Position')
        axs.set_title(f'Daily Position for {sym}')
        axs.plot(symbolData[sym][3], symbolData[sym][0])
        axs.set_xticklabels(axs.get_xticks(), rotation=45)
        axs.xaxis.set_major_locator(mdates.MinuteLocator(interval=10))
        axs.xaxis.set_major_formatter( xfmt )

    plt.show()