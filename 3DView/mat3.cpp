#include <algorithm>
#include <iostream>
#include "vec3.h"
#include "mat3.h"

namespace egc {

	mat3& mat3::operator =(const mat3& srcMatrix) {
		for (int i = 0; i < 9; i++) 
			this->matrixData[i] = srcMatrix.matrixData[i];
		return *this;
	}

	mat3 mat3::operator *(float scalarValue) const {
		mat3 m;
		for (int i = 0; i < 9; i++)
			m.matrixData[i] = this->matrixData[i]*scalarValue;
		return m;
	}

	mat3 mat3::operator *(const mat3& srcMatrix) const {

		mat3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				float sum = 0;
				for (int k = 0; k < 3; k++) {
					sum = sum + this->at(i, k) * srcMatrix.at(k, j);
				}
				result.at(i, j) = sum;
			}
		}
		return result;
	}

	vec3 mat3::operator *(const vec3& srcVector) const {

		vec3 resultVector;

		resultVector.x = at(0, 0) * srcVector.x + at(0, 1) * srcVector.y + at(0, 2) * srcVector.z;
		resultVector.y = at(1, 0) * srcVector.x + at(1, 1) * srcVector.y + at(1, 2) * srcVector.z;
		resultVector.z = at(2, 0) * srcVector.x + at(2, 1) * srcVector.y + at(2, 2) * srcVector.z;

		return resultVector;
	}

	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 result;
		for (int i = 0; i < 9; i++) {
			result.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}
		return result;
	}

	float& mat3::at(int i, int j) {
		return matrixData[3 * j + i];
	}

	const float& mat3::at(int i, int j) const {
		return matrixData[3 * j + i];
	}

	float mat3::determinant() const {
		float result=0;
		float m11c = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
		float m12c = at(1, 0) * at(2, 2) - at(1, 2) * at(2, 0);
		float m13c = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);
		result = at(0, 0) * m11c - at(0, 1) * m12c + at(0, 2) * m13c;
		return result;
	}

	mat3 mat3::inverse() const {
		mat3 result;

		float m11c = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
		float m12c = -(at(1, 0) * at(2, 2) - at(2, 0) * at(1, 2));
		float m13c = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);

		float m21c = -(at(0, 1) * at(2, 2) - at(2, 1) * at(0, 2));
		float m22c = at(0, 0) * at(2, 2) - at(0, 2) * at(2, 0);
		float m23c = -(at(0, 0) * at(2, 1) - at(0, 1) * at(2, 0));

		float m31c = at(0, 1) * at(1, 2) - at(1, 1) * at(0, 2);
		float m32c = -(at(0, 0) * at(1, 2) - at(1, 0) * at(0, 2));
		float m33c = at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);

		result.at(0, 0) = m11c;
		result.at(0, 1) = m21c;
		result.at(0, 2) = m31c;
		result.at(1, 0) = m12c;
		result.at(1, 1) = m22c;
		result.at(1, 2) = m32c;
		result.at(2, 0) = m13c;
		result.at(2, 1) = m23c;
		result.at(2, 2) = m33c;


		return result*(1/(*this).determinant());
	}


	mat3 mat3::transpose() const {
		mat3 resultMatrix;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				resultMatrix.at(i, j) = at(j, i);
			}
		}
		return resultMatrix;
	}

}
