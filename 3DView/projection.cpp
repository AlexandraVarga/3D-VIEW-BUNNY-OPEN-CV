//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"
#include "include/SDL_render.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
		mat4 viewTransformMatrix;

        viewTransformMatrix.at(0, 0) = width / 2;
        viewTransformMatrix.at(0, 3) = width / 2 + startX;
        viewTransformMatrix.at(1, 1) = -height / 2;
        viewTransformMatrix.at(1, 3) = height / 2 + startY;

        return viewTransformMatrix;
    }
    
    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 cameraMatrix;

        vec3 w = -mc.cameraTarget.normalize();

        vec3 tw = crossProduct(mc.cameraUp, w);

        vec3 u = tw.normalize();

        vec3 v = crossProduct(w, u);

        mat4 m1;

        m1.at(0, 0) = u.x;
        m1.at(0, 1) = u.y;
        m1.at(0, 2) = u.z;
        
        m1.at(1, 0) = v.x;
        m1.at(1, 1) = v.y;
        m1.at(1, 2) = v.z;
       
        m1.at(2, 0) = w.x;
        m1.at(2, 1) = w.y;
        m1.at(2, 2) = w.z;

        mat4 m2;
        
        m2.at(0, 3) = -mc.cameraPosition.x;
        m2.at(1, 3) = -mc.cameraPosition.y;
        m2.at(2, 3) = -mc.cameraPosition.z;
        
        cameraMatrix = m1 * m2;

        return cameraMatrix;
    }
    
    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveProjectionMatrix;

        float t = tan(fov / 2.0f);

        perspectiveProjectionMatrix.at(0, 0) = -1.0f / (aspect * t);
        perspectiveProjectionMatrix.at(1, 1) = -1.0f / t;
        perspectiveProjectionMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
        perspectiveProjectionMatrix.at(2, 3) = (2 * zFar * zNear) / (zFar - zNear);
        perspectiveProjectionMatrix.at(3, 2) = 1;
        perspectiveProjectionMatrix.at(3, 3) = 0;


        return perspectiveProjectionMatrix;
    }
    
    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4 &iv)
    {
        iv.x = iv.x / iv.w;
        iv.y = iv.y / iv.w;
        iv.z = iv.z / iv.w;
        iv.w = 1;
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4 & vertex)
    {
        if (-abs(vertex.w) <= vertex.x && vertex.x  <= abs(vertex.w) && -abs(vertex.w) <= vertex.y && vertex.y <= abs(vertex.w) && -abs(vertex.w) <= vertex.z && vertex.z <= abs(vertex.w))
            return false;
        else
            return true;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle)
    {
        return (clipPointInHomogeneousCoordinate(triangle[0]) || clipPointInHomogeneousCoordinate(triangle[1]) || clipPointInHomogeneousCoordinate(triangle[2]));
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec3 n;
        n = crossProduct((triangle[1] - triangle[0]), (triangle[2] - triangle[0]));
        return n;
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec4 triangleCenter;
        triangleCenter.x = (triangle[0].x + triangle[1].x + triangle[2].x)/2;
        triangleCenter.y = (triangle[0].y + triangle[1].y + triangle[2].y) / 2;
        triangleCenter.z = (triangle[0].z + triangle[1].z + triangle[2].z) / 2;
        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4> &triangle, const egc::vec3 &normalVector)
    {
        if (dotProduct((triangle[1] - triangle[0]), normalVector) > 0)
            return false;
        else true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
	void displayNormalVectors(egc::vec3 &normalVector, egc::vec4 &triangleCenter, SDL_Renderer *renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {
        vec4 secondPoint;
        secondPoint.x= triangleCenter.x+normalVector.x*0.5;
        secondPoint.y = triangleCenter.x + normalVector.y*0.5;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        triangleCenter= perspectiveMatrix * viewTransformMatrix * triangleCenter;
        secondPoint = perspectiveMatrix * viewTransformMatrix * secondPoint;
        SDL_RenderDrawLine(renderer, triangleCenter.x, triangleCenter.y, secondPoint.x, secondPoint.y);
    }
}


