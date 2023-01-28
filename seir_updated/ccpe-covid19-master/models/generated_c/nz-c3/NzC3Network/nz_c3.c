#include "nz_c3.h"

// nz-c3 Initialisation function
void NzC3Init(NzC3* me) {
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
    me->level = me->controller_data.level;
}

// nz-c3 Execution function
void NzC3Run(NzC3* me) {
    // Mappings
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
    me->level = me->controller_data.level;
    me->p = me->plant_data.p;
    me->rc = me->plant_data.rc;
    me->ru = me->plant_data.ru;
    me->s = me->plant_data.s;
    me->cases = me->plant_data.cases;
}