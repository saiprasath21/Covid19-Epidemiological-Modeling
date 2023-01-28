#ifndef NZ_C1_H_
#define NZ_C1_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Plant/plant.h"
#include "Controller/controller.h"

typedef int bool;
#define false 0
#define true 1

#include "config.h"

// nz-c1 Data Struct
typedef struct {
    
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
    double level;

    // Declare Daughter Automata
    Plant plant_data;
    Controller controller_data;
} NzC1;

// nz-c1 Initialisation function
void NzC1Init(NzC1* me);

// nz-c1 Execution function
void NzC1Run(NzC1* me);

#endif // NZ_C1_H_