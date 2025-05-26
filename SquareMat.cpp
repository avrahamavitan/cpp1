// avrahamavitan@gmail.com
#include "SquareMat.hpp"
#include <cmath>

using namespace mat;

// Constructor: create n x n matrix, initialize all entries to 0
SquareMat::SquareMat(int n) : size(n) {
    if (n <= 0) throw std::invalid_argument("Invalid matrix size");
    allocate(); // allocate 2D array
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            data[i][j] = 0.0; // set each entry to zero
}

// Allocate memory for data array
void SquareMat::allocate() {
    data = new double*[size]; // array of pointers
    for (int i = 0; i < size; ++i)
        data[i] = new double[size]; // each row is an array of doubles
}

// Free allocated memory
void SquareMat::deallocate() {
    for (int i = 0; i < size; ++i)
        delete[] data[i]; // delete each row
    delete[] data;       // delete array of pointers
}

// Copy data from other matrix
void SquareMat::copy(const SquareMat& other) {
    size = other.size;   // copy size
    allocate();          // allocate new memory
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            data[i][j] = other.data[i][j]; // copy each value
}

// Copy constructor: build from another matrix
SquareMat::SquareMat(const SquareMat& other) {
    copy(other);
}

// Assignment operator: clean old data and copy new data
SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this != &other) {
        deallocate();  // free existing memory
        copy(other);   // copy new data
    }
    return *this;
}

// Destructor: free memory
SquareMat::~SquareMat() {
    deallocate();
}

// Access row by index (non-const)
double* SquareMat::operator[](int row) {
    if (row < 0 || row >= size) throw std::out_of_range("Row out of range");
    return data[row]; // return pointer to row
}

// Access row by index (const version)
const double* SquareMat::operator[](int row) const {
    if (row < 0 || row >= size) throw std::out_of_range("Row out of range");
    return data[row];
}

// Add two matrices
SquareMat SquareMat::operator+(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] + other.data[i][j];
    return result;
}

// Subtract two matrices
SquareMat SquareMat::operator-(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] - other.data[i][j];
    return result;
}

// Unary minus: negate each entry
SquareMat SquareMat::operator-() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = -data[i][j];
    return result;
}

// Matrix multiplication
SquareMat SquareMat::operator*(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            for (int k = 0; k < size; ++k)
                result[i][j] += data[i][k] * other.data[k][j];
    return result;
}

// Scalar multiplication: multiply each entry by scalar
SquareMat SquareMat::operator*(double scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] * scalar;
    return result;
}

// Free function: scalar * matrix
SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar; // reuse member function
}

// Element-wise multiplication (mod %) with another matrix
SquareMat SquareMat::operator%(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = static_cast<int>(data[i][j]) % static_cast<int>(other.data[i][j]);
    return result;
}

// Modulo each entry by integer
SquareMat SquareMat::operator%(int mod) const {
    if (mod == 0) throw std::invalid_argument("Modulo by zero");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = static_cast<int>(data[i][j]) % mod;
    return result;
}

// Divide each entry by scalar
SquareMat SquareMat::operator/(double scalar) const {
    if (scalar == 0) throw std::invalid_argument("Division by zero");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] / scalar;
    return result;
}

// Matrix power: raise to non-negative integer power
SquareMat SquareMat::operator^(int power) const {
    if (power < 0) throw std::invalid_argument("Negative powers not supported");
    SquareMat result(size);
    for (int i = 0; i < size; ++i) result[i][i] = 1; // identity
    SquareMat base(*this);
    while (power) {
        if (power % 2) result = result * base; // multiply when bit is set
        base = base * base; // square base
        power /= 2;
    }
    return result;
}

// Pre-increment: add 1 to each entry
SquareMat& SquareMat::operator++() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            ++data[i][j];
    return *this;
}

// Post-increment: return old matrix, then add 1
SquareMat SquareMat::operator++(int) {
    SquareMat tmp(*this);
    ++(*this);
    return tmp;
}

// Pre-decrement: subtract 1 from each entry
SquareMat& SquareMat::operator--() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            --data[i][j];
    return *this;
}

// Post-decrement: return old matrix, then subtract 1
SquareMat SquareMat::operator--(int) {
    SquareMat tmp(*this);
    --(*this);
    return tmp;
}

// Transpose matrix: swap rows and columns
SquareMat SquareMat::operator~() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[j][i];
    return result;
}

// Helper: compute determinant recursively
double SquareMat::calcDeterminant(double** mat, int n) const {
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    double det = 0;
    for (int p = 0; p < n; ++p) {
        // build submatrix for minor
        double** submat = new double*[n-1];
        for (int i = 0; i < n-1; ++i)
            submat[i] = new double[n-1];
        for (int i = 1; i < n; ++i) {
            int colIdx = 0;
            for (int j = 0; j < n; ++j) {
                if (j == p) continue;
                submat[i-1][colIdx++] = mat[i][j];
            }
        }
        double sign = (p % 2 == 0) ? 1 : -1; // alternating signs
        det += sign * mat[0][p] * calcDeterminant(submat, n-1);
        // free submatrix memory
        for (int i = 0; i < n-1; ++i) delete[] submat[i];
        delete[] submat;
    }
    return det;
}

// Determinant operator
double SquareMat::operator!() const {
    return calcDeterminant(data, size);
}

// Equality: compare sums of entries
bool SquareMat::operator==(const SquareMat& other) const {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            sum1 += data[i][j];
            sum2 += other.data[i][j];
        }
    return sum1 == sum2;
}

// Inequality: opposite of ==
bool SquareMat::operator!=(const SquareMat& other) const {
    return !(*this == other);
}

// Less than: compare sums
bool SquareMat::operator<(const SquareMat& other) const {
    double s1 = 0, s2 = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            s1 += data[i][j];
            s2 += other.data[i][j];
        }
    return s1 < s2;
}

// Greater than: use <
bool SquareMat::operator>(const SquareMat& other) const {
    return other < *this;
}

// Less or equal: not greater
bool SquareMat::operator<=(const SquareMat& other) const {
    return !(other < *this);
}

// Greater or equal: not less
bool SquareMat::operator>=(const SquareMat& other) const {
    return !(*this < other);
}

// Compound add
SquareMat& SquareMat::operator+=(const SquareMat& other) {
    return *this = *this + other;
}

// Compound subtract
SquareMat& SquareMat::operator-=(const SquareMat& other) {
    return *this = *this - other;
}

// Compound multiply by matrix
SquareMat& SquareMat::operator*=(const SquareMat& other) {
    return *this = *this * other;
}

// Compound multiply by scalar
SquareMat& SquareMat::operator*=(double scalar) {
    return *this = *this * scalar;
}

// Compound divide by scalar
SquareMat& SquareMat::operator/=(double scalar) {
    return *this = *this / scalar;
}

// Compound element-wise multiply
SquareMat& SquareMat::operator%=(const SquareMat& other) {
    return *this = *this % other;
}

// Compound modulo by scalar
SquareMat& SquareMat::operator%=(int mod) {
    return *this = *this % mod;
}

// Stream operators in namespace mat
namespace mat {

// Output matrix to stream
std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        for (int j = 0; j < mat.size; ++j) {
            os << mat.data[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

// Input matrix from stream
std::istream& operator>>(std::istream& in, SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        for (int j = 0; j < mat.size; ++j) {
            double val;
            if (!(in >> val)) {
                throw std::invalid_argument("Invalid input: expected a real number.");
            }
            mat.data[i][j] = val; // store value
        }
    }
    return in;
}

} // end namespace mat
