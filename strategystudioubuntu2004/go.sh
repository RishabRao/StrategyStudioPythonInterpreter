#!/bin/bash

if [ -e iexdownloaderparser/parse_all.sh ]; then
	echo "Great! You properly cloned the repo using --recursive!"
else
	echo "ERROR! You didnt check out the repo correctly. You MUST use git clone --recursive (url); otherwise the sub repos dont get fetched too! (yes you can use additional commands instead but just do this instead)!"
	exit
fi

# vagrant destroy -f

if [ -e ~/.ssh/id_rsa ]; then
	echo "You already have your ssh key! great!"
else
	echo "You need to run ssh-keygen -t rsa -b 4096 to generate a new public / private key and add to gitlab"
	exit
fi

if [ -e strategy_studio_ubuntu20_gcc940_sdk.3.4.0.0.tar.gz ]; then
	echo "Great! You already downloaded the Strategy Studio SDK"
else
	echo "You need to download strategy_studio_ubuntu20_gcc940_sdk.3.4.0.0.tar.gz and place it into the same directory as Vagrantfile before proceeding!"
	exit
fi

if [ -e strategy_studio_ubuntu20_gcc940_server_backtesting_upgrade.3.4.0.0.tar.gz ]; then
        echo "Great! You already downloaded the Strategy Studio Backtesting Engine!"
else
        echo "You need to download strategy_studio_ubuntu20_gcc940_server_backtesting_upgrade.3.4.0.0.tar.gz and place it into the same directory as Vagrantfile before proceeding!"
        exit
fi

if [ -e license.txt ]; then
	echo "Great! You already placed your license.txt file in this folder!"
else
	echo "ERROR! You need to place your personal license.txt file in the same folder as the Vagrantfile before proceeding!"
	exit
fi

echo "Compressing PybindStrategy"
tar -czf PybindStrategy.tar.gz -C ../PybindStrategy/ .

echo "All dependencies are met! Launching VM!!"
echo "Bringing up VM"
source set_vagrant_env.sh

vagrant up

if [ -e iexdownloaderparser/data/text_tick_data/tick_AAPL_20211105.txt.gz ]; then
	echo "Great! You've already generated the required market data!"
else
	echo "Market data has not yet been generated... generating now!"
	vagrant ssh -c 'cd /vagrant ; provision_scripts/generate_data.sh'
fi

if [ -e iexdownloaderparser/data/text_tick_data/tick_AAPL_20211105.txt.gz ]; then
        echo "Great! You've generated the required market data!"
else
        echo "ERROR! Something failed generating the marketdata; this can not be fixed automatically; consult the Professor"
	exit
fi

vagrant ssh -c "cd ~/ss/bt/db ; pypy3 /vagrant/provision_scripts/delete_instance.py"
vagrant ssh -c '/vagrant/provision_scripts/build_strategy.sh'
vagrant ssh -c '/vagrant/provision_scripts/run_backtest.sh'
rm PybindStrategy.tar.gz
# vagrant ssh -c '/vagrant/provision_scripts/generate_results.sh'

vagrant ssh -c 'rm -r /home/vagrant/ss/bt/backtesting-results/csv_files/latest'
vagrant ssh -c 'mkdir /home/vagrant/ss/bt/backtesting-results/csv_files/latest'

vagrant ssh -c 'mv `ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_fill.csv | head -n1` /home/vagrant/ss/bt/backtesting-results/csv_files/latest'
vagrant ssh -c 'mv `ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_pnl.csv | head -n1`  /home/vagrant/ss/bt/backtesting-results/csv_files/latest'
# vagrant ssh -c 'ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_fill.csv | head -n1 | mv /home/vagrant/ss/bt/backtesting-results/csv_files/latest'



if vagrant plugin list | grep -q "vagrant-scp"; then
    echo "vagrant-scp plugin is installed."
else
    echo "vagrant-scp plugin is not installed."
	vagrant plugin install vagrant-scp
fi

# latest_fill_file=$(vagrant ssh -c "ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_fill.csv | head -n1")
# latest_order_file=$(vagrant ssh -c "ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_order.csv | head -n1")
# latest_pnl_file=$(vagrant ssh -c "ls -t /home/vagrant/ss/bt/backtesting-results/csv_files/BACK_*_pnl.csv | head -n1")

vagrant scp :/home/vagrant/ss/bt/backtesting-results/csv_files/latest ../PybindStrategy/VisualizationScript/data/


cp ../PybindStrategy/VisualizationScript/data/latest/BACK_*_fill.csv ../PybindStrategy/VisualizationScript/data/fills.csv
cp ../PybindStrategy/VisualizationScript/data/latest/BACK_*_pnl.csv ../PybindStrategy/VisualizationScript/data/pnl.csv

# rm -r ../PybindStrategy/VisualizationScript/data/csv_files
rm -r ../PybindStrategy/VisualizationScript/data/latest


