#include <stdio.h>
#include <gcrypt.h>
#include <sys/types.h>
#include "structurePoint.h"

int main()
{
    size_t scanned;
    gcry_mpi_t U = gcry_mpi_new(0);
    gcry_mpi_scan(&U, GCRYMPI_FMT_HEX, "1", 0, &scanned);
    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_scan(&D, GCRYMPI_FMT_HEX, "2", 0, &scanned);
    settings();
    struct point point1; 
    struct point j = {u, v, D};

    point1 = binaryForm(point2, q);
    equal(point1);
    linear(point2, U, D);

    save();
}
