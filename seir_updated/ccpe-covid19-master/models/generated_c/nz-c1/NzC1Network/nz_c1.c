#include "nz_c1.h"

// nz-c1 Initialisation function
void NzC1Init(NzC1* me) {
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

// nz-c1 Execution function
void NzC1Run(NzC1* me) {
    // Mappings
    me->plant_data.r0 = me->controller_data.r0;
    me->plant_data.r0c = me->controller_data.r0c;
    me->plant_data.c = me->controller_data.c;

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