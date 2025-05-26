//avrahamavitan@gmail.com

#pragma once

#include <iostream>
#include <stdexcept>

namespace mat {

// SquareMat: square matrix of doubles
class SquareMat {
private:
    int size;        // dimension of matrix
    double** data;   // 2D array of values

    void allocate();
    void deallocate();
    void copy(const SquareMat& other);
    double calcDeterminant(double** mat, int n) const;

public:
    SquareMat(int size);                  // create zero matrix
    SquareMat(const SquareMat& other);    // copy constructor
    SquareMat& operator=(const SquareMat& other);
    ~SquareMat();                         // destructor

    double* operator[](int index);        // access row
    const double* operator[](int index) const;

    SquareMat operator+(const SquareMat& other) const;
    SquareMat operator-(const SquareMat& other) const;
    SquareMat operator-() const;

    SquareMat operator*(const SquareMat& other) const;
    SquareMat operator*(double scalar) const;
    friend SquareMat operator*(double scalar, const SquareMat& mat);

    SquareMat operator%(const SquareMat& other) const;
    SquareMat operator%(int mod) const;

    SquareMat operator/(double scalar) const;
    SquareMat operator^(int power) const;

    SquareMat& operator++();
    SquareMat operator++(int);
    SquareMat& operator--();
    SquareMat operator--(int);

    SquareMat operator~() const;

    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    double operator!() const;

    SquareMat& operator+=(const SquareMat& other);
    SquareMat& operator-=(const SquareMat& other);
    SquareMat& operator*=(const SquareMat& other);
    SquareMat& operator*=(double scalar);
    SquareMat& operator/=(double scalar);
    SquareMat& operator%=(const SquareMat& other);
    SquareMat& operator%=(int mod);

    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
    friend std::istream& operator>>(std::istream& in, SquareMat& mat);
};

} // namespace mat
