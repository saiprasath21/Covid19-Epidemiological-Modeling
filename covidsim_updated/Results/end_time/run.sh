#!/bin/bash  
cd /home/sai/Desktop/COVID-19/covidsim_updated/systems
java -jar modular-code-generation-0.5.0.jar nz_c2_10_tr.yaml 
cd output
make
./nz_c2_10
mv out.csv /home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time/level0_start



