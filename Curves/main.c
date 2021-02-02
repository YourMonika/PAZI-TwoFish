#include <stdio.h>
#include "structures.h"
#include <sys/types.h>

int main() {
    printf("Hello, World!\n");
    set_params();

    point Point;
    init_p(&Point);
    Point.X = u;
    Point.Y = v;
    Point.Z = one;

    point check;
    init_p(&check);

    gcry_mpi_t rand1 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand1, 256, GCRY_STRONG_RANDOM);
    gcry_mpi_t rand2 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand2, 256, GCRY_STRONG_RANDOM);

    check = binaryMethod(&Point, rand1);
    ifOnCurve(&check);

    check = binaryMethod(&Point, q);
    ifIdentity(&check);

    checkNeighbors(Point);

    ifLinear(&Point, rand1, rand2);


    release_memory();

    return 0;
}