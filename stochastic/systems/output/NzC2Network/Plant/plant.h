#ifndef PLANT_H_
#define PLANT_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int bool;
#define false 0
#define true 1

#include "config.h"

// Plant States
enum PlantStates {
    PLANT_MODEL,
};

// Plant Data Struct
typedef struct {
    
    // Declare Inputs
    double r0;
    double control_efficiency;
    
    // Declare Outputs
    double active_cases;
    double c_dot;
    
    // Declare Internal Variables
    double t;
    double total_cases;
    double clinical_cases;
    double new_cases;
    double dead_cases;

    // State
    enum PlantStates state;
} Plant;

// Plant Initialisation function
void PlantInit(Plant* me);

// Plant Execution function
void PlantRun(Plant* me);

#endif // PLANT_H_
