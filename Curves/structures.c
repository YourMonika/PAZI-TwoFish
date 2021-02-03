/*Created by Shubin Nikita -> GitHub: YourMonika
 * CoSec 172
 * PAZI
 * Edwards Curve
 * lib gcrypt
 */

#include "structures.h"
#include <gcrypt.h>
/*
 *                                     PARAMETERS
 */
void init_p(point *P){
    P->X = gcry_mpi_new(0);
    P->Y = gcry_mpi_new(0);
    P->Z = gcry_mpi_new(0);
}

void release_p(point* P){
    gcry_mpi_release(P->X);
    gcry_mpi_release(P->Y);
    gcry_mpi_release(P->Z);
}


void set_params(){
    // Parameters been get from id-tc26-gost-3410-2012-256-paramSetA
    // https://docplayer.ru/46408167-Tehnicheskiy-komitet-026-zadanie-parametrov-skruchennyh-ellipticheskih-krivyh-edvardsa-v-sootvetstvii-s-gost-r.html

    size_t scanned;
    p = gcry_mpi_new(0);
    a = gcry_mpi_new(0);
    d = gcry_mpi_new(0);
    q = gcry_mpi_new(0);
    u = gcry_mpi_new(0);
    v = gcry_mpi_new(0);

    gcry_mpi_scan(&p, GCRYMPI_FMT_HEX, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97", 0, &scanned);
    gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "1", 0, &scanned);
    gcry_mpi_scan(&d, GCRYMPI_FMT_HEX, "605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB", 0, &scanned);
    gcry_mpi_scan(&q, GCRYMPI_FMT_HEX, "400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67", 0, &scanned);
    gcry_mpi_scan(&u, GCRYMPI_FMT_HEX, "D", 0, &scanned);
    gcry_mpi_scan(&v, GCRYMPI_FMT_HEX, "60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7", 0, &scanned);

    /*
    gcry_mpi_scan(&p, GCRYMPI_FMT_HEX, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDC7", 0, &scanned);
    
    gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "1", 0, &scanned);    

    gcry_mpi_scan(&d, GCRYMPI_FMT_HEX, "9E4F5D8C017D8D9F13A5CF3CDF5BFE4DAB402D54198E31EBDE28A0621050439CA6B39E0A515C06B304E2CE43E79E369E91A0CFC2BC2A22B4CA302DBB33EE7550", 0, &scanned);    
    
    gcry_mpi_scan(&q, GCRYMPI_FMT_HEX, "3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC98CDBA46506AB004C33A9FF5147502CC8EDA9E7A769A12694623CEF47F023ED", 0, &scanned);    
    
    gcry_mpi_scan(&u, GCRYMPI_FMT_HEX, "12", 0, &scanned);    
    
    gcry_mpi_scan(&v, GCRYMPI_FMT_HEX, "469AF79D1FB1F5E16B99592B77A01E2A0FDFB0D01794368D9A56117F7B38669522DD4B650CF789EEBF068C5D139732F0905622C04B2BAAE7600303EE73001A3D", 0, &scanned);

     */
    two = gcry_mpi_new(0);
    one = gcry_mpi_new(0);
    zero = gcry_mpi_new(0);

    gcry_mpi_scan(&two, GCRYMPI_FMT_HEX, "2", 0, &scanned);
    gcry_mpi_scan(&one, GCRYMPI_FMT_HEX, "1", 0, &scanned);
    gcry_mpi_scan(&zero, GCRYMPI_FMT_HEX, "0", 0, &scanned);
}

void release_memory()
{
    gcry_mpi_release(p);
    gcry_mpi_release(a);
    gcry_mpi_release(d);
    gcry_mpi_release(q);
    gcry_mpi_release(u);
    gcry_mpi_release(v);
    gcry_mpi_release(zero);
    gcry_mpi_release(one);
    gcry_mpi_release(two);
}

/*
 *                                           PARAMETERS
 *
 *                                           FUNCTIONS
 */

/*
 * simplification of gcry-funcs
 */
void transform_p(point * Point){
    gcry_mpi_t tempo = gcry_mpi_new(0);
    if (gcry_mpi_cmp(Point->Z, zero) != 0){
        //x = X/Z
        gcry_mpi_invm(tempo, Point->Z, p);
        gcry_mpi_mulm(Point->X, Point->X, tempo, p);
        //y = Y/Z
        gcry_mpi_mulm(Point->Y, Point->Y, tempo, p);
        Point->Z = one;
    }
}

point add_p(const point * Point1, const point * Point2){
    point Point3;
    init_p(&Point3);
    
    gcry_mpi_t X1 = gcry_mpi_new(0);
    gcry_mpi_t Y1 = gcry_mpi_new(0);
    gcry_mpi_t X2 = gcry_mpi_new(0);
    gcry_mpi_t Y2 = gcry_mpi_new(0);
    X1 = Point1->X;
    Y1 = Point1->Y;
    X2 = Point2->X;
    Y2 = Point2->Y;

    gcry_mpi_t tem1 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem1, X1, X2, p);

    gcry_mpi_t tem2 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem2, Y1, Y2, p);

    gcry_mpi_t tempo1 = gcry_mpi_new(0);
    gcry_mpi_mulm(tempo1, tem1, d, p);

    gcry_mpi_t tem3 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem3, tempo1, tem2, p);

    gcry_mpi_t tempo2 = gcry_mpi_new(0);
    // initialising Point3.X
    gcry_mpi_addm(tempo1, X1, Y1, p);
    gcry_mpi_addm(tempo2, X2, Y2, p);
    gcry_mpi_mulm(tempo1, tempo1, tempo2, p);
    gcry_mpi_subm(tempo1, tempo1, tem1, p);
    gcry_mpi_subm(tempo1, tempo1, tem2, p);
    gcry_mpi_subm(tempo2, one, tem3, p);
    gcry_mpi_mulm(Point3.X, tempo2, tempo1, p);
    // initialising Point3.Y
    gcry_mpi_addm(tempo1, one, tem3, p);
    gcry_mpi_mulm(tempo2, a, tem1, p);
    gcry_mpi_subm(tempo2, tem2, tempo2, p);
    gcry_mpi_mulm(Point3.Y, tempo1, tempo2, p);
    // initializing Point3.Z
    gcry_mpi_powm(tempo1, tem3, two, p);
    gcry_mpi_subm(Point3.Z, one, tempo1, p);

    transform_p(&Point3);
    return Point3;
}

point double_p(const point * Point){
    point P3;
    init_p(&P3);
    gcry_mpi_t X1 = gcry_mpi_new(0);
    gcry_mpi_t Y1 = gcry_mpi_new(0);
    gcry_mpi_t Z1 = gcry_mpi_new(0);

    X1 = Point->X;
    Y1 = Point->Y;
    Z1 = Point->Z;
    //    sqred(added(X, Y, p), tt, p);
    gcry_mpi_t B = gcry_mpi_new(0);
    gcry_mpi_t tempo = gcry_mpi_new(0);
    gcry_mpi_addm(tempo, X1, Y1, p);
    gcry_mpi_powm(B, tempo, two, p);
    //gcry_mpi_t C = sqred(X, tt, p);
    gcry_mpi_t C = gcry_mpi_new(0);
    gcry_mpi_powm(C, X1, two, p);
    //gcry_mpi_t D = sqred(Y, tt, p);
    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_powm(D, Y1, two, p);
    //gcry_mpi_t E = muled(a, C, p);
    gcry_mpi_t E = gcry_mpi_new(0);
    gcry_mpi_mulm(E, a, C, p);
    //gcry_mpi_t F = added(E, D, p);
    gcry_mpi_t F = gcry_mpi_new(0);
    gcry_mpi_addm(F, E, D, p);
    //gcry_mpi_t H = sqred(z1, tt, p);
    gcry_mpi_t H = gcry_mpi_new(0);
    gcry_mpi_powm(H, Z1, two, p);
    //gcry_mpi_t J = subed(F, muled(two, H), p);
    gcry_mpi_t J = gcry_mpi_new(0);
    gcry_mpi_mulm(tempo, two, H, p);
    gcry_mpi_subm(J, F, tempo, p);
    //P3.X
    gcry_mpi_subm(tempo, B, C, p);
    gcry_mpi_subm(tempo, tempo, D, p);
    gcry_mpi_mulm(P3.X, tempo, J, p);
    //P3.Y
    gcry_mpi_subm(tempo, E, D, p);
    gcry_mpi_mulm(P3.Y, F, tempo, p); 
    //P3.Z
    gcry_mpi_mulm(P3.Z, F, J, p);

    transform_p(&P3);
    return P3;
 }

point binaryMethod(const point* Point, gcry_mpi_t* I)
{
    point Q;
    init_p(&Q);
    
    Q.X = zero;
    Q.Y = one;
    Q.Z = one;
    
    for(unsigned long int i = gcry_mpi_get_nbits(*I) - 1; i>0; --i)
    {
        Q = double_p(&Q);
        if (gcry_mpi_test_bit(*I, i) == 1)
        { 
            Q = add_p(&Q, Point);
        }
        
        if (i == 1)
        {
            Q = double_p(&Q);
            if(gcry_mpi_test_bit(*I, i-1) == 1)
            {
                Q = add_p(&Q, Point);
            } 
            
        }
    }
    return Q;

}

void ifOnCurve(point * Point){
    //gcry_mpi_t X2 = sqred(Point.X, tt, p);
    gcry_mpi_t X = gcry_mpi_new(0);
    gcry_mpi_powm(X, Point->X, two, p);
    //gcry_mpi_t Y2 = sqred(Point.Y, tt, p);
    gcry_mpi_t Y = gcry_mpi_new(0);
    gcry_mpi_powm(Y, Point->Y, two, p);
    //(added(muled(a, X2, p), Y2, p) == added(oo, muled(muled(d, X2, p), Y2, p), p)) ? printf("Test 1: +\n") : printf("Test 1: -\n");
    gcry_mpi_t A = gcry_mpi_new(0);
    gcry_mpi_mulm(A, a, X, p);
    gcry_mpi_addm(A, A, Y, p);
    gcry_mpi_t B = gcry_mpi_new(0);
    gcry_mpi_mulm(B, d, X, p);
    gcry_mpi_mulm(B, B, Y, p);
    gcry_mpi_addm(B, one, B, p);
    if ((gcry_mpi_cmp(A, B) == 0) ){
        printf("Test onCurve: +\n");
    }
    else{
        printf("Test onCurve: -\n");
    }
    gcry_mpi_release(X); gcry_mpi_release(Y);gcry_mpi_release(A);gcry_mpi_release(B);
}

void ifIdentity(point * Point){
    if ((gcry_mpi_cmp(Point->X, zero) == 0) && (gcry_mpi_cmp(Point->Y, one) == 0) && (gcry_mpi_cmp(Point->Z, one) == 0)) {
        printf("Test identity: +\n");
    }
    else{
        printf("Test identity: -\n");
    }
}

void checkNeighbors(point Point){
    point P1;
    init_p(&P1);

    gcry_mpi_t tempo = gcry_mpi_new(0);
    gcry_mpi_addm(tempo, q, one, p);
    P1 = binaryMethod(&Point, &tempo);
            //binaryMethod(&Point, added(q, oo, p));
    if ((gcry_mpi_cmp(P1.X, Point.X) == 0) && (gcry_mpi_cmp(P1.Y, Point.Y) == 0) && (gcry_mpi_cmp(P1.Z, Point.Z) == 0)){
        printf("Test neighbors. [ q+1 ] P = P: + __ ");
    }
    else{
        printf("Test neighbors. [ q+1 ] P = P: - __ "); // [q+1]P==P
    }


    gcry_mpi_subm(tempo, q, one, p);
    P1 = binaryMethod(&Point, &tempo);
        //point P2 = binaryMethod(&Point, subed(q, oo, p));
    gcry_mpi_t tempoX = gcry_mpi_new(0);
    gcry_mpi_neg(tempoX, Point.X);
    gcry_mpi_mod(tempoX, tempoX, p);
    ((gcry_mpi_cmp(P1.X, tempoX) == 0) && (gcry_mpi_cmp(P1.Y, Point.Y) == 0)  && (gcry_mpi_cmp(P1.Z, Point.Z) == 0) ) ? printf("[q-1] P = -P : +\n") : printf("[q-1] P = -P : -\n");
    // [q-1]P==-P
}

void ifLinear(point * Point, gcry_mpi_t * k1, gcry_mpi_t * k2){
    
    if(gcry_mpi_cmp(*k1, *k2) < 0)  // !!! 
    {
	gcry_mpi_swap(*k1,*k2);
    }

    point Point1;
    point Point2;

    init_p(&Point1);
    init_p(&Point2);

    gcry_mpi_t tempo = gcry_mpi_new(0);
    gcry_mpi_addm(tempo, *k1, *k2, p);    
    
    Point1 = binaryMethod(Point, k1);
    Point2 = binaryMethod(Point, k2);
    
    Point1 = add_p(&Point1, &Point2);
    Point2 = binaryMethod(Point, &tempo);
    
    (gcry_mpi_cmp(Point1.X, Point2.X) == 0 && gcry_mpi_cmp(Point1.Y, Point2.Y) == 0 && gcry_mpi_cmp(Point1.Z, Point2.Z) == 0) ? printf("Test linearity : +\n") : printf("Test linearity : -\n");
}

/*int main(){

    
    set_params();
   
    gcry_mpi_t rand1 = gcry_mpi_new(0);
    printf("rand1\n\n");
    gcry_mpi_dump(rand1);
    gcry_mpi_randomize(rand1, 256, GCRY_STRONG_RANDOM);
    printf("rand1");
    gcry_mpi_t rand2 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand2, 256, GCRY_STRONG_RANDOM);
    printf("rand2");
    point f;
    init_p(&f);
    printf("init f");
    f.X = u;
    f.Y = v;
    f.Z = one;
    printf("init f");
    point k;
    init_p(&k);
    printf("init K");
    k = binaryMethod(&f, &rand1); // Random values for better accuracy
    printf("binary");

    
    
}*/
