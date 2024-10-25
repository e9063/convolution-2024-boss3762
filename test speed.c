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

    double time_parallel_start = omp_get_wtime();
    omp_set_num_threads(8);
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < NA - NF + 1; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[i+j]*F[NF - j - 1];
        }
        R[i] = sum;
    }
    // for(int i = 0; i < NA - NF + 1; i++){
    //     printf("%d\n", R[i]);
    // }
    double time_parallel_end = omp_get_wtime();
    

    int *R2 = malloc(sizeof(int) * (NA - NF + 1));

    double time_sequential_start = omp_get_wtime();
    int countt = 0;
    for(int i = 0; i < NA; i++){
        int sum = 0;
        for(int j = 0; j < NF; j++){
            sum += A[i+j]*F[NF - j - 1];
        }
        R2[i] = sum;
        //printf("%d\n", sum);
        countt++;
        if(countt == NA - NF+1){
            break;
        }
    }
    double time_sequential_end = omp_get_wtime();

    printf("Seq time: %.6f\n", time_sequential_end - time_sequential_start);
    printf("Paral time: %.6f\n", time_parallel_end - time_parallel_start);
    printf("Speed: %.6f\n", (time_sequential_end - time_sequential_start) / (time_parallel_end - time_parallel_start));
    // ---- free memory ----
    free(F);
    free(A);
    free(R);
    free(R2);
    // ---- end free ----
    return 0;
}