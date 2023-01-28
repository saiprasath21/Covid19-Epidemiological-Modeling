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
    PLANT_UNVACCINATED,
    PLANT_PARTIALLY_VACCINATED,
    PLANT_FULLY_VACCINATED,
};

// Plant Data Struct
typedef struct {
    
    // Declare Inputs
    double r0;
    double r0c;
    double c;
    
    // Declare Outputs
    double s;
    double e;
    double p;
    double iu;
    double ic;
    double ru;
    double rc;
    double d;
    double cases;
    double c_dot;
    
    // Declare Internal Variables
    double t;
    double beta;
    double betac;
    double cfr;

    // State
    enum PlantStates state;
} Plant;

// Plant Initialisation function
void PlantInit(Plant* me);

// Plant Execution function
void PlantRun(Plant* me);

#endif // PLANT_H_