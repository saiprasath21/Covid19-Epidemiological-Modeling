#include "plant.h"

static double CalcCfr(double icu_patients) {
    if(icu_patients > 300) {
        return 0.08 - ((0.08 - 0.06) * 300) / icu_patients;
    }
    return 0.06;
}


// Plant Initialisation function
void PlantInit(Plant* me) {
    // Initialise State
    me->state = PLANT_UNVACCINATED;

    // Initialise Outputs
    me->s = 60461828 - (6 + 6 * 3.071752496328926) * 155;
    me->e = 4 * (1 + 3.071752496328926) * 155;
    me->p = (1 + 3.071752496328926) * 155;
    me->iu = 3.071752496328926 * 155;
    me->ic = 155;
    me->ru = 0;
    me->rc = 0;
    me->d = 0;
    me->cases = 155;
    me->c_dot = 0;

    // Initialise Internal Variables
    me->t = 0;
    me->beta = 0;
    me->cfr = CalcCfr(0);
}

// Plant Execution function
void PlantRun(Plant* me) {
    // Create intermediary variables
    enum PlantStates state_u = me->state;
    double s_u = me->s;
    double e_u = me->e;
    double p_u = me->p;
    double iu_u = me->iu;
    double ic_u = me->ic;
    double ru_u = me->ru;
    double rc_u = me->rc;
    double d_u = me->d;
    double cases_u = me->cases;
    double c_dot_u = me->c_dot;

    double t_u = me->t;
    double beta_u = me->beta;
    double cfr_u = me->cfr;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case PLANT_UNVACCINATED: // Logic for state unvaccinated
            if(365 >= 0 && me->t >= 365 && -1 > 0) {
                // Next state is partially_vaccinated
                state_u = PLANT_PARTIALLY_VACCINATED;
            }
            else if(365 >= 0 && me->t >= 365 && -1 <= 0) {
                // Next state is fully_vaccinated
                state_u = PLANT_FULLY_VACCINATED;
            }
            break;
        case PLANT_PARTIALLY_VACCINATED: // Logic for state partially_vaccinated
            if(me->s <= 0) {
                s_u = 0;

                // Next state is fully_vaccinated
                state_u = PLANT_FULLY_VACCINATED;
            }
            break;
        case PLANT_FULLY_VACCINATED: // Logic for state fully_vaccinated
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->s = s_u;
    me->e = e_u;
    me->p = p_u;
    me->iu = iu_u;
    me->ic = ic_u;
    me->ru = ru_u;
    me->rc = rc_u;
    me->d = d_u;
    me->cases = cases_u;
    me->c_dot = c_dot_u;

    me->t = t_u;
    me->beta = beta_u;
    me->cfr = cfr_u;


    // Intra-location logic for every state
    switch(me->state) {
        case PLANT_UNVACCINATED: // Intra-location logic for state unvaccinated
            s_u = me->s + ((-me->beta * me->s * (0.15 * me->p + me->iu + me->ic)) / 60461828) * STEP_SIZE;
            e_u = me->e + ((me->beta * me->s * (0.15 * me->p + me->iu + me->ic)) / 60461828 - 0.25 * me->e) * STEP_SIZE;
            p_u = me->p + (0.25 * me->e - 1 * me->p) * STEP_SIZE;
            iu_u = me->iu + (1 * me->p - (0.1 + 0.1) * me->iu) * STEP_SIZE;
            ic_u = me->ic + (0.1 * me->iu - 0.1 * me->ic) * STEP_SIZE;
            ru_u = me->ru + 0.1 * (1 - me->cfr) * me->iu * STEP_SIZE;
            rc_u = me->rc + 0.1 * (1 - me->cfr) * me->ic * STEP_SIZE;
            d_u = me->d + 0.1 * me->cfr * (me->iu + me->ic) * STEP_SIZE;
            cases_u = me->cases + 0.1 * me->iu * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            beta_u = me->r0 / (0.15 / 1 + 1 / 0.1);
            c_dot_u = 0.1 * iu_u;
            cfr_u = CalcCfr((iu_u + ic_u) * 0.0125);

            if(t_u < 365 && me->t > 365) {
                // Need to saturate t to 365
                t_u = 365;
            }

            break;
        case PLANT_PARTIALLY_VACCINATED: // Intra-location logic for state partially_vaccinated
            s_u = me->s + ((-me->beta * me->s * (0.15 * me->p + me->iu + me->ic)) / 60461828 - 60461828 / -1) * STEP_SIZE;
            e_u = me->e + ((me->beta * me->s * (0.15 * me->p + me->iu + me->ic)) / 60461828 - 0.25 * me->e) * STEP_SIZE;
            p_u = me->p + (0.25 * me->e - 1 * me->p) * STEP_SIZE;
            iu_u = me->iu + (1 * me->p - (0.1 + 0.1) * me->iu) * STEP_SIZE;
            ic_u = me->ic + (0.1 * me->iu - 0.1 * me->ic) * STEP_SIZE;
            ru_u = me->ru + 0.1 * (1 - me->cfr) * me->iu * STEP_SIZE;
            rc_u = me->rc + 0.1 * (1 - me->cfr) * me->ic * STEP_SIZE;
            d_u = me->d + 0.1 * me->cfr * (me->iu + me->ic) * STEP_SIZE;
            cases_u = me->cases + 0.1 * me->iu * STEP_SIZE;

            beta_u = me->r0 / (0.15 / 1 + 1 / 0.1);
            c_dot_u = 0.1 * iu_u;
            cfr_u = CalcCfr((iu_u + ic_u) * 0.0125);

            if(s_u > 0 && me->s < 0) {
                // Need to saturate S to 0
                s_u = 0;
            }

            break;
        case PLANT_FULLY_VACCINATED: // Intra-location logic for state fully_vaccinated
            e_u = me->e + ((me->beta * me->s * (0.15 * me->p + me->iu + me->ic)) / 60461828 - 0.25 * me->e) * STEP_SIZE;
            p_u = me->p + (0.25 * me->e - 1 * me->p) * STEP_SIZE;
            iu_u = me->iu + (1 * me->p - (0.1 + 0.1) * me->iu) * STEP_SIZE;
            ic_u = me->ic + (0.1 * me->iu - 0.1 * me->ic) * STEP_SIZE;
            ru_u = me->ru + 0.1 * (1 - me->cfr) * me->iu * STEP_SIZE;
            rc_u = me->rc + 0.1 * (1 - me->cfr) * me->ic * STEP_SIZE;
            d_u = me->d + 0.1 * me->cfr * (me->iu + me->ic) * STEP_SIZE;
            cases_u = me->cases + 0.1 * me->iu * STEP_SIZE;

            s_u = 0;
            beta_u = me->r0 / (0.15 / 1 + 1 / 0.1);
            c_dot_u = 0.1 * iu_u;
            cfr_u = CalcCfr((iu_u + ic_u) * 0.0125);

            break;
    }

    // Update from intermediary variables
    me->s = s_u;
    me->e = e_u;
    me->p = p_u;
    me->iu = iu_u;
    me->ic = ic_u;
    me->ru = ru_u;
    me->rc = rc_u;
    me->d = d_u;
    me->cases = cases_u;
    me->c_dot = c_dot_u;

    me->t = t_u;
    me->beta = beta_u;
    me->cfr = cfr_u;

}