#ifndef SQUARE_MAT_H
#define SQUARE_MAT_H

namespace matrix
{
    class SquareMat
    {
    private:
        int size;
        double **data;

    public:
        SquareMat(double **arr, int n);
        SquareMat(int n);
        double *operator[](int i);
    };
}
#endif