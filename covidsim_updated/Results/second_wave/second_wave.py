import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

ts = 0
tc = 170
import os

data = pd.read_csv('1%.csv')
time = data['Time']
f1 = data['nz_c2_10.total_cases']
level = data['nz_c2_10.Level']

data = pd.read_csv('5%.csv')
f2 = data['nz_c2_10.total_cases']

data = pd.read_csv('10%.csv')
f3 = data['nz_c2_10.total_cases']

data = pd.read_csv('actual.csv')
f5 = data['Real']

print(f1[tc], f2[tc], f3[tc], f5[tc])

plt.plot(time[ts:tc], 400*level[ts:tc])
plt.plot(time[ts:tc], f1[ts:tc],c='b',label='1%')
# plt.plot(time[ts:tc], f2[ts:tc],c='g',label='5%')
# plt.plot(time[ts:tc], f3[ts:tc],c='r',label='10%')
#plt.plot(time[0:tc], f4[0:tc],c='y',label='+2')
plt.plot(time[ts:tc], f5[ts:tc],label='Real')

plt.legend()
plt.show()

