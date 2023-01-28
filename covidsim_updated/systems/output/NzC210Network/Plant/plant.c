#include "plant.h"

static double CalcBp(double ro) {
    return ro / (0.15 * 1 + 10);
}

static double CalcCfr(double icu_patients) {
    if(icu_patients > 300) {
        return 0.02 - ((0.02 - 0.01) * 300) / icu_patients;
    }
    return 0.01;
}

static double Find(double x, double t) {
    if(x < 1 && t < 80) {
        return 0;
    }
    return x;
}


// Plant Initialisation function
void PlantInit(Plant* me) {
    // Initialise State
    me->state = PLANT_UNCONSTRAINED;

    // Initialise Outputs
    me->c_dot = 0;
    me->cases = 64.0;
    me->i_sum = 64.0;
    me->i_iso = 64.0;
    me->s = (4822233 - me->i2 * 9) - me->u1;
    me->e1 = 0.0;
    me->e2 = 0.0;
    me->e3 = 0.0;
    me->e4 = 0.0;
    me->p1 = 300.0;
    me->u1 = 355.0;
    me->i1 = 7.0;
    me->i2 = 7.0;
    me->i3 = 7.0;
    me->i4 = 7.0;
    me->i5 = 6.0;
    me->i6 = 6.0;
    me->i7 = 6.0;
    me->i8 = 6.0;
    me->i9 = 6.0;
    me->i10 = 6.0;
    me->d = 0;

    // Initialise Internal Variables
    me->t = 0;
    me->bp = CalcBp(me->ro) * 0.15;
    me->p_sum = me->p1;
    me->bi = CalcBp(me->ro);
    me->biso = CalcBp(me->roc);
    me->r = 0;
    me->cfr = 0.01;
    me->e_sum = me->e1 + me->e2 + me->e3 + me->e4;
}

// Plant Execution function
void PlantRun(Plant* me) {
    // Create intermediary variables
    enum PlantStates state_u = me->state;
    double c_dot_u = me->c_dot;
    double cases_u = me->cases;
    double i_sum_u = me->i_sum;
    double i_iso_u = me->i_iso;
    double s_u = me->s;
    double e1_u = me->e1;
    double e2_u = me->e2;
    double e3_u = me->e3;
    double e4_u = me->e4;
    double p1_u = me->p1;
    double u1_u = me->u1;
    double i1_u = me->i1;
    double i2_u = me->i2;
    double i3_u = me->i3;
    double i4_u = me->i4;
    double i5_u = me->i5;
    double i6_u = me->i6;
    double i7_u = me->i7;
    double i8_u = me->i8;
    double i9_u = me->i9;
    double i10_u = me->i10;
    double d_u = me->d;

    double t_u = me->t;
    double bp_u = me->bp;
    double p_sum_u = me->p_sum;
    double bi_u = me->bi;
    double biso_u = me->biso;
    double r_u = me->r;
    double cfr_u = me->cfr;
    double e_sum_u = me->e_sum;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case PLANT_UNCONSTRAINED: // Logic for state unconstrained
            if(me->t == -1) {
                e1_u = me->e1 + 1;
                s_u = me->s - 1;

                // Next state is unconstrained
                state_u = PLANT_UNCONSTRAINED;
            }
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->c_dot = c_dot_u;
    me->cases = cases_u;
    me->i_sum = i_sum_u;
    me->i_iso = i_iso_u;
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->e3 = e3_u;
    me->e4 = e4_u;
    me->p1 = p1_u;
    me->u1 = u1_u;
    me->i1 = i1_u;
    me->i2 = i2_u;
    me->i3 = i3_u;
    me->i4 = i4_u;
    me->i5 = i5_u;
    me->i6 = i6_u;
    me->i7 = i7_u;
    me->i8 = i8_u;
    me->i9 = i9_u;
    me->i10 = i10_u;
    me->d = d_u;

    me->t = t_u;
    me->bp = bp_u;
    me->p_sum = p_sum_u;
    me->bi = bi_u;
    me->biso = biso_u;
    me->r = r_u;
    me->cfr = cfr_u;
    me->e_sum = e_sum_u;


    // Intra-location logic for every state
    switch(me->state) {
        case PLANT_UNCONSTRAINED: // Intra-location logic for state unconstrained
            s_u = me->s + ((-1 * me->s * (me->bp * me->p_sum + me->bi * me->u1 + me->biso * me->i_sum)) / 4822233) * STEP_SIZE;
            e1_u = me->e1 + ((me->s * (me->bp * me->p_sum + me->bi * me->u1 + me->biso * me->i_sum)) / 4822233 - 1 * me->e1) * STEP_SIZE;
            e2_u = me->e2 + (1 * me->e1 - 1 * me->e2) * STEP_SIZE;
            e3_u = me->e3 + (1 * me->e2 - 1 * me->e3) * STEP_SIZE;
            e4_u = me->e4 + (1 * me->e3 - 1 * me->e4) * STEP_SIZE;
            p1_u = me->p1 + (1 * me->e4 - 1 * me->p1) * STEP_SIZE;
            u1_u = me->u1 + (1 * me->p1 - me->c * me->u1) * STEP_SIZE;
            i1_u = me->i1 + (me->c * me->u1 - 1 * me->i1) * STEP_SIZE;
            i2_u = me->i2 + (1 * me->i1 - 1 * me->i2) * STEP_SIZE;
            i3_u = me->i3 + (1 * me->i2 - 1 * me->i3) * STEP_SIZE;
            i4_u = me->i4 + (1 * me->i3 - 1 * me->i4) * STEP_SIZE;
            i5_u = me->i5 + (1 * me->i4 - 1 * me->i5) * STEP_SIZE;
            i6_u = me->i6 + (1 * me->i5 - 1 * me->i6) * STEP_SIZE;
            i7_u = me->i7 + (1 * me->i6 - 1 * me->i7) * STEP_SIZE;
            i8_u = me->i8 + (1 * me->i7 - 1 * me->i8) * STEP_SIZE;
            i9_u = me->i9 + (1 * me->i8 - 1 * me->i9) * STEP_SIZE;
            i10_u = me->i10 + (1 * me->i9 - 1 * me->i10) * STEP_SIZE;
            r_u = me->r + 1 * (1 - me->cfr) * me->i10 * STEP_SIZE;
            d_u = me->d + 1 * me->cfr * me->i10 * STEP_SIZE;
            cases_u = me->cases + me->c * me->u1 * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            i_sum_u = Find(i1_u + i2_u + i3_u + i4_u + i5_u + i6_u + i7_u + i8_u + i9_u + i10_u, t_u);
            u1_u = Find(u1_u, t_u);
            e_sum_u = e1_u + e2_u + e3_u + e4_u;
            p_sum_u = Find(p1_u, t_u);
            i_iso_u = i1_u + i2_u + i3_u + i4_u + i5_u + i6_u + i7_u + i8_u + i9_u + i10_u;
            bi_u = CalcBp(me->ro);
            biso_u = CalcBp(me->roc);
            bp_u = CalcBp(me->ro) * 0.15;
            c_dot_u = me->c * u1_u;
            cfr_u = CalcCfr((me->i_sum + u1_u) * 0.0125);

            if((t_u > -1 && me->t < -1) || (t_u < -1 && me->t > -1)) {
                // Need to saturate t to -1
                t_u = -1;
            }

            break;
    }

    // Update from intermediary variables
    me->c_dot = c_dot_u;
    me->cases = cases_u;
    me->i_sum = i_sum_u;
    me->i_iso = i_iso_u;
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->e3 = e3_u;
    me->e4 = e4_u;
    me->p1 = p1_u;
    me->u1 = u1_u;
    me->i1 = i1_u;
    me->i2 = i2_u;
    me->i3 = i3_u;
    me->i4 = i4_u;
    me->i5 = i5_u;
    me->i6 = i6_u;
    me->i7 = i7_u;
    me->i8 = i8_u;
    me->i9 = i9_u;
    me->i10 = i10_u;
    me->d = d_u;

    me->t = t_u;
    me->bp = bp_u;
    me->p_sum = p_sum_u;
    me->bi = bi_u;
    me->biso = biso_u;
    me->r = r_u;
    me->cfr = cfr_u;
    me->e_sum = e_sum_u;

}