import sqlite3

# import os
# current_dir = os.getcwd()
# print("current directory: ",current_dir)

# Connect to the SQLite database
conn = sqlite3.connect('strategy.db')
# sqlite creates the db if it doesnt exist (double edged sword)

cursor = conn.cursor()

# # Query the sqlite_master table to get all table names
# cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
# tables = cursor.fetchall()

# # Print the table names
# for table in tables:
#     print(table[0])
# Delete the data created by Strategy Studio when you build your strategy. 
# If there is no row(first time you build), nothing will happen
cursor.execute("DELETE FROM StrategyInstance WHERE instName = 'TestPybindStrategy'")
# cursor.execute("DELETE FROM StrategyType WHERE strategyTypeName = 'PybindStrat'")

# Commit the changes to the database
conn.commit()

# Close the connection
conn.close()
