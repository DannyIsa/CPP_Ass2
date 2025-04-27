#include "square_mat.h"

namespace matrix
{
    SquareMat::SquareMat(double **arr, int n) : size(n)
    {
        data = new double *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                data[i][j] = arr[i][j];
            }
        }
    }

    SquareMat::SquareMat(int n) : size(n)
    {
        data = new double *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                data[i][j] = 0.0;
            }
        }
    }

    double *SquareMat::operator[](int i)
    {
        return data[i];
    }
}