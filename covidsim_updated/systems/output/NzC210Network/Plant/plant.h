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
    PLANT_UNCONSTRAINED,
};

// Plant Data Struct
typedef struct {
    
    // Declare Inputs
    double ro;
    double roc;
    double c;
    
    // Declare Outputs
    double c_dot;
    double cases;
    double i_sum;
    double i_iso;
    double s;
    double e1;
    double e2;
    double e3;
    double e4;
    double p1;
    double u1;
    double i1;
    double i2;
    double i3;
    double i4;
    double i5;
    double i6;
    double i7;
    double i8;
    double i9;
    double i10;
    double d;
    
    // Declare Internal Variables
    double t;
    double bp;
    double p_sum;
    double bi;
    double biso;
    double r;
    double cfr;
    double e_sum;

    // State
    enum PlantStates state;
} Plant;

// Plant Initialisation function
void PlantInit(Plant* me);

// Plant Execution function
void PlantRun(Plant* me);

#endif // PLANT_H_