/*Created by Shubin Nikita -> GitHub: YourMonika
 * CoSec 172
 * PAZI
 * Edwards Curve
 * lib gcrypt
 */

#ifndef CURVES_STRUCTURES_H
#define CURVES_STRUCTURES_H
#include <gcrypt.h>

/*
 *                                             PARAMETERS
 */
gcry_mpi_t p;
gcry_mpi_t a;
gcry_mpi_t d;
gcry_mpi_t q;
gcry_mpi_t u;
gcry_mpi_t v;

gcry_mpi_t zero;
gcry_mpi_t one;
gcry_mpi_t two;

void set_params();
void release_memory();

/*
 *                                            PARAMETERS
 *
 *                                            STRUCTS
 *                                            &
 *                                            FUNCTIONS
 */

typedef struct{
    gcry_mpi_t X;
    gcry_mpi_t Y;
    gcry_mpi_t Z;
} point;

void transform_p(point * Point); // project -> affine
point add_p(const point * Point1, const point * Point2); // addition
point double_p(const point * Point); // doubling season
point binaryMethod(const point * Point, gcry_mpi_t I); // solving binary point

void ifOnCurve(const point * Point);
void ifIdentity(const point * Point);
void checkNeighbors(point Point);
void ifLinear(point * Point, gcry_mpi_t k1, gcry_mpi_t k2);

#endif //CURVES_STRUCTURES_H
