#include "zbuffer.h"
#include <algorithm>

namespace egc {

	float Fab(float x, float y, float ax, float ay, float bx, float by, float cx, float cy) {
		return (ay - by) * x + (bx - ax) * y + ax * by - bx * ay;
	}
	float Fbc(float x, float y, float ax, float ay, float bx, float by, float cx, float cy) {
		return (by - cy) * x + (cx - bx) * y + bx * cy - cx * by;
	}
	float Fca(float x, float y, float ax, float ay, float bx, float by, float cx, float cy) {
		return (cy - ay) * x + (ax - cx) * y + cx * ay - ax * cy;
	}

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) {
		alpha = Fbc(pixel.x, pixel.y, triangleVertices.at(0).x, triangleVertices.at(0).y, triangleVertices.at(1).x, triangleVertices.at(1).y, triangleVertices.at(2).x, triangleVertices.at(2).y)
			/ Fbc(triangleVertices.at(0).x, triangleVertices.at(0).y, triangleVertices.at(0).x, triangleVertices.at(0).y, triangleVertices.at(1).x, triangleVertices.at(1).y, triangleVertices.at(2).x, triangleVertices.at(2).y);
		beta = Fca(pixel.x, pixel.y, triangleVertices.at(0).x, triangleVertices.at(0).y, triangleVertices.at(1).x, triangleVertices.at(1).y, triangleVertices.at(2).x, triangleVertices.at(2).y)
			/ Fca(triangleVertices.at(1).x, triangleVertices.at(1).y, triangleVertices.at(0).x, triangleVertices.at(0).y, triangleVertices.at(1).x, triangleVertices.at(1).y, triangleVertices.at(2).x, triangleVertices.at(2).y);
		gamma = 1 - alpha - beta;
	}

	float max_of_3(float x, float y, float z) {
		return std::max(x, std::max(y, z));
	}

	float min_of_3(float x, float y, float z) {
		return std::min(x, std::min(y, z));
	}

	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax) {
		float x_min = min_of_3(triangle.at(0).x, triangle.at(1).x, triangle.at(2).x);
		float x_max = max_of_3(triangle.at(0).x, triangle.at(1).x, triangle.at(2).x);
		float y_min = min_of_3(triangle.at(0).y, triangle.at(1).y, triangle.at(2).y);
		float y_max = max_of_3(triangle.at(0).y, triangle.at(1).y, triangle.at(2).y);

		for (int i = x_min; i <= x_max; i++) {
			for (int j = y_min; j <= y_max; j++) {
				float alpha, beta, gamma;
				computeAlphaBetaGamma(triangle, vec2(i, j), alpha, beta, gamma);
				if (0.0f <= alpha && alpha <= 1.0f && 0.0f <= beta && beta <= 1.0f && 0.0f <= gamma && gamma <= 1.0f) {
					float z = triangle.at(0).z * alpha + triangle.at(1).z * beta + triangle.at(2).z * gamma;
					if (z > depthBuffer[i][j]) {
						depthBuffer[i][j] = z;
						if (zmin < z) {
							zmin = z;
						}
						if (zmax > z) {
							zmax = z;
						}
					}
				}
			}
		}
	}

}
