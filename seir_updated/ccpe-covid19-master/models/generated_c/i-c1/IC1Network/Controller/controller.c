#include "controller.h"

// Controller Initialisation function
void ControllerInit(Controller* me) {
    // Initialise State
    me->state = CONTROLLER_PRE_PHASE0;

    // Initialise Outputs
    me->r0 = 0;
    me->r0c = 0;
    me->phase = 0;

    // Initialise Internal Variables
    me->t = 0;
}

// Controller Execution function
void ControllerRun(Controller* me) {
    // Create intermediary variables
    enum ControllerStates state_u = me->state;
    double r0_u = me->r0;
    double r0c_u = me->r0c;
    double phase_u = me->phase;

    double t_u = me->t;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case CONTROLLER_PRE_PHASE0: // Logic for state Pre_Phase0
            if(me->t >= 10) {
                t_u = 0;

                // Next state is Pre_Phase1
                state_u = CONTROLLER_PRE_PHASE1;
            }
            break;
        case CONTROLLER_PRE_PHASE1: // Logic for state Pre_Phase1
            if(me->t >= 6) {
                t_u = 0;

                // Next state is Pre_Phase2
                state_u = CONTROLLER_PRE_PHASE2;
            }
            break;
        case CONTROLLER_PRE_PHASE2: // Logic for state Pre_Phase2
            if(me->t >= 10) {
                t_u = 0;

                // Next state is Pre_Phase3
                state_u = CONTROLLER_PRE_PHASE3;
            }
            break;
        case CONTROLLER_PRE_PHASE3: // Logic for state Pre_Phase3
            if(me->t >= 129) {
                t_u = 0;

                // Next state is Pre_Phase4
                state_u = CONTROLLER_PRE_PHASE4;
            }
            break;
        case CONTROLLER_PRE_PHASE4: // Logic for state Pre_Phase4
            if(me->t >= 32) {
                // Next state is Phase2
                state_u = CONTROLLER_PHASE2;
            }
            break;
        case CONTROLLER_PHASE3: // Logic for state Phase3
            if(me->c_dot <= 10 && me->t >= 14) {
                t_u = 0;

                // Next state is Phase2
                state_u = CONTROLLER_PHASE2;
            }
            break;
        case CONTROLLER_PHASE2: // Logic for state Phase2
            if(me->ic >= 6046) {
                t_u = 0;

                // Next state is Phase3
                state_u = CONTROLLER_PHASE3;
            }
            else if(me->c_dot <= 5 && me->t >= 14) {
                t_u = 0;

                // Next state is Phase1
                state_u = CONTROLLER_PHASE1;
            }
            break;
        case CONTROLLER_PHASE1: // Logic for state Phase1
            if(me->ic >= 6046) {
                t_u = 0;

                // Next state is Phase3
                state_u = CONTROLLER_PHASE3;
            }
            else if(me->ic >= 3023) {
                t_u = 0;

                // Next state is Phase2
                state_u = CONTROLLER_PHASE2;
            }
            else if(me->c_dot <= 0.01 && me->t >= 14) {
                t_u = 0;

                // Next state is Phase0
                state_u = CONTROLLER_PHASE0;
            }
            break;
        case CONTROLLER_PHASE0: // Logic for state Phase0
            if(me->ic >= 6046) {
                t_u = 0;

                // Next state is Phase3
                state_u = CONTROLLER_PHASE3;
            }
            else if(me->ic >= 605) {
                t_u = 0;

                // Next state is Phase1
                state_u = CONTROLLER_PHASE1;
            }
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->r0 = r0_u;
    me->r0c = r0c_u;
    me->phase = phase_u;

    me->t = t_u;


    // Intra-location logic for every state
    switch(me->state) {
        case CONTROLLER_PRE_PHASE0: // Intra-location logic for state Pre_Phase0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 6.3533;
            r0c_u = 6.3533;
            phase_u = 0;

            if(t_u < 10 && me->t > 10) {
                // Need to saturate t to 10
                t_u = 10;
            }

            break;
        case CONTROLLER_PRE_PHASE1: // Intra-location logic for state Pre_Phase1
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 4.8051;
            r0c_u = 0.5808;
            phase_u = 1;

            if(t_u < 6 && me->t > 6) {
                // Need to saturate t to 6
                t_u = 6;
            }

            break;
        case CONTROLLER_PRE_PHASE2: // Intra-location logic for state Pre_Phase2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 3.2704;
            r0c_u = 0.5808;
            phase_u = 2;

            if(t_u < 10 && me->t > 10) {
                // Need to saturate t to 10
                t_u = 10;
            }

            break;
        case CONTROLLER_PRE_PHASE3: // Intra-location logic for state Pre_Phase3
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.5808;
            r0c_u = 0.5808;
            phase_u = 3;

            if(t_u < 129 && me->t > 129) {
                // Need to saturate t to 129
                t_u = 129;
            }

            break;
        case CONTROLLER_PRE_PHASE4: // Intra-location logic for state Pre_Phase4
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.6472;
            r0c_u = 0.5808;
            phase_u = 2;

            if(t_u < 32 && me->t > 32) {
                // Need to saturate t to 32
                t_u = 32;
            }

            break;
        case CONTROLLER_PHASE3: // Intra-location logic for state Phase3
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.5808;
            r0c_u = 0.5808;
            phase_u = 3;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_PHASE2: // Intra-location logic for state Phase2
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 3.2704;
            r0c_u = 0.5808;
            phase_u = 2;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_PHASE1: // Intra-location logic for state Phase1
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 4.8051;
            r0c_u = 0.5808;
            phase_u = 1;

            if(t_u < 14 && me->t > 14) {
                // Need to saturate t to 14
                t_u = 14;
            }

            break;
        case CONTROLLER_PHASE0: // Intra-location logic for state Phase0
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 6.3533;
            r0c_u = 6.3533;
            phase_u = 0;

            break;
    }

    // Update from intermediary variables
    me->r0 = r0_u;
    me->r0c = r0c_u;
    me->phase = phase_u;

    me->t = t_u;

}