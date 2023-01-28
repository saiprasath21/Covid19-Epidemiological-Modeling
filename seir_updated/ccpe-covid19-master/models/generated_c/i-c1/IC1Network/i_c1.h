#ifndef I_C1_H_
#define I_C1_H_

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

// i-c1 Data Struct
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
    double phase;

    // Declare Daughter Automata
    Plant plant_data;
    Controller controller_data;
} IC1;

// i-c1 Initialisation function
void IC1Init(IC1* me);

// i-c1 Execution function
void IC1Run(IC1* me);

#endif // I_C1_H_