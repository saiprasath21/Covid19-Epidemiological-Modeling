#!/bin/bash  
java -jar modular-code-generation-0.5.0.jar nz_c2_10_tr.yaml 
cd output
make
./nz_c2_10
cd /home/sai/Desktop/COVID-19/covidsim_updated
python3 Plots.py



