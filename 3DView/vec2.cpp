#include <stdio.h>
#include "vec2.h"

namespace egc {


    vec2& vec2::operator =(const vec2& srcVector) {

        this->x = srcVector.x;
        this->y = srcVector.y;

        return *this;
    }

    vec2 vec2::operator +(const vec2& srcVector) const {

        vec2 result;
        result.x = srcVector.x + this->x;
        result.y = srcVector.y + this->y;

        return result;
    }

    vec2& vec2::operator +=(const vec2& srcVector) {

        this->x += srcVector.x;
        this->y += srcVector.y;

        return *this;
    }

    vec2 vec2::operator *(float scalarValue) const {

        vec2 result;
        result.x = scalarValue * this->x;
        result.y = scalarValue * this->y;

        return result;
    }

    vec2 vec2::operator -(const vec2& srcVector) const {

        vec2 result;
        result.x = this->x - srcVector.x;
        result.y = this->y - srcVector.y;

        return result;
    }

    vec2& vec2::operator -=(const vec2& srcVector) {

        this->x -= srcVector.x;
        this->y -= srcVector.y;

        return *this;
    }

    vec2 vec2::operator -() const {

        vec2 result;

        result.x = -this->x;
        result.y = -this->y;

        return result;
    }

    float vec2::length() const {

        return sqrt(this->x * this->x + this->y * this->y);
    }

    vec2& vec2::normalize() {

        *this = (*this) * (1 / sqrt(this->x * this->x + this->y * this->y));

        return *this;
    }

    float dotProduct(const egc::vec2& v1, const egc::vec2& v2)
    {
        return v1.x * v2.x, v2.x * v2.y;
    }
}