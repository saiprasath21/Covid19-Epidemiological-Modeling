#include "plant.h"
#include "functions.h"
#include<math.h>
#include<time.h>
#define R 50000
#define C 10

double data[R][C];

static double Initialize(double r0, double t, double total_cases, double population, double initial_cases, double initial_case_distribution_factor, double subclinical, double c_iso, double c_subclinical, double p_hosp, double mean_hosp, double g_shape, double g_scale, double iso_mean, double onset_shape, double onset_scale, double reporting_shape, double reporting_scale, double end_active, double control_efficiency) {


    for(int i=0;i<R;i++)for(int j=0;j<C;j++)data[i][j]=-1;
    
    double subclinical_cases = poisson((initial_cases) * subclinical / (1 - subclinical));
    //initial_cases = 10.0;subclinical_cases=0.0;
    //printf("Subclinical Cases: %lf \n", subclinical_cases);
    
    for(int i=0;i<initial_cases + subclinical_cases;i++) //initializing all the case data for the outbreak model
    {
    data[i][0] = 1; //active or not
    
    if(i<initial_cases){data[i][1]=0;}
    else data[i][1]=1;
    //else if(i<100) data[i][2] = -1; //exposure time
    //else if(i<200) data[i][2] = -2;
    //else if(i<300) data[i][2] =-3;
    //if(i<10){data[i][2]=-7;} 500 - 6 - 4
    if(i<200){data[i][2]=-8;}
    else if(i<500){data[i][2]=-6;}
    else if(i<900){data[i][2]=-4;}
    else data[i][2] = -1 * rand()%2;
    if(data[i][1]==0) // is the person is clinical otherwise he/she remains undetected for the whole time (12 effectively but 30)
    {
      //printf("Found a clinical case \n");
      data[i][3] = gamma_sampling(onset_shape, onset_scale);
      //data[i][4] = hosp_calc(p_hosp);
      if(hosp_calc(p_hosp)) // if the person is hospitalized
      {
        data[i][5] = exponential(1/mean_hosp); //determining the length of hospitalization
        //data[i][8] = 0; //report immediatly after hospitalized (assuming no delay)
      }
      else
      {
        data[i][7] = exponential(1/iso_mean);
        data[i][9] = gamma_sampling(reporting_shape, reporting_scale);
        //printf("Delay: %lf \n", data[i][9]);
      }

    }    
    }
    
    /*
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)printf("%lf  ", data[i][j]);
      printf("\n");
    }
    */
    
    
    for(int i=0;i<initial_cases + subclinical_cases;i++) //checking active, hospitalized, isolated and reported
    {
      if(data[i][0]==1){  
     
      if(data[i][2] + end_active < t){//printf("Time up Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
      data[i][0]=0;} //not active anymore; but not reported
      else if(data[i][1]==0) // not valid for subclinical cases
      {
        if(t > data[i][2] + data[i][3] && data[i][5]!=-1){//printf("Hosp Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
        data[i][4]=1; data[i][8]=1;} // the person is hospitalized; case reported
        if(t > data[i][2] + data[i][3] + data[i][7] && data[i][7]!=-1 && data[i][6]==-1)data[i][6]=1; //person is isolated
        if(t > data[i][2] + data[i][3] + data[i][7] + data[i][9] && data[i][6]==1){//printf("Reported Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
        data[i][8]=1;data[i][0]=0;data[i][6]=0;}
        //case reported; no more active; completed isolation;
      }
      }
      
       if(t > data[i][2] + data[i][3] + data[i][5] && data[i][4]==1){data[i][4]=0;data[i][0]=0;} //discharged from the hospital; not active anymore; (to keep count of active hospitalized people)
    }
    
    
    return initial_cases + subclinical_cases;
}

static double OutbreakStep(double r0, double t, double total_cases, double population, double initial_cases, double initial_case_distribution_factor, double subclinical, double c_iso, double c_subclinical, double p_hosp, double mean_hosp, double g_shape, double g_scale, double iso_mean, double onset_shape, double onset_scale, double reporting_shape, double reporting_scale, double end_active, double control_efficiency) {

    printf("************************* Entering Outbreak at time %lf *************************  %lf \n", t, r0);
    double new_cases = 0;double l=0.0;
    
    /* Manually setting the parameter values
    if(t<25){r0=0.8;control_efficiency=0.52;}
    else {r0=1.3;control_efficiency=0.32;}
    */
    
    for(int i=0;i<total_cases;i++) //checking active, hospitalized, isolated and reported
    {
      if(data[i][0]==1){  
     
      if(data[i][2] + end_active < t){//printf("Time up Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
      data[i][0]=0;} //not active anymore; but not reported
      else if(data[i][1]==0) // not valid for subclinical cases
      {
        if(t > data[i][2] + data[i][3] && data[i][5]!=-1){//printf("Hosp Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
        data[i][4]=1; data[i][8]=1;} // the person is hospitalized; case reported
        if(t > data[i][2] + data[i][3] + data[i][7] && data[i][7]!=-1 && data[i][6]==-1)data[i][6]=1; //person is isolated
        if(t > data[i][2] + data[i][3] + data[i][7] + data[i][9] && data[i][6]==1){//printf("Reported Case: %d exposed at %lf not active at time %lf \n", i, data[i][2], t);
        data[i][8]=1;data[i][6]=0;}
        //case reported; no more active; completed isolation;
      }
      }
      
       if(t > data[i][2] + data[i][3] + data[i][5] && data[i][4]==1){data[i][4]=0;data[i][0]=0;} //discharged from the hospital; not active anymore; (to keep count of active hospitalized people)
    }
    
   
    // generating new cases
    for(int i=0; i<total_cases; i++)
    {
      if(data[i][0]==1)//if the case is active
      {
        if(data[i][1]==0)//if the case is clinical
        {
          if(data[i][4]==1 || data[i][8]==1) continue;//hospitalized or reported cases can't contribute (note that the case is not active)
          else 
          {
             //whether or not the person is isolated is taken care in lambda definition
            l = lambda_calc(r0, total_cases, population, t, data[i][2] + data[i][3] + data[i][7], data[i][2], c_iso , g_shape, g_scale, control_efficiency);
            //printf("%lf %lf %lf %lf %lf %lf %lf %lf \n", r0, total_cases, population, t, data[i][2] + data[i][3] + data[i][7], c_iso , g_shape, g_scale );
            //printf("Lambda for clinical: %lf \n", l);
            double x = (poisson(l));
            new_cases += x;
            //printf("Newcases from clinical case %d: %lf   Exposed: %lf \n", i, x, data[i][2]);
            //printf("Newcases from clinical population: %lf \n", (double)new_cases);
          }
        }
        else
        {
        //subclinical case directly generate the new number of cases; no isolation; only 50% that of clinical cases in contagiousness
            l = lambda_calc(c_subclinical * r0, total_cases, population, t, data[i][2] + data[i][3] + data[i][7], data[i][2], 1.0 , g_shape, g_scale, control_efficiency);
            //printf("Lambda for subclinical: %lf \n", l);
            double x = (poisson(l));
            new_cases += x;
            //printf("Newcases from sub-clinical case %d: %lf   Exposed: %lf \n", i, x, data[i][2]);
            //printf("Newcases from subclinical population: %lf \n", (double)new_cases);
        }
      }
      
      else continue;
    
    }
    
    if(t==107)
    {
      new_cases+=0;
    }
    
    //assigning values to new cases
    //printf("Assigning values to new cases: \n");
   // new_cases += 10.0;
    for(int i=total_cases;i<total_cases + new_cases; i++) //initializing all the case data for the outbreak model
    {
    data[i][0] = 1; //active or not
    data[i][1] = subclinical_calc(subclinical);
    //printf("Case ID: %d --> %lf \n", i, data[i][1]);
    data[i][2] = t; //exposure time
    if(data[i][1]==0) // is the person is clinical otherwise he/she remains undetected for the whole time (12 effectively but 30)
    {
      //printf("Found a clinical case \n");
      data[i][3] = gamma_sampling(onset_shape, onset_scale);
      //data[i][4] = hosp_calc(p_hosp);
      if(hosp_calc(p_hosp)) // if the person is hospitalized
      {
        data[i][5] = exponential(1/mean_hosp); //determining the length of hospitalization
        //data[i][8] = 0; //report immediatly after hospitalized (assuming no delay)
      }
      else
      {
        data[i][7] = exponential(1/iso_mean);
        data[i][9] = gamma_sampling(reporting_shape, reporting_scale);
      }

    }    
    }
    
    
    printf("Total new cases in this step: %lf \n",(double)new_cases);
    /*
    for(int i=0;i<total_cases + new_cases; i++)
    {
      for(int j=0;j<C;j++)
        printf("%lf  ", data[i][j]);
      printf("\n");
    }
    */
    printf("Total cases: %lf  at time: %lf\n",total_cases + (double)new_cases, t);
    return total_cases + (double)new_cases;
}

static double CalcActive(double t) {// active and clinical

    int sum = 0;
    for(int i=0;i<R;i++)
    {
      //if(data[i][0]==1 && data[i][1]==0)sum++;
      if((data[i][8]==1 && t < data[i][2]+data[i][3]+data[i][7]+data[i][9] + 14 && data[i][7]!=-1)||(data[i][4]==1))sum++;
      //if((data[i][8]==1 && (t-20) < data[i][2]+data[i][3]+data[i][7]+data[i][9] && data[i][7]!=-1)||(data[i][4]==1))sum++;
    }
    return sum;
}

static double CalcReported() {// only clinical cases are reported

    int sum = 0;
    for(int i=0;i<R;i++)
    {
      if(data[i][8]==1)sum++;
    }
    return sum;
}


static double Calcend(double t) {// only cases that might die

    int sum = 0;
    for(int i=0;i<R;i++)
    {
      if(data[i][1]==1 && data[i][0]==0)sum++;
    }
    return sum;
}

static double calchosp() {// only clinical cases are reported

    int sum = 0;
    for(int i=0;i<R;i++)
    {
      if(data[i][4]==0)sum++;
    }
    return sum;
}


// Plant Initialisation function
void PlantInit(Plant* me) {
    // Initialise State
    me->state = PLANT_MODEL;

    // Initialise Outputs
    me->active_cases = 452 * 0.67;
    me->new_cases = 0.0;
    // Initialise Internal Variables
    me->t = 0;
    //actual value: 730
    me->total_cases = Initialize(me->r0, me->t, me->total_cases, 4822233, 840.0, 4.8, 0.33, 0.65, 0.5, 0.0525, 10, 5.67, 2.83, 6.0, 6.0, 0.95, 1, 3.48, 30, me->control_efficiency);
    //me->total_cases = Initialize(2.5, me->t, me->total_cases, 4822233, 870.0, 4.8, 0.33, 0.65, 0.5, 0.0525, 10, 5.67, 2.83, 6.0, 6.0, 0.95, 1, 3.48, 30, me->control_efficiency);
    me->c_dot = CalcReported();
    me->clinical_cases = CalcReported();
    me->active_cases = CalcActive(0);
    me->dead_cases = (Calcend(0) + CalcReported())*0.01;
}

// Plant Execution function
void PlantRun(Plant* me) {
    // Create intermediary variables
    enum PlantStates state_u = me->state;
    double active_cases_u = me->active_cases;
    double c_dot_u = me->c_dot;

    double t_u = me->t;
    double total_cases_u = me->total_cases;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case PLANT_MODEL: // Logic for state model
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->active_cases = active_cases_u;
    me->c_dot = c_dot_u;

    me->t = t_u;
    me->total_cases = total_cases_u;

    double sub=0;
    // Intra-location logic for every state
    switch(me->state) {
        case PLANT_MODEL: // Intra-location logic for state model
            t_u = me->t + 1 * STEP_SIZE;
            sub = Calcend(me->t);
            c_dot_u = CalcReported();
            me->new_cases = total_cases_u;
            total_cases_u = OutbreakStep(me->r0, t_u, me->total_cases, 4822233 , 840.0, 4.8, 0.33, 0.65, 0.5, 0.0525, 10, 5.67, 2.83, 6.0, 6.0, 0.95, 1, 3.48, 30, me->control_efficiency);
            //total_cases_u = OutbreakStep(2.5, t_u, me->total_cases, 4822233 , 870.0, 4.8, 0.33, 0.65, 0.5, 0.0525, 10, 5.67, 2.83, 6.0, 6.0, 0.95, 1, 3.48, 30, me->control_efficiency);
            me->new_cases = total_cases_u - me->new_cases;
            active_cases_u = CalcActive(t_u);
            //c_dot_u = CalcReported();
            c_dot_u = CalcReported() - c_dot_u;
            sub = Calcend(t_u) - sub;
            break;
    }

    // Update from intermediary variables
    me->active_cases = active_cases_u;
    if(0.0125 * me->active_cases/0.67 > 300) me->dead_cases += (c_dot_u + sub) * 0.02;
    else me->dead_cases += (c_dot_u + sub) * 0.01;
    me->c_dot = c_dot_u;
    me->clinical_cases = CalcReported();
    me->t = t_u;
    me->total_cases = total_cases_u;

}
