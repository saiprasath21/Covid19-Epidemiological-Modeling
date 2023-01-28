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
    PLANT_ISOLATED_BELOW,
    PLANT_ISOLATED_ABOVE,
};

// Plant Data Struct
typedef struct {
    
    // Declare Inputs
    double ro;
    double roc;
    double c_home;
    double c_gen;
    double psi;
    double ll;
    
    // Declare Outputs
    double s;
    double e1;
    double e2;
    double e3;
    double e4;
    double p1;
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
    double r;
    double d;
    double prob;
    double c_dot;
    double cases;
    double i_sum;
    double i_iso;
    double state_level;
    
    // Declare Internal Variables
    double i_home;
    double bp;
    double p_sum;
    double bi;
    double biso;
    double cfr;
    double t;
    double e_sum;
    double p_dead;

    // State
    enum PlantStates state;
} Plant;

// Plant Initialisation function
void PlantInit(Plant* me);

// Plant Execution function
void PlantRun(Plant* me);

#endif // PLANT_H_