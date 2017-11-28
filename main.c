#include <stdio.h>
#include <math.h>

#define PI 3.14159265

typedef struct Ponto
{
    double x, y;
} ponto;

typedef struct Vector
{
    ponto p1, p2;
    double i, j;
} vector;

typedef struct Triangle
{
    ponto vertices[3];
    vector sides[3];
} triangle;

ponto newPonto(double x, double y);
vector newVector(ponto p1, ponto p2);
vector newVector2(double i, double j);
triangle newTriangle(ponto p1, ponto p2, ponto p3);
vector multiplicarPorEscalar(vector v, double e);
vector getVersor(vector v);
vector projecaoDeV1SobreV2(vector v1, vector v2);
int produtoVetorial(vector v1, vector v2);
int isPointLeftOfVector(ponto p, vector v);
int isPointRightOfVector(ponto p, vector v);
int isPointOnVector(ponto p, vector v);
int isPointInsideTriangle(ponto p, triangle t);
int isPointOutsideTriangle(ponto p, triangle t);
int isPointOnBorderOfTriangle(ponto p, triangle t);
double produtoEscalar(vector v1, vector v2);
double modulo(vector v);
double anguloEntre(vector v1, vector v2);
double distPontoParaSegmento(ponto p, vector v);
double distPontoParaReta(ponto p, vector v);
void printVector(vector v);

int main()
{
    ponto p1 = newPonto(0, 0);
    ponto p2 = newPonto(2, 2);
    ponto p3 = newPonto(-2, 2);

    triangle t = newTriangle(p1, p2, p3);

    ponto testInside = newPonto(0, 1);
    ponto testBorder = newPonto(1, 1);
    ponto testOutside = newPonto(-10, -10);

    printf("teste dentro:\n");
    printf("is point inside triangle? %d\n", isPointInsideTriangle(testInside, t));
    printf("is point outside triangle? %d\n", isPointOutsideTriangle(testInside, t));
    printf("is point on border of triangle? %d\n\n", isPointOnBorderOfTriangle(testInside, t));

    printf("teste borda:\n");
    printf("is point inside triangle? %d\n", isPointInsideTriangle(testBorder, t));
    printf("is point outside triangle? %d\n", isPointOutsideTriangle(testBorder, t));
    printf("is point on border of triangle? %d\n\n", isPointOnBorderOfTriangle(testBorder, t));

    printf("teste fora:\n");
    printf("is point inside triangle? %d\n", isPointInsideTriangle(testOutside, t));
    printf("is point outside triangle? %d\n", isPointOutsideTriangle(testOutside, t));
    printf("is point on border of triangle? %d\n\n", isPointOnBorderOfTriangle(testOutside, t));

    return 0;
}

ponto newPonto(double x, double y)
{
    ponto p;

    p.x = x;
    p.y = y;

    return p;
}

vector newVector(ponto p1, ponto p2)
{
    vector v;

    v.p1 = p1;
    v.p2 = p2;
    v.i = p2.x - p1.x;
    v.j = p2.y - p1.y;

    return v;
}

vector newVector2(double i, double j)
{
    vector v;

    v.i = i;
    v.j = j;

    return v;
}

triangle newTriangle(ponto p1, ponto p2, ponto p3)
{
    triangle t;

    if (p1.y < p2.y && p1.y < p3.y) 
    {
        t.vertices[0] = p1;

        if (p2.x > p3.x)
        {
            t.vertices[1] = p2;
            t.vertices[2] = p3;
        }
        else 
        {
            t.vertices[1] = p3;
            t.vertices[2] = p2;
        }
    }
    else if (p2.y < p1.y && p2.y < p3.y) 
    {
        t.vertices[0] = p2;

        if (p1.x > p3.x) 
        {
            t.vertices[1] = p1;
            t.vertices[2] = p3;
        }
        else 
        {
            t.vertices[1] = p3;
            t.vertices[2] = p1;
        }
    }
    else 
    {
        t.vertices[0] = p3;

        if (p1.x > p2.x) 
        {
            t.vertices[1] = p1;
            t.vertices[2] = p2;
        }
        else 
        {
            t.vertices[1] = p2;
            t.vertices[2] = p1;
        }
    }

    t.sides[0] = newVector(t.vertices[0], t.vertices[1]);
    t.sides[1] = newVector(t.vertices[1], t.vertices[2]);
    t.sides[2] = newVector(t.vertices[2], t.vertices[0]);

    return t;
}

vector multiplicarPorEscalar(vector v, double e)
{
    v.i *= e;
    v.j *= e;

    return v;
}

vector getVersor(vector v)
{
    double mod = modulo(v);

    v.i /= mod;
    v.j /= mod;

    return v;
}

vector projecaoDeV1SobreV2(vector v1, vector v2)
{
    double num = produtoEscalar(v1, v2);
    double den = pow(modulo(v2), 2.0);
    double escalar = num / den;

    return multiplicarPorEscalar(v2, escalar);
}

int produtoVetorial(vector v1, vector v2)
{
    return ((v1.i * v2.j) - (v1.j * v2.i));
}

int isPointLeftOfVector(ponto p, vector v)
{
    vector v2 = newVector(v.p1, p);
    return (produtoVetorial(v, v2) > 0);
}

int isPointRightOfVector(ponto p, vector v)
{
    vector v2 = newVector(v.p1, p);
    return (produtoVetorial(v, v2) < 0);
}

int isPointOnVector(ponto p, vector v)
{
    double menorX, menorY, maiorX, maiorY;

    if (v.p1.x < v.p2.x)
    {
        menorX = v.p1.x;
        maiorX = v.p2.x;
    }
    else 
    {
        menorX = v.p2.x;
        maiorX = v.p1.x;
    }

    if (v.p1.y < v.p2.y)
    {
        menorY = v.p1.y;
        maiorY = v.p2.y;
    }
    else 
    {
        menorY = v.p2.y;
        maiorY = v.p1.y;
    }

    if (p.x < menorX || p.x > maiorX || p.y < menorY || p.y > maiorY) return 0;

    vector v2 = newVector(v.p1, p);
    return (produtoVetorial(v, v2) == 0);
}

int isPointInsideTriangle(ponto p, triangle t)
{
    return (isPointLeftOfVector(p, t.sides[0]) & isPointLeftOfVector(p, t.sides[1]) & isPointLeftOfVector(p, t.sides[2]));
}

int isPointOutsideTriangle(ponto p, triangle t)
{
    return (!isPointInsideTriangle(p, t) && !isPointOnBorderOfTriangle(p, t));
}

int isPointOnBorderOfTriangle(ponto p, triangle t)
{
    return (isPointOnVector(p, t.sides[0]) | isPointOnVector(p, t.sides[1]) | isPointOnVector(p, t.sides[2]));
}

double produtoEscalar(vector v1, vector v2)
{
    return (v1.i * v2.i) + (v1.j * v2.j);
}

double modulo(vector v)
{
    return sqrt((v.i * v.i) + (v.j * v.j));
}

double anguloEntre(vector v1, vector v2)
{
    return acos((produtoEscalar(v1, v2))/(modulo(v1) * modulo(v2))) * 180.0 / PI;
}

double distPontoParaSegmento(ponto p, vector v)
{
    double aux1 = produtoEscalar(newVector(v.p2, v.p1), newVector(v.p2, p));
    double aux2 = produtoEscalar(v, newVector(v.p1, p));

    if (aux1 > 0 && aux2 > 0) return distPontoParaReta(p, v);

    double r1 = modulo(newVector(v.p1, p));
    double r2 = modulo(newVector(v.p2, p));

    return (r1 < r2) ? r1 : r2;
}

double distPontoParaReta(ponto p, vector v)
{
    return (modulo(produtoVetorial(v, newVector(v.p1, p)))) / modulo(v);
}

void printVector(vector v)
{
    printf("i = %.2lf, j = %.2lf\n", v.i, v.j);
}