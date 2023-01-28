import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
plt.rcParams['axes.labelsize'] = 16
plt.rcParams['axes.titlesize'] = 16

data = pd.read_csv('new_tradeoff.csv')

total_cases = data['Cases']
cases0 = data['Level 0']
cases1 = data['Level 1']
cases2 = data['Level 2']
cases3 = data['Level 3']
cases4 = data['Level 4']

gdp = data['GDP']

plt.plot(gdp, cases0, label='Level 0')
plt.plot(gdp, cases1, label='Level 1')
plt.plot(gdp, cases2, label='Level 2')
plt.plot(gdp, cases3, label='Level 3')
plt.plot(gdp, cases4, label='Level 4')
plt.axvline(x=6.2, c='black', linewidth=2)
plt.axvline(x=7.5, c='black', linewidth=2)
plt.axvline(x=10.3, c='black', linewidth=2)
plt.xlabel('Economic Indicator (GDP)')
plt.ylabel('Time spent at respective levels')
plt.legend()
plt.show()


# plt.scatter(gdp, total_cases, s=200, facecolors='none', edgecolors='r')
# plt.plot(gdp, total_cases, c='b', linewidth=5.0, label='Pareto Optimal Front')
#plt.fill_between(gdp, total_cases, 15000, facecolor='y')
# plt.xlabel('Economic Indicator (GDP)')
# plt.ylabel('Total Cases at t=200')
# plt.legend()
# plt.show()