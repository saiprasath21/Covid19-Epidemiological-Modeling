import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt
import os
import glob
plt.rcParams['axes.labelsize'] = 16
plt.rcParams['axes.titlesize'] = 16

os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time/level0_start')
files = glob.glob("*.csv")
files = sorted(files)
data = []
values = []
x1 = []
x2 = []
y = []
feature = 'nz_c2_10.total_cases'
# for f in files:
#     df = pd.read_csv(f)
#     data.append(df[feature])
#     val = "( " + str(f[0:2]) + " , " + str(f[3:5]) + " )" 
#     values.append(val)
#     x1.append(int(f[0:2]))
#     x2.append(int(f[3:5]))
#     y.append(int(df[feature][200]))

for f in files:
    df = pd.read_csv(f)
    data.append(df[feature])
    val = str(f[0:2])
    values.append(val)

ts = 0
te = 200
for i in range(len(data)):
    plt.plot(np.arange(ts, te) , data[i][ts:te], label = values[i])

plt.legend()
plt.show()

diff = []

for i in range(len(data)):
    diff.append(data[i][te])

diff = np.array(diff).astype('float32')
diff = diff - np.amin(diff)

plt.bar(np.arange(2,10), diff)
plt.xlabel('Time spent at level 4 (Level 3 = 18)')
plt.ylabel('Extra Cases')
plt.show()
# hm = np.reshape(y, (15,15))

# import seaborn as sns
# h = sns.heatmap(hm, cmap="YlGnBu", linewidths=0.5)
# plt.xticks(0.5 + np.arange(0,15), np.arange(10,40,2))
# plt.yticks(0.5 + np.arange(0,15), np.arange(10,40,2))
# plt.xlabel("Time at Level 4")
# plt.ylabel("Time at Level 3")
# plt.show()