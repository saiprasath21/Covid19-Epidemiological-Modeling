#include "plant.h"

static double FuncPow(double x, double y) {
    return pow(x, x);
}

static double CalcBp(double ro, double t) {
    return (ro / (0.15 * 1 + 10)) * (1 + 0 * cos((2 * 3.1415 * (t - 0)) / 365));
}

static double CalcCfr(double icu_patients) {
    if(icu_patients > 300) {
        return 0.02 - ((0.02 - 0.01) * 300) / icu_patients;
    }
    return 0.01;
}

static double Find(double x) {
    if(x < 1) {
        return 0;
    }
    return x;
}


// Plant Initialisation function
void PlantInit(Plant* me) {
    // Initialise State
    me->state = PLANT_UNCONSTRAINED;

    // Initialise Outputs
    me->s = (4822233 - me->e1) - me->i1;
    me->e1 = 929;
    me->e2 = 0.0;
    me->e3 = 0.0;
    me->e4 = 0.0;
    me->p1 = 0.0;
    me->i1 = 39.0 / 0.67;
    me->i2 = 0;
    me->i3 = 0;
    me->i4 = 0;
    me->i5 = 0;
    me->i6 = 0;
    me->i7 = 0;
    me->i8 = 0;
    me->i9 = 0;
    me->i10 = 0;
    me->r = 0;
    me->d = 0;
    me->prob = 1;
    me->c_dot = 0;
    me->cases = 39.0;
    me->i_sum = me->i1 + me->i2 + me->i3 + me->i4 + me->i5 + me->i6 + me->i7 + me->i8 + me->i9 + me->i10;
    me->i_iso = me->i_sum * 0.67;
    me->state_level = 0;

    // Initialise Internal Variables
    me->i_home = 0;
    me->bp = me->bi * 0.15;
    me->p_sum = me->p1;
    me->bi = CalcBp(me->ro, 0);
    me->biso = CalcBp(me->roc, 0);
    me->cfr = 0.01;
    me->t = 0;
    me->e_sum = me->e1 + me->e2 + me->e3 + me->e4;
    me->p_dead = 0;
}

// Plant Execution function
void PlantRun(Plant* me) {
    // Create intermediary variables
    enum PlantStates state_u = me->state;
    double s_u = me->s;
    double e1_u = me->e1;
    double e2_u = me->e2;
    double e3_u = me->e3;
    double e4_u = me->e4;
    double p1_u = me->p1;
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
    double r_u = me->r;
    double d_u = me->d;
    double prob_u = me->prob;
    double c_dot_u = me->c_dot;
    double cases_u = me->cases;
    double i_sum_u = me->i_sum;
    double i_iso_u = me->i_iso;
    double state_level_u = me->state_level;

    double i_home_u = me->i_home;
    double bp_u = me->bp;
    double p_sum_u = me->p_sum;
    double bi_u = me->bi;
    double biso_u = me->biso;
    double cfr_u = me->cfr;
    double t_u = me->t;
    double e_sum_u = me->e_sum;
    double p_dead_u = me->p_dead;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case PLANT_UNCONSTRAINED: // Logic for state unconstrained
            if(me->c_home > 0 && 0.67 * me->i_sum <= 1000) {
                i_iso_u = 0.67 * me->i_sum;
                i_home_u = 0;

                // Next state is isolated_below
                state_u = PLANT_ISOLATED_BELOW;
            }
            else if(me->c_home > 0 && 0.67 * me->i_sum > 1000) {
                i_iso_u = 1000;
                i_home_u = 0.67 * me->i_sum - 1000;

                // Next state is isolated_above
                state_u = PLANT_ISOLATED_ABOVE;
            }
            break;
        case PLANT_ISOLATED_BELOW: // Logic for state isolated_below
            if(me->c_home == 0) {
                i_iso_u = 0;
                i_home_u = 0;

                // Next state is unconstrained
                state_u = PLANT_UNCONSTRAINED;
            }
            else if(me->c_home > 0 && 0.67 * me->i_sum > 1000) {
                i_iso_u = 1000;
                i_home_u = 0.67 * me->i_sum - 1000;

                // Next state is isolated_above
                state_u = PLANT_ISOLATED_ABOVE;
            }
            break;
        case PLANT_ISOLATED_ABOVE: // Logic for state isolated_above
            if(me->c_home == 0) {
                i_iso_u = 0;
                i_home_u = 0;

                // Next state is unconstrained
                state_u = PLANT_UNCONSTRAINED;
            }
            else if(me->c_home > 0 && 0.67 * me->i_sum <= 1000) {
                i_iso_u = 0.67 * me->i_sum;
                i_home_u = 0;

                // Next state is isolated_below
                state_u = PLANT_ISOLATED_BELOW;
            }
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->e3 = e3_u;
    me->e4 = e4_u;
    me->p1 = p1_u;
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
    me->r = r_u;
    me->d = d_u;
    me->prob = prob_u;
    me->c_dot = c_dot_u;
    me->cases = cases_u;
    me->i_sum = i_sum_u;
    me->i_iso = i_iso_u;
    me->state_level = state_level_u;

    me->i_home = i_home_u;
    me->bp = bp_u;
    me->p_sum = p_sum_u;
    me->bi = bi_u;
    me->biso = biso_u;
    me->cfr = cfr_u;
    me->t = t_u;
    me->e_sum = e_sum_u;
    me->p_dead = p_dead_u;


    // Intra-location logic for every state
    switch(me->state) {
        case PLANT_UNCONSTRAINED: // Intra-location logic for state unconstrained
            s_u = me->s + ((-1 * me->s * (me->bp * me->p_sum + me->bi * (me->i_sum - 0.67 * me->i_sum) + me->biso * 0.67 * me->i_sum + me->ll)) / 4822233) * STEP_SIZE;
            e1_u = me->e1 + ((me->s * (me->bp * me->p_sum + me->bi * (me->i_sum - 0.67 * me->i_sum) + me->biso * 0.67 * me->i_sum + me->ll)) / 4822233 - 1 * me->e1) * STEP_SIZE;
            e2_u = me->e2 + (1 * me->e1 - 1 * me->e2) * STEP_SIZE;
            e3_u = me->e3 + (1 * me->e2 - 1 * me->e3) * STEP_SIZE;
            e4_u = me->e4 + (1 * me->e3 - 1 * me->e4) * STEP_SIZE;
            p1_u = me->p1 + (1 * me->e4 - 1 * me->p1) * STEP_SIZE;
            i1_u = me->i1 + (1 * me->p1 - 1 * me->i1) * STEP_SIZE;
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
            cases_u = me->cases + 1 * me->p1 * 0.67 * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            i_sum_u = Find(i1_u + i2_u + i3_u + i4_u + i5_u + i6_u + i7_u + i8_u + i9_u + i10_u);
            e_sum_u = e1_u + e2_u + e3_u + e4_u;
            p_sum_u = Find(p1_u);
            i_iso_u = me->i_sum * 0.67;
            i_home_u = 0;
            bi_u = CalcBp(me->ro, t_u);
            biso_u = CalcBp(me->roc, t_u);
            bp_u = CalcBp(me->ro, t_u) * 0.15;
            c_dot_u = 1 * p1_u * 0.67;
            prob_u = FuncPow(1 - 1.0, cases_u * 0.67 * (0.4 + 0.01 + me->p_dead));
            state_level_u = 0;
            cfr_u = CalcCfr(me->i_sum * 0.0125);

            break;
        case PLANT_ISOLATED_BELOW: // Intra-location logic for state isolated_below
            s_u = me->s + ((-1 * me->s * (me->bp * me->p_sum + me->bi * ((me->i_sum - me->i_iso) - me->i_home * me->c_home) + me->psi) * (1 - me->c_gen)) / 4822233) * STEP_SIZE;
            e1_u = me->e1 + ((me->s * (me->bp * me->p_sum + me->bi * ((me->i_sum - me->i_iso) - me->i_home * me->c_home) + me->psi) * (1 - me->c_gen)) / 4822233 - 1 * me->e1) * STEP_SIZE;
            e2_u = me->e2 + (1 * me->e1 - 1 * me->e2) * STEP_SIZE;
            e3_u = me->e3 + (1 * me->e2 - 1 * me->e3) * STEP_SIZE;
            e4_u = me->e4 + (1 * me->e3 - 1 * me->e4) * STEP_SIZE;
            p1_u = me->p1 + (1 * me->e4 - 1 * me->p1) * STEP_SIZE;
            i1_u = me->i1 + (1 * me->p1 - 1 * me->i1) * STEP_SIZE;
            i2_u = me->i2 + (1 * me->i1 - 1 * me->i2) * STEP_SIZE;
            i3_u = me->i3 + (1 * me->i2 - 1 * me->i3) * STEP_SIZE;
            i4_u = me->i4 + (1 * me->i3 - 1 * me->i4) * STEP_SIZE;
            i5_u = me->i5 + (1 * me->i4 - 1 * me->i5) * STEP_SIZE;
            i6_u = me->i6 + (1 * me->i5 - 1 * me->i6) * STEP_SIZE;
            i7_u = me->i7 + (1 * me->i6 - 1 * me->i7) * STEP_SIZE;
            i8_u = me->i8 + (1 * me->i7 - 1 * me->i8) * STEP_SIZE;
            i9_u = me->i9 + (1 * me->i8 - 1 * me->i9) * STEP_SIZE;
            i10_u = me->i10 + (1 * me->i9 - 1 * me->i10) * STEP_SIZE;
            r_u = me->r + 1 * (1 - 0.67 * me->p_dead) * me->i10 * STEP_SIZE;
            d_u = me->d + 1 * 0.67 * me->p_dead * me->i10 * STEP_SIZE;
            cases_u = me->cases + 1 * me->p1 * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            i_sum_u = i1_u + i2_u + i3_u + i4_u + i5_u + i6_u + i7_u + i8_u + i9_u + i10_u;
            e_sum_u = e1_u + e2_u + e3_u + e4_u;
            p_sum_u = p1_u;
            i_iso_u = 0.67 * me->i_sum;
            i_home_u = 0;
            bi_u = CalcBp(me->ro, t_u);
            bp_u = me->bi * 0.15;
            c_dot_u = 1 * p1_u;
            prob_u = FuncPow(1 - 1.0, cases_u * 0.67 * (0.4 + 0.01 + me->p_dead));
            state_level_u = 1;

            break;
        case PLANT_ISOLATED_ABOVE: // Intra-location logic for state isolated_above
            s_u = me->s + ((-1 * me->s * (me->bp * me->p_sum + me->bi * ((me->i_sum - me->i_iso) - me->i_home * me->c_home) + me->psi) * (1 - me->c_gen)) / 4822233) * STEP_SIZE;
            e1_u = me->e1 + ((me->s * (me->bp * me->p_sum + me->bi * ((me->i_sum - me->i_iso) - me->i_home * me->c_home) + me->psi) * (1 - me->c_gen)) / 4822233 - 1 * me->e1) * STEP_SIZE;
            e2_u = me->e2 + (1 * me->e1 - 1 * me->e2) * STEP_SIZE;
            e3_u = me->e3 + (1 * me->e2 - 1 * me->e3) * STEP_SIZE;
            e4_u = me->e4 + (1 * me->e3 - 1 * me->e4) * STEP_SIZE;
            p1_u = me->p1 + (1 * me->e4 - 1 * me->p1) * STEP_SIZE;
            i1_u = me->i1 + (1 * me->p1 - 1 * me->i1) * STEP_SIZE;
            i2_u = me->i2 + (1 * me->i1 - 1 * me->i2) * STEP_SIZE;
            i3_u = me->i3 + (1 * me->i2 - 1 * me->i3) * STEP_SIZE;
            i4_u = me->i4 + (1 * me->i3 - 1 * me->i4) * STEP_SIZE;
            i5_u = me->i5 + (1 * me->i4 - 1 * me->i5) * STEP_SIZE;
            i6_u = me->i6 + (1 * me->i5 - 1 * me->i6) * STEP_SIZE;
            i7_u = me->i7 + (1 * me->i6 - 1 * me->i7) * STEP_SIZE;
            i8_u = me->i8 + (1 * me->i7 - 1 * me->i8) * STEP_SIZE;
            i9_u = me->i9 + (1 * me->i8 - 1 * me->i9) * STEP_SIZE;
            i10_u = me->i10 + (1 * me->i9 - 1 * me->i10) * STEP_SIZE;
            r_u = me->r + 1 * (1 - 0.67 * me->p_dead) * me->i10 * STEP_SIZE;
            d_u = me->d + 1 * 0.67 * me->p_dead * me->i10 * STEP_SIZE;
            cases_u = me->cases + 1 * me->p1 * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            i_sum_u = i1_u + i2_u + i3_u + i4_u + i5_u + i6_u + i7_u + i8_u + i9_u + i10_u;
            e_sum_u = e1_u + e2_u + e3_u + e4_u;
            p_sum_u = p1_u;
            i_iso_u = 1000;
            i_home_u = 0.67 * me->i_sum - 1000;
            bi_u = CalcBp(me->ro, t_u);
            bp_u = me->bi * 0.15;
            c_dot_u = 1 * p1_u;
            prob_u = FuncPow(1 - 1.0, cases_u * 0.67 * (0.4 + 0.01 + me->p_dead));
            state_level_u = 2;

            break;
    }

    // Update from intermediary variables
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->e3 = e3_u;
    me->e4 = e4_u;
    me->p1 = p1_u;
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
    me->r = r_u;
    me->d = d_u;
    me->prob = prob_u;
    me->c_dot = c_dot_u;
    me->cases = cases_u;
    me->i_sum = i_sum_u;
    me->i_iso = i_iso_u;
    me->state_level = state_level_u;

    me->i_home = i_home_u;
    me->bp = bp_u;
    me->p_sum = p_sum_u;
    me->bi = bi_u;
    me->biso = biso_u;
    me->cfr = cfr_u;
    me->t = t_u;
    me->e_sum = e_sum_u;
    me->p_dead = p_dead_u;

}