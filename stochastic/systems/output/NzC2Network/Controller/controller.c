#include "controller.h"

// Controller Initialisation function
void ControllerInit(Controller* me) {
    // Initialise State
    me->state = CONTROLLER_LEVEL0;

    // Initialise Outputs
    me->r0 = 0;
    me->level = 0;
}

// Controller Execution function
void ControllerRun(Controller* me) {
    // Create intermediary variables
    enum ControllerStates state_u = me->state;
    double r0_u = me->r0;
    double level_u = me->level;
    printf("Active cases = %lf", me->ic);


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case CONTROLLER_LEVEL0: // Logic for state Level0
            if(me->ic >= 40000) {
                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            break;
        case CONTROLLER_LEVEL4: // Logic for state Level4
            if(me->ic <= 40000 / 2) {
                // Next state is Level0
                state_u = CONTROLLER_LEVEL0;
            }
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->r0 = r0_u;
    me->level = level_u;


    // Intra-location logic for every state
    switch(me->state) {
        case CONTROLLER_LEVEL0: // Intra-location logic for state Level0
            r0_u = 2.5;
            level_u = 0;

            break;
        case CONTROLLER_LEVEL4: // Intra-location logic for state Level4
            r0_u = 0.316;
            level_u = 4;

            break;
    }

    // Update from intermediary variables
    me->r0 = r0_u;
    me->level = level_u;

}