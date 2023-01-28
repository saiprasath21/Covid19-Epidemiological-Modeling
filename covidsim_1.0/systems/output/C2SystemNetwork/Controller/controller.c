#include "controller.h"

// Controller Initialisation function
void ControllerInit(Controller* me) {
    // Initialise State
    me->state = CONTROLLER_PRE_LEVEL0;

    // Initialise Outputs
    me->r0 = 0;
    me->r0c = 0;
    me->level = 0;
    me->c_gen = 0;
    me->c_iso = 0;
    me->psi = 0;
    me->ll = 0;

    // Initialise Internal Variables
    me->t = 0;
}

// Controller Execution function
void ControllerRun(Controller* me) {
    // Create intermediary variables
    enum ControllerStates state_u = me->state;
    double r0_u = me->r0;
    double r0c_u = me->r0c;
    double level_u = me->level;
    double c_gen_u = me->c_gen;
    double c_iso_u = me->c_iso;
    double psi_u = me->psi;
    double ll_u = me->ll;

    double t_u = me->t;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case CONTROLLER_PRE_LEVEL0: // Logic for state Pre_Level0
            if(me->t >= 6) {
                t_u = 0;

                // Next state is Pre_Level4
                state_u = CONTROLLER_PRE_LEVEL4;
            }
            break;
        case CONTROLLER_PRE_LEVEL4: // Logic for state Pre_Level4
            if(me->t >= 33) {
                t_u = 0;

                // Next state is Level3
                state_u = CONTROLLER_LEVEL3;
            }
            break;
        case CONTROLLER_LEVEL4: // Logic for state Level4
            if(me->ic < 40000 && me->t >= 14) {
                t_u = 0;

                // Next state is Level3
                state_u = CONTROLLER_LEVEL3;
            }
            break;
        case CONTROLLER_LEVEL3: // Logic for state Level3
            if(me->ic >= 40000) {
                t_u = 0;

                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            else if(me->c_dot <= 10 && me->t >= 14) {
                t_u = 0;

                // Next state is Level2
                state_u = CONTROLLER_LEVEL2;
            }
            break;
        case CONTROLLER_LEVEL2: // Logic for state Level2
            if(me->ic >= 40000) {
                t_u = 0;

                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            else if(me->ic >= 500) {
                t_u = 0;

                // Next state is Level3
                state_u = CONTROLLER_LEVEL3;
            }
            else if(me->c_dot <= 5 && me->t >= 14) {
                t_u = 0;

                // Next state is Level1
                state_u = CONTROLLER_LEVEL1;
            }
            break;
        case CONTROLLER_LEVEL1: // Logic for state Level1
            if(me->ic >= 40000) {
                t_u = 0;

                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            else if(me->ic >= 250) {
                t_u = 0;

                // Next state is Level2
                state_u = CONTROLLER_LEVEL2;
            }
            else if(me->c_dot <= 0.01 && me->t >= 14) {
                t_u = 0;

                // Next state is Level0
                state_u = CONTROLLER_LEVEL0;
            }
            break;
        case CONTROLLER_LEVEL0: // Logic for state Level0
            if(me->ic >= 50) {
                t_u = 0;

                // Next state is Level1
                state_u = CONTROLLER_LEVEL1;
            }
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->r0 = r0_u;
    me->r0c = r0c_u;
    me->level = level_u;
    me->c_gen = c_gen_u;
    me->c_iso = c_iso_u;
    me->psi = psi_u;
    me->ll = ll_u;

    me->t = t_u;


    // Intra-location logic for every state
    switch(me->state) {
        case CONTROLLER_PRE_LEVEL0: // Intra-location logic for state Pre_Level0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 2.5;
            level_u = 0;
            ll_u = 0;

            if(t_u < 6 && me->t > 6) {
                // Need to saturate t to 6
                t_u = 6;
            }

            break;
        case CONTROLLER_PRE_LEVEL4: // Intra-location logic for state Pre_Level4
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.316;
            r0c_u = 0.316;
            level_u = 4;
            ll_u = 0;

            if(t_u < 33 && me->t > 33) {
                // Need to saturate t to 33
                t_u = 33;
            }

            break;
        case CONTROLLER_LEVEL4: // Intra-location logic for state Level4
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.316;
            r0c_u = 0.316;
            level_u = 4;
            ll_u = 0;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL3: // Intra-location logic for state Level3
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.827;
            r0c_u = 0.316;
            level_u = 3;
            ll_u = 0;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL2: // Intra-location logic for state Level2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 1.384;
            r0c_u = 0.316;
            level_u = 2;
            ll_u = 0;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL1: // Intra-location logic for state Level1
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 1.57;
            r0c_u = 0.316;
            level_u = 1;
            ll_u = 0;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL0: // Intra-location logic for state Level0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 2.5;
            level_u = 0;
            ll_u = 3;

            break;
    }

    // Update from intermediary variables
    me->r0 = r0_u;
    me->r0c = r0c_u;
    me->level = level_u;
    me->c_gen = c_gen_u;
    me->c_iso = c_iso_u;
    me->psi = psi_u;
    me->ll = ll_u;

    me->t = t_u;

}