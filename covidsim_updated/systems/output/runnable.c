#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "NzC210Network/nz_c2_10.h"

NzC210 nz_c2_10_data;

int main(void) {
    NzC210Init(&nz_c2_10_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,nz_c2_10.C_dot,nz_c2_10.Level,nz_c2_10.total_cases,nz_c2_10.deaths,nz_c2_10.Iu,nz_c2_10.Ic\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f\n", 0.0, nz_c2_10_data.c_dot, nz_c2_10_data.level, nz_c2_10_data.total_cases, nz_c2_10_data.deaths, nz_c2_10_data.iu, nz_c2_10_data.ic);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        NzC210Run(&nz_c2_10_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, nz_c2_10_data.c_dot, nz_c2_10_data.level, nz_c2_10_data.total_cases, nz_c2_10_data.deaths, nz_c2_10_data.iu, nz_c2_10_data.ic);
            last_log = i;
        }
#endif
    }

    return 0;
}