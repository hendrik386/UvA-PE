#include <utility>

#include "Universe.hpp"

#include <fstream>
#include <random>
#include <csv.h>
#include <omp.h>

#include "Bhtree.hpp"
#include "Utility.hpp"

std::vector<Body> Universe::initializeBodies(const int& bodyCount) {
	std::vector<Body> bodies;

	std::uniform_real_distribution<double> randAngle(0.0, 200.0 * Utility::pi);
	std::uniform_real_distribution<double> randRadius(INNER_BOUND, systemSize);
	std::uniform_real_distribution<double> randHeight(0.0, SYSTEM_THICKNESS);
	std::default_random_engine gen(0);

	//STARS
	const double starVelocity = 0.67 * sqrt((G * SOLAR_MASS) / Utility::astronomicalUnitsToMeters(4 * BINARY_SEPARATION));

	//STAR 1
	bodies.emplace_back(
		Vector3D(0.0 /* -BINARY_SEPARATION */, 0.0, 0.0),
		Vector3D(0.0, 0.0 /* starVelocity */, 0.0),
		Vector3D(0.0, 0.0, 0.0),
		SOLAR_MASS
	);

	//STAR 2
	//bodies.emplace_back(
	//	Vector3D(BINARY_SEPARATION, 0.0, 0.0),
	//	Vector3D(0.0, -starVelocity, 0.0),
	//	Vector3D(0.0, 0.0, 0.0),
	//	SOLAR_MASS
	//);


	///STARTS AT NUMBER OF STARS///
	double totalExtraMass = 0.0;
	for(int index = bodies.size(); index < bodyCount; index++) {
		// Calculate body properties
		const double angle = randAngle(gen);
		const double radius = sqrt(systemSize) * sqrt(randRadius(gen));
		const double velocity = pow(((G * (SOLAR_MASS + ((radius - INNER_BOUND) / systemSize) * EXTRA_MASS * SOLAR_MASS)) / Utility::astronomicalUnitsToMeters(radius)), 0.5);

		// Create the body
		bodies.emplace_back(
			Vector3D(radius * cos(angle), radius * sin(angle), randHeight(gen) - SYSTEM_THICKNESS / 2),
			Vector3D(velocity * sin(angle), -velocity * cos(angle), 0.0),
			Vector3D(0.0, 0.0, 0.0),
			(EXTRA_MASS * SOLAR_MASS) / bodyCount
		);

		// Add the mass
		totalExtraMass += (EXTRA_MASS * SOLAR_MASS) / bodyCount;
	}

	Utility::logInfo("Total Disk Mass: " + std::to_string(totalExtraMass));
	Utility::logInfo("Each Particle weight: " + std::to_string((EXTRA_MASS * SOLAR_MASS) / bodies.size()));
	Utility::logInfo("______________________________\n");

	return bodies;
}

void Universe::interactBodies() {
	// Sun interacts individually
	Utility::logDebug("Calculating Force from star...");

	Body& sun = bodies[0];

	for(int index = 1; index < bodies.size(); index++) {
		Body::singleInteraction(sun, bodies[index], false, true, true, false, false);
	}

	Utility::logDebug("Building Octree...");

	// Build tree
	Octant root = Octant(Vector3D(0.0, 0.0, 0.1374 /* Does this help? */), 60 * systemSize);
	Bhtree tree(root);

	for(int index = 1; index < bodies.size(); index++) {
		Body& body = bodies[index];

		if(root.contains(body.position)) {
			tree.insert(body);
		}
	}

	Utility::logDebug("Calculating particle interactions...");

	// Loop through interactions
	#pragma omp parallel for
	for(int index = 1; index < bodies.size(); index++) {
		Body& body = bodies[index];

		if(root.contains(body.position)) {
			tree.interact(&body);
		}
	}

	Utility::logDebug("Updating particle positions...");

	updateBodies();
}

void Universe::updateBodies() {
	double massAbove = 0.0;
	double massBelow = 0.0;

	#pragma omp parallel for
	for(int index = 0; index < bodies.size(); ++index) {
		Body& body = bodies[index];

		if constexpr (DEBUG_INFO) {
			if(index == 0) {
				Utility::logDebug("Star x acceleration: " + std::to_string(body.acceleration.x));
				Utility::logDebug("Star y acceleration: " + std::to_string(body.acceleration.y));
			} else if(body.position.y > 0.0) {
				massAbove += body.mass;
			} else {
				massBelow += body.mass;
			}
		}

		body.update();
	}

	Utility::logDebug("Mass Below: " + std::to_string(massBelow));
	Utility::logDebug("Mass Above: " + std::to_string(massAbove));
	Utility::logDebug("Ratio: " + std::to_string(massBelow / massAbove));
}

Universe Universe::loadFromCsvFile(const std::filesystem::path& filePath, const double& systemSize) {
	std::vector<Body> bodies;

	// Read CSV file
	io::CSVReader<10> in(filePath);
	in.read_header(io::ignore_extra_column, "position.x", "position.y", "position.z", "velocity.x", "velocity.y", "velocity.z", "acceleration.x", "acceleration.y", "acceleration.z", "mass");
	double positionX;
	double positionY;
	double positionZ;
	double velocityX;
	double velocityY;
	double velocityZ;
	double accelerationX;
	double accelerationY;
	double accelerationZ;
	double mass;
	while(in.read_row(positionX, positionY, positionZ, velocityX, velocityY, velocityZ, accelerationX, accelerationY, accelerationZ, mass)) {
		bodies.emplace_back(
			Vector3D(positionX, positionY, positionZ),
			Vector3D(velocityX, velocityY, velocityZ),
			Vector3D(accelerationX, accelerationY, accelerationZ),
			mass
		);
	}

	return Universe(bodies, systemSize);
}

Universe::Universe(std::vector<Body> bodies, const double& systemSize) : bodies(std::move(bodies)), systemSize(systemSize) {
	Utility::logInfo(std::to_string(SYSTEM_THICKNESS) + "AU thick disk\n");
}

// Universe::Universe(const int& bodyCount, const double& systemSize) : systemSize(systemSize), bodies(initializeBodies(bodyCount)) {
// }

void Universe::simulate(const int& steps, const int& renderInterval, const bool& createImages, const int& imageWidth, const int& imageHeight) {
	Image image(imageWidth, imageHeight);

	if(createImages) {
		image.createFrame(1, renderInterval, bodies, systemSize);
	}

	for(int step = 1; step < steps; step++) {
		Utility::logInfo("Beginning timestep: " + std::to_string(step));

		interactBodies();

		if((step % renderInterval == 0 && createImages) || step == steps - 1) {
			image.createFrame(step + 1, renderInterval, bodies, systemSize);
		}

		Utility::logDebug("-------Done------- timestep: " + std::to_string(step) + "\n");
	}

	Utility::logInfo("We made it\n");
}

void Universe::writeToCsvFile(const std::filesystem::path& filePath) {
	// Open the file for writing
	std::ofstream file(filePath);

	// Write the header
	file << R"("position.x","position.y","position.z","velocity.x","velocity.y","velocity.z","acceleration.x","acceleration.y","acceleration.z","mass")" << std::endl;

	// Write the bodies
	for(const auto& body : bodies) {
		file << body.position.x << ',' << body.position.y << ',' << body.position.z << ',' << body.velocity.x << ',' << body.velocity.y << ',' << body.velocity.z << ',' << body.acceleration.x << ',' << body.acceleration.y << ',' << body.acceleration.z << ',' << body.mass << std::endl;
	}
}
