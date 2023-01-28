import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

tc = 400
import os
os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/systems/output')

data = pd.read_csv('out.csv')
time = data['Time']
active_cases = data['nz_c2_10.total_cases']
level = data['nz_c2_10.Level']

# os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated')
# data1 = pd.read_csv('actual.csv')
# graph = data1['Real']
# actual_time = np.arange(0,len(graph))

# data2 = pd.read_csv('seir.csv')
# graph2 = data2['nz-c2.cases']
# actual_time2 = np.arange(0,len(graph2))

# data3 = pd.read_csv('stoca.csv')
# graph3 = data3['nz-c2.clinical_cases']
# print(len(graph3))
# iter = 25
# sim_time = 601
# avg_total = np.zeros((sim_time))
# for i in range(0,iter):
#     avg_total += np.array(graph3[i*sim_time:(i+1)*sim_time])
#     #plt.plot(np.arange(0,tc),graph3[i*sim_time:(i+1)*sim_time][0:tc], alpha=0.1, c='y')

# avg_total = avg_total/iter


# actual_time3 = np.arange(0,len(avg_total))

pp = np.mean(active_cases[0:tc])/2

plt.plot(time[0:tc], active_cases[0:tc],c='b',label='Predicted')
plt.plot(time[0:tc], level[0:tc]*pp, c='g',label='Control Level')

#plt.plot(actual_time[0:tc] ,graph[0:tc] ,c='r',label='Actual')
#plt.plot(actual_time2[0:tc] ,graph2[0:tc] ,c='g',label='SEIR')
#plt.plot(actual_time3[0:tc] ,graph3[0:tc] ,c='m',label='Stochastic')
plt.legend()
plt.show()

