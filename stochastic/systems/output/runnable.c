#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>
#include "config.h"

#include "NzC2Network/nz_c2.h"

NzC2 nz_c2_data;

int main(void) {

    #if ENABLE_LOGGING
    FILE* fp = fopen(LOGGING_FILE, "w");
    fprintf(fp, "Time,nz-c2.total_cases,nz-c2.clinical_cases,nz-c2.c_dot,nz-c2.Level,nz-c2.active_cases,nz-c2.dead_cases\n");
    srand(time(0));
    for(int k=0;k<100;k++){
    printf("Iteration ------------------------------------ %d \n", k);
     NzC2Init(&nz_c2_data);
    srand(time(0));
    fprintf(fp, "%f,%f,%f,%f,%f,%f,%f\n", 0.0, nz_c2_data.total_cases,nz_c2_data.clinical_cases,nz_c2_data.c_dot,nz_c2_data.level,nz_c2_data.active_cases,nz_c2_data.dead_cases);
    unsigned int last_log = 0;
#endif

    unsigned int i = 0;
    for(i=1; i <= (SIMULATION_TIME / STEP_SIZE); i++) {
        NzC2Run(&nz_c2_data);

        /* Logging */
#if ENABLE_LOGGING
        if((i - last_log) >= LOGGING_INTERVAL / STEP_SIZE) {
            fprintf(fp, "%f,%f,%f,%f,%f,%f,%f\n", i*STEP_SIZE, nz_c2_data.total_cases,nz_c2_data.clinical_cases,nz_c2_data.c_dot,nz_c2_data.level,nz_c2_data.active_cases,nz_c2_data.dead_cases);
            last_log = i;
        }
#endif
    }
}
    return 0;
}
