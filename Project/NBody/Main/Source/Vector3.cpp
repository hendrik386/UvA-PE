#include <cmath>

#include "Vector3.hpp"

Vector3D::Vector3D(const double& x, const double& y, const double& z) : x(x), y(y), z(z) {
}

double Vector3D::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

Vector3D& Vector3D::operator +=(const Vector3D& other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3D& Vector3D::operator -=(const Vector3D& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3D& Vector3D::operator *=(const double& other) {
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

Vector3D& Vector3D::operator /=(const double& other) {
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

Vector3D operator +(const Vector3D& left, const Vector3D& right) {
	return Vector3D(left) += right;
}

Vector3D operator -(const Vector3D& left, const Vector3D& right) {
	return Vector3D(left) -= right;
}

Vector3D operator *(const Vector3D& left, const double& right) {
	return Vector3D(left) *= right;
}

Vector3D operator *(const double& left, const Vector3D& right) {
	return right * left;
}

Vector3D operator /(const Vector3D& left, const double& right) {
	return Vector3D(left) /= right;
}
