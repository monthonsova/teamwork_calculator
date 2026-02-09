#include <stdio.h>
#include <math.h>

typedef struct Cal {
    double *numArr;
    char   *op;
    int     numCount;
    int     opCount;
} Cal;


Cal inputEvaluate(char *input);
double calculate(Cal cal);

int main(void) {

    printf("test");
    
    return 0;
}

Cal inputEvaluate(char *input) {
    
    Cal evaluated;
    return evaluated;
}

double calculate(Cal cal) {
    
    return 0.0;
}