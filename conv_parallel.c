#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here
    int *R = malloc(sizeof(int) * (NA - NF + 1));

   
    omp_set_num_threads(8);
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < NA - NF + 1; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[i+j]*F[NF - j - 1];
        }
        R[i] = sum;
        printf("%d\n", sum);
    }

    // ---- free memory ----
    free(F);
    free(A);
    free(R);
    // ---- end free ----
    return 0;
}