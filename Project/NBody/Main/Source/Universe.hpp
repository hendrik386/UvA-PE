#pragma once

#include <filesystem>
#include <vector>

#include "Body.hpp"
#include "Constants.hpp"
#include "Image.hpp"

class Universe {
		std::vector<Body> initializeBodies(const int& bodyCount);

		void interactBodies();

		void updateBodies();

	public:
		static Universe loadFromCsvFile(const std::filesystem::path& filePath, const int& imageWidth, const int& imageHeight);

		Image image;

		std::vector<Body> bodies;

		/**
		 * Creates a new universe.
		 * @param bodyCount Number of small particles.
		 * @param imageWidth The width of the rendered image.
		 * @param imageHeight The height of the rendered image.
		 */
		Universe(const int& bodyCount, const int& imageWidth, const int& imageHeight);

		Universe(std::vector<Body>  bodies, const int& imageWidth, const int& imageHeight);

		void simulate();

		void writeToCsvFile(const std::filesystem::path& filePath);
};

