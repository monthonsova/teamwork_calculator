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

    char input[256];
    scanf("%[^\n]s", input);
    Cal result = inputEvaluate(input);
    double finalResult = calculate(result);
    printf("Final Result: %.6f\n", finalResult);
    
    return 0;
}

Cal inputEvaluate(char *input) {
    int index = 0;
    int startIntNumber = 0;
    int numberCount = 0;
    double *numArr = new double[100];
    char *op = new char[50];
    int opIndex = 0;

    while (input[index] != '\0') {
        if(input[index] != '+' && input[index] != '-' && input[index] != '*' && input[index] != '/' && input[index] != '%' && input[index] != '.') {
            index++;
            continue; 
        } 
        
        if(input[index] != '.') {
            double number = 0;
            int dotPos = -1;

            for(int i = startIntNumber; i < index; i++) {
                if(input[i] == '.') {
                    dotPos = i;
                    break;
                }
            }

            if(dotPos == -1) { 
                for(int i = startIntNumber; i < index; i++) {
                    number = number * 10 + (input[i] - '0');
                }
            } else {
                for(int i = startIntNumber; i < dotPos; i++) {
                    number = number * 10 + (input[i] - '0');
                }
                double expo = 1;
                for(int i = dotPos + 1; i < index; i++) {
                    number += (input[i] - '0') * pow(10, -expo);
                    expo++;
                }
            }

            numArr[numberCount++] = number;
            startIntNumber = index + 1;
        }
        if(input[index] == '+' || input[index] == '-' || input[index] == '*' || input[index] == '/' || input[index] == '%') {
            op[opIndex] = input[index];
            opIndex++;
        }
        index++;
    }

    if (startIntNumber < index) {
        double lastNumber = 0;
        int dotPos = -1;

        for (int i = startIntNumber; i < index; i++) {
            if (input[i] == '.') {
                dotPos = i;
                break;
            }
        }

        if (dotPos == -1) {
            for (int i = startIntNumber; i < index; i++) {
                lastNumber = lastNumber * 10 + (input[i] - '0');
            }
        } else {
            for (int i = startIntNumber; i < dotPos; i++) {
                lastNumber = lastNumber * 10 + (input[i] - '0');
            }
            double divisor = 10;
            for (int i = dotPos + 1; i < index; i++) {
                lastNumber += (input[i] - '0') / divisor;
                divisor *= 10;
            }
        }
        
        numArr[numberCount] = lastNumber;
        numberCount++; 
    }
    

    Cal evaluated;
    evaluated.numArr = numArr;
    evaluated.op = op;
    evaluated.numCount = numberCount;
    evaluated.opCount = opIndex;
    return evaluated;

}
double calculate(Cal cal) {
    double *nums = cal.numArr;
    char *ops = cal.op;
    int numCount = cal.numCount;
    int opCount = cal.opCount;
    

    for (int i = 0; i < opCount; i++) {
        if (ops[i] == '*' || ops[i] == '/' || ops[i] == '%') {
            double result = 0;
            
            if (ops[i] == '*') {
                result = nums[i] * nums[i + 1];
            } else if (ops[i] == '/') {
                result = nums[i] / nums[i + 1];
            } else if (ops[i] == '%') {
                result = (int)nums[i] % (int)nums[i + 1];
            }
            
         
            nums[i] = result;
            for (int j = i + 1; j < numCount - 1; j++) {
                nums[j] = nums[j + 1];
            }
            
      
            for (int j = i; j < opCount - 1; j++) {
                ops[j] = ops[j + 1];
            }
            
            numCount--;
            opCount--;
            i--; 
        }
    }
    
 
    for (int i = 0; i < opCount; i++) {
        if (ops[i] == '+') {
            nums[i] = nums[i] + nums[i + 1];
        } else if (ops[i] == '-') {
            nums[i] = nums[i] - nums[i + 1];
        }
        
   
        for (int j = i + 1; j < numCount - 1; j++) {
            nums[j] = nums[j + 1];
        }
        

        for (int j = i; j < opCount - 1; j++) {
            ops[j] = ops[j + 1];
        }
        
        numCount--;
        opCount--;
        i--; 
    }
    
    return nums[0];
}