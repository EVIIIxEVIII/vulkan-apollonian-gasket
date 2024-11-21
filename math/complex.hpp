#ifndef COMPLEX_H
#define COMPLEX_H

class complex {
public:
    complex(double real, double imaginary): real(real), imaginary(imaginary) {};

    double getImaginary() const;
    double getReal() const;

    complex operator*(const complex& other) const;
    complex operator*(const double t) const;
    complex operator-(const complex& other) const;
    complex operator+(const complex& other) const;

    complex sqrt() const;

private:
    double real;
    double imaginary;
};


#endif
