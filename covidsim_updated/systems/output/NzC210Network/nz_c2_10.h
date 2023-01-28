#ifndef NZ_C2_10_H_
#define NZ_C2_10_H_

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

// nz_c2_10 Data Struct
typedef struct {
    
    // Declare Outputs
    double c_dot;
    double level;
    double total_cases;
    double deaths;
    double iu;
    double ic;

    // Declare Daughter Automata
    Plant plant_data;
    Controller controller_data;
} NzC210;

// nz_c2_10 Initialisation function
void NzC210Init(NzC210* me);

// nz_c2_10 Execution function
void NzC210Run(NzC210* me);

#endif // NZ_C2_10_H_