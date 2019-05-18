#include "Image.hpp"

#include <cmath>
#include <filesystem>
#include <fstream>

#include "Body.hpp"
#include "Color.hpp"
#include "Constants.hpp"
#include "Utility.hpp"

unsigned char Image::colorDepth(const unsigned char& value, const unsigned char& pixel, const double& factor) {
	return fmax(fmin((value * factor + pixel), 255), 0);
	//	unsigned char t = fmax(fmin((value*factor+pixel),255),0);
	//	return 2*t-(t*t)/255;
}

double Image::toPixelSpace(const double& point, const int& size, const double& systemSize) {
	return (size / 2.0) * (1.0 + point / (systemSize * RENDER_SCALE));
}

Image::Image(const int& width, const int& height) : width(width), height(height), image(std::make_unique<double[]>(width * height * 3)) {
}

void Image::clear() {
	for(int pixel = 0; pixel < width * height * 3; pixel++) {
		image[pixel] = 0.0; // image[pixel] / 1.2;
	}
}

void Image::colorAt(const int& x, const int& y, const Color& color, const double& factor) {
	int pixelIndex = 3 * (x + width * y);

	image[pixelIndex] += color.red * factor; //colorDepth(color.r, image[pixelIndex+0], factor);
	image[pixelIndex + 1] += color.green * factor; //colorDepth(color.g, image[pixelIndex+1], factor);
	image[pixelIndex + 2] += color.blue * factor; //colorDepth(color.b, image[pixelIndex+2], factor);
}

void Image::colorDot(const double& x, const double& y, const double& vMagnitude, const double& systemSize) {
	const double velocityMax = MAX_VEL_COLOR; // 35000
	const double velocityMin = sqrt(0.8 * (G * (SOLAR_MASS + EXTRA_MASS * SOLAR_MASS)) / Utility::astronomicalUnitsToMeters(systemSize)); //MIN_VEL_COLOR;
	const double vPortion = sqrt((vMagnitude - velocityMin) / velocityMax);

	const Color color(
		Utility::clamp(4 * (vPortion - 0.333)),
		Utility::clamp(fmin(4 * vPortion, 4.0 * (1.0 - vPortion))),
		Utility::clamp(4 * (0.5 - vPortion))
	);

	for(int i = -DOT_SIZE / 2; i < DOT_SIZE / 2; ++i) {
		for(int j = -DOT_SIZE / 2; j < DOT_SIZE / 2; ++j) {
			double pixelSpaceX = toPixelSpace(x, width, systemSize);
			double pixelSpaceY = toPixelSpace(y, height, systemSize);
			double pixelSpaceXFloored = floor(pixelSpaceX);
			double pixelSpaceYFloored = floor(pixelSpaceY);

			colorAt(
				int(pixelSpaceXFloored + i),
				int(pixelSpaceYFloored + j),
				color,
				PARTICLE_BRIGHTNESS / (
					pow(
						exp(
							pow(
								PARTICLE_SHARPNESS * (pixelSpaceXFloored + i - pixelSpaceX),
								2.0
							)
						) + exp(
							pow(
								PARTICLE_SHARPNESS * (pixelSpaceYFloored + j - pixelSpaceY),
								2.0
							)
						),
						0.75 // 1.25
					) + 1.0
				)
			);
		}
	}
}

void Image::createFrame(const int& step, const int& renderInterval, const std::vector<Body>& bodies, const double& systemSize) {
	Utility::logInfo("Writing frame " + std::to_string(step));

	Utility::logDebug("Clearing Pixels...");

	clear();

	Utility::logDebug("Rendering Particles...");

	renderBodies(bodies, systemSize);

	Utility::logDebug("Writing frame to file...");

	writeRender(step, renderInterval);
}

void Image::renderBodies(const std::vector<Body>& bodies, const double& systemSize) {
	/// ORTHOGONAL PROJECTION
	for(const auto& body : bodies) {
		double x = toPixelSpace(body.position.x, width, systemSize);
		double y = toPixelSpace(body.position.y, height, systemSize);

		if(x > DOT_SIZE && x < width - DOT_SIZE && y > DOT_SIZE && y < height - DOT_SIZE) {
			colorDot(body.position.x, body.position.y, body.velocity.magnitude(), systemSize);
		}
	}
}

void Image::writeRender(const int& step, const int& renderInterval) {
	char imageData[width * height * 3];
	for(int i = 0; i < width * height * 3; i++) {
		imageData[i] = int(255.0 * Utility::clamp(image[i]));
	}

	// Generate the filename for the image
	std::filesystem::path name = "./images/Step";
	int frame = step / renderInterval + 1; // renderInterval;
	for(int i = (frame == 1000
		? 1
		: 0 /* Evil hack to avoid extra 0 at 1000 */); i < 4 - floor(log(frame) / log(10)); i++) {
		name += "0";
	}
	name += std::to_string(frame);
	name += ".ppm";

	// Generate the image base path if needed
	if(!std::filesystem::exists(name.parent_path())) {
		std::filesystem::create_directory(name.parent_path());
	}

	// Open a stream for the file
	std::ofstream file(name, std::ofstream::binary);
	if(file.is_open()) {
		// Write the data
		//		size = file.tellg();
		file << "P6\n" << width << " " << height << "\n" << "255\n";
		file.write(imageData, width * height * 3);
	}
}
