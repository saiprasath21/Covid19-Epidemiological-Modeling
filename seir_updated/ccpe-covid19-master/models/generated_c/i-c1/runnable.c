#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "IC1Network/i_c1.h"

IC1 i_c1_data;

int main(void) {
    IC1Init(&i_c1_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,i-c1.S,i-c1.E,i-c1.P,i-c1.Iu,i-c1.Ic,i-c1.Ru,i-c1.Rc,i-c1.D,i-c1.cases,i-c1.Phase\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", 0.0, i_c1_data.s, i_c1_data.e, i_c1_data.p, i_c1_data.iu, i_c1_data.ic, i_c1_data.ru, i_c1_data.rc, i_c1_data.d, i_c1_data.cases, i_c1_data.phase);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        IC1Run(&i_c1_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, i_c1_data.s, i_c1_data.e, i_c1_data.p, i_c1_data.iu, i_c1_data.ic, i_c1_data.ru, i_c1_data.rc, i_c1_data.d, i_c1_data.cases, i_c1_data.phase);
            last_log = i;
        }
#endif
    }

    return 0;
}