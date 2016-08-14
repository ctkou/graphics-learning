// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <stdio.h>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float rad = degrees * pi/180.0;
  vec3 normalized_axis = glm::normalize(axis);
  mat3 dualMatrix = mat3(
    0, normalized_axis.z, -normalized_axis.y, // first column
	-normalized_axis.z, 0, normalized_axis.x, // second column
	normalized_axis.y, -normalized_axis.x, 0  // third column
  );
  return mat3(1.0) * cos(rad) + glm::outerProduct(normalized_axis, normalized_axis) * (1-cos(rad)) + dualMatrix * sin(rad);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotationMatrix = rotate(degrees, up);
  eye = rotationMatrix * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  mat3 rotationMatrix = rotate(degrees, glm::cross(eye, up));
  up = rotationMatrix * up;
  eye = rotationMatrix * eye;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);
  vec3 e = vec3(0) - eye;
  mat4 rotation = glm::transpose(glm::mat4(
    glm::vec4(u, 0),
	glm::vec4(v, 0),
	glm::vec4(w, 0),
	glm::vec4( glm::vec3(0), 1 )
  ));
  mat4 translation = glm::mat4(
    glm::vec4(1, 0, 0, 0),
	glm::vec4(0, 1, 0, 0),
	glm::vec4(0, 0, 1, 0),
	glm::vec4(e, 1)
  );
  return rotation * translation;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
