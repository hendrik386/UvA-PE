#pragma once

#include "Constants.hpp"
#include "Vector3.hpp"

class Octant {
		Vector3D center;

		double length;

		double lengthDiv2;

		double lengthDiv4;

		double plusBound[3];

		double minBound[3];

		double plusZ;

		double minZ;

		double plusY;

		double minY;

		double plusX;

		double minX;

	public:
		Octant(const Vector3D& m, const double l);

		double getLength();

		bool contains(const Vector3D& p);

		bool isInU(const Vector3D& p);

		bool isInN(const Vector3D& p);

		bool isInE(const Vector3D& p);

		bool containsUNW(const Vector3D& p);

		Octant* mUNW();

		bool containsUNE(const Vector3D& p);

		Octant* mUNE();

		bool containsUSW(const Vector3D& p);

		Octant* mUSW();

		bool containsUSE(const Vector3D& p);

		Octant* mUSE();

		bool containsDNW(const Vector3D& p);

		Octant* mDNW();

		bool containsDNE(const Vector3D& p);

		Octant* mDNE();

		bool containsDSW(const Vector3D& p);

		Octant* mDSW();

		bool containsDSE(const Vector3D& p);

		Octant* mDSE();
};