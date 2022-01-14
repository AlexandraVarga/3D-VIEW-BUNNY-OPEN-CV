#include <algorithm>
#include <iostream>
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"

namespace egc {

	mat4& mat4::operator =(const mat4& srcMatrix) {
		for (int i = 0; i < 16; i++)
			this->matrixData[i] = srcMatrix.matrixData[i];
		return *this;
	}

	mat4 mat4::operator *(float scalarValue) const {
		mat4 m;
		for (int i = 0; i < 16; i++)
			m.matrixData[i] = this->matrixData[i] * scalarValue;
		return m;
	}

	mat4 mat4::operator *(const mat4& srcMatrix) const {
		mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0;
				for (int k = 0; k < 4; k++) {
					sum = sum + this->at(i, k) * srcMatrix.at(k, j);
				}
				result.at(i, j) = sum;
			}
		}
		return result;
	}

	vec4 mat4::operator *(const vec4& srcVector) const {
		vec4 resultVector;

		resultVector.x = at(0, 0) * srcVector.x + at(0, 1) * srcVector.y + at(0, 2) * srcVector.z + at(0, 3) * srcVector.w;
		resultVector.y = at(1, 0) * srcVector.x + at(1, 1) * srcVector.y + at(1, 2) * srcVector.z + at(1, 3) * srcVector.w;
		resultVector.z = at(2, 0) * srcVector.x + at(2, 1) * srcVector.y + at(2, 2) * srcVector.z + at(2, 3) * srcVector.w;
		resultVector.w = at(3, 0) * srcVector.x + at(3, 1) * srcVector.y + at(3, 2) * srcVector.z + at(3, 3) * srcVector.w;

		return resultVector;
	}

	mat4 mat4::operator +(const mat4& srcMatrix) const {
		mat4 result;
		for (int i = 0; i < 16; i++) {
			result.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}
		return result;
	}

	float& mat4::at(int i, int j) {
		return matrixData[4 * j + i];
	}

	const float& mat4::at(int i, int j) const {
		return matrixData[4 * j + i];
	}

	//NOT SO ELEGANT
	/*float mat4::determinant() const {
		float result = 0;

		mat3 temp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp.at(i, j) = at(i + 1, j + 1);
			}
		}
		float m11c = temp.determinant();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j > 0)
					temp.at(i, j) = at(i + 1, j + 1);
				else
					temp.at(i, j) = at(i + 1, j);
			}
		}
		float m12c = temp.determinant();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j > 1)
					temp.at(i, j) = at(i + 1, j + 1);
				else
					temp.at(i, j) = at(i + 1, j);
			}
		}
		float m13c = temp.determinant();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp.at(i, j) = at(i + 1, j);
			}
		}
		float m14c = temp.determinant();

		result = at(0, 0) * m11c - at(0, 1) * m12c + at(0, 2) * m13c - at(0, 3) * m14c;
		return result;


	}*/

	float mat4::determinant() const
	{
		float suma = 0;
		for (int i = 0; i < 4; i++) {
			mat3 aux;
			int index = 0;
			for (int j = 0; j < 4; j++) {
				for (int k = 1; k < 4; k++)
				{
					if (j != i) {
						aux.matrixData[index++] = at(k,j);
					}
				}
			}
			if (i % 2)
				suma += (-1) * aux.determinant() * this->matrixData[4 * i];
			else
				suma += aux.determinant() * this->matrixData[4 * i];
		}

		return suma;
	}

	mat4 mat4::inverse() const
	{
		float det = this->determinant();

		mat4 inv;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat3 aux;
				int index = 0;
				for (int x = 0; x < 4; x++)
					for (int z = 0; z < 4; z++)
					{
						if (x != i && z != j) {
							aux.matrixData[index++] = this->matrixData[4 * x + z];
						}
					}
				inv.matrixData[4 * i + j] = aux.determinant() / det;
				if ((i + j) % 2) {
					inv.matrixData[4 * i + j] *= -1;
				}
			}
		}
		inv = inv.transpose();
		return inv;
	}

	mat4 mat4::transpose() const {
		mat4 result;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.at(i, j) = at(j, i);
			}
		}

		return result;
	}
}