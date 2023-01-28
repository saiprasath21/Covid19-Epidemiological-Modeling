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
    PLANT_INITIAL,
};

// Plant Data Struct
typedef struct {
    
    // Declare Outputs
    double s;
    double e1;
    double e2;
    double p1;
    double p2;
    double i1;
    double i2;
    double l1;
    double l2;
    double r;
    double d;
    double prob;
    double c_dot;
    double cases;
    
    // Declare Internal Variables
    double t;
    double b;
    double p_sum;
    double i_sum;
    double l_sum;
    double l2_sum;
    double p2_sum;
    double e_sum;
    double g;

    // State
    enum PlantStates state;
} Plant;

// Plant Initialisation function
void PlantInit(Plant* me);

// Plant Execution function
void PlantRun(Plant* me);

#endif // PLANT_H_