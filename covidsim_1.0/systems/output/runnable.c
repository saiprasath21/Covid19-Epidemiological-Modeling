#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "C2SystemNetwork/c2_system.h"

C2System c2_system_data;

int main(void) {
    C2SystemInit(&c2_system_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,c2_system.cases,c2_system.C_dot,c2_system.Level,c2_system.total,c2_system.D\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f\n", 0.0, c2_system_data.cases, c2_system_data.c_dot, c2_system_data.level, c2_system_data.total, c2_system_data.d);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        C2SystemRun(&c2_system_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, c2_system_data.cases, c2_system_data.c_dot, c2_system_data.level, c2_system_data.total, c2_system_data.d);
            last_log = i;
        }
#endif
    }

    return 0;
}