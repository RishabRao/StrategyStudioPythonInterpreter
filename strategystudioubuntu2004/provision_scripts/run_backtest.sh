#!/bin/bash

startDate='2021-11-05'
endDate='2021-11-05'
instanceName='TestPybindStrategy'

(cd /home/vagrant/ss/bt && ./StrategyServerBacktesting&)

echo "Sleeping for 2 seconds while waiting for strategy studio to boot"
sleep 2

# Start the backtest
(cd /home/vagrant/ss/bt/utilities/ && ./StrategyCommandLine cmd start_backtest $startDate $endDate $instanceName 0)

# Get the line number which ends with finished. 
foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/ss/bt/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)

# DEBUGGING OUTPUT
echo "Last line found:",$foundFinishedLogFile

# If the line ending with finished. is less than the previous length of the log file, then strategyBacktesting has not finished, 
# once its greater than the previous, it means it has finished.
while ((logFileNumLines > foundFinishedLogFile))
do
    foundFinishedLogFile=$(grep -nr "finished.$" /home/vagrant/ss/bt/logs/main_log.txt | gawk '{print $1}' FS=":"|tail -1)

    #DEBUGGING OUTPUT
    echo "Waiting for strategy to finish"
    sleep 1
done

echo "Sleeping for 10 seconds..."

sleep 10

echo "run_backtest.sh: Strategy Studio finished backtesting"

latestCRA=$(ls /home/vagrant/ss/bt/backtesting-results/BACK_*.cra -t | head -n1)

# Print the path of the craFile
echo "CRA file found:", $latestCRA

# Navigate to utilities directory
cd /home/vagrant/ss/bt/utilities/

# Use the StrategyCommandLine utility to eport the CRA file to CSV format
# Name of file should be the latest craFile created
./StrategyCommandLine cmd export_cra_file $latestCRA ~/ss/bt/backtesting-results/csv_files
