#include "complex.hpp"
#include <math.h>

double complex::getReal() const {
  return real;
}

double complex::getImaginary() const {
  return imaginary;
}

complex complex::sqrt() const {
    double magnitude = std::sqrt(real * real + imaginary * imaginary);
    double angle = atan2(imaginary, real);

    double newReal = std::sqrt(magnitude) * cos(angle / 2);
    double newImaginary = std::sqrt(magnitude) * sin(angle / 2);

    return complex(newReal, newImaginary);
}

complex complex::operator*(const complex& other) const {
    double newReal = real * other.real - imaginary * other.imaginary;
    double newImaginary = real * other.imaginary + imaginary * other.real;
    return complex(newReal, newImaginary);
}

complex complex::operator*(const double t) const {
    double newReal = real * t;
    double newImaginary = imaginary * t;
    return complex(newReal, newImaginary);
}

complex complex::operator-(const complex& other) const {
    double newReal = real - other.real;
    double newImaginary = imaginary - other.imaginary;
    return complex(newReal, newImaginary);
}

complex complex::operator+(const complex& other) const {
    double newReal = real + other.real;
    double newImaginary = imaginary + other.imaginary;
    return complex(newReal, newImaginary);
}
