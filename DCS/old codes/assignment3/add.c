#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    
    const int N = 12; 
    
    int *array = NULL;
    int *local_data = NULL;
    int local_sum = 0;
    int total_sum = 0;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (N % size != 0) {
        if (rank == 0) {
            printf("Error: Array size must be divisible by the number of processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    chunk_size = N / size;

    local_data = (int*)malloc(chunk_size * sizeof(int));
    if (local_data == NULL) {
        printf("Process %d: Memory allocation failed.\n", rank);
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        array = (int*)malloc(N * sizeof(int));
        if (array == NULL) {
            printf("Process 0: Memory allocation failed.\n");
            MPI_Finalize();
            return 1;
        }

        printf("Original array elements: \n");
        for (int i = 0; i < N; i++) {
            array[i] = i + 1;
            printf("%d ", array[i]);
        }
        printf("\n\n");
    }

    MPI_Scatter(array, chunk_size, MPI_INT, 
                local_data, chunk_size, MPI_INT, 
                0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_data[i];
    }
    
    printf("Process %d calculated a local sum of %d\n", rank, local_sum);

    
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nFinal total sum: %d\n", total_sum);
    }

    if (rank == 0) {
        free(array);
    }
    free(local_data);

    MPI_Finalize();
    return 0;
}