#include "nz_c2_10.h"

// nz_c2_10 Initialisation function
void NzC210Init(NzC210* me) {
    // Initialise Sub-objects
    PlantInit(&me->plant_data);

    ControllerInit(&me->controller_data);

    // Initialise Outputs
    me->c_dot = me->plant_data.c_dot;
    me->level = me->controller_data.level;
    me->total_cases = me->plant_data.cases;
    me->deaths = me->plant_data.d;
    me->iu = me->plant_data.u1;
    me->ic = me->plant_data.i_iso;
}

// nz_c2_10 Execution function
void NzC210Run(NzC210* me) {
    // Mappings
    me->controller_data.c_dot = me->plant_data.c_dot;
    me->controller_data.ic = me->plant_data.i_iso;
    me->plant_data.ro = me->controller_data.r0;
    me->plant_data.roc = me->controller_data.r0c;
    me->plant_data.c = me->controller_data.c;

    // Run Automata
    PlantRun(&me->plant_data);

    ControllerRun(&me->controller_data);

    // Output Mapping
    me->c_dot = me->plant_data.c_dot;
    me->ic = me->plant_data.i_iso;
    me->iu = me->plant_data.u1;
    me->level = me->controller_data.level;
    me->deaths = me->plant_data.d;
    me->total_cases = me->plant_data.cases;
}