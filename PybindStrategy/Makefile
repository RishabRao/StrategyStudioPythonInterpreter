# Conditional settings based on passed in variables
ifdef INTEL
    CC=icc
else
    CC=g++
endif

ifdef DEBUG
    CFLAGS=-c -g -fPIC -fpermissive -std=c++11
else
    CFLAGS=-c -fPIC -fpermissive -O3 -std=c++11
endif

LIBPATH=../../../libs/x64
INCLUDEPATH=../../../includes

INCLUDES=-I/usr/include -I/usr/include/python3.8 -I$(INCLUDEPATH) -I./includes
LDFLAGS= -lpython3.8 $(LIBPATH)/libstrategystudio_analytics.a $(LIBPATH)/libstrategystudio.a $(LIBPATH)/libstrategystudio_transport.a $(LIBPATH)/libstrategystudio_marketmodels.a $(LIBPATH)/libstrategystudio_utilities.a $(LIBPATH)/libstrategystudio_flashprotocol.a
LIBRARY=PybindStrategy.so
PYSRC=MyStrategy.py BaseStrategy.py

SOURCES=PybindStrat.cpp
HEADERS=PybindStrat.h $(wildcard includes/*.h) # recompile if any header changes
# $(info    HEADERS is $(HEADERS))
 
OBJECTS=$(SOURCES:.cpp=.o)
DEPENDENCIES=$(HEADERS:%.h=%.d)

all: $(HEADERS) $(LIBRARY)

$(LIBRARY) : $(OBJECTS)
	$(CC) -shared -Wl,-soname,$(LIBRARY).1 -o $(LIBRARY) $(OBJECTS) $(LDFLAGS)

# Recompile if any header changes
-include $(DEPENDENCIES)

.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP $< -o $@

clean:
	rm -rf *.o $(LIBRARY) $(DEPENDENCIES)

copy_strategy: all
	cp $(LIBRARY) /home/vagrant/ss/bt/strategies_dlls/.
	cp $(PYSRC) /home/vagrant/ss/bt/strategies_dlls/.
	cp $(PYSRC) /home/vagrant/ss/bt/.
launch_backtest: 
	#cd /home/vagrant/Desktop/strategy_studio/backtesting/utilities ; ./StrategyCommandLine cmd start_backtest 2021-11-05 2021-11-05 TestTwoDiaIndexArbStrategy 1
	cd /home/vagrant/ss/bt/utilities ; ./StrategyCommandLine cmd start_backtest 2021-11-05 2021-11-05 TestOneDiaIndexArbStrategy 1

run_backtest: all
	cd ~/Downloads/ss_backtesting ; echo $PWD ; ./run_backtest.sh
	export TEST_VAR="satyanshshrey" ; \
	echo $$TEST_VAR

output_results: 
	export TEST_VAR="satyanshshrey" ; \
	echo $$TEST_VAR
	export CRA_RESULT=`cd ~/Downloads/ss_backtesting ; find ./backtesting-results -name 'BACK*cra' | tail -n 1` ; \
	echo $$CRA_RESULT
	
	