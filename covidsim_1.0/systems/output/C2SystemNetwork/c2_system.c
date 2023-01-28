#include "c2_system.h"

// c2_system Initialisation function
void C2SystemInit(C2System* me) {
    // Initialise Sub-objects
    PlantInit(&me->plant_data);

    ControllerInit(&me->controller_data);

    // Initialise Outputs
    me->cases = me->plant_data.i_sum;
    me->c_dot = me->plant_data.c_dot;
    me->level = me->controller_data.level;
    me->total = me->plant_data.cases;
    me->d = me->plant_data.d;
}

// c2_system Execution function
void C2SystemRun(C2System* me) {
    // Mappings
    me->controller_data.c_dot = me->plant_data.c_dot;
    me->controller_data.ic = me->plant_data.i_iso;
    me->plant_data.ro = me->controller_data.r0;
    me->plant_data.roc = me->controller_data.r0c;
    me->plant_data.c_gen = me->controller_data.c_gen;
    me->plant_data.c_home = me->controller_data.c_iso;
    me->plant_data.ll = me->controller_data.ll;
    me->plant_data.psi = me->controller_data.psi;

    // Run Automata
    PlantRun(&me->plant_data);

    ControllerRun(&me->controller_data);

    // Output Mapping
    me->c_dot = me->plant_data.c_dot;
    me->d = me->plant_data.d;
    me->level = me->controller_data.level;
    me->cases = me->plant_data.i_sum;
    me->total = me->plant_data.cases;
}