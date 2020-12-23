#include "structurePoint.h"

struct point convert(struct point point) // projectile -> affine
{
    
    gcry_mpi_t x = gcry_mpi_new(0);
    x = point.x;
    gcry_mpi_t y = gcry_mpi_new(0);
    y = point.y;
    gcry_mpi_t z = gcry_mpi_new(0);
    z = point.z;

    struct point newpoint;
    newpoint.x = gcry_mpi_new(0);
    newpoint.y = gcry_mpi_new(0);
    newpoint.z = gcry_mpi_new(0);

    gcry_mpi_t extra = gcry_mpi_new(0);
    
    gcry_mpi_invm(extra, z, p); 
    gcry_mpi_mulm(newpoint.x, x, extra, p); 
    gcry_mpi_mulm(newpoint.y, y, extra, p); 
    newpoint.z = one; // -------------------invertion
  
    return newpoint;
    
    gcry_mpi_release(x);
    gcry_mpi_release(y);
    gcry_mpi_release(z);
    gcry_mpi_release(buff);
}

struct point double(struct point f)
{
    gcry_mpi_t x1 = gcry_mpi_new(0);
    x1 = f.x;
    gcry_mpi_t y1 = gcry_mpi_new(0);
    y1 = f.y;
    gcry_mpi_t z1 = gcry_mpi_new(0);
    z1 = f.z;
    gcry_mpi_t buff = gcry_mpi_new(0);

    gcry_mpi_t B = gcry_mpi_new(0);
    gcry_mpi_addm(buff, x1, y1, p);
    gcry_mpi_powm(B, buff, two, p);
    
    gcry_mpi_t C = gcry_mpi_new(0);
    gcry_mpi_powm(C, x1, two, p);
    
    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_powm(D, y1, two, p);

    gcry_mpi_t E = gcry_mpi_new(0);
    gcry_mpi_mulm(E, a, C, p);
    
    gcry_mpi_t F = gcry_mpi_new(0);
    gcry_mpi_addm(F, E, D, p);
    
    gcry_mpi_t H = gcry_mpi_new(0);
    gcry_mpi_powm(H, z1, two, p);
    
    gcry_mpi_t J = gcry_mpi_new(0);
    gcry_mpi_mulm(buff, two, H, p);
    gcry_mpi_subm(J, F, buff, p);

    struct point newpoint;
    newpoint.x = gcry_mpi_new(0);
    newpoint.y = gcry_mpi_new(0);
    newpoint.z = gcry_mpi_new(0);
    gcry_mpi_subm(buff, B, C, p);
    gcry_mpi_subm(buff, buff, D, p);
    gcry_mpi_mulm(newpoint.x, buff, J, p);
    gcry_mpi_subm(buff, E, D, p);
    gcry_mpi_mulm(newpoint.y, F, buff, p);
    gcry_mpi_mulm(newpoint.z, F, J, p);
    
    newpoint = convert(newpoint);
    return newpoint;
}

struct point summ(struct point point1, struct point point2)
{
    gcry_mpi_t x1 = gcry_mpi_new(0);
    x1 = point1.x;
    gcry_mpi_t y1 = gcry_mpi_new(0);
    y1 = point1.y;
    gcry_mpi_t x2 = gcry_mpi_new(0);
    x2 = point2.x;
    gcry_mpi_t y2 = gcry_mpi_new(0);
    y2 = point2.y;
    
    gcry_mpi_t buff = gcry_mpi_new(0);
    gcry_mpi_t buff2 = gcry_mpi_new(0);

    gcry_mpi_t C = gcry_mpi_new(0);
    gcry_mpi_mulm(C, x1, x2, p); 

    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_mulm(D, y1, y2, p); 
    
    gcry_mpi_t E = gcry_mpi_new(0);
    gcry_mpi_mulm(buff, d, C, p); 
    gcry_mpi_mulm(E, buff, D, p); 

    struct point newpoint;
    newpoint.x = gcry_mpi_new(0);
    newpoint.y = gcry_mpi_new(0);
    gcry_mpi_addm(buff, x1, y1, p);
    gcry_mpi_addm(buff2, x2, y2, p);
    gcry_mpi_mulm(buff, buff, buff2, p);
    gcry_mpi_subm(buff, buff, C, p);
    gcry_mpi_subm(buff, buff, D, p);
    gcry_mpi_subm(buff2, one, E, p);
    gcry_mpi_mulm(newpoint.x, buff2, buff, p);
    gcry_mpi_addm(buff, one, E, p);
    gcry_mpi_mulm(buff2, a, C, p);
    gcry_mpi_subm(buff2, D, buff2, p);
    gcry_mpi_mulm(newpoint.y, buff, buff2, p);
    gcry_mpi_powm(buff, E, two, p);
    gcry_mpi_subm(newpoint.z, one, buff, p);

    newpoint = convert(newpoint);
    return newpoint;

}

struct point binaryForm(struct point point, gcry_mpi_t seed)
{
    size_t scanned;
    struct point newpoint;
    gcry_mpi_t null = gcry_mpi_new(0);
    gcry_mpi_scan(&null, GCRYMPI_FMT_HEX, "0", 0, &scanned);
    newpoint.x = gcry_mpi_new(0);
    newpoint.x = null;
    newpoint.y = gcry_mpi_new(0);
    newpoint.y = one;
    newpoint.z = gcry_mpi_new(0);
    newpoint.z = one;

    unsigned long int i;
    unsigned long int iterator = gcry_mpi_get_nbits(seed) - 1;
    for(i = iterator; i > 0; --i)
    {
        newpoint = double(newpoint);
        if(gcry_mpi_test_bit(seed, i) == 1)
        {
            newpoint = summ(newpoint, point);
        }
        
        if(i == 1)
        {
            newpoint = double(newpoint);
            if(gcry_mpi_test_bit(seed, i-1) == 1)
            {
                newpoint = summ(newpoint, point);
            }    
        }
    }
    return newpoint;    
}


void equal(struct point point) 
{
    gcry_mpi_t x = gcry_mpi_new(0);
    x = point.x;
    gcry_mpi_t y = gcry_mpi_new(0);
    y = point.y;
    gcry_mpi_t z = gcry_mpi_new(0);    
    z = point.z;
    
    if ((gcry_mpi_cmp_ui(x, 0) == 0) && (gcry_mpi_cmp_ui(y, 1) == 0) && (gcry_mpi_cmp_ui(z, 1) == 0))
    {
        printf(1);    
    }
    else
    {
        printf(0);
    }
}


void linear(struct point point, gcry_mpi_t k1, gcry_mpi_t k2)
{
    struct point first, second;
    gcry_mpi_t buff = gcry_mpi_new(0);
    gcry_mpi_addm(buff, k1, k2, p);

    first = summ(binaryForm(point, k1), binaryForm(point, k2)); 
    second = binaryForm(point, buff);

    if (!gcry_mpi_cmp(first.x, second.x) && !gcry_mpi_cmp(first.y, second.y) && !gcry_mpi_cmp(first.z, second.z))
    {
        printf(1);    
    }
    else
    {
        printf(0);
    }
}
