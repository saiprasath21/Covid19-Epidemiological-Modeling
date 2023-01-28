#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "CovidsimSystemNetwork/covidsim_system.h"

CovidsimSystem covidsim_system_data;

int main(void) {
    CovidsimSystemInit(&covidsim_system_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,covidsim_system.S,covidsim_system.E1,covidsim_system.E2,covidsim_system.P1,covidsim_system.P2,covidsim_system.I1,covidsim_system.I2,covidsim_system.L1,covidsim_system.L2,covidsim_system.R,covidsim_system.D,covidsim_system.prob,covidsim_system.cases,covidsim_system.C_dot\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", 0.0, covidsim_system_data.s, covidsim_system_data.e1, covidsim_system_data.e2, covidsim_system_data.p1, covidsim_system_data.p2, covidsim_system_data.i1, covidsim_system_data.i2, covidsim_system_data.l1, covidsim_system_data.l2, covidsim_system_data.r, covidsim_system_data.d, covidsim_system_data.prob, covidsim_system_data.cases, covidsim_system_data.c_dot);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        CovidsimSystemRun(&covidsim_system_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, covidsim_system_data.s, covidsim_system_data.e1, covidsim_system_data.e2, covidsim_system_data.p1, covidsim_system_data.p2, covidsim_system_data.i1, covidsim_system_data.i2, covidsim_system_data.l1, covidsim_system_data.l2, covidsim_system_data.r, covidsim_system_data.d, covidsim_system_data.prob, covidsim_system_data.cases, covidsim_system_data.c_dot);
            last_log = i;
        }
#endif
    }

    return 0;
}