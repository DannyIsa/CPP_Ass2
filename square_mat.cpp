// daniisakov@gmail.com

#include "square_mat.h"
#include <iostream>

namespace matrix
{
    // Constructor with array input
    SquareMat::SquareMat(double **arr, int n) : size(n) // Initialize size in constructor
    {
        // Make sure size is positive
        if (n <= 0)
        {
            size = 0;
            data = nullptr; // Set data to null
            return;
        }

        // Allocate memory for the matrix
        data = new double *[size];

        // Copy values from input array
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                data[i][j] = arr[i][j]; // Copy each element
            }
        }
    }

    // Constructor that creates a zero matrix of size n
    SquareMat::SquareMat(int n) : size(n)
    {
        // Check if size is valid
        if (n <= 0)
        {
            size = 0;
            data = nullptr;
            return;
        }

        // Allocate memory and initialize to zeros
        data = new double *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                data[i][j] = 0.0; // Set all elements to zero
            }
        }
    }

    // Copy constructor - makes a copy of another matrix
    SquareMat::SquareMat(const SquareMat &other) : size(other.size)
    {
        // Handle empty matrix
        if (size <= 0)
        {
            data = nullptr;
            return;
        }

        // Allocate memory
        data = new double *[size];

        // Copy values from other matrix
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                // Copy each element
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Destructor - free memory when object is deleted
    SquareMat::~SquareMat()
    {
        // Only delete if data exists
        if (data != nullptr)
        {
            // Delete each row first
            for (int i = 0; i < size; i++)
            {
                delete[] data[i];
            }
            // Then delete the array of pointers
            delete[] data;
        }
    }

    // Assignment operator - for statements like m1 = m2
    SquareMat &SquareMat::operator=(const SquareMat &other)
    {
        // Check for self-assignment (like m1 = m1)
        if (this == &other)
            return *this;

        // Free existing memory
        if (data != nullptr)
        {
            for (int i = 0; i < size; i++)
            {
                delete[] data[i];
            }
            delete[] data;
        }

        // Copy from other matrix
        size = other.size;

        if (size <= 0)
        {
            data = nullptr;
            return *this;
        }

        // Allocate new memory
        data = new double *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
            {
                data[i][j] = other.data[i][j]; // Copy values
            }
        }

        return *this; // Return reference to this object
    }

    // Access operators - allows using m[i][j] syntax
    double *SquareMat::operator[](int i)
    {
        // Check if index is valid
        if (i < 0 || i >= size)
        {
            return nullptr; // Return null for invalid index
        }
        return data[i]; // Return pointer to row i
    }

    const double *SquareMat::operator[](int i) const
    {
        // Same as above but for const objects
        if (i < 0 || i >= size)
        {
            return nullptr;
        }
        return data[i];
    }

    // Helper method to calculate sum of all elements
    double SquareMat::calculateSum() const
    {
        // Initialize sum to zero
        double sum = 0.0;

        // Add up all elements in the matrix
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                sum += data[i][j]; // Add current element to sum
            }
        }

        return sum; // Return the total sum
    }

    // Get cofactor of matrix (submatrix without row p and column q)
    double *SquareMat::getCofactor(int p, int q) const
    {
        int n = size;
        // Create array for the cofactor (smaller by 1 in each dimension)
        double *cofactor = new double[(n - 1) * (n - 1)];
        int i = 0, j = 0; // indices for cofactor array

        // Loop through the original matrix
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                // Skip the row p and column q
                if (row != p && col != q)
                {
                    // Copy element to cofactor array
                    cofactor[i * (n - 1) + j] = data[row][col];
                    j++; // Move to next column in cofactor

                    // If we reached the end of a row in cofactor
                    if (j == n - 1)
                    {
                        j = 0; // Reset column index
                        i++;   // Move to next row
                    }
                }
            }
        }
        return cofactor; // Return the cofactor array
    }

    // Calculate determinant using recursion
    double SquareMat::calculateDeterminant() const
    {
        // Base cases
        // For 1x1 matrix, determinant is the single element
        if (size == 1)
            return data[0][0];

        // For 2x2 matrix, determinant is ad - bc
        if (size == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        // For larger matrices, use cofactor expansion
        double det = 0;
        int sign = 1; // Start with positive sign

        // Expand along the first row
        for (int i = 0; i < size; i++)
        {
            // Get the cofactor (submatrix) for element (0,i)
            double *cofactor = getCofactor(0, i);

            // Convert 1D cofactor array to 2D array for SquareMat constructor
            double **temp = new double *[size - 1];
            for (int j = 0; j < size - 1; j++)
            {
                temp[j] = new double[size - 1];
                for (int k = 0; k < size - 1; k++)
                {
                    temp[j][k] = cofactor[j * (size - 1) + k];
                }
            }

            // Create a matrix from the cofactor
            SquareMat cofactorMat(temp, size - 1);

            // Add this term to the determinant
            // Formula: det += sign * element * det(cofactor)
            det += sign * data[0][i] * cofactorMat.calculateDeterminant();

            // Clean up memory
            for (int j = 0; j < size - 1; j++)
            {
                delete[] temp[j];
            }
            delete[] temp;
            delete[] cofactor;

            // Flip the sign for next term (alternating +/-)
            sign = -sign;
        }

        return det;
    }

    // Addition operator (m1 + m2)
    SquareMat SquareMat::operator+(const SquareMat &other) const
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return SquareMat(0); // Return empty matrix if sizes don't match
        }

        // Create result matrix
        SquareMat result(size);

        // Add corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Subtraction operator (m1 - m2)
    SquareMat SquareMat::operator-(const SquareMat &other) const
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return SquareMat(0); // Return empty matrix if sizes don't match
        }

        // Create result matrix
        SquareMat result(size);

        // Subtract corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Unary minus operator (-m1)
    SquareMat SquareMat::operator-() const
    {
        // Create result matrix
        SquareMat result(size);

        // Negate all elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = -data[i][j];
            }
        }
        return result;
    }

    // Matrix multiplication (m1 * m2)
    SquareMat SquareMat::operator*(const SquareMat &other) const
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return SquareMat(0); // Return empty matrix if sizes don't match
        }

        // Create result matrix
        SquareMat result(size);

        // Perform matrix multiplication
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = 0; // Initialize element to 0

                // Calculate dot product of row i and column j
                for (int k = 0; k < size; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Scalar multiplication (m1 * scalar)
    SquareMat SquareMat::operator*(double scalar) const
    {
        // Create result matrix
        SquareMat result(size);

        // Multiply each element by scalar
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Scalar multiplication (scalar * m1)
    SquareMat operator*(double scalar, const SquareMat &mat)
    {
        // Just call the other multiplication operator
        return mat * scalar;
    }

    // Element-wise multiplication (m1 % m2)
    SquareMat SquareMat::operator%(const SquareMat &other) const
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return SquareMat(0); // Return empty matrix if sizes don't match
        }

        // Create result matrix
        SquareMat result(size);

        // Multiply corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }
        return result;
    }

    // Modulo with scalar (m1 % scalar)
    SquareMat SquareMat::operator%(int scalar) const
    {
        // Check for division by zero
        if (scalar == 0)
        {
            return SquareMat(0); // Return empty matrix if scalar is zero
        }

        // Create result matrix
        SquareMat result(size);

        // Apply modulo to each element
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // Cast to int, do modulo, store as double
                result.data[i][j] = (int)data[i][j] % scalar;
            }
        }
        return result;
    }

    // Division by scalar (m1 / scalar)
    SquareMat SquareMat::operator/(double scalar) const
    {
        // Check for division by zero
        if (scalar == 0)
        {
            return SquareMat(0); // Return empty matrix if scalar is zero
        }

        // Create result matrix
        SquareMat result(size);

        // Divide each element by scalar
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Power operator (m1 ^ power)
    SquareMat SquareMat::operator^(int power) const
    {
        // Handle negative power
        if (power < 0)
        {
            return SquareMat(0); // Return empty matrix for negative power
        }

        // Special case: power = 0 (identity matrix)
        if (power == 0)
        {
            SquareMat result(size);
            for (int i = 0; i < size; i++)
            {
                result.data[i][i] = 1.0; // Set diagonal elements to 1
            }
            return result;
        }

        // Special case: power = 1 (return copy of this matrix)
        if (power == 1)
        {
            return *this;
        }

        // For powers > 1, multiply matrix by itself 'power' times
        SquareMat result = *this;
        for (int i = 1; i < power; i++)
        {
            result = result * (*this); // Multiply by original matrix
        }

        return result;
    }

    // Pre-increment operator (++m)
    SquareMat &SquareMat::operator++()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] += 1.0;
            }
        }
        return *this;
    }

    // Post-increment operator (m++)
    SquareMat SquareMat::operator++(int)
    {
        SquareMat temp = *this;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] += 1.0;
            }
        }

        return temp;
    }

    // Pre-decrement operator (--m)
    SquareMat &SquareMat::operator--()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] -= 1.0;
            }
        }
        return *this;
    }

    // Post-decrement operator (m--)
    SquareMat SquareMat::operator--(int)
    {
        SquareMat temp = *this;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] -= 1.0;
            }
        }

        return temp;
    }

    // Transpose operator (~m)
    SquareMat SquareMat::operator~() const
    {
        // Create result matrix
        SquareMat result(size);

        // Swap rows and columns
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[j][i]; // Flip indices
            }
        }
        return result;
    }

    // Equality operator (m1 == m2)
    bool SquareMat::operator==(const SquareMat &other) const
    {
        // Matrices are equal if their sums are equal
        // This is a simple way to compare matrices
        return calculateSum() == other.calculateSum();
    }

    // Inequality operator (m1 != m2)
    bool SquareMat::operator!=(const SquareMat &other) const
    {
        // Matrices are not equal if their sums are not equal
        return calculateSum() != other.calculateSum();
    }

    // Less than operator (m1 < m2)
    bool SquareMat::operator<(const SquareMat &other) const
    {
        // Matrix is less than another if its sum is less
        return calculateSum() < other.calculateSum();
    }

    // Greater than operator (m1 > m2)
    bool SquareMat::operator>(const SquareMat &other) const
    {
        // Matrix is greater than another if its sum is greater
        return calculateSum() > other.calculateSum();
    }

    // Less than or equal operator (m1 <= m2)
    bool SquareMat::operator<=(const SquareMat &other) const
    {
        // Matrix is less than or equal if its sum is less than or equal
        return calculateSum() <= other.calculateSum();
    }

    // Greater than or equal operator (m1 >= m2)
    bool SquareMat::operator>=(const SquareMat &other) const
    {
        // Matrix is greater than or equal if its sum is greater than or equal
        return calculateSum() >= other.calculateSum();
    }

    // Determinant operator (!m)
    double SquareMat::operator!() const
    {
        // Calculate determinant using helper method
        return calculateDeterminant();
    }

    // Compound addition (m1 += m2)
    SquareMat &SquareMat::operator+=(const SquareMat &other)
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return *this; // Return unchanged if sizes don't match
        }

        // Add corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // Compound subtraction (m1 -= m2)
    SquareMat &SquareMat::operator-=(const SquareMat &other)
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return *this; // Return unchanged if sizes don't match
        }

        // Subtract corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    // Compound matrix multiplication (m1 *= m2)
    SquareMat &SquareMat::operator*=(const SquareMat &other)
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return *this; // Return unchanged if sizes don't match
        }

        // Create temporary matrix for result
        SquareMat result(size);

        // Perform matrix multiplication
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = 0; // Initialize to 0

                // Calculate dot product of row i and column j
                for (int k = 0; k < size; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        // Copy result back to this matrix
        *this = result;
        return *this;
    }

    // Compound scalar multiplication (m1 *= scalar)
    SquareMat &SquareMat::operator*=(double scalar)
    {
        // Multiply each element by scalar
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Compound division by scalar (m1 /= scalar)
    SquareMat &SquareMat::operator/=(double scalar)
    {
        // Check for division by zero
        if (scalar == 0)
        {
            return *this; // Return unchanged if scalar is zero
        }

        // Divide each element by scalar
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] /= scalar;
            }
        }
        return *this;
    }

    // Compound element-wise multiplication (m1 %= m2)
    SquareMat &SquareMat::operator%=(const SquareMat &other)
    {
        // Check if matrices have same size
        if (size != other.size)
        {
            return *this; // Return unchanged if sizes don't match
        }

        // Multiply corresponding elements
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] *= other.data[i][j];
            }
        }
        return *this;
    }

    // Compound modulo with scalar (m1 %= scalar)
    SquareMat &SquareMat::operator%=(int scalar)
    {
        // Check for modulo by zero
        if (scalar == 0)
        {
            return *this; // Return unchanged if scalar is zero
        }

        // Apply modulo to each element
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // Cast to int, do modulo, store as double
                data[i][j] = (int)data[i][j] % scalar;
            }
        }
        return *this;
    }

    // Output operator (nullptr << m)
    void operator<<(void *os, const SquareMat &mat)
    {
        // Get matrix size
        int size = mat.size;

        // Print each element
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // Get current value
                double val = mat.data[i][j];

                // Convert to string
                std::string valStr = std::to_string(val);

                // Format to 2 decimal places
                size_t decimalPos = valStr.find('.');
                if (decimalPos != std::string::npos && decimalPos + 3 < valStr.length())
                {
                    valStr = valStr.substr(0, decimalPos + 3);
                }

                // Print value
                std::cout << valStr;

                // Add space between elements (except last one in row)
                if (j < size - 1)
                    std::cout << " ";
            }
            // New line after each row
            std::cout << std::endl;
        }
    }
}