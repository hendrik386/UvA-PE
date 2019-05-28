#pragma once

#if __GNUC__ >= 8
	#include <filesystem>
	using namespace std;
#else
	#include <experimental/filesystem>
	using namespace std::experimental;
#endif

#include <vector>

#include "Body.hpp"
#include "Constants.hpp"
#include "Image.hpp"
#include "Worker.hpp"

class Universe {
		const double systemSize;

		std::vector<Body> initializeBodies(const int& bodyCount);

		void interactBodies();

		void updateBodies();

		Worker *m_upNorthWestWorker = nullptr;
		Worker *m_upNorthEastWorker = nullptr;
		Worker *m_upSouthWestWorker = nullptr;
		Worker *m_upSouthEastWorker = nullptr;
		Worker *m_downNorthWestWorker = nullptr;
		Worker *m_downNorthEastWorker = nullptr;
		Worker *m_downSouthWestWorker = nullptr;
		Worker *m_downSouthEastWorker = nullptr;

	public:
		static Universe loadFromCsvFile(const filesystem::path& filePath, const double& systemSize);
		static Universe loadFromCsvFile(const filesystem::path& filePath, const double& systemSize, int &bodyCount);

		std::vector<Body> bodies;

		/**
		 * Creates a new universe.
		 * @param bodies The bodies to place in the universe.
		 * @param systemSize Farthest particles in AU.
		 */
		Universe(std::vector<Body> bodies, const double& systemSize);

		Universe(const int& bodyCount, const double& systemSize);

		~Universe();

		/**
		 * Performs universe simulation.
		 * @param steps Will automatically stop running after this many steps.
		 * @param renderInterval How many timesteps to simulate in between each frame rendered.
		 * @param createImages Whether to create images during the simulation.
		 * @param imageWidth The width of the rendered image.
		 * @param imageHeight The height of the rendered image.
		 */
		void simulate(const int& steps, const int& renderInterval, const bool& createImages, const int& imageWidth = 0, const int& imageHeight = 0);

		void writeToCsvFile(const filesystem::path& filePath);
};

