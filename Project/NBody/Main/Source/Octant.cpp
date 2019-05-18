#include "Octant.hpp"

Octant::Octant(const Vector3D& center, const double& length) :
	center(center),
	length(length),
	lengthDiv2(length / 2.0f),
	lengthDiv4(length / 4.0f),
	positiveBound(center + lengthDiv2),
	negativeBound(center - lengthDiv2),
	positive(center + lengthDiv4 + lengthDiv4),
	negative(center + lengthDiv4 - lengthDiv4) {
}

double Octant::getLength() {
	return length;
}

bool Octant::contains(const Vector3D& point) {
	return point.x <= positiveBound.x && point.x >= negativeBound.x && point.y <= positiveBound.y && point.y >= negativeBound.y && point.z <= positiveBound.z && point.z >= negativeBound.z;

	// return point.x <= center->x + length / 2.0 && point.x >= center->x - length / 2.0 &&
	// 	   point.y <= center->y + length / 2.0 && point.y >= center->y - length / 2.0 &&
	// 	   point.z <= center->z + length / 2.0 && point.z >= center->z - length / 2.0;
}

bool Octant::isInU(const Vector3D& point) {
	// double midZ = center.z + lengthDiv4;
	// double positive.z = midZ + lengthDiv4;
	// double negative.z = midZ - lengthDiv4;

	return point.z <= positive.z && point.z >= negative.z;
}

bool Octant::isInN(const Vector3D& point) {
	// double midY = center.y + lengthDiv4;
	// double positive.y = midY + lengthDiv4;
	// double negative.y = midY - lengthDiv4;

	return point.y <= positive.y && point.y >= negative.y;
}

bool Octant::isInE(const Vector3D& point) {
	// double midX = center.x + lengthDiv4;
	// double positive.x = midX + lengthDiv4;
	// double negative.x = midX - lengthDiv4;

	return point.x <= positive.x && point.x >= negative.x;
}

Octant* Octant::centerUpNorthWest() {
	return new Octant(
		Vector3D(
			center.x - lengthDiv4,
			center.y + lengthDiv4,
			center.z + lengthDiv4
		),
		lengthDiv2
	);
}

Octant* Octant::centerUpNorthEast() {
	return new Octant(center + lengthDiv4, lengthDiv2);
}

Octant* Octant::centerUpSouthWest() {
	return new Octant(
		Vector3D(
			center.x - lengthDiv4,
			center.y - lengthDiv4,
			center.z + lengthDiv4
		),
		lengthDiv2
	);
}

Octant* Octant::centerUpSouthEast() {
	return new Octant(
		Vector3D(
			center.x + lengthDiv4,
			center.y - lengthDiv4,
			center.z + lengthDiv4
		),
		lengthDiv2
	);
}

Octant* Octant::centerDownNorthWest() {
	return new Octant(
		Vector3D(
			center.x - lengthDiv4,
			center.y + lengthDiv4,
			center.z - lengthDiv4
		),
		lengthDiv2
	);
}

Octant* Octant::centerDownNorthEast() {
	return new Octant(
		Vector3D(
			center.x + lengthDiv4,
			center.y + lengthDiv4,
			center.z - lengthDiv4
		),
		lengthDiv2
	);
}

Octant* Octant::centerDownSouthWest() {
	return new Octant(center - lengthDiv4, lengthDiv2);
}

Octant* Octant::centerDownSouthEast() {
	return new Octant(
		Vector3D(
			center.x + lengthDiv4,
			center.y - lengthDiv4,
			center.z - lengthDiv4
		),
		lengthDiv2
	);
}

bool Octant::containsUpNorthWest(const Vector3D& point) {
	Vector3D centerUpNorthWest(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z + lengthDiv4
	);

	return point >= centerUpNorthWest - lengthDiv4 && point <= centerUpNorthWest + lengthDiv4;
}

bool Octant::containsUpNorthEast(const Vector3D& point) {
	Vector3D centerUpNorthEast = center + lengthDiv4;

	return point >= centerUpNorthEast - lengthDiv4 && point <= centerUpNorthEast + lengthDiv4;
}

bool Octant::containsUpSouthWest(const Vector3D& point) {
	Vector3D centerUpSouthWest(
		center.x - lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
	);

	return point >= centerUpSouthWest - lengthDiv4 && point <= centerUpSouthWest + lengthDiv4;
}

bool Octant::containsUpSouthEast(const Vector3D& point) {
	Vector3D centerUpSouthEast(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z + lengthDiv4
	);

	return point >= centerUpSouthEast - lengthDiv4 && point <= centerUpSouthEast + lengthDiv4;
}

bool Octant::containsDownNorthWest(const Vector3D& point) {
	Vector3D centerDownNorthWest(
		center.x - lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
	);

	return point >= centerDownNorthWest - lengthDiv4 && point <= centerDownNorthWest + lengthDiv4;
}

bool Octant::containsDownNorthEast(const Vector3D& point) {
	Vector3D centerDownNorthEast(
		center.x + lengthDiv4,
		center.y + lengthDiv4,
		center.z - lengthDiv4
	);

	return point >= centerDownNorthEast - lengthDiv4 && point <= centerDownNorthEast + lengthDiv4;
}

bool Octant::containsDownSouthWest(const Vector3D& point) {
	Vector3D centerDownSouthWest = center - lengthDiv4;

	return point >= centerDownSouthWest - lengthDiv4 && point <= centerDownSouthWest + lengthDiv4;
}

bool Octant::containsDownSouthEast(const Vector3D& point) {
	Vector3D centerDownSouthEast(
		center.x + lengthDiv4,
		center.y - lengthDiv4,
		center.z - lengthDiv4
	);

	return point >= centerDownSouthEast - lengthDiv4 && point <= centerDownSouthEast + lengthDiv4;
}
