import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error

ss=0.001
note = 1
val = int(note/ss)
tt=60

train=tt

#confirmed = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,3,3,4,5,5,5,5,5,5,5,6,8,8,12,20,28,39,52,102,102,155,205,283,368,451,514,589,647,708,797,868,950,1039,1106,1160,1210,1239,1283,1312,1330,1349,1366,1386,1401,1409,1422,1431,1440,1445,1451,1456,1461,1470,1469,1472,1474,1476,1479,1485,1487,1487,1486,1488,1489,1490,1492,1494,1497,1497,1497,1497,1498,1498,1499,1499,1499,1503,1503,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1504,1506,1506,1507,1507,1509,1511,1513,1515,1516,1519,1520,1522,1526,1528,1528,1528,1530,1530,1530,1533,1534,1536,1537,1540,1542,1543,1544,1544,1545,1547,1548,1549,1550,1553,1554,1555,1555,1555,1556,1556,1556,1556,1557,1559,1560,1560,1562,1565,1567,1567,1569,1569,1569,1569,1569,1569,1570,1570,1589,1602,1609,1622,1631,1643,1649,1654,1665,1671,1674,1683,1690,1695,1702,1714,1727,1729,1738,1752,1757,1759,1764,1767,1772,1776,1782,1788,1792,1793]
death = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,4,4,5,9,9,9,11,11,12,12,13,14,17,18,18,19,19,19,19,19,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,24,24,24,24,24,24,24]
recovered = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,22,27,37,50,56,63,74,83,92,103,127,156,176,241,282,317,373,422,471,546,628,728,770,816,867,912,974,1006,1036,1095,1118,1142,1180,1214,1229,1241,1252,1263,1266,1276,1302,1316,1332,1347,1368,1371,1386,1398,1402,1411,1421,1428,1433,1433,1433,1447,1452,1455,1455,1456,1456,1461,1462,1474,1481,1481,1481,1481,1481,1481,1481,1481,1481,1481,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1482,1483,1483,1484,1484,1484,1484,1484,1484,1484,1490,1490,1490,1490,1490,1492,1492,1494,1497,1497,1497,1497,1498,1498,1499,1506,1506,1506,1506,1506,1506,1511,1513,1513,1513,1513,1514,1514,1514,1518,1518,1518,1518,1523,1523,1524,1524,1524,1524,1526,1526,1526,1531,1531,1531,1531,1531,1531,1531,1531,1538,1538,1538,1538,1539,1539,1554,1561,1568,1570,1585,1598,1606,1622,1630,1631,1632,1634,1635,1639,1648,1655]

confirmed = [64, 88, 132, 173, 231, 315, 394, 469, 541, 615, 667, 744, 817, 899, 974, 1051, 1121, 1174, 1211, 1239, 1283, 1310, 1335, 1355, 1366, 1382, 1393, 1410, 1422, 1432, 1442, 1445, 1451, 1456, 1461, 1467, 1473, 1476, 1479, 1480, 1482, 1485, 1490, 1490, 1491, 1491, 1493, 1495, 1496, 1497, 1498, 1501, 1501, 1501, 1501, 1502, 1503, 1503, 1503, 1503, 1503, 1503, 1503, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1504, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1506, 1510, 1523, 1535, 1540, 1553, 1565, 1574, 1584, 1589, 1594, 1601, 1603, 1610, 1617, 1620, 1625, 1631, 1640, 1644, 1648, 1650, 1654, 1658, 1660, 1662, 1667, 1669, 1673]

day_zero=0
for i in range(0, len(confirmed)):
    if(confirmed[i]==64):
        day_zero=i
        break
print("Day 0: "+ str(day_zero))

confirmed = confirmed[day_zero:]
# death = death[day_zero:]
# recovered = recovered[day_zero:]
actual_time = np.arange(0,len(confirmed))

# active = np.array(confirmed) - np.array(recovered) - np.array(death)
train_confirmed = confirmed[0:train]
# train_active= active[0:train]
# train_recovered = recovered[0:train]
# train_death = death[0:train]

def cost_function(I):
	global ss
	population = 4822233
	initial_case_distribution_factor= 4.8
	initial_cases = 64
	de=4
	ne=4
	eps=1
	dp=1
	np=1
	phi=1
	ip=0.15
	di=10
	ni=10
	gamma=1
	p_sick=1
	CFR0=0.01
	CFR1=0.02
	n_ICU=300
	p_ICU=0.0125

	E1 = I[0]
	E2 = I[1]
	E3 = I[2]
	E4 = I[3]
	P1 = I[5]
	U1 = I[7]
	I1 = I[6]
	I2 = I[4]
	I3 = I[4]
	I4 = I[4]
	I5 = I[4]
	I6 = I[4]
	I7 = I[4]
	I8 = I[4]
	I9 = I[4]
	I10 = I[4]
	S = population - I[0] - I[1] - I[2] - I[3] - 9 * I[4] - I[5] - I[6] - I[7]
	CFR = CFR0
	R=0
	D=0
	c=0.67

	cases = initial_cases
	res1 = []
	res2 = []
	res3 = []
	for i in range(0,int(tt/ss)):

		j = i*ss

		if(j<5):
			R0=2.5
			R0c=0.02
			c = 0.1
		elif(j<38):
			R0=0.316
			R0c=0.02
			c = 0.01
		elif(j<38+16):
			R0 = 0.827
			R0c= 0.02
			c = 0.15
		elif(j<38+16+26):
			R0 = 1.384
			R0c = 0.02
			c= 0.20
		elif(j<38+16+26+64):
			R0 = 2.5
			R0c = 0.02
			c= 0.30
		else:
			R0 = 0.827
			R0c = 0.02
			c=I[9]


		bi = R0 / (ip * dp + di)
		biso = R0c / (ip * dp + di)
		bp = ip * bi

		E1t = E1
		E2t = E2
		E3t = E3
		E4t = E4
		P1t = P1
		U1t = U1
		I1t = I1
		I2t = I2
		I3t = I3
		I4t = I4
		I5t = I5
		I6t = I6
		I7t = I7
		I8t = I8
		I9t = I9
		I10t = I10
		St = S
		I_sum = I1 + I2 + I3 + I4 + I5 + I6 + I7 + I8 + I9 + I10
		P_sum = P1

		# if(I_sum * 0.1 < 1):
		# 	I_sum = 0.0


		if(I_sum * p_ICU > n_ICU): 
			CFR = CFR1 - (CFR1 - CFR0) * n_ICU / (I_sum * p_ICU)

		S+= ss*(-1 * St * (bp * P_sum + bi * U1t + biso * I_sum) / population)
		E1+= ss*(St * (bp * P_sum + bi * U1t + biso *  I_sum) / population - eps * E1t)
		E2+= ss*(eps * E1t - eps * E2t)
		E3+= ss*(eps * E2t - eps * E3t)
		E4+= ss*(eps * E3t - eps * E4t)
		P1+= ss*(eps * E4t - phi * P1t)
		U1+= ss*(phi * P1t - c * U1t)
		I1+= ss*(c * U1t - gamma * I1t) 
		I2+= ss*(gamma * I1t - gamma * I2t)
		I3+= ss*(gamma * I2t - gamma * I3t)
		I4+= ss*(gamma * I3t - gamma * I4t)
		I5+= ss*(gamma * I4t - gamma * I5t)
		I6+= ss*(gamma * I5t - gamma * I6t)
		I7+= ss*(gamma * I6t - gamma * I7t)
		I8+= ss*(gamma * I7t - gamma * I8t)
		I9+= ss*(gamma * I8t - gamma * I9t)
		I10+= ss*(gamma * I9t - gamma * I10t)    
		R+= ss*(gamma * (1 - CFR) * I10t)
		D+= ss*(gamma * CFR * I10t) 
		cases += ss*(c * U1t)

		if(i%val==0):
			res1.append(cases)
			res2.append(D)
			res3.append(I_sum)


	#return mean_squared_error(res1,train_confirmed) #+ mean_squared_error(res2, train_death) + mean_squared_error(res3, train_active) 
	return res1

# I = [2.38238494e-09, 4.41479463e-16, 2.17210626e-15, 5.42691492e-10,
#        7.11111111e+00, 4.64887386e-09, 7.48187599e-10, 1.79200069e+02]
I = [5.39060033e-13, 5.35896606e-13, 5.47770758e-13, 4.91268046e-13,
       7.11111111e+00, 1.74547824e-12, 4.40563815e-15, 4.29839779e+02]
# [2.50679655e+03, 3.66644196e-17, 1.94290749e+03, 1.01566237e-15,
#      6.46766169e+00]
flag=1

if(flag==1):
	total_cases = cost_function(I)
	print(total_cases)
	print("Length = "+str(len(total_cases)), str(total_cases[-1]))
	time = np.arange(0,note*len(total_cases),note)
	plt.plot(time, total_cases)
	plt.plot(actual_time,confirmed)
	plt.show()

else:
	from scipy.optimize import minimize


	def constrain1(I):
		return [I[6] + 9*I[4] - 64.0]

	con1 = {'type':'eq','fun':constrain1}

	b=(0,10000)
	bnds=(b,b,b,b,b,b,b,b)
	res = minimize(cost_function, I, method='SLSQP',bounds=bnds,constraints=con1)
	print(res)