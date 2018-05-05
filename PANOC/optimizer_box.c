#include "../globals/globals.h"
#include "panoc.h"
#include "function_evaluator.h"

#include"math.h"
#include<stdlib.h>
#include<stdio.h>

#include "../include/optimizer.h"
#include "constraints/constraint_functions.h"

static struct indicator_box_square_function* indicator_box_square_function_data; /* data related to the constraints used by the prox operator */


int optimizer_init_with_box(struct optimizer_problem* problem,real_t lower_bound,real_t upper_bound){

    /* prepare proxg(x) */
    constraint_functions_init_box(&indicator_box_square_function_data,problem->dimension,lower_bound,upper_bound);
    if(indicator_box_square_function_data==NULL) goto fail_1;
    problem->proxg=indicator_box_square_function_data->proxg;

    if(optimizer_init(problem)==FAILURE) goto fail_2;

    return SUCCESS;
     
    fail_2:
        constraint_functions_cleanup_box(indicator_box_square_function_data);
    fail_1:
        return FAILURE;
}