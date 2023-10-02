# group_02_project

## Setup
- Vagrant
- VirtualBox

```sh
git clone --recursive https://gitlab.engr.illinois.edu/ie421_high_frequency_trading_spring_2023/ie421_hft_spring_2023_group_02/group_02_project.git

cd group_02_project/strategystudioubuntu2004/
# Add license.txt to this folder

./go.sh
```

## Requirements
* Make sure you have jupyter-nbconvert installed. ie ```jupyter-nbconvert``` from command line should return output
* Make sure you also have jupyter notebook installed and are able to run jupyter notebooks.

## Usage
* Simply edit the ```VisualizationScripts/your_strategy.ipynb```. The first cell will contain a python class of a strategy. We have filled in an example strategy for you (it sucks!) but you can edit the class to hopefully perform a bit better an make some money! 
* Once you have coded a strategy to backtest it simply run the next cell. This will run a shell script that runs our Python binded strategy studio code with your strategy.
* Run the next cell to see a visualization of your strategy. Currently we will graph your P&L and position.
