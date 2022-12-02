#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int readcsv(double *x, double *y, char *file_path) {
    FILE *file = fopen(file_path, "r");
    size_t m = 0;

    if(file == NULL)
        return m;
    
    char c;
    char str[64];
    
    do {
        int i = 0;

        do {
            c = fgetc(file);
            if(c == '.' || c == '-' || isdigit(c)) {
                str[i++] = c;
            }
        } while(c == '-' || c == '.' || isdigit(c));
        str[i] = '\0';
        *x++ = atof(str);

        double *tmp = x;
        x = y;
        y = tmp;
        m += (c == ',');

    } while(c != EOF);

    return m;
}

double sq (double x) {
    return x * x;
}

double cost (int m, double *x, double *y, double theta1, double theta0) {
    double cost = 0;
    for(int i = 0 ; i < m ; i++) {
        cost += sq(x[i] * theta1 + theta0 - y[i]) / (2 * m);
    }

    return cost;
}

void gradient_function (int m, double *x, double *y, double theta1, double theta0, double *gradient) {
    gradient[0] = 0;
    gradient[1] = 0;

    for(int i = 0 ; i < m ; i++) {
        gradient[0] += (x[i] * theta1 + theta0 - y[i]) * x[i] / m;
        gradient[1] += (x[i] * theta1 + theta0 - y[i]) / m;
    }
}

void gradient_descent (int m, double *x, double *y, double *theta1, double *theta0, int steps, double alpha) {
    for(int i = 0 ; i < steps ; i++) {
        double gradient[2];
        gradient_function(m, x, y, *theta1, *theta0, gradient);
        *theta1 += -alpha * gradient[0];
        *theta0 += -alpha * gradient[1];
    }
}

int main() {

    double x[100];
    double y[100];
    char file_path[] = "data/ex1data1.csv";
    int m = readcsv(x, y, file_path);

    printf("Cost in (0, 0): %lf\n", cost(m, x, y, 0, 0));

    double gradient[2];
    gradient_function(m, x, y, 0, 0, gradient);
    printf("Gradient in (0, 0): (%lf, %lf)\n", gradient[0], gradient[1]);

    int steps = 1500;
    double theta1 = 0;
    double theta0 = 0;
    double alpha = 0.01;
    gradient_descent(m, x, y, &theta1, &theta0, steps, alpha);
    
    printf("theta1 = %lf, theta0 = %lf, cost = %lf\n", theta1, theta0, cost(m, x, y, theta1, theta0));

    return 0;
}