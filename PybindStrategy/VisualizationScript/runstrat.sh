
jupyter-nbconvert --TagRemovePreprocessor.enabled=True --TagRemovePreprocessor.remove_cell_tags={\"remove\"} --to python your_strategy.ipynb --output ../MyStrategy.py
cd ../../strategystudioubuntu2004
./go.sh
