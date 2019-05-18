#pragma once

#include "Constants.hpp"
#include "Vector3.hpp"

class Octant {
		Vector3D center;

		double length;

		double lengthDiv2;

		double lengthDiv4;

		Vector3D positiveBound;

		Vector3D negativeBound;

		Vector3D positive;

		Vector3D negative;

	public:
		Octant(const Vector3D& center, const double& length);

		double getLength();

		bool contains(const Vector3D& point);

		bool isInU(const Vector3D& point);

		bool isInN(const Vector3D& point);

		bool isInE(const Vector3D& point);

		Octant centerUpNorthWest();

		Octant centerUpNorthEast();

		Octant centerUpSouthWest();

		Octant centerUpSouthEast();

		Octant centerDownNorthWest();

		Octant centerDownNorthEast();

		Octant centerDownSouthWest();

		Octant centerDownSouthEast();

		bool containsUpNorthWest(const Vector3D& point);

		bool containsUpNorthEast(const Vector3D& point);

		bool containsUpSouthWest(const Vector3D& point);

		bool containsUpSouthEast(const Vector3D& point);

		bool containsDownNorthWest(const Vector3D& point);

		bool containsDownNorthEast(const Vector3D& point);

		bool containsDownSouthWest(const Vector3D& point);

		bool containsDownSouthEast(const Vector3D& point);
};