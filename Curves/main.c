#include <stdio.h>
#include "structures.c"
#include "structures.h"
#include <sys/types.h>
#include <gcrypt.h>
int main() {
    printf("Hello, World!\n");
    set_params();

    point Point;
    init_p(&Point);
    Point.X = u;
    Point.Y = v;
    Point.Z = one;
    printf("point \"Point\" created, initialized\n\n");
    point check;
    init_p(&check);
    printf("point \"check\" created\n\n");
    
    gcry_mpi_t rand1 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand1, 256, GCRY_STRONG_RANDOM);
    gcry_mpi_t rand2 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand2, 256, GCRY_STRONG_RANDOM);
    printf("randoms mpi_t initialized\n\n");

    check = binaryMethod(&Point, &rand1);
    printf("point \"check\" initialized\n\n\n");
    
    ifOnCurve(&check);
    
    check = binaryMethod(&Point, &q);
    ifIdentity(&check);

    checkNeighbors(Point);

    ifLinear(&check, &rand1, &rand2);


    release_memory();

    return 0;
}
