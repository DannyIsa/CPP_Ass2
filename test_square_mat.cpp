// daniisakov@gmail.com

#include <iostream>
#include <iomanip>
#include <string>
#include "square_mat.h"

using namespace matrix;
using namespace std;

void assert_true(bool condition, const string &testName)
{
    if (condition)
    {
        cout << "[✅ PASS] " << testName << endl;
    }
    else
    {
        cout << "[❌ FAIL] " << testName << endl;
    }
}

// Helper function to compare matrices
bool matrices_equal(const SquareMat &m1, const SquareMat &m2, int buffer = 100)
{
    if (m1[0] == nullptr || m2[0] == nullptr)
    {
        return false;
    }

    int size = 0;
    while (m1[size] != nullptr && size < buffer)
    {
        size++;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (m1[i][j] != m2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

// Helper to create a matrix with predefined values
SquareMat createTestMatrix(int size, double startValue = 1.0, double increment = 1.0)
{
    double **arr = new double *[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = startValue + (i * size + j) * increment;
        }
    }

    SquareMat result(arr, size);

    // Clean up the temporary array
    for (int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return result;
}

// Helper to create a matrix with specific values
SquareMat createMatrixFromValues(double **values, int size)
{
    double **arr = new double *[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = values[i][j];
        }
    }

    SquareMat result(arr, size);

    // Clean up the temporary array
    for (int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return result;
}

// Helper to create a matrix from a 2D array literal
template <size_t N>
SquareMat createMatrixFromArray(double (&values)[N][N])
{
    int size = N;
    double **arr = new double *[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = values[i][j];
        }
    }

    SquareMat result(arr, size);

    // Clean up the temporary array
    for (int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return result;
}

// Assert that a matrix has expected values using array literal
template <size_t N>
void assert_matrix_values(const SquareMat &mat, double (&expected)[N][N],
                          const string &message)
{
    SquareMat expectedMat = createMatrixFromArray(expected);
    assert_true(matrices_equal(mat, expectedMat), message);
}

// Assert that two matrices are equal after an operation
void assert_operation_result(const SquareMat &result, const SquareMat &expected, const string &operation)
{
    assert_true(matrices_equal(result, expected),
                "Matrix " + operation + " operation works correctly");
}

// Test arithmetic operators
void test_arithmetic_operators()
{
    cout << "\n=== Testing Arithmetic Operators ===\n";

    // Create test matrices
    SquareMat m1 = createTestMatrix(3);
    SquareMat m2 = createTestMatrix(3, 9.0, -1.0);

    // Test plus
    SquareMat m3 = m1 + m2;
    double addition_expected[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    assert_matrix_values(m3, addition_expected, "Addition operator works correctly");

    // Test minus
    SquareMat m4 = m1 - m2;
    double subtraction_expected[3][3] = {{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
    assert_matrix_values(m4, subtraction_expected, "Subtraction operator works correctly");

    // Test unary minus
    SquareMat m5 = -m1;
    double unary_minus_expected[3][3] = {{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}};
    assert_matrix_values(m5, unary_minus_expected, "Unary minus operator works correctly");

    // Test matrix multiplication
    SquareMat m6 = m1 * m2;
    double matrix_mult_expected[3][3] = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    assert_matrix_values(m6, matrix_mult_expected, "Matrix multiplication operator works correctly");

    // Test scalar multiplication (matrix * scalar)
    SquareMat m7 = m1 * 2.0;
    double scalar_mult_expected[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    assert_matrix_values(m7, scalar_mult_expected, "Scalar multiplication (matrix * scalar) works correctly");

    // Test scalar multiplication (scalar * matrix)
    SquareMat m8 = 3.0 * m1;
    double scalar_mult2_expected[3][3] = {{3, 6, 9}, {12, 15, 18}, {21, 24, 27}};
    assert_matrix_values(m8, scalar_mult2_expected, "Scalar multiplication (scalar * matrix) works correctly");
}

// Test element-wise operations
void test_element_wise_operations()
{
    cout << "\n=== Testing Element-wise Operations ===\n";

    // Create test matrices
    SquareMat m1 = createTestMatrix(3);
    SquareMat m2 = createTestMatrix(3, 9.0, -1.0);

    // Test element-wise multiplication
    SquareMat m3 = m1 % m2;
    double elem_mult_expected[3][3] = {{9, 16, 21}, {24, 25, 24}, {21, 16, 9}};
    assert_matrix_values(m3, elem_mult_expected, "Element-wise multiplication operator works correctly");

    // Test modulo with scalar
    SquareMat m4 = m1 % 3;
    double modulo_expected[3][3] = {{1, 2, 0}, {1, 2, 0}, {1, 2, 0}};
    assert_matrix_values(m4, modulo_expected, "Modulo with scalar operator works correctly");

    // Test division by scalar
    SquareMat m5 = m1 / 2.0;
    double division_expected[3][3] = {{0.5, 1.0, 1.5}, {2.0, 2.5, 3.0}, {3.5, 4.0, 4.5}};
    assert_matrix_values(m5, division_expected, "Division by scalar operator works correctly");
}

// Test power and special operations
void test_power_and_special_operations()
{
    cout << "\n=== Testing Power and Special Operations ===\n";

    // Create test matrix
    SquareMat m1 = createTestMatrix(3);

    // Test power operator
    SquareMat m2 = m1 ^ 2;
    double power_expected[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    assert_matrix_values(m2, power_expected, "Power operator works correctly");

    // Test transpose
    SquareMat m3 = ~m1;
    double transpose_expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    assert_matrix_values(m3, transpose_expected, "Transpose operator works correctly");

    // Test determinant
    double det = !m1;
    assert_true(det == 0.0, "Determinant operator works correctly");

    // Create a matrix with non-zero determinant
    double m4_values[3][3] = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
    SquareMat m4 = createMatrixFromArray(m4_values);
    double det2 = !m4;
    assert_true(det2 != 0.0, "Determinant operator works for non-singular matrix");
}

// Test increment/decrement operators
void test_increment_decrement_operators()
{
    cout << "\n=== Testing Increment/Decrement Operators ===\n";

    // Create test matrix using helper function
    SquareMat m1 = createTestMatrix(3); // 1,2,3,4,5,6,7,8,9

    // Test pre-increment
    SquareMat m2 = m1;
    SquareMat &m3 = ++m2;
    double preinc_expected[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    assert_matrix_values(m2, preinc_expected, "Pre-increment operator works correctly");
    assert_true(&m3 == &m2, "Pre-increment returns reference to the object");

    // Test post-increment
    SquareMat m4 = m1;
    SquareMat m5 = m4++;
    double postinc_obj_expected[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    assert_matrix_values(m4, postinc_obj_expected, "Post-increment changes the object correctly");
    double postinc_ret_expected[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    assert_matrix_values(m5, postinc_ret_expected, "Post-increment returns original value");

    // Test pre-decrement
    SquareMat m6 = m1;
    SquareMat &m7 = --m6;
    double predec_expected[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    assert_matrix_values(m6, predec_expected, "Pre-decrement operator works correctly");
    assert_true(&m7 == &m6, "Pre-decrement returns reference to the object");

    // Test post-decrement
    SquareMat m8 = m1;
    SquareMat m9 = m8--;
    double postdec_obj_expected[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    assert_matrix_values(m8, postdec_obj_expected, "Post-decrement changes the object correctly");
    double postdec_ret_expected[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    assert_matrix_values(m9, postdec_ret_expected, "Post-decrement returns original value");
}

// Test comparison operators
void test_comparison_operators()
{
    cout << "\n=== Testing Comparison Operators ===\n";

    // Create test matrices
    SquareMat m1 = createTestMatrix(3);                                  // sum = 45
    SquareMat m2 = createTestMatrix(3, 9.0, -1.0);                       // sum = 45
    double m3_values[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}}; // sum = 90
    SquareMat m3 = createMatrixFromArray(m3_values);

    // Test equality
    assert_true(m1 == m2, "Equality operator works correctly (equal sums)");
    assert_true(!(m1 == m3), "Equality operator works correctly (different sums)");

    // Test inequality
    assert_true(!(m1 != m2), "Inequality operator works correctly (equal sums)");
    assert_true(m1 != m3, "Inequality operator works correctly (different sums)");

    // Test less than
    assert_true(!(m1 < m2), "Less than operator works correctly (equal sums)");
    assert_true(m1 < m3, "Less than operator works correctly (different sums)");

    // Test greater than
    assert_true(!(m1 > m2), "Greater than operator works correctly (equal sums)");
    assert_true(m3 > m1, "Greater than operator works correctly (different sums)");

    // Test less than or equal
    assert_true(m1 <= m2, "Less than or equal operator works correctly (equal sums)");
    assert_true(m1 <= m3, "Less than or equal operator works correctly (different sums)");

    // Test greater than or equal
    assert_true(m1 >= m2, "Greater than or equal operator works correctly (equal sums)");
    assert_true(m3 >= m1, "Greater than or equal operator works correctly (different sums)");
}

// Test compound assignment operators
void test_compound_assignment_operators()
{
    cout << "\n=== Testing Compound Assignment Operators ===\n";

    // Create test matrices
    SquareMat m1 = createTestMatrix(3);
    SquareMat m2 = createTestMatrix(3, 9.0, -1.0);

    // Test compound addition
    SquareMat m3 = m1;
    m3 += m2;
    double compound_add_expected[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    assert_matrix_values(m3, compound_add_expected, "Compound addition operator works correctly");

    // Test compound subtraction
    SquareMat m4 = m1;
    m4 -= m2;
    double compound_sub_expected[3][3] = {{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
    assert_matrix_values(m4, compound_sub_expected, "Compound subtraction operator works correctly");

    // Test compound matrix multiplication
    SquareMat m5 = m1;
    m5 *= m2;
    double compound_mult_expected[3][3] = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    assert_matrix_values(m5, compound_mult_expected, "Compound matrix multiplication operator works correctly");

    // Test compound scalar multiplication
    SquareMat m6 = m1;
    m6 *= 2.0;
    double compound_scalar_mult_expected[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    assert_matrix_values(m6, compound_scalar_mult_expected, "Compound scalar multiplication operator works correctly");

    // Test compound division by scalar
    SquareMat m7 = m1;
    m7 /= 2.0;
    double compound_div_expected[3][3] = {{0.5, 1.0, 1.5}, {2.0, 2.5, 3.0}, {3.5, 4.0, 4.5}};
    assert_matrix_values(m7, compound_div_expected, "Compound division by scalar operator works correctly");

    // Test compound element-wise multiplication
    SquareMat m8 = m1;
    m8 %= m2;
    double compound_elem_mult_expected[3][3] = {{9, 16, 21}, {24, 25, 24}, {21, 16, 9}};
    assert_matrix_values(m8, compound_elem_mult_expected, "Compound element-wise multiplication operator works correctly");

    // Test compound modulo with scalar
    SquareMat m9 = m1;
    m9 %= 3;
    double compound_modulo_expected[3][3] = {{1, 2, 0}, {1, 2, 0}, {1, 2, 0}};
    assert_matrix_values(m9, compound_modulo_expected, "Compound modulo with scalar operator works correctly");
}

int main()
{
    cout << "Starting SquareMat unit tests...\n";

    // Run tests
    test_arithmetic_operators();
    test_element_wise_operations();
    test_power_and_special_operations();
    test_increment_decrement_operators();
    test_comparison_operators();
    test_compound_assignment_operators();

    // Print summary
    // cout << "\n=== Test Summary ===\n";
    // cout << "Passed: " << passedTests << " / " << totalTests << " tests" << endl;
    // cout << "Success rate: " << fixed << setprecision(2)
    //      << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << endl;

    // return (passedTests == totalTests) ? 0 : 1; // Return success only if all tests passed
    return 0;
}