import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

tc = 120
import os

data = pd.read_csv('level2_for_5_days_before_level4.csv')
time = data['Time']
f1 = data['nz_c2_10.total_cases']
level = data['nz_c2_10.Level']

data = pd.read_csv('level3_for_5_days_before_level4.csv')
f2 = data['nz_c2_10.total_cases']

data = pd.read_csv('actual.csv')
f5 = data['Real']

print(f1[tc], f2[tc], f5[tc])

plt.plot(time[0:tc], 400*level[0:tc])
plt.plot(time[0:tc], f1[0:tc],c='b',label='level 2')
plt.plot(time[0:tc], f2[0:tc],c='g',label='level 3')
plt.plot(time[0:tc], f5[0:tc],label='Real')

plt.legend()
plt.show()

