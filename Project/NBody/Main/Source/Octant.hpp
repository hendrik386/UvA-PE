#pragma once

/*
 * Octant.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: peterwhidden
 */

#include "Constants.hpp"
#include "Vector3.hpp"

class Octant {
		Vector3D mid;

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
		Octant(const Vector3D& m, const double l) : mid(m) {
			length = l;
			lengthDiv2 = length / 2.0f;
			lengthDiv4 = length / 4.0f;

			plusBound[0] = mid.x + lengthDiv2;
			plusBound[1] = mid.y + lengthDiv2;
			plusBound[2] = mid.z + lengthDiv2;

			minBound[0] = mid.x - lengthDiv2;
			minBound[1] = mid.y - lengthDiv2;
			minBound[2] = mid.z - lengthDiv2;

			double midZ = mid.z + lengthDiv4;
			plusZ = midZ + lengthDiv4;
			minZ = midZ - lengthDiv4;

			double midY = mid.y + lengthDiv4;
			plusY = midY + lengthDiv4;
			minY = midY - lengthDiv4;

			double midX = mid.x + lengthDiv4;
			plusX = midX + lengthDiv4;
			minX = midX - lengthDiv4;
		}

		~Octant() {
			// delete mid;
		}

		double getLength() {
			return length;
		}

		inline bool contains(const Vector3D& p) {
			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];

			// return p.x <= mid->x + length / 2.0 && p.x >= mid->x - length / 2.0 &&
			// 	   p.y <= mid->y + length / 2.0 && p.y >= mid->y - length / 2.0 &&
			// 	   p.z <= mid->z + length / 2.0 && p.z >= mid->z - length / 2.0;
		}

		bool isInU(const Vector3D& p) {
			// double midZ = mid.z + lengthDiv4;
			// double plusZ = midZ + lengthDiv4;
			// double minZ = midZ - lengthDiv4;

			return p.z <= plusZ && p.z >= minZ;
		}

		bool isInN(const Vector3D& p) {
			// double midY = mid.y + lengthDiv4;
			// double plusY = midY + lengthDiv4;
			// double minY = midY - lengthDiv4;

			return p.y <= plusY && p.y >= minY;
		}

		bool isInE(const Vector3D& p) {
			// double midX = mid.x + lengthDiv4;
			// double plusX = midX + lengthDiv4;
			// double minX = midX - lengthDiv4;

			return p.x <= plusX && p.x >= minX;
		}

		bool containsUNW(const Vector3D& p) {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y + lengthDiv4,
				mid.z + lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mUNW() {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y + lengthDiv4,
				mid.z + lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsUNE(const Vector3D& p) {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y + lengthDiv4,
				mid.z + lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mUNE() {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y + lengthDiv4,
				mid.z + lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsUSW(const Vector3D& p) {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y - lengthDiv4,
				mid.z + lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mUSW() {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y - lengthDiv4,
				mid.z + lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsUSE(const Vector3D& p) {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y - lengthDiv4,
				mid.z + lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mUSE() {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y - lengthDiv4,
				mid.z + lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsDNW(const Vector3D& p) {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y + lengthDiv4,
				mid.z - lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mDNW() {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y + lengthDiv4,
				mid.z - lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsDNE(const Vector3D& p) {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y + lengthDiv4,
				mid.z - lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mDNE() {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y + lengthDiv4,
				mid.z - lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsDSW(const Vector3D& p) {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y - lengthDiv4,
				mid.z - lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mDSW() {
			Vector3D newMid(
				mid.x - lengthDiv4,
				mid.y - lengthDiv4,
				mid.z - lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}

		bool containsDSE(const Vector3D& p) {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y - lengthDiv4,
				mid.z - lengthDiv4
			);

			double plusBound[3];
			double minBound[3];

			plusBound[0] = newMid.x + lengthDiv4;
			plusBound[1] = newMid.y + lengthDiv4;
			plusBound[2] = newMid.z + lengthDiv4;

			minBound[0] = newMid.x - lengthDiv4;
			minBound[1] = newMid.y - lengthDiv4;
			minBound[2] = newMid.z - lengthDiv4;

			return p.x <= plusBound[0] && p.x >= minBound[0] &&
				p.y <= plusBound[1] && p.y >= minBound[1] &&
				p.z <= plusBound[2] && p.z >= minBound[2];
		}

		Octant* mDSE() {
			Vector3D newMid(
				mid.x + lengthDiv4,
				mid.y - lengthDiv4,
				mid.z - lengthDiv4
			);

			return new Octant(newMid, lengthDiv2);
		}
};