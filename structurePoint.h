#ifndef STRUCTUREPOINT_H
#define STRUCTUREPOINT_H

#include "params.h"

struct point
{
    gcry_mpi_t x;
    gcry_mpi_t y;
    gcry_mpi_t z;
};

struct point convert(struct point); // done
struct point double(struct point); // done
struct point summ(struct point, struct point); // done
struct point binaryForm(struct point, gcry_mpi_t); // done
// void onCurve(struct point) undone 
void equal(struct point) undone // done
// void neighbors(struct point);
void linear(struct point, gcry_mpi_t, gcry_mpi_t); // done

#endif
