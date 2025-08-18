#pragma once
#include <cmath>
#include <iostream>

namespace Motus2D {

struct Vector2D {
    float x{0.0f};
    float y{0.0f};

    // Constructors
    Vector2D() = default;
    Vector2D(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Operator Overloads
    Vector2D operator+(const Vector2D& other) const { return {x + other.x, y + other.y}; }
    Vector2D operator-(const Vector2D& other) const { return {x - other.x, y - other.y}; }
    Vector2D operator*(float scalar) const { return {x * scalar, y * scalar}; }
    Vector2D operator/(float scalar) const { return {x / scalar, y / scalar}; }

    Vector2D& operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }
    Vector2D& operator-=(const Vector2D& other) { x -= other.x; y -= other.y; return *this; }
    Vector2D& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2D& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    // Vector Utilities
    float magnitude() const { return std::sqrt(x * x + y * y); }
    Vector2D normalized() const {
        float mag = magnitude();
        return (mag == 0) ? Vector2D{0,0} : Vector2D{x/mag, y/mag};
    }
    float dot(const Vector2D& other) const { return x * other.x + y * other.y; }
    float cross(const Vector2D& other) const { return x * other.y - y * other.x; }

    void print() const { std::cout << "(" << x << ", " << y << ")"; }
};

} // namespace Motus2D
