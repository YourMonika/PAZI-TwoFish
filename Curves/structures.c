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
gcry_mpi_t muled(gcry_mpi_t A, gcry_mpi_t B, gcry_mpi_t m){
    gcry_mpi_t result;
    gcry_mpi_mulm(result, A, B, m);

    return result;
}
gcry_mpi_t added(gcry_mpi_t A, gcry_mpi_t B, gcry_mpi_t m){
    gcry_mpi_t result;
    gcry_mpi_addm(result, A, B, m);

    return result;
}
gcry_mpi_t subed(gcry_mpi_t A, gcry_mpi_t B, gcry_mpi_t m){
    gcry_mpi_t result;
    gcry_mpi_subm(result, A, B, m);

    return result;
}
gcry_mpi_t inved(gcry_mpi_t A, gcry_mpi_t m){
    gcry_mpi_t result;
    gcry_mpi_invm(result, A, m);

    return result;
}
gcry_mpi_t sqred(gcry_mpi_t b, gcry_mpi_t e, gcry_mpi_t m) {
    gcry_mpi_t result;
    gcry_mpi_powm(result, b, e, m);

    return result;
}

/*
 * end of gcry-simplification
 */

point transform_p(const point * Point){
    point Q;
    if (Point->Z != 0){
        gcry_mpi_t tempo;
        //x = X/Z
        gcry_mpi_invm(tempo, Point->Z, p);
        gcry_mpi_mulm(Q.X, Point->X, tempo, p);
        //y = Y/Z
        gcry_mpi_mulm(Q.Y, Point->Y, tempo, p);
        Q.Z = 0;
    }
    return Q;
}

point add_p(const point * Point1, const point * Point2){
    gcry_mpi_t X1 = Point1->X;
    gcry_mpi_t Y1 = Point1->Y;
    gcry_mpi_t X2 = Point2->X;
    gcry_mpi_t Y2 = Point2->Y;

    gcry_mpi_t tem1;
    gcry_mpi_t tem2;
    gcry_mpi_t tem3;
    gcry_mpi_t tempo;

    gcry_mpi_mulm(tem1, X1, X2, p);
    gcry_mpi_mulm(tem2, Y1, Y2, p);
    gcry_mpi_mulm(tempo, tem1, d, p);
    gcry_mpi_mulm(tem3, tempo, tem2, p);
    gcry_mpi_t oo;
    gcry_mpi_scan(&oo, GCRYMPI_FMT_HEX, "1", 0, 0);

    gcry_mpi_t X3 = muled(subed(oo, tem3, p), subed(subed(muled(added(X1, Y1, p), added(X2, Y2, p), p), tem1, p), tem2, p), p);
    gcry_mpi_t Y3 = muled(added(oo, tem3, p), subed(tem2, muled(a, tem1, p), p), p);
    gcry_mpi_t tt;
    gcry_mpi_scan(&tt, GCRYMPI_FMT_HEX, "2", 0, 0);
    gcry_mpi_t Z3 = subed(oo, sqred(tem3, tt, p), p);

    gcry_mpi_release(tem1);gcry_mpi_release(tem2);gcry_mpi_release(tem3);gcry_mpi_release(tempo);
    gcry_mpi_release(X1);gcry_mpi_release(X2);gcry_mpi_release(Y1);gcry_mpi_release(Y2);gcry_mpi_release(oo);
    gcry_mpi_release(tt);

    point Point3;
    Point3.X = X3;
    Point3.Y = Y3;
    Point3.Z = Z3;

    return Point3;
}

point double_p(const point * Point){
    gcry_mpi_t X = Point->X;
    gcry_mpi_t Y = Point->Y;
    gcry_mpi_t tt;
    gcry_mpi_scan(&tt, GCRYMPI_FMT_HEX, "2", 0, 0);

    gcry_mpi_t B = sqred(added(X, Y, p), tt, p);
    gcry_mpi_t C = sqred(X, tt, p);
    gcry_mpi_t D = sqred(Y, tt, p);
    gcry_mpi_t E = muled(a, C, p);
    gcry_mpi_t F = added(E, D, p);

    gcry_mpi_t X3 = muled(subed(subed(B, C, p), D, p), subed(F, tt, p), p);
    gcry_mpi_t Y3 = muled(F, muled(E, D, p), p);
    gcry_mpi_t Z3 = subed(sqred(F, tt, p), muled(tt, F, p), p);

    gcry_mpi_release(X);gcry_mpi_release(Y);gcry_mpi_release(B);gcry_mpi_release(C);
    gcry_mpi_release(D);gcry_mpi_release(E);gcry_mpi_release(F);gcry_mpi_release(tt);

    point result = {X3, Y3, Z3};
    point * p_result = &result;
    return transform_p(p_result);
 }

point binaryMethod(const point * Point, gcry_mpi_t I){
    gcry_mpi_t X0, Y0, Z0;

    gcry_mpi_scan(&X0, GCRYMPI_FMT_HEX, "0", 0, 0);
    gcry_mpi_scan(&Y0, GCRYMPI_FMT_HEX, "1", 0, 0);
    gcry_mpi_scan(&Z0, GCRYMPI_FMT_HEX, "0", 0, 0);

    point Q = {X0, Y0, Z0};
    point * Qp = &Q;
    for(long i = gcry_mpi_get_nbits(I) - 1; i>=0; i--){
        Q = double_p(Qp);
        if (gcry_mpi_test_bit(I, i)) Q = add_p(Qp, Point);

    }
    return Q;

}

void ifOnCurve(point Point){
    gcry_mpi_t tt;
    gcry_mpi_scan(&tt, GCRYMPI_FMT_HEX, "2", 0, 0);
    gcry_mpi_t X2 = sqred(Point.X, tt, p);
    gcry_mpi_t Y2 = sqred(Point.Y, tt, p);
    gcry_mpi_t oo;
    gcry_mpi_scan(&oo, GCRYMPI_FMT_HEX, "1", 0, 0);
    (added(muled(a, X2, p), Y2, p) == added(oo, muled(muled(d, X2, p), Y2, p), p)) ? printf("Test 1: +\n") : printf("Test 1: -\n");
    gcry_mpi_release(oo); gcry_mpi_release(X2); gcry_mpi_release(Y2); gcry_mpi_release(tt);
}

void ifIdentity(point Point){
    gcry_mpi_t oo;
    gcry_mpi_t zz;
    gcry_mpi_scan(&zz, GCRYMPI_FMT_HEX, "0", 0, 0);
    gcry_mpi_scan(&oo, GCRYMPI_FMT_HEX, "1", 0, 0);
    (Point.X == zz && Point.Y == oo && Point.Z == zz) ? printf("Test 2: +\n") : printf("Test 2: -\n");
    gcry_mpi_release(oo); gcry_mpi_release(zz);
}

void checkNeighbors(point Point){
    gcry_mpi_t oo;
    gcry_mpi_scan(&oo, GCRYMPI_FMT_HEX, "1", 0, 0);
    point P1 = binaryMethod(&Point, added(q, oo, p));
    (P1.X == Point.X && P1.Y == Point.Y && P1.Z == Point.Z) ? printf("Test 3: +") : printf("Test 3: -"); // [q+1]P==P
///////////
    point P2 = binaryMethod(&Point, subed(q, oo, p));
    gcry_mpi_t tempoX;
    gcry_mpi_t tempoZ;
    gcry_mpi_neg(tempoX, Point.X);
    gcry_mpi_neg(tempoZ, Point.Z);
    gcry_mpi_mod(tempoX, tempoX, p);
    gcry_mpi_mod(tempoZ, tempoZ, p);
    (P2.X == tempoX && P2.Y == Point.Y && P2.Z == tempoZ) ? printf("+\n") : printf("-\n");// [q-1]P==-P
}

void ifLinear(point Point, gcry_mpi_t k1, gcry_mpi_t k2){
    point tem1 = binaryMethod(&Point, k1);
    point tem2;
    tem2 = binaryMethod(&Point, k2);
    point P1 = add_p(&tem1, &tem2);
    gcry_mpi_t tem3;
    gcry_mpi_add(tem3, k1, k2);
    point P2 = binaryMethod(&Point, tem3);
    (P1.X == P2.X && P1.Y == P2.Y && P1.Z == P2.Z) ? printf("Test 4 : +\n") : printf("Test 4 : -\n");
}