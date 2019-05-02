#include <cmath>

#include "Vector3.hpp"

double vec3::magnitude() {
	return sqrt(x * x + y * y + z * z);
}
