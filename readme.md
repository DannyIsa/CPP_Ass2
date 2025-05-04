<!-- daniisakov@gmail.com -->

# Matrix Namespace

A simple matrix operation handling library. It contains a class called `SquareMat` that makes matrix operations easy.

## What can it do?

- Create square matrices of any size
- Perform basic math operations:
  - Add matrices (`+`)
  - Subtract matrices (`-`)
  - Multiply matrices (`*`)
  - Divide by numbers (`/`)
- Special matrix operations:
  - Transpose a matrix (`~`)
  - Calculate determinant (`!`)
  - Raise to a power (`^`)
- Element-by-element operations:
  - Multiply elements (`%`)
  - Calculate remainder with integers (`%`)
- Compare matrices (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- Increment/decrement all elements (`++`, `--`)
- Compound assignments (`+=`, `-=`, `*=`, `/=`, `%=`)

## How to use it

### Creating matrices

```cpp
// Include the header
#include "square_mat.h"

// Use the namespace
using namespace matrix;

// Create a 3x3 matrix from a 2D array
double **arr = new double *[3];
for (int i = 0; i < 3; i++) {
    arr[i] = new double[3];
}

// Fill with values: 1,2,3,4,5,6,7,8,9
arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;
arr[2][0] = 7; arr[2][1] = 8; arr[2][2] = 9;

// Create matrix
SquareMat m1(arr, 3);

// Create a zero matrix
SquareMat m2(3); // 3x3 matrix filled with zeros
```

### Basic operations

```cpp
// Addition
SquareMat m3 = m1 + m2;

// Subtraction
SquareMat m4 = m1 - m2;

// Matrix multiplication
SquareMat m5 = m1 * m2;

// Scalar multiplication
SquareMat m6 = m1 * 2.0;
SquareMat m7 = 3.0 * m1;

// Transpose (flip rows and columns)
SquareMat m8 = ~m1;

// Calculate determinant
double det = !m1;
```

### Compound operations

```cpp
// Add m2 to m1
m1 += m2;

// Multiply all elements by 2
m1 *= 2.0;

// Divide all elements by 2
m1 /= 2.0;
```
