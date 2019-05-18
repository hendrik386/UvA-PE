#include "Body.hpp"

#include <cmath>

#include "Constants.hpp"
#include "Utility.hpp"

void Body::singleInteraction(Body& left, Body& right, const bool& singleTreePart, const bool& updateLeftAcceleration, const bool& updateRightAcceleration, const bool& updateLeftFriction, const bool& updateRightFriction) {
	Vector3D positionDifference = (left.position - right.position) * TO_METERS;

	double distance = positionDifference.magnitude();
	double F = TIME_STEP * (G * left.mass * right.mass) / ((distance * distance + SOFTENING * SOFTENING) * distance);

	if(updateLeftAcceleration) {
		left.acceleration -= F * positionDifference / left.mass;
	}

	if(updateRightAcceleration) {
		right.acceleration += F * positionDifference / right.mass;
	}

	// Friction
	if constexpr (ENABLE_FRICTION) {
		if(singleTreePart) {
			double friction = 0.5 / pow(2.0, FRICTION_FACTOR * (((distance + SOFTENING)) / (TO_METERS)));

			Utility::logInfo(std::to_string(friction) + "\n");

			if(friction > 0.0001) {
				if(updateLeftFriction) {
					left.acceleration += friction * (right.velocity - left.velocity) / 2;
				}

				if(updateRightFriction) {
					right.acceleration -= friction * (left.velocity - right.velocity) / 2; // NOTE: Not sure if this is correct, but it is unused so not important for now
				}
			}
		}
	}
}

Body::Body(const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const double& mass) : position(position), velocity(velocity), acceleration(acceleration), mass(mass) {
}

double Body::magnitude(const Body& other) const {
	return Vector3D(position.x - other.position.x, position.y - other.position.y, position.z - other.position.z).magnitude();
}

void Body::update() {
	// Update velocity
	velocity += acceleration;

	// Reset acceleration
	acceleration.x = 0.0;
	acceleration.y = 0.0;
	acceleration.z = 0.0;

	// Update position
	position += TIME_STEP * velocity / TO_METERS;
}
