#include <stdio.h>
#include "structures.h"
#include "structures.c"
#include <sys/types.h>

int main() {
    printf("Hello, World!\n");
    set_params();

    size_t scanned;
    gcry_mpi_t uno = gcry_mpi_new(0);
    gcry_mpi_scan(&uno, GCRYMPI_FMT_HEX, "F", 0, &scanned);
    gcry_mpi_t duo = gcry_mpi_new(0);
    gcry_mpi_scan(&duo, GCRYMPI_FMT_HEX, "4", 0, &scanned);

    point check;
    point j = {u, v, duo};

    check = binaryMethod(&j, q);
    ifOnCurve(check);
    ifIdentity(check);
    checkNeighbors(check);
    ifLinear(j, uno, duo);

    release_memory();

    return 0;
}