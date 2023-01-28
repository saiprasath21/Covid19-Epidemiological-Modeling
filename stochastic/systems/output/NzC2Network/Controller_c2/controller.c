#include "controller.h"

// Controller Initialisation function
void ControllerInit(Controller* me) {
    // Initialise State
    me->state = CONTROLLER_PRE_LEVEL0;

    // Initialise Outputs
    me->r0 = 2.5;
    me->r0c = 2.5;
    me->c = 0;
    me->level = 0;

    // Initialise Internal Variables
    me->t = 0;
}

// Controller Execution function
void ControllerRun(Controller* me) {
    // Create intermediary variables
    enum ControllerStates state_u = me->state;
    double r0_u = me->r0;
    double r0c_u = me->r0c;
    double c_u = me->c;
    double level_u = me->level;

    double t_u = me->t;


    printf("Current Time = %f \n", t_u);
    printf("R0 = %f \n", r0_u);
    
    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case CONTROLLER_PRE_LEVEL0: // Logic for state Pre_Level0
            if(me->t >= 4) {
                t_u = 0;

                // Next state is Pre_Level4
                state_u = CONTROLLER_PRE_LEVEL4;
            }
            break;
        case CONTROLLER_PRE_LEVEL4: // Logic for state Pre_Level4
            if(me->t >= 33) {
                t_u = 0;

                // Next state is Pre_Level3
                state_u = CONTROLLER_PRE_LEVEL3;
            }
            break;
        case CONTROLLER_PRE_LEVEL3: // Logic for state Pre_Level3
            if(me->t >= 16) {
                t_u = 0;

                // Next state is Pre_Level2
                state_u = CONTROLLER_PRE_LEVEL2;
            }
            break;
        case CONTROLLER_PRE_LEVEL2: // Logic for state Pre_Level2
            if(me->t >= 26) {
                t_u = 0;

                // Next state is Pre_Level1
                state_u = CONTROLLER_PRE_LEVEL1;
            }
            break;
        case CONTROLLER_PRE_LEVEL1: // Logic for state Pre_Level1
            if(me->t >= 64) {
                t_u = 0;

                // Next state is Pre_Level3_2
                state_u = CONTROLLER_PRE_LEVEL3_2;
            }
            break;
        case CONTROLLER_PRE_LEVEL3_2: // Logic for state Pre_Level3_2
            if(me->t >= 19) {
                t_u = 0;

                // Next state is Level2
                state_u = CONTROLLER_LEVEL2;
            }
            break;
        case CONTROLLER_LEVEL4: // Logic for state Level4
            if(me->ic < 100 && me->t >= 14) {
                t_u = 0;

                // Next state is Level3
                state_u = CONTROLLER_LEVEL3;
            }
            break;
        case CONTROLLER_LEVEL3: // Logic for state Level3
            if(me->ic >= 100) {
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
            if(me->ic >= 100) {
                t_u = 0;

                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            else if(me->ic >= 50) {
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
            if(me->ic >= 100) {
                t_u = 0;

                // Next state is Level4
                state_u = CONTROLLER_LEVEL4;
            }
            else if(me->ic >= 5) {
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
            if(me->ic >= 1) {
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
    me->c = c_u;
    me->level = level_u;

    me->t = t_u;


    // Intra-location logic for every state
    switch(me->state) {
        case CONTROLLER_PRE_LEVEL0: // Intra-location logic for state Pre_Level0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 0.02;
            c_u = 0.1;
            level_u = 0;

            if(t_u < 4 && me->t > 4) {
                // Need to saturate t to 5
                t_u = 4;
            }

            break;
        case CONTROLLER_PRE_LEVEL4: // Intra-location logic for state Pre_Level4
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.316;
            r0c_u = 0.02;
            c_u = 0.4;
            level_u = 4;

            if(t_u < 33 && me->t > 33) {
                // Need to saturate t to 33
                t_u = 33;
            }

            break;
        case CONTROLLER_PRE_LEVEL3: // Intra-location logic for state Pre_Level3
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.827;
            r0c_u = 0.02;
            c_u = 0.2;
            level_u = 3;

            if(t_u < 16 && me->t > 16) {
                // Need to saturate t to 16
                t_u = 16;
            }

            break;
        case CONTROLLER_PRE_LEVEL2: // Intra-location logic for state Pre_Level2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 1.384;
            r0c_u = 0.02;
            c_u = 0.175;
            level_u = 2;

            if(t_u < 26 && me->t > 26) {
                // Need to saturate t to 26
                t_u = 26;
            }

            break;
        case CONTROLLER_PRE_LEVEL1: // Intra-location logic for state Pre_Level1
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 0.02;
            c_u = 0.01;
            level_u = 1;

            if(t_u < 64 && me->t > 64) {
                // Need to saturate t to 64
                t_u = 64;
            }

            break;
        case CONTROLLER_PRE_LEVEL3_2: // Intra-location logic for state Pre_Level3_2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.827;
            r0c_u = 0.02;
            c_u = 0.2;
            level_u = 3;

            if(t_u < 19 && me->t > 19) {
                // Need to saturate t to 19
                t_u = 19;
            }

            break;
        case CONTROLLER_LEVEL4: // Intra-location logic for state Level4
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.316;
            r0c_u = 0.02;
            c_u = 0.4;
            level_u = 4;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL3: // Intra-location logic for state Level3
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.827;
            r0c_u = 0.02;
            c_u = 0.2;
            level_u = 3;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL2: // Intra-location logic for state Level2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 1.384;
            r0c_u = 0.02;
            c_u = 0.175;
            level_u = 2;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL1: // Intra-location logic for state Level1
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 0.02;
            c_u = 0.01;
            level_u = 1;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_LEVEL0: // Intra-location logic for state Level0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            r0c_u = 0.02;
            c_u = 0.1;
            level_u = 0;

            break;
    }

    // Update from intermediary variables
    me->r0 = r0_u;
    me->r0c = r0c_u;
    me->c = c_u;
    me->level = level_u;

    me->t = t_u;

}
