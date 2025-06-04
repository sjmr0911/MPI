#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, data;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número total de procesos

    if (size < 2) {
        if (rank == 0)
            printf("Este programa requiere al menos 2 procesos.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        data = 100;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // Enviar a proceso 1
        printf("Proceso %d envió el valor %d al proceso 1.\n", rank, data);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Recibir de proceso 0
        printf("Proceso %d recibió el valor %d del proceso 0.\n", rank, data);
    }

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}
