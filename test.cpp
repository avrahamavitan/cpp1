//avrahamavitan@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <sstream>
using namespace mat; // assuming the SquareMat class is in namespace mat
// Test that valid operations work without errors
TEST_CASE("Valid operations do not throw") {
    SquareMat a(2), b(2); // create two 2x2 matrices
    a[0][0] = 1; a[0][1] = 2; // set values in matrix a
    a[1][0] = 3; a[1][1] = 4;
    b[0][0] = 5; b[0][1] = 6; // set values in matrix b
    b[1][0] = 7; b[1][1] = 8;

    // check each operator does not throw an exception
    CHECK_NOTHROW(a + b); // add
    CHECK_NOTHROW(a - b); // subtract
    CHECK_NOTHROW(-a);    // unary minus
    CHECK_NOTHROW(a * b); // matrix multiply
    CHECK_NOTHROW(a * 2.5); // scalar multiply
    CHECK_NOTHROW(a % b); // element-wise multiply
    CHECK_NOTHROW(a % 3); // modulo each element by 3
    CHECK_NOTHROW(a / 2.0); // divide each element by 2
    CHECK_NOTHROW(a ^ 2); // power 2
    CHECK_NOTHROW(++a); // pre-increment
    CHECK_NOTHROW(a++); // post-increment
    CHECK_NOTHROW(--a); // pre-decrement
    CHECK_NOTHROW(a--); // post-decrement
    CHECK_NOTHROW(~a);   // transpose
    CHECK_NOTHROW(!a);   // determinant
    // comparison operators
    CHECK_NOTHROW(a == b);
    CHECK_NOTHROW(a != b);
    CHECK_NOTHROW(a < b);
    CHECK_NOTHROW(a <= b);
    CHECK_NOTHROW(a > b);
    CHECK_NOTHROW(a >= b);
    // combined assignments
    CHECK_NOTHROW(a += b);
    CHECK_NOTHROW(a -= b);
    CHECK_NOTHROW(a *= 2.0);
    CHECK_NOTHROW(a /= 2.0);
    CHECK_NOTHROW(a %= 2);
}

// Test that mismatched sizes throw invalid_argument
TEST_CASE("Size mismatch exceptions") {
    SquareMat a(2), c(3);
    CHECK_THROWS_AS(a + c, std::invalid_argument);
    CHECK_THROWS_AS(a - c, std::invalid_argument);
    CHECK_THROWS_AS(a * c, std::invalid_argument);
    CHECK_THROWS_AS(a % c, std::invalid_argument);
    CHECK_THROWS_AS(a += c, std::invalid_argument);
    CHECK_THROWS_AS(a -= c, std::invalid_argument);
    CHECK_THROWS_AS(a %= c, std::invalid_argument);
}

// Test division and modulo by zero throw invalid_argument
TEST_CASE("Zero division and modulo exceptions") {
    SquareMat m(2); // matrix with values
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    CHECK_THROWS_AS(m / 0.0, std::invalid_argument);
    CHECK_THROWS_AS(m %= 0, std::invalid_argument);
    CHECK_THROWS_AS(m % 0, std::invalid_argument);
}

// Test that negative power throws invalid_argument
TEST_CASE("Negative power exception") {
    SquareMat m(2);
    CHECK_THROWS_AS(m ^ -1, std::invalid_argument);
}

// Test that reading bad input throws invalid_argument
TEST_CASE("Stream extraction validation") {
    std::istringstream bad_in("1 2 x 4");
    SquareMat m(2);
    CHECK_THROWS_AS(bad_in >> m, std::invalid_argument); // x is not a number
}

// Test that compound assignments give correct results
TEST_CASE("Compound assignment correctness") {
    SquareMat m1(2), m2(2);
    m1[0][0] = 1; m1[1][1] = 2;
    m2[0][0] = 3; m2[1][1] = 4;
    
    m1 += m2; // add m2 to m1
    CHECK(m1[0][0] == 4); CHECK(m1[1][1] == 6);

    m1 -= m2; // subtract m2
    CHECK(m1[0][0] == 1); CHECK(m1[1][1] == 2);

    m1 *= 2;  // multiply by 2
    CHECK(m1[0][0] == 2); CHECK(m1[1][1] == 4);

    m1 /= 2;  // divide by 2
    CHECK(m1[0][0] == 1); CHECK(m1[1][1] == 2);

    m1 %= 2;  // modulo 2
    CHECK(m1[0][0] == 1); CHECK(m1[1][1] == 0);
}

// Test <= and >= work for equal sums
TEST_CASE("Less-equal and greater-equal for equal sums") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[1][1] = 1;
    b[0][0] = 2; b[1][1] = 0;
    CHECK(a <= b); CHECK(a >= b); // both sums are 2
}

// Bulk tests: run many checks for sizes 1-4 and values 0-9
TEST_CASE("Bulk operator tests") {
    for (int size = 1; size <= 4; ++size) {
        for (int v = 0; v <= 9; ++v) {
            SquareMat m(size);
            // fill matrix with the same value
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    m[i][j] = v;
            
            // check addition result
            auto add = m + m; // each element should be 2*v
            CHECK(add[0][0] == 2*v);
            
            // check subtraction result
            auto sub = m - m; // should be zero
            CHECK(sub[0][0] == 0);
            
            // check multiplication result
            auto mul = m * m; // each element = size * v * v
            CHECK(mul[0][0] == size * v * v);
            
            // check scalar multiply
            auto sm = m * 2; // each element = 2*v
            CHECK(sm[0][0] == 2*v);
            
            // check transpose
            auto tr = ~m; // transpose should keep same values
            CHECK(tr[0][0] == v);
        }
    }
}
