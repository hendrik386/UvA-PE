#include "Octant.hpp"

Octant::Octant(const Vector3D& m, const double l) : center(m) {
	length = l;
	lengthDiv2 = length / 2.0f;
	lengthDiv4 = length / 4.0f;

	plusBound[0] = center.x + lengthDiv2;
	plusBound[1] = center.y + lengthDiv2;
	plusBound[2] = center.z + lengthDiv2;

	minBound[0] = center.x - lengthDiv2;
	minBound[1] = center.y - lengthDiv2;
	minBound[2] = center.z - lengthDiv2;

	double midZ = center.z + lengthDiv4;
	plusZ = midZ + lengthDiv4;
	minZ = midZ - lengthDiv4;

	double midY = center.y + lengthDiv4;
	plusY = midY + lengthDiv4;
	minY = midY - lengthDiv4;

	double midX = center.x + lengthDiv4;
	plusX = midX + lengthDiv4;
	minX = midX - lengthDiv4;
}

double Octant::getLength() {
	return length;
}

bool Octant::contains(const Vector3D& p) {
	return p.x <= plusBound[0] && p.x >= minBound[0] &&
		p.y <= plusBound[1] && p.y >= minBound[1] &&
		p.z <= plusBound[2] && p.z >= minBound[2];

	// return p.x <= center->x + length / 2.0 && p.x >= center->x - length / 2.0 &&
	// 	   p.y <= center->y + length / 2.0 && p.y >= center->y - length / 2.0 &&
	// 	   p.z <= center->z + length / 2.0 && p.z >= center->z - length / 2.0;
}

bool Octant::isInU(const Vector3D& p) {
	// double midZ = center.z + lengthDiv4;
	// double plusZ = midZ + lengthDiv4;
	// double minZ = midZ - lengthDiv4;

	return p.z <= plusZ && p.z >= minZ;
}

bool Octant::isInN(const Vector3D& p) {
	// double midY = center.y + lengthDiv4;
	// double plusY = midY + lengthDiv4;
	// double minY = midY - lengthDiv4;

	return p.y <= plusY && p.y >= minY;
}

bool Octant::isInE(const Vector3D& p) {
	// double midX = center.x + lengthDiv4;
	// double plusX = midX + lengthDiv4;
	// double minX = midX - lengthDiv4;

	return p.x <= plusX && p.x >= minX;
}

bool Octant::containsUNW(const Vector3D& p) {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z + lengthDiv4
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

Octant* Octant::mUNW() {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z + lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsUNE(const Vector3D& p) {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y + lengthDiv4,
		center.z + lengthDiv4
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

Octant* Octant::mUNE() {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y + lengthDiv4,
		center.z + lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsUSW(const Vector3D& p) {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
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

Octant* Octant::mUSW() {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsUSE(const Vector3D& p) {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
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

Octant* Octant::mUSE() {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsDNW(const Vector3D& p) {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
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

Octant* Octant::mDNW() {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsDNE(const Vector3D& p) {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
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

Octant* Octant::mDNE() {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsDSW(const Vector3D& p) {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y - lengthDiv4,
		center.z - lengthDiv4
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

Octant* Octant::mDSW() {
	Vector3D newMid(
		center.x - lengthDiv4,
		center.y - lengthDiv4,
		center.z - lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}

bool Octant::containsDSE(const Vector3D& p) {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z - lengthDiv4
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

Octant* Octant::mDSE() {
	Vector3D newMid(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z - lengthDiv4
	);

	return new Octant(newMid, lengthDiv2);
}
