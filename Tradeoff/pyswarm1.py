import sys
import numpy as np
import matplotlib.pyplot as plt

# Import PySwarms
import pyswarms as ps
from pyswarm import pso

def cost_function(I):

    a = I[0]
    b = I[1]
    c = I[2]
    d = I[3]
    e = I[4]
    f = 600-a-b-c-d-e-6
    '''
    #Fixed parameters
    U = 10
    R = 100
    I_s = 9.4e-12
    v_t = 25.85e-3
    #c = abs(U - v_t * np.log(abs(I[:, 0] / I_s)) - R * I[:, 0])
    '''
    population = 4822233
    initial_case_distribution_factor= 4.8
    initial_cases = 39
    eps = 0.15
    alpha = 0.25
    gamma = 0.1
    delta = 1
    cc=0.1
    CFR = 0.01

    S= population - (6 + 6 * initial_case_distribution_factor) * initial_cases
    E= 4 * (1 + initial_case_distribution_factor) * initial_cases
    P= (1 + initial_case_distribution_factor) * initial_cases
    Iu= initial_case_distribution_factor * initial_cases
    Ic= initial_cases
    Ru = 0
    Rc = 0
    D = 0
    R0 = 2.5
    R0c= 2.5
    beta = R0 / (eps / delta + 1 / gamma)
    betac = R0c / (eps / delta + 1 / gamma)
    res = np.zeros(600)
    for i in range(1,600):
      if(i<6):
          R0=2.5
          R0c=2.5
      elif(i>a+6 and i<6+a+b):
          R0=0.316
          R0c=0.316
      elif(i>6+a+b and i<6+a+b+c):
          R0=0.827
          R0c = 0.316
      elif(i>6+a+b+c and i<6+a+b+c+d):
          R0=1.384
          R0c = 0.316
      elif(i>6+a+b+c+d and i<6+a+b+c+d+e):
          R0=1.57
          R0c = 0.316
      elif(i>6+a+b+c+d+e):
          R0 = 2.5
          R0c = 2.5
      elif(i<6+a):
          R0=2.5
          R0c = 2.5
      #print(S, E, P, Iu, Ic, Ru, Rc, D)
      beta= R0 / (eps / delta + 1 / gamma)
      betac= R0c / (eps / delta + 1 / gamma)
      #print(i, R0, R0c)
      S1 = S
      E1 = E
      P1 = P
      Iu1 = Iu
      Ic1 = Ic
      Ru1 = Ru
      Rc1 = Rc
      D1 = D
      #print((beta * S1 * (eps * P1 + Iu1) + betac * S1 * Ic1)/population)
      S= S1 - (beta * S1 * (eps * P1 + Iu1) + betac * S1 * Ic1) / population
      E= E1 + (beta * S1 * (eps * P1 + Iu1) + betac * S1 * Ic1) / population - alpha * E1
      P= P1 + alpha * E1 - delta * P1
      Iu= Iu1 + delta * P1 - (gamma + cc) * Iu1
      Ic= Ic1 + cc * Iu1 - gamma * Ic1
      Ru= Ru1 + gamma * (1 - CFR) * Iu1
      Rc= Rc1 + gamma * (1 - CFR) * Ic1
      D= D1 + gamma * CFR * (Iu1 + Ic1)

      res[i]=D

    return D
    #return (b*0.37+c*0.20+d*0.10+(610-a-b-c-d-6)*0.05)/600 * 210 + D*4.24*100000
    #return D*50 + a/2.5 + 50 * b/0.316 + 30 * c/0.827 + d/1.384 + (100-6-a-b-c-d)/1.57
    #return D + b + c + d

def con(I):
    a = I[0]
    b = I[1]
    c = I[2]
    d = I[3]
    e = I[4]
    loss = (b*37 + c*19 + d*8.8 + e*3.8)/600
    return [600-6-a-b-c-d-e, loss, 3-loss]

'''
options = {'c1': 0.5, 'c2': 0.3, 'w':0.3}
max_bound = 100 * np.ones(4)
min_bound = np.zeros(4)
bounds = (min_bound, max_bound)
print(bounds)
# Call instance of PSO
optimizer = ps.single.GlobalBestPSO(n_particles=100, dimensions=1, options=options, bounds=bounds)

# Perform optimization
cost, pos = optimizer.optimize(cost_function, iters=100)

print(pos[0])
'''
max_bound = 600 * np.ones(5)
min_bound = np.zeros(5)
xopt, fopt = pso(cost_function, min_bound, max_bound,f_ieqcons=con,maxiter=10000)
b = xopt[1]
c = xopt[2]
d = xopt[3]
e = xopt[4]
print(xopt,(b*37 + c*19 + d*8.8 + e*3.8)/600, fopt)

'''
xopt = [ 0.99999992 ,21.00000011  ,0.          ,0.        ]
rr = cost_function(xopt)
plt.plot(np.arange(100), rr)
plt.show()


ll = np.zeros((1,4))
ll[0][0]=6
ll[0][1]=39
ll[0][2]=39+14
ll[0][3]=39+14+14
res = cost_function(ll)
print(res)

plt.plot(np.arange(600), res)
plt.show()
'''

