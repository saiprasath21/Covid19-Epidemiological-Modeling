#include "plant.h"

static double PGen(double t) {
    if(t >= 30 && t <= 900) {
        return 0.5 * 1;
    }
    return 0;
}

static double PtrSick(double i, double l) {
    if(i + l >= 0 * 4822233) {
        return 0 * 1;
    }
    return 0;
}

static double PtrHosp(double i, double l) {
    if((i + l) * 0.67 * 0.006 >= 0 * 4822233) {
        return 0 * 1;
    }
    return 0;
}

static double PtrIcu(double i, double l) {
    if((i + l) * 0.67 * 0.006 * 0.25 >= 0 * 4822233) {
        return 0 * 1;
    }
    return 0;
}

static double Iiso(double i, double l, double t) {
    if(t >= 100 && t <= 1000 && 0.67 * (i + l) <= 1000) {
        return 0.67 * i * 1;
    }
    else if(t >= 100 && t <= 1000 && 0.67 * (i + l) > 1000) {
        return (i / (i + l)) * 1000 * 1;
    }
    return 0;
}

static double Liso(double i, double l, double t) {
    if(t >= 100 && t <= 1000 && 0.67 * (i + l) <= 1000) {
        return 0.67 * l * 1;
    }
    else if(t >= 100 && t <= 1000 && 0.67 * (i + l) > 1000) {
        return (l / (i + l)) * 1000 * 1;
    }
    return 0;
}

static double Ihome(double i, double l, double t) {
    if(t >= 100 && t <= 1000 && 0.67 * (i + l) > 1000) {
        return i - (i / (i + l)) * 1000 * 1;
    }
    return 0;
}

static double Lhome(double i, double l, double t) {
    if(t >= 100 && t <= 1000 && 0.67 * (i + l) > 1000) {
        return l - (l / (i + l)) * 1000 * 1;
    }
    return 0;
}

static double Maxi(double a, double b, double c, double d) {
    if(a >= b && a >= c && a >= d) {
        return a;
    }
    else if(b >= a && b >= c && b >= d) {
        return b;
    }
    else if(c >= a && c >= b && c >= d) {
        return c;
    }
    return d;
}

static double Beta(double t, double p) {
    return (2.5 / (0.5 * 1 + 10 + 0.5 * 10)) * (1 + 0 * cos((2 * 3.1428 * (t - 0)) / 365)) * (1 - p);
}

static double FuncPow(double x, double y) {
    return pow(x, x);
}


// Plant Initialisation function
void PlantInit(Plant* me) {
    // Initialise State
    me->state = PLANT_INITIAL;

    // Initialise Outputs
    me->s = 4822233 - (6 + 6 * 4.8) * 39;
    me->e1 = 4 * (1 + 4.8) * 39;
    me->e2 = 0;
    me->p1 = (1 + 4.8) * 39;
    me->p2 = 0;
    me->i1 = (1 + 4.8) * 39;
    me->i2 = 0;
    me->l1 = 0;
    me->l2 = 0;
    me->r = 0;
    me->d = 0;
    me->prob = 1;
    me->c_dot = 0;
    me->cases = 0;

    // Initialise Internal Variables
    me->t = 0;
    me->b = Beta(me->t, me->g);
    me->p_sum = me->p1 + me->p2;
    me->i_sum = me->i1 + me->i2;
    me->l_sum = me->l1 + me->l2;
    me->l2_sum = 0;
    me->p2_sum = 0;
    me->e_sum = me->e1 + me->e2;
    me->g = Maxi(PGen(me->t), PtrSick(me->i_sum, me->l_sum), PtrHosp(me->i_sum, me->l_sum), PtrIcu(me->i_sum, me->l_sum));
}

// Plant Execution function
void PlantRun(Plant* me) {
    // Create intermediary variables
    enum PlantStates state_u = me->state;
    double s_u = me->s;
    double e1_u = me->e1;
    double e2_u = me->e2;
    double p1_u = me->p1;
    double p2_u = me->p2;
    double i1_u = me->i1;
    double i2_u = me->i2;
    double l1_u = me->l1;
    double l2_u = me->l2;
    double r_u = me->r;
    double d_u = me->d;
    double prob_u = me->prob;
    double c_dot_u = me->c_dot;
    double cases_u = me->cases;

    double t_u = me->t;
    double b_u = me->b;
    double p_sum_u = me->p_sum;
    double i_sum_u = me->i_sum;
    double l_sum_u = me->l_sum;
    double l2_sum_u = me->l2_sum;
    double p2_sum_u = me->p2_sum;
    double e_sum_u = me->e_sum;
    double g_u = me->g;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case PLANT_INITIAL: // Logic for state initial
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->p1 = p1_u;
    me->p2 = p2_u;
    me->i1 = i1_u;
    me->i2 = i2_u;
    me->l1 = l1_u;
    me->l2 = l2_u;
    me->r = r_u;
    me->d = d_u;
    me->prob = prob_u;
    me->c_dot = c_dot_u;
    me->cases = cases_u;

    me->t = t_u;
    me->b = b_u;
    me->p_sum = p_sum_u;
    me->i_sum = i_sum_u;
    me->l_sum = l_sum_u;
    me->l2_sum = l2_sum_u;
    me->p2_sum = p2_sum_u;
    me->e_sum = e_sum_u;
    me->g = g_u;


    // Intra-location logic for every state
    switch(me->state) {
        case PLANT_INITIAL: // Intra-location logic for state initial
            s_u = me->s + ((-1 * me->s * (10 + me->b * (((0.5 * me->p_sum + me->i_sum) - Iiso(me->i_sum, me->l_sum, me->t)) - 0.5 * Ihome(me->i_sum, me->l_sum, me->t)) + 0.5 * ((me->l_sum - Liso(me->i_sum, me->l_sum, me->t)) - 0.5 * Lhome(me->i_sum, me->l_sum, me->t)))) / 4822233) * STEP_SIZE;
            e1_u = me->e1 + ((me->s * (10 + me->b * (((0.5 * me->p_sum + me->i_sum) - Iiso(me->i_sum, me->l_sum, me->t)) - 0.5 * Ihome(me->i_sum, me->l_sum, me->t)) + 0.5 * ((me->l_sum - Liso(me->i_sum, me->l_sum, me->t)) - 0.5 * Lhome(me->i_sum, me->l_sum, me->t)))) / 4822233 - 0.25 * me->e1) * STEP_SIZE;
            e2_u = me->e2 + (0.25 * me->e1 - 0.25 * me->e2) * STEP_SIZE;
            p1_u = me->p1 + (0.25 * me->e2 - 1 * me->p1) * STEP_SIZE;
            p2_u = me->p2 + (1 * me->p1 - 1 * me->p2) * STEP_SIZE;
            i1_u = me->i1 + (1 * me->p2 - 0.1 * me->i1) * STEP_SIZE;
            i2_u = me->i2 + (0.1 * me->i1 - 0.1 * me->i2) * STEP_SIZE;
            l1_u = me->l1 + (0.1 * me->i2 - 0.1 * me->l1) * STEP_SIZE;
            l2_u = me->l2 + (0.1 * me->l1 - 0.1 * me->l2) * STEP_SIZE;
            r_u = me->r + 0.1 * (1 - 0.67 * 0.003) * me->l2 * STEP_SIZE;
            d_u = me->d + 0.1 * 0.67 * 0.003 * me->l2 * STEP_SIZE;
            cases_u = me->cases + 1 * me->p2 * STEP_SIZE;
            l2_sum_u = me->l2_sum + 1 * me->p2 * STEP_SIZE;
            p2_sum_u = me->p2_sum + 0.1 * me->l2 * STEP_SIZE;
            t_u = me->t + 1 * STEP_SIZE;

            i_sum_u = i1_u + i2_u;
            e_sum_u = e1_u + e2_u;
            p_sum_u = p1_u + p2_u;
            l_sum_u = l1_u + l2_u;
            g_u = Maxi(PGen(t_u), PtrSick(me->i_sum, me->l_sum), PtrHosp(me->i_sum, me->l_sum), PtrIcu(me->i_sum, me->l_sum));
            b_u = Beta(t_u, me->g);
            c_dot_u = 1 * p2_u;
            prob_u = FuncPow(1 - 0.4, 0.67 * 1 * p2_sum_u * 0.01) * FuncPow(1 - 0.5, 0.67 * 0.006 * 1 * p2_sum_u * 0.01) * FuncPow(1 - 0.1, 0.67 * 0.003 * 0.1 * l2_sum_u * 0.01);

            break;
    }

    // Update from intermediary variables
    me->s = s_u;
    me->e1 = e1_u;
    me->e2 = e2_u;
    me->p1 = p1_u;
    me->p2 = p2_u;
    me->i1 = i1_u;
    me->i2 = i2_u;
    me->l1 = l1_u;
    me->l2 = l2_u;
    me->r = r_u;
    me->d = d_u;
    me->prob = prob_u;
    me->c_dot = c_dot_u;
    me->cases = cases_u;

    me->t = t_u;
    me->b = b_u;
    me->p_sum = p_sum_u;
    me->i_sum = i_sum_u;
    me->l_sum = l_sum_u;
    me->l2_sum = l2_sum_u;
    me->p2_sum = p2_sum_u;
    me->e_sum = e_sum_u;
    me->g = g_u;

}