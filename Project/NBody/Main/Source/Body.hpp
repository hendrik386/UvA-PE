#pragma once

#include "Vector3.hpp"

class Body {
	public:
		static void singleInteraction(Body& left, Body& right, const bool& singleTreePart, const bool& updateLeftAcceleration, const bool& updateRightAcceleration, const bool& updateLeftFriction, const bool& updateRightFriction);

		/**
		 * Position, expressed in AU.
		 */
		Vector3D position;

		Vector3D velocity;

		Vector3D acceleration;

		double mass;

		Body(const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration, const double& mass);

		double magnitude(const Body& other) const;

		void update();
};
