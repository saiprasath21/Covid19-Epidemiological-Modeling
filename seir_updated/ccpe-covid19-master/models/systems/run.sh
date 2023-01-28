#!/bin/bash  
java -jar modular-code-generation-0.5.0.jar nz-c2.yaml 
cd output
make
./nz_c2
