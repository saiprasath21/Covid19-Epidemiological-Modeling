#include "i_c1.h"

// i-c1 Initialisation function
void IC1Init(IC1* me) {
    // Initialise Sub-objects
    PlantInit(&me->plant_data);

    ControllerInit(&me->controller_data);

    // Initialise Outputs
    me->s = me->plant_data.s;
    me->e = me->plant_data.e;
    me->p = me->plant_data.p;
    me->iu = me->plant_data.iu;
    me->ic = me->plant_data.ic;
    me->ru = me->plant_data.ru;
    me->rc = me->plant_data.rc;
    me->d = me->plant_data.d;
    me->cases = me->plant_data.cases;
    me->phase = me->controller_data.phase;
}

// i-c1 Execution function
void IC1Run(IC1* me) {
    // Mappings
    me->controller_data.c_dot = me->plant_data.c_dot;
    me->controller_data.ic = me->plant_data.ic;
    me->plant_data.r0 = me->controller_data.r0;

    // Run Automata
    PlantRun(&me->plant_data);

    ControllerRun(&me->controller_data);

    // Output Mapping
    me->d = me->plant_data.d;
    me->e = me->plant_data.e;
    me->ic = me->plant_data.ic;
    me->iu = me->plant_data.iu;
    me->p = me->plant_data.p;
    me->phase = me->controller_data.phase;
    me->rc = me->plant_data.rc;
    me->ru = me->plant_data.ru;
    me->s = me->plant_data.s;
    me->cases = me->plant_data.cases;
}