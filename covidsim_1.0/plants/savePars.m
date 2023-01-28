    function pari  = savePars(N,R0,para)
%N=5*10^6; % population size, NZ
eps=1.0; % ne/de
phi=1.0; % np/dp
gamma= 2.0; % ni/di
delta = 2.0; % nl/dl
ip = 0.5; % infectiousness in the prodromal state
dp=1.0; % duration of the prodromal state
di=5.0; % duration of the infectious state
dl = 5.0;
cl = 0.5;
bi=(R0/(ip * dp + di + cl*dl)) ; % transmission rate,per day
bp=ip*bi; % transmission rate of the prodromal cases
bl = cl * bi; % tranmission rate for late infectious state
p_sick=0.67; % symptomatic
p_dead=0.0045; % fraction of sick people who die
pari=[N;eps;phi;gamma;delta;bi;bp;bl;p_sick;p_dead;0.50;];
return
end