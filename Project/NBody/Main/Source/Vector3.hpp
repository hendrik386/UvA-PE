#pragma once

class Vector3D {
	public:
		double x;

		double y;

		double z;

		Vector3D(const double& x, const double& y, const double& z);

		double magnitude() const;

		Vector3D& operator +=(const Vector3D& other);

		Vector3D& operator +=(const double& other);

		Vector3D& operator -=(const Vector3D& other);

		Vector3D& operator -=(const double& other);

		Vector3D& operator *=(const double& other);

		Vector3D& operator /=(const double& other);

		friend Vector3D operator +(const Vector3D& left, const Vector3D& right);

		friend Vector3D operator +(const Vector3D& left, const double& right);

		friend Vector3D operator -(const Vector3D& left, const Vector3D& right);

		friend Vector3D operator -(const Vector3D& left, const double& right);

		friend Vector3D operator *(const Vector3D& left, const double& right);

		friend Vector3D operator *(const double& left, const Vector3D& right);

		friend Vector3D operator /(const Vector3D& left, const double& right);

		friend bool operator <(const Vector3D& left, const Vector3D& right);

		friend bool operator <=(const Vector3D& left, const Vector3D& right);

		friend bool operator >(const Vector3D& left, const Vector3D& right);

		friend bool operator >=(const Vector3D& left, const Vector3D& right);
};
