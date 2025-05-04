// daniisakov@gmail.com

#ifndef SQUARE_MAT_H
#define SQUARE_MAT_H

#include <string>

namespace matrix
{
    // This class represents a square matrix and supports various operations
    class SquareMat
    {
    private:
        int size;       // Size of the matrix (n x n)
        double **data;  // 2D array to store matrix elements

        // Helper methods
        double calculateSum() const;         // Calculate sum of all elements
        double calculateDeterminant() const; // Calculate matrix determinant
        double *getCofactor(int p, int q) const; // Get submatrix without row p and column q

    public:
        // Constructors and destructor
        SquareMat(double **arr, int n);     // Create matrix from 2D array
        SquareMat(int n);                   // Create zero matrix of size n
        SquareMat(const SquareMat &other);  // Copy constructor
        ~SquareMat();                       // Destructor

        // Assignment operator
        SquareMat &operator=(const SquareMat &other);

        // Access operator - allows using m[i][j] syntax
        double *operator[](int i);          // For non-const objects
        const double *operator[](int i) const; // For const objects

        // Basic arithmetic operators
        SquareMat operator+(const SquareMat &other) const;  // Addition
        SquareMat operator-(const SquareMat &other) const;  // Subtraction
        SquareMat operator-() const;                        // Unary minus
        SquareMat operator*(const SquareMat &other) const;  // Matrix multiplication
        SquareMat operator*(double scalar) const;           // Matrix * scalar
        friend SquareMat operator*(double scalar, const SquareMat &mat); // scalar * Matrix

        // Element-wise operations
        SquareMat operator%(const SquareMat &other) const;  // Element-wise multiplication
        SquareMat operator%(int scalar) const;              // Modulo with scalar

        // Division by scalar
        SquareMat operator/(double scalar) const;

        // Power operator
        SquareMat operator^(int power) const;

        // Increment/decrement
        SquareMat &operator++();   // Pre-increment (++m)
        SquareMat operator++(int); // Post-increment (m++)
        SquareMat &operator--();   // Pre-decrement (--m)
        SquareMat operator--(int); // Post-decrement (m--)

        // Transpose
        SquareMat operator~() const;

        // Comparison operators
        bool operator==(const SquareMat &other) const;
        bool operator!=(const SquareMat &other) const;
        bool operator<(const SquareMat &other) const;
        bool operator>(const SquareMat &other) const;
        bool operator<=(const SquareMat &other) const;
        bool operator>=(const SquareMat &other) const;

        // Determinant
        double operator!() const;

        // Compound assignment
        SquareMat &operator+=(const SquareMat &other);  // m1 += m2
        SquareMat &operator-=(const SquareMat &other);  // m1 -= m2
        SquareMat &operator*=(const SquareMat &other);  // m1 *= m2 (matrix)
        SquareMat &operator*=(double scalar);           // m1 *= scalar
        SquareMat &operator/=(double scalar);           // m1 /= scalar
        SquareMat &operator%=(const SquareMat &other);  // m1 %= m2 (element-wise)
        SquareMat &operator%=(int scalar);              // m1 %= scalar (modulo)

        // Output operator
        friend void operator<<(void *os, const SquareMat &mat);
    };
}
#endif