#include "Body.hpp"

double body::magnitude(const body* other) {
	return std::sqrt(
		std::pow(position.x - other->position.x, 2) +
			std::pow(position.y - other->position.y, 2) +
			std::pow(position.z - other->position.z, 2)
	);
}
