
#include "Structs.h"
#include <stdlib.h>
#include <string.h>

// -------------------------- const definitions -------------------------

/**
 * @var int SUCCESS_VALUE
 * @brief The value to return id there was a success in the function.
 */
#define SUCCESS_VALUE 1

/**
 * @var int FAILER_VALUE
 * @brief The value if there is a failer in the function.
 */
#define FAILER_VALUE 0

/**
 * @var char NEW_LINE
 * @brief The value of a new line, to add after every concatenate.
 */
#define NEW_LINE "\n"

/**
 * @var int THE_FIRST_IS_SMALLER
 * @brief The value if the the fist vector is smaller.
 */
#define THE_FIRST_IS_SMALLER -1

/**
 * @var int THE_SECOND_IS_SMALLER
 * @brief The value if the the second vector is smaller.
 */
#define THE_SECOND_IS_SMALLER 1

/**
 * @var int BOTH_EQUAL
 * @brief The value if the two vectors are equal.
 */
#define BOTH_EQUAL 0

// -------------------------- functions declaration -------------------------

/**
 * @brief A function that gets a single vector and compute it's norm.
 * @param pMaxVector a vector to compute a norm.
 * @return double, the norm of the vector.
 */
static double getNorm(Vector *pMaxVector);

// ------------------------------ functions -----------------------------


int vectorCompare1By1(const void *a, const void *b)
{
    if (a == NULL || b == NULL)
    {
        return FAILER_VALUE;
    }
    int counter = 0;
    Vector a1 = *(Vector*)a;
    Vector a2 = *(Vector*)b;
    double *d1 = a1.vector;
    double *d2 = a2.vector;
    if (d1 == NULL || d2 == NULL)
    {
        return FAILER_VALUE;
    }
    while (counter < a1.len && counter < a2.len)
    {
        if (d1[counter] < d2[counter])
        {
            return THE_FIRST_IS_SMALLER;
        }
        if (d1[counter] > d2[counter])
        {
            return THE_SECOND_IS_SMALLER;
        }
        counter++;
    }
    if (counter < a1.len && counter == a2.len)
    {
        return THE_SECOND_IS_SMALLER;
    }
    else if (counter == a1.len && counter < a2.len)
    {
        return THE_FIRST_IS_SMALLER;
    }
    return BOTH_EQUAL;
}

static double getNorm(Vector *pMaxVector)
{
    if (pMaxVector == NULL)
    {
        return 0.0;
    }
    int counter = 0;
    double sum = 0.0;
    while(counter < pMaxVector->len)
    {
        sum = sum + (pMaxVector->vector[counter] * pMaxVector->vector[counter]);
        counter++;
    }
    return sum;
}

int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
    if (pVector == NULL || pMaxVector == NULL)
    {
        return FAILER_VALUE;
    }
    Vector* pMax = (Vector*)pMaxVector;
    Vector* p = (Vector*)pVector;
    if (pMax->vector == NULL)
    {
        pMax->vector = (double*)malloc(p->len * sizeof(double));
        if (pMax->vector == NULL)
        {
            return FAILER_VALUE;
        }
        memcpy(pMax->vector, p->vector, p->len * (sizeof(double)));
        pMax->len = p->len;
    }
    else if (getNorm(p) > getNorm(pMax))
    {
        pMax->vector = (double*)realloc(pMax->vector, p->len * sizeof(double));
        if (pMax->vector == NULL)
        {
            return FAILER_VALUE;
        }
        memcpy(pMax->vector, p->vector, p->len * (sizeof(double)));
        pMax->len = p->len;
    }
    return SUCCESS_VALUE;
}

Vector *findMaxNormVectorInTree(RBTree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    Vector* max = (Vector*)malloc(sizeof(Vector));
    if (max == NULL)
    {
        return NULL;
    }
    max->len = 0;
    max->vector = NULL;
    if (forEachRBTree(tree, copyIfNormIsLarger, max) == FAILER_VALUE)
    {
        return NULL;
    }
    return max;
}

void freeVector(void *pVector)
{
    if (pVector != NULL)
    {
        Vector* v = (Vector*)pVector;
        free(v->vector);
        v->vector = NULL;
        free(v);
        v = NULL;
    }
}

int stringCompare(const void *a, const void *b)
{
    char *p1 = (char*)a;
    char *p2 = (char*)b;
    return strcmp(p1, p2);
}

int concatenate(const void *word, void *pConcatenated)
{
    if (word == NULL || pConcatenated == NULL)
    {
        return FAILER_VALUE;
    }
    char* p = (char*)pConcatenated;
    char* w = (char*)word;
    strcat(p, w);
    strcat(p, NEW_LINE);
    return SUCCESS_VALUE;
}

void freeString(void *s)
{
    if (s != NULL)
    {
        char* c = (char*)s;
        free(c);
        c = NULL;
    }
}

