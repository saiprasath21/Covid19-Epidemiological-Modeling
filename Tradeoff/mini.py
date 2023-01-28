import sys
import numpy as np
import matplotlib.pyplot as plt
from pyswarm import pso
from scipy.optimize import minimize

def cost_function(I):

    a = I[0]
    b = I[1]
    c = I[2]
    d = I[3]
    f = 140-a-b-c-d-6

    population = 4822233
    initial_case_distribution_factor= 4.8
    initial_cases = 39
    eps = 0.15
    alpha = 0.25
    gamma = 0.1
    delta = 1
    cc=0.1
    CFR = 0.01
    cases = 0.0

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
    res = np.zeros(140)
    for i in range(1,140):

      if((Iu + Ic) * 0.0125 > 300):
          CFR = 0.02 - (0.01)*300/((Iu + Ic) * 0.0125)

      if(i<6+a):
          R0=2.5
          R0c = 2.5
          cc=0.1
      elif(i>a+6 and i<6+a+b):
          R0=0.316
          R0c=0.02
          cc=0.3
      elif(i>6+a+b and i<6+a+b+c):
          R0=0.827
          R0c = 0.02
          cc=0.2
      elif(i>6+a+b+c and i<6+a+b+c+d):
          R0=1.384
          R0c = 0.02
          cc=0.15
      elif(i>6+a+b+c+d):
          R0= 2.5
          R0c = 0.02
          cc=0.01

      #print(i,R0, CFR, S, E, P, Iu, Ic, Ru, Rc, D)
      beta= R0 / (eps / delta + 1 / gamma)
      betac= R0c / (eps / delta + 1 / gamma)
      #print(i, R0, D)
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
      #print(Iu1, Ic1)
      D= D1 + gamma * CFR * (Iu1 + Ic1)

      cases = cases + cc * Iu1

      if(Ic<1):
          Ic=0
      if(Iu<1):
          Iu=0
      res[i]= cases

    return cases


global qq

def con1(I):
    a = I[0]
    b = I[1]
    c = I[2]
    d = I[3]
    e = 140 - 6 - a - b - c - d
    loss = (b * 37 + c * 19 + d * 8.8 + e * 3.8) / 140
    return [140-6-a-b-c-d,qq-loss]


k=100
xx = np.zeros(k)
yy = np.zeros(k)
total=0
lb = [0,0,0,0]
ub=[140,140,140,140]

for i in range(1,k+1):
    qq = i*0.5
    #sol = minimize(cost_function, x0,method='SLSQP',constraints=cc)
    print(qq)
    #print(sol)
    #xopt = sol.x
    xopt, fopt = pso(cost_function, lb, ub, ieqcons=[], f_ieqcons=con1, args=(), kwargs={},
                     swarmsize=100, omega=0.5, phip=0.5, phig=0.5, maxiter=1000, minstep=1e-8,
                     minfunc=1e-8, debug=False)

    a = xopt[0]
    b = xopt[1]
    c = xopt[2]
    d = xopt[3]
    e = 140-6-a-b-c-d
    #print(a,b,c,d)
    #if(sol.status==0):
    total = total + 1
    xx[total-1]=(b*37 + c*19 + d*8.8 + e*3.8)/600
    yy[total-1]=fopt
    print(xx[total-1], yy[total-1])
    #else:
        #break

