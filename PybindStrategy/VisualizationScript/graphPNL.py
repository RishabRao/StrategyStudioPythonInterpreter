import matplotlib.pyplot as plt
import csv

def graphPNL(aFileName = "data/pnl.csv"):
      myInstances = {}
      with open(aFileName, 'r') as file:
        csv_reader = csv.reader(file)

        header = next(csv_reader)

        for row in csv_reader:
          if (row[0] not in myInstances):
            myInstances[row[0]] = []

          myInstances[row[0]].append(float(row[2]))


      for myInstanceName, myPnls in myInstances.items():

        plt.figure(figsize=(20,20))
        plt.plot(myPnls)

        plt.title("PNL For " + myInstanceName)
        plt.xlabel("Time Increasing")
        plt.xticks([])
        plt.ylabel("PNL")
        plt.grid(True)

        plt.show()
