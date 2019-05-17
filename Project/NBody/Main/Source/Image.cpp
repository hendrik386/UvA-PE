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

double Image::toPixelSpace(const double& point, const int& size) {
	return (size / 2.0) * (1.0 + point / (SYSTEM_SIZE * RENDER_SCALE));
}

Image::Image(const int& width, const int& height) : width(width), height(height), image(new char[width * height * 3]), hdImage(new double[width * height * 3]) {
}

Image::~Image() {
	delete[] image;
	delete[] hdImage;
}

void Image::clear() {
	for(int i = 0; i < width * height * 3; i++) {
		//	char* current = image + i;
		image[i] = 0; //char(image[i]/1.2);
		hdImage[i] = 0.0;
	}
}

void Image::colorAt(const int& x, const int& y, const Color& color, const double& factor) {
	int pixelIndex = 3 * (x + width * y);
	hdImage[pixelIndex + 0] += color.red * factor; //colorDepth(color.r, image[pixelIndex+0], factor);
	hdImage[pixelIndex + 1] += color.green * factor; //colorDepth(color.g, image[pixelIndex+1], factor);
	hdImage[pixelIndex + 2] += color.blue * factor; //colorDepth(color.b, image[pixelIndex+2], factor);
}

void Image::colorDot(const double& x, const double& y, const double& vMagnitude) {
	const double velocityMax = MAX_VEL_COLOR; //35000
	const double velocityMin = sqrt(0.8 * (G * (SOLAR_MASS + EXTRA_MASS * SOLAR_MASS)) / (SYSTEM_SIZE * TO_METERS)); //MIN_VEL_COLOR;
	const double vPortion = sqrt((vMagnitude - velocityMin) / velocityMax);

	Color c(
		Utility::clamp(4 * (vPortion - 0.333)),
		Utility::clamp(fmin(4 * vPortion, 4.0 * (1.0 - vPortion))),
		Utility::clamp(4 * (0.5 - vPortion))
	);

	for(int i = -DOT_SIZE / 2; i < DOT_SIZE / 2; i++) {
		for(int j = -DOT_SIZE / 2; j < DOT_SIZE / 2; j++) {
			double xP = floor(toPixelSpace(x, width));
			double yP = floor(toPixelSpace(y, height));
			double cFactor = PARTICLE_BRIGHTNESS /
				(pow(
					exp(
						pow(
							PARTICLE_SHARPNESS *
								(xP + i - toPixelSpace(x, width)), 2.0
						)
					)
						+ exp(
						pow(
							PARTICLE_SHARPNESS *
								(yP + j - toPixelSpace(y, height)), 2.0
						)
					),/*1.25*/0.75
				) + 1.0);

			colorAt(int(xP + i), int(yP + j), c, cFactor);
		}
	}
}

void Image::createFrame(const int& step, const std::vector<Body>& bodies) {
	Utility::logInfo("Writing frame " + std::to_string(step));

	Utility::logDebug("Clearing Pixels...");

	clear();

	Utility::logDebug("Rendering Particles...");

	renderBodies(bodies);

	Utility::logDebug("Writing frame to file...");

	writeRender(step);
}

void Image::renderBodies(const std::vector<Body>& bodies) {
	/// ORTHOGONAL PROJECTION
	for(const auto& body : bodies) {
		double x = toPixelSpace(body.position.x, width);
		double y = toPixelSpace(body.position.y, height);

		if(x > DOT_SIZE && x < width - DOT_SIZE && y > DOT_SIZE && y < height - DOT_SIZE) {
			double vMagnitude = body.velocity.magnitude();
			colorDot(body.position.x, body.position.y, vMagnitude);
		}
	}
}

void Image::writeRender(const int& step) {
	for(int i = 0; i < width * height * 3; i++) {
		image[i] = int(255.0 * Utility::clamp(hdImage[i]));
	}

	// Generate the filename for the image
	std::filesystem::path name = "./images/Step";
	int frame = step / RENDER_INTERVAL + 1; //RENDER_INTERVAL;
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
		file.write(image, width * height * 3);
	}
}
