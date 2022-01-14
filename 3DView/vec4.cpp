#include <iostream>
#include "vec4.h"

namespace egc {
	vec4& vec4::operator =(const vec4& srcVector)
	{
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		this->w = srcVector.w;
		return *this;
	}
	vec4 vec4::operator +(const vec4& srcVector) const {
		vec4 result;
		result.x = this->x + srcVector.x;
		result.y = this->y + srcVector.y;
		result.z = this->z + srcVector.z;
		return result;
	}

	vec4& vec4::operator +=(const vec4& srcVector) {
		this->x = this->x + srcVector.x;
		this->y = this->y + srcVector.y;
		this->z = this->z + srcVector.z;
		return *this;
	}

	vec4 vec4::operator *(float scalarValue) const {
		vec4 result;
		result.x = this->x * scalarValue;
		result.y = this->y * scalarValue;
		result.z = this->z * scalarValue;
		return result;
	}

	vec4 vec4::operator -(const vec4& srcVector) const {
		vec4 result;
		result.x = this->x - srcVector.x;
		result.y = this->y - srcVector.y;
		result.z = this->z - srcVector.z;
		result.w = this->w - srcVector.w;
		return result;
	}

	vec4& vec4::operator -=(const vec4& srcVector) {
		this->x = this->x - srcVector.x;
		this->y = this->y - srcVector.y;
		this->z = this->z - srcVector.z;
		this->w = this->w - srcVector.w;
		return *this;
	}

	vec4 vec4::operator -() const {
		vec4 result;
		result.x = this->x * -1;
		result.y = this->y * -1;
		result.z = this->z * -1;
		return result;
	}

	float vec4::length() const {
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	vec4& vec4::normalize() {
		int l = (*this).length();
		this->x = this->x / l;
		this->y = this->y / l;
		this->z = this->z / l;
		return *this;
	}

	float dotProduct(const vec4& v1, const vec4& v2) {
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
}