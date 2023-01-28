#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "NzC1Network/nz_c1.h"

NzC1 nz_c1_data;

int main(void) {
    NzC1Init(&nz_c1_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,nz-c1.S,nz-c1.E,nz-c1.P,nz-c1.Iu,nz-c1.Ic,nz-c1.Ru,nz-c1.Rc,nz-c1.D,nz-c1.cases,nz-c1.Level\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", 0.0, nz_c1_data.s, nz_c1_data.e, nz_c1_data.p, nz_c1_data.iu, nz_c1_data.ic, nz_c1_data.ru, nz_c1_data.rc, nz_c1_data.d, nz_c1_data.cases, nz_c1_data.level);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        NzC1Run(&nz_c1_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, nz_c1_data.s, nz_c1_data.e, nz_c1_data.p, nz_c1_data.iu, nz_c1_data.ic, nz_c1_data.ru, nz_c1_data.rc, nz_c1_data.d, nz_c1_data.cases, nz_c1_data.level);
            last_log = i;
        }
#endif
    }

    return 0;
}