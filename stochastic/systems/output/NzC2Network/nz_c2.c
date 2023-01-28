#include "nz_c2.h"

// nz-c2 Initialisation function
void NzC2Init(NzC2* me) {
    // Initialise Sub-objects
    PlantInit(&me->plant_data);

    ControllerInit(&me->controller_data);
    printf("Initialize R0 value: %lf \n", me->controller_data.r0);
    // Initialise Outputs
    me->total_cases = me->plant_data.total_cases;
    me->clinical_cases = me->plant_data.clinical_cases;
    me->c_dot = me->plant_data.c_dot;
    me->active_cases = me->plant_data.active_cases;
    me->level = me->controller_data.level;
    me->dead_cases = 0;
}

// nz-c2 Execution function
void NzC2Run(NzC2* me) {
    // Mappings
    me->controller_data.ic = me->plant_data.active_cases;
    //me->controller_data.ic = me->plant_data.active_cases;
    printf("Controller R0 value: %lf \n", me->controller_data.r0);
    me->plant_data.r0 = me->controller_data.r0;
    printf("Plant R0 value: %lf \n", me->plant_data.r0);
    me->plant_data.control_efficiency = 0.0;
    // Run Automata
    PlantRun(&me->plant_data);

    ControllerRun(&me->controller_data);

    // Output Mapping
    printf("Current Level: %lf \n", me->controller_data.level);
    me->total_cases = me->plant_data.total_cases;
    me->clinical_cases = me->plant_data.clinical_cases;
    me->c_dot = me->plant_data.c_dot;
    me->level = me->controller_data.level;
    me->active_cases = me->plant_data.active_cases;
    me->dead_cases = me->plant_data.dead_cases;
}
