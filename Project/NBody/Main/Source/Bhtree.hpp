#pragma once

#include "stdio.h"

#include "Body.hpp"
#include "Octant.hpp"

class Bhtree {
		Body* rootBody;

		Body* toDelete;

		Octant* rootOctant;

		Bhtree* upNorthWest;

		Bhtree* upNorthEast;

		Bhtree* upSouthWest;

		Bhtree* upSouthEast;

		Bhtree* downNorthWest;

		Bhtree* downNorthEast;

		Bhtree* downSouthWest;

		Bhtree* downSouthEast;

	public:
		Bhtree(Octant* __restrict__ rootOctant);

		~Bhtree();

		bool isExternal() const;

		void insert(Body* __restrict__ body);

		void interact(Body* __restrict__ body);
};



