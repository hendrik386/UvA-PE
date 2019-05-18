#pragma once

#include <memory>

#include "Body.hpp"
#include "Octant.hpp"

class Bhtree {
		Body* rootBody = nullptr;

		bool deleteRootBody = false;

		Octant rootOctant;

		std::unique_ptr<Bhtree> upNorthWest = nullptr;

		std::unique_ptr<Bhtree> upNorthEast = nullptr;

		std::unique_ptr<Bhtree> upSouthWest = nullptr;

		std::unique_ptr<Bhtree> upSouthEast = nullptr;

		std::unique_ptr<Bhtree> downNorthWest = nullptr;

		std::unique_ptr<Bhtree> downNorthEast = nullptr;

		std::unique_ptr<Bhtree> downSouthWest = nullptr;

		std::unique_ptr<Bhtree> downSouthEast = nullptr;

	public:
		Bhtree(const Octant& rootOctant);

		~Bhtree();

		bool isExternal() const;

		void insert(Body& body);

		void interact(Body* __restrict__ body);
};



