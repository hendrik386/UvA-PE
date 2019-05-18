#pragma once

#include <filesystem>
#include <vector>

#include "Body.hpp"
#include "Constants.hpp"
#include "Image.hpp"

class Universe {
		const double systemSize;

		std::vector<Body> initializeBodies(const int& bodyCount);

		void interactBodies();

		void updateBodies();

	public:
		static Universe loadFromCsvFile(const std::filesystem::path& filePath, const double& systemSize);

		std::vector<Body> bodies;

		/**
		 * Creates a new universe.
		 * @param bodies The bodies to place in the universe.
		 * @param systemSize Farthest particles in AU.
		 */
		Universe(std::vector<Body> bodies, const double& systemSize);

		Universe(const int& bodyCount, const double& systemSize);

		/**
		 * Performs universe simulation.
		 * @param steps Will automatically stop running after this many steps.
		 * @param renderInterval How many timesteps to simulate in between each frame rendered.
		 * @param createImages Whether to create images during the simulation.
		 * @param imageWidth The width of the rendered image.
		 * @param imageHeight The height of the rendered image.
		 */
		void simulate(const int& steps, const int& renderInterval, const bool& createImages, const int& imageWidth = 0, const int& imageHeight = 0);

		void writeToCsvFile(const std::filesystem::path& filePath);
};

