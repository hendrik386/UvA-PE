#pragma once

#include "stdio.h"

#include "Body.hpp"
#include "Octant.hpp"

class Bhtree {
		Body* rootBody = nullptr;

		Body* toDelete = nullptr;

		Octant rootOctant;

		Bhtree* upNorthWest = nullptr;

		Bhtree* upNorthEast = nullptr;

		Bhtree* upSouthWest = nullptr;

		Bhtree* upSouthEast = nullptr;

		Bhtree* downNorthWest = nullptr;

		Bhtree* downNorthEast = nullptr;

		Bhtree* downSouthWest = nullptr;

		Bhtree* downSouthEast = nullptr;

	public:
		Bhtree(const Octant& rootOctant);

		~Bhtree();

		bool isExternal() const;

		void insert(Body* __restrict__ body);

		void interact(Body* __restrict__ body);
};



