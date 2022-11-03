
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

f1 = pd.read_csv("jeu4.csv",header=None)
plt.scatter(f1[0],f1[1], marker = "o", color = "red")
""" plt.plot(20,352, marker="o", color="red")
plt.plot(30,128, marker="o", color="red")
plt.plot(40,62.3, marker="o", color="red")
plt.plot(50,35.7, marker="o", color="red")
plt.plot(100,6.3, marker="o", color="red")
plt.plot(300,0.4, marker="o", color="red")
plt.plot(500,0.1, marker="o", color="red") """

x=np.linspace(0, 500, 30)
y=696594.312500*pow(x,-2.527187)
plt.plot(x,y)

plt.show()