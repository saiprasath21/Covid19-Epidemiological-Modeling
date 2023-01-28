#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "NzC3Network/nz_c3.h"

NzC3 nz_c3_data;

int main(void) {
    NzC3Init(&nz_c3_data);

#if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,nz-c3.S,nz-c3.E,nz-c3.P,nz-c3.Iu,nz-c3.Ic,nz-c3.Ru,nz-c3.Rc,nz-c3.D,nz-c3.cases,nz-c3.Level\n");
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", 0.0, nz_c3_data.s, nz_c3_data.e, nz_c3_data.p, nz_c3_data.iu, nz_c3_data.ic, nz_c3_data.ru, nz_c3_data.rc, nz_c3_data.d, nz_c3_data.cases, nz_c3_data.level);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        NzC3Run(&nz_c3_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, nz_c3_data.s, nz_c3_data.e, nz_c3_data.p, nz_c3_data.iu, nz_c3_data.ic, nz_c3_data.ru, nz_c3_data.rc, nz_c3_data.d, nz_c3_data.cases, nz_c3_data.level);
            last_log = i;
        }
#endif
    }

    return 0;
}