#pragma once

#include <memory>
#include <vector>

class Body;

class Color;

class Image {
		std::unique_ptr<double[]> image;

		unsigned char colorDepth(const unsigned char& value, const unsigned char& pixel, const double& factor);

		double toPixelSpace(const double& point, const int& size, const double& systemSize);

	public:
		/**
		 * Image render width.
		 */
		const int width;

		/**
		 * Image render height.
		 */
		const int height;

		Image(const int& width, const int& height);

		void clear();

		void colorAt(const int& x, const int& y, const Color& color, const double& factor);

		void colorDot(const double& x, const double& y, const double& vMagnitude, const double& systemSize);

		void createFrame(const int& step, const int& renderInterval, const std::vector<Body>& bodies, const double& systemSize);

		void renderBodies(const std::vector<Body>& bodies, const double& systemSize);

		void writeRender(const int& step, const int& renderInterval);
};

