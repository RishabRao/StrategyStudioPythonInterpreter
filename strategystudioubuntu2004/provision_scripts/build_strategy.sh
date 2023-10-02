#!/bin/bash
mkdir -p /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/PybindStrategy/
tar -xzf /vagrant/PybindStrategy.tar.gz -C /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/PybindStrategy
cd /home/vagrant/ss/sdk/RCM/StrategyStudio/examples/strategies/
cd PybindStrategy
mkdir -p /home/vagrant/ss/bt/strategies_dlls
echo "removing old .so files..."
rm /home/vagrant/ss/bt/strategies_dlls/PybindStrategy.so
make copy_strategy
cd /home/vagrant/ss/bt/ ; ./StrategyServerBacktesting &
sleep 1
cd /home/vagrant/ss/bt/utilities
# ./StrategyCommandLine cmd terminate -all    
./StrategyCommandLine cmd create_instance TestPybindStrategy PybindStrategy UIUC SIM-1001-101 dlariviere 1000000 -symbols "AAPL"
./StrategyCommandLine cmd strategy_instance_list
./StrategyCommandLine cmd quit

