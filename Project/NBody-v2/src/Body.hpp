#ifndef BODY_HPP_
#define BODY_HPP_

#include <cmath>

#include "Vector3.hpp"

struct body {
	vec3 position;

	vec3 velocity;

	vec3 acceleration;

	double mass;

	double magnitude(const body* __restrict__ other);
};

#endif
