#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "NzC2Network/nz_c2.h"

NzC2 nz_c2_data;

int main(void) {
    NzC2Init(&nz_c2_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,nz-c2.S,nz-c2.E,nz-c2.P,nz-c2.Iu,nz-c2.Ic,nz-c2.Ru,nz-c2.Rc,nz-c2.D,nz-c2.cases,nz-c2.Level\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", 0.0, nz_c2_data.s, nz_c2_data.e, nz_c2_data.p, nz_c2_data.iu, nz_c2_data.ic, nz_c2_data.ru, nz_c2_data.rc, nz_c2_data.d, nz_c2_data.cases, nz_c2_data.level);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        NzC2Run(&nz_c2_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, nz_c2_data.s, nz_c2_data.e, nz_c2_data.p, nz_c2_data.iu, nz_c2_data.ic, nz_c2_data.ru, nz_c2_data.rc, nz_c2_data.d, nz_c2_data.cases, nz_c2_data.level);
            last_log = i;
        }
#endif
    }

    return 0;
}