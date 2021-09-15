#include <stdio.h>
#include "util_from_others.h"

// function to interpolate the given data points using Lagrange's formula
// xi corresponds to the new data point whose value is to be obtained
// n represents the number of known data points
float interpolate(struct Data f[], float xi, int n){
    float result = 0; // Initialize result
  
    for (int i=0; i<n; i++){
        // Compute individual terms of above formula
        float term = f[i].y;
        for (int j=0;j<n;j++){
            if (j!=i)
                term = term*(xi - f[j].x)/(float)(f[i].x - f[j].x);
        }
  
        // Add current term to result
        result += term;
    }
  
    return result;
}

void print_coefficients(float x_n[8], float y_n[8], int index){
    float coefficients[7];
    float newCoefficients[7];
    
    for(int m=0 ; m<7 ; ++m) coefficients[m]=0;

    for(int m=0 ; m<7 ; ++m){
        for(int nc=0 ; nc<7 ; ++nc) newCoefficients[nc]=0;

        if(m>0){
            newCoefficients[0]=-x_n[0]/(x_n[m]-x_n[0]);
            newCoefficients[1]=1/(x_n[m]-x_n[0]);
        }
        else{
            newCoefficients[0]=-x_n[1]/(x_n[m]-x_n[1]);
            newCoefficients[1]=1/(x_n[m]-x_n[1]);
        }

        int startIndex = 1;

        if(m==0) startIndex = 2;

        for(int n=startIndex ; n<7 ; ++n){
            if(m==n) continue;
            for(int nc=6 ; nc>=1 ; --nc){
                newCoefficients[nc]=newCoefficients[nc]*(-x_n[n]/(x_n[m]-x_n[n]))+newCoefficients[nc-1]/(x_n[m]-x_n[n]);
            }
            newCoefficients[0]=newCoefficients[0]*(-x_n[n]/(x_n[m]-x_n[n]));
        }
        for (int nc=0; nc<7; nc++) coefficients[nc]+=y_n[m]*newCoefficients[nc];
    }

    printf("Polynomial %d: ", index);
    for(int i=0 ; i<6 ; ++i)
        printf("%.1f,",coefficients[i]);
    printf("%.1f\n",coefficients[6]);
}
