function [dxdt] = odeSIRrefine(t,x,par)
N=par(1); 
eps=par(2); 
phi=par(3);
gamma=par(4); 
delta = par(5);
bi=par(6); 
bp=par(7);
bl = par(8); 
p_sick=par(9);
p_dead=par(10);
pe = par(11);


S=x(1); % susceptible
E1=x(2); % exposed
E2=x(3); % pre-symptomatic
E3=x(4);% untested infection
E4=x(5);% tested infection
P1=x(6);% untested recovered
I1=x(7);
I2=x(8);
I3=x(9);
I4=x(10);
I5=x(11);
I6=x(12);
I7=x(13);
I8=x(14);
I9=x(15);
I10=x(16);
L1=x(17);
L2=x(18);
L3=x(19);
L4=x(20);
L5=x(21);
L6=x(22);
L7=x(23);
L8=x(24);
L9=x(25);
L10=x(26);
R=x(27);
D=x(28);
cases=x(29);


%{
S=x(1); % susceptible
E1=x(2); % exposed
P1=x(3);% untested recovered
I1=x(4);% tested recovered
R=x(5);
D=x(6);
cases=x(7);


Isum = I1;

dSdt=-S*(bp * P1 + bi * (Isum -  Isum * p_sick * pe));
dE1dt=S*(bp * P1 + bi * (Isum -  Isum * p_sick * pe)) - eps * E1;
dP1dt= eps * E1 - phi * P1;
dI1dt= phi * P1 - gamma * I1;
dRdt = gamma * I1 * (1 - p_sick * p_dead);
dDdt = gamma * I1 * p_sick * p_dead;
dCdt = phi * P1 * p_sick;
dxdt = [dSdt;dE1dt;dP1dt;dI1dt;dRdt; dDdt; dCdt;];


%}
Isum = I1 + I2 + I3 + I4 + I5 + I6 + I7 + I8 + I9 + I10;
Lsum = L1 + L2 + L3 + L4 + L5 + L6 + L7 + L8 + L9 + L10;
dSdt=-S*(bp * P1 + bi * (Isum -  Isum * pe * p_sick) + bl * (Lsum - Lsum * p_sick * pe));
dE1dt=S*(bp * P1 + bi * (Isum -  Isum * pe * p_sick) + bl * (Lsum - Lsum * p_sick * pe)) - eps * E1;
dE2dt = eps * E1 - eps * E2;
dE3dt = eps * E2 - eps * E3;
dE4dt = eps * E3 - eps * E4;
dP1dt= eps * E4 - phi * P1;
dI1dt= phi * P1 - gamma * I1;
dI2dt= gamma * I1 - gamma * I2;
dI3dt= gamma * I2 - gamma * I3;
dI4dt= gamma * I3 - gamma * I4;
dI5dt= gamma * I4 - gamma * I5;
dI6dt= gamma * I5 - gamma * I6;
dI7dt= gamma * I6 - gamma * I7;
dI8dt= gamma * I7 - gamma * I8;
dI9dt= gamma * I8 - gamma * I9;
dI10dt= gamma * I9 - gamma * I10;
dL1dt = gamma * I10 - delta * L1;
dL2dt = delta * L1 - delta * L2;
dL3dt = delta * L2 - delta * L3;
dL4dt = delta * L3 - delta * L4;
dL5dt = delta * L4 - delta * L5;
dL6dt = delta * L5 - delta * L6;
dL7dt = delta * L6 - delta * L7;
dL8dt = delta * L7 - delta * L8;
dL9dt = delta * L8 - delta * L9;
dL10dt = delta * L9 - delta * L10;
dRdt = gamma * L10 * (1 - p_sick * p_dead);
dDdt = gamma * L10 * p_sick * p_dead;
dCdt = phi * P1 * p_sick;
dxdt = [dSdt;dE1dt;dE2dt;dE3dt;dE4dt;dP1dt;dI1dt;dI2dt;dI3dt;dI4dt;dI5dt;dI6dt;dI7dt;dI8dt;dI9dt;dI10dt;dL1dt;dL2dt;dL3dt;dL4dt;dL5dt;dL6dt;dL7dt;dL8dt;dL9dt;dL10dt;dRdt; dDdt; dCdt;];


return
end