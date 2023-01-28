#include "covidsim_system.h"

// covidsim_system Initialisation function
void CovidsimSystemInit(CovidsimSystem* me) {
    // Initialise Sub-objects
    PlantInit(&me->plant_data);

    // Initialise Outputs
    me->s = me->plant_data.s;
    me->e1 = me->plant_data.e1;
    me->e2 = me->plant_data.e2;
    me->p1 = me->plant_data.p1;
    me->p2 = me->plant_data.p2;
    me->i1 = me->plant_data.i1;
    me->i2 = me->plant_data.i2;
    me->l1 = me->plant_data.l1;
    me->l2 = me->plant_data.l2;
    me->r = me->plant_data.r;
    me->d = me->plant_data.d;
    me->prob = me->plant_data.prob;
    me->cases = me->plant_data.cases;
    me->c_dot = me->plant_data.c_dot;
}

// covidsim_system Execution function
void CovidsimSystemRun(CovidsimSystem* me) {

    // Run Automata
    PlantRun(&me->plant_data);

    // Output Mapping
    me->c_dot = me->plant_data.c_dot;
    me->d = me->plant_data.d;
    me->e1 = me->plant_data.e1;
    me->e2 = me->plant_data.e2;
    me->i1 = me->plant_data.i1;
    me->i2 = me->plant_data.i2;
    me->l1 = me->plant_data.l1;
    me->l2 = me->plant_data.l2;
    me->p1 = me->plant_data.p1;
    me->p2 = me->plant_data.p2;
    me->r = me->plant_data.r;
    me->s = me->plant_data.s;
    me->cases = me->plant_data.cases;
    me->prob = me->plant_data.prob;
}