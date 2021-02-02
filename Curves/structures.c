/*Created by Shubin Nikita -> GitHub: YourMonika
 * CoSec 172
 * PAZI
 * Edwards Curve
 * lib gcrypt
 */

#include "structures.h"
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

void show_p(point* P, char A){
    printf("\n Look at this POINT %c\n", A);
    gcry_mpi_dump(P->X); printf("_");
    gcry_mpi_dump(P->X); printf("_");
    gcry_mpi_dump(P->X); printf("\n\n");
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

    gcry_mpi_scan(&p, GCRYMPI_FMT_HEX, "115792089237316195423570985008687907853269984665640564039457584007913129639319", 0, &scanned);
    gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "1", 0, &scanned);
    gcry_mpi_scan(&d, GCRYMPI_FMT_HEX, "2724414110474605931834268501164757645998726878473076809432604223414351675387", 0, &scanned);
    gcry_mpi_scan(&q, GCRYMPI_FMT_HEX, "28948022309329048855892746252171976963338560298092253442512153408785530358887", 0, &scanned);
    gcry_mpi_scan(&u, GCRYMPI_FMT_HEX, "D", 0, &scanned);
    gcry_mpi_scan(&v, GCRYMPI_FMT_HEX, "43779144989398987843428779166090436406934195821915183574454224403186176950503", 0, &scanned);

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
        Point->Z = zero;
    }
}

point add_p(const point * Point1, const point * Point2){
    gcry_mpi_t X1 = gcry_mpi_copy(Point1->X);
    gcry_mpi_t Y1 = gcry_mpi_copy(Point1->Y);
    gcry_mpi_t X2 = gcry_mpi_copy(Point2->X);
    gcry_mpi_t Y2 = gcry_mpi_copy(Point2->Y);

    gcry_mpi_t tem1 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem1, X1, X2, p);

    gcry_mpi_t tem2 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem2, Y1, Y2, p);

    gcry_mpi_t tempo1 = gcry_mpi_new(0);
    gcry_mpi_mulm(tempo1, tem1, d, p);

    gcry_mpi_t tem3 = gcry_mpi_new(0);
    gcry_mpi_mulm(tem3, tempo1, tem2, p);

    point Point3;
    init_p(&Point3);

    gcry_mpi_t tempo2 = gcry_mpi_new(0);
    // initialising Point3.X
    gcry_mpi_addm(tempo1, X1, Y1, p);
    gcry_mpi_addm(tempo1, X2, Y2, p);
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
    gcry_mpi_t X1 = gcry_mpi_new(0);
    gcry_mpi_t Y1 = gcry_mpi_new(0);

    X1 = Point->X;
    Y1 = Point->Y;
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

    point P3;
    init_p(&P3);

    gcry_mpi_t double_swing = gcry_mpi_new(0);
    //gcry_mpi_t X3 = muled(subed(subed(B, C, p), D, p), subed(F, tt, p), p);
    gcry_mpi_subm(tempo, B, C, p);
    gcry_mpi_subm(tempo, tempo, D, p);
    gcry_mpi_subm(double_swing, F, two, p);
    gcry_mpi_mulm(P3.X, tempo, double_swing, p);
    //gcry_mpi_t Y3 = muled(F, muled(E, D, p), p);
    gcry_mpi_mulm(tempo, E, D, p);
    gcry_mpi_mulm(P3.Y, F, tempo, p);
    //gcry_mpi_t Z3 = subed(sqred(F, tt, p), muled(tt, F, p), p);
    gcry_mpi_powm(tempo, F, two, p);
    gcry_mpi_mulm(double_swing, two, F, p);
    gcry_mpi_subm(P3.Z, tempo, double_swing, p);

    gcry_mpi_release(X1);gcry_mpi_release(Y1);gcry_mpi_release(B);gcry_mpi_release(C);
    gcry_mpi_release(D);gcry_mpi_release(E);gcry_mpi_release(F);gcry_mpi_release(tempo);
    gcry_mpi_release(double_swing);

    transform_p(&P3);
    return P3;

 }

point binaryMethod(const point * Point, gcry_mpi_t I){
    point Q = {zero, one, zero};
    for(long i = gcry_mpi_get_nbits(I) - 1; i>=0; i--){
        Q = double_p(&Q);
        if (gcry_mpi_test_bit(I, i)) Q = add_p(&Q, Point);
    }
    return Q;

}

void ifOnCurve(point * Point){
    show_p(Point, '0');
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
        printf("Test 1: +\n");
    }
    else{
        printf("Test 1: -\n");
    }
    gcry_mpi_release(X); gcry_mpi_release(Y);gcry_mpi_release(A);gcry_mpi_release(B);
}

void ifIdentity(point * Point){
    show_p(Point, '0');
    if ((gcry_mpi_cmp(Point->X, zero) == 0) && (gcry_mpi_cmp(Point->Y, one) == 0) && (gcry_mpi_cmp(Point->Z, zero) == 0)) {
        printf("Test 2: +\n");
    }
    else{
        printf("Test 2: -\n");
    }
}

void checkNeighbors(point Point){
    show_p(&Point, '1');
    point P1;
    init_p(&P1);

    gcry_mpi_t tempo = gcry_mpi_new(0);
    gcry_mpi_addm(tempo, q, one, p);
    P1 = binaryMethod(&Point, tempo);
            //binaryMethod(&Point, added(q, oo, p));
    show_p(&P1, '2');
    if ((gcry_mpi_cmp(P1.X, Point.X) == 0) && (gcry_mpi_cmp(P1.Y, Point.Y) == 0) && (gcry_mpi_cmp(P1.Z, Point.Z) == 0)){
        printf("Test 3: +");
    }
    else{
         printf("Test 3: -"); // [q+1]P==P
    }


    gcry_mpi_subm(tempo, q, one, p);
    P1 = binaryMethod(&Point, tempo);
        //point P2 = binaryMethod(&Point, subed(q, oo, p));
    gcry_mpi_t tempoX = gcry_mpi_new(0);
    gcry_mpi_t tempoZ = gcry_mpi_new(0);
    gcry_mpi_neg(tempoX, Point.X);
    gcry_mpi_neg(tempoZ, Point.Z);
    gcry_mpi_mod(tempoX, tempoX, p);
    gcry_mpi_mod(tempoZ, tempoZ, p);
    show_p(&P1, '3');
    if ((gcry_mpi_cmp(P1.X, tempoX) == 0) && (gcry_mpi_cmp(P1.Y, Point.Y) == 0)  && (gcry_mpi_cmp(P1.Z, tempoZ) == 0) ) {
        printf("+\n");
    }
    else {
        printf("-\n");
    }// [q-1]P==-P
}

void ifLinear(point * Point, gcry_mpi_t k1, gcry_mpi_t k2){
    point tem1;
    point tem2;
    init_p(&tem1);
    init_p(&tem2);
    tem1 = binaryMethod(Point, k1);
    tem2 = binaryMethod(Point, k2);
    point Point1;
    point Point2;
    init_p(&Point1);
    init_p(&Point2);
    Point1 = add_p(&tem1, &tem2);
    gcry_mpi_t tempo = gcry_mpi_new(0);
    gcry_mpi_add(tempo, k1, k2);
    Point2 = binaryMethod(Point, tempo);
    show_p(Point, '1');show_p(&Point1, '2');show_p(&Point2, '3');
    (Point1.X == Point2.X && Point1.Y == Point2.Y && Point1.Z == Point2.Z) ? printf("Test 4 : +\n") : printf("Test 4 : -\n");
}