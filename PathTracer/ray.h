#ifndef _RAY_H
#define _RAY_H

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
using namespace std;
// ====================================================================
// ====================================================================

// Ray class mostly copied from Peter Shirley and Keith Morley
#include "hit.h"
class Ray {

public:

	// CONSTRUCTOR & DESTRUCTOR
	Ray() {}
	Ray(const glm::vec3 &orig, const glm::vec3 &dir) {
		origin = orig;
		direction = dir;
	}
	Ray(const Ray& r) { *this = r; }

	// ACCESSORS
	const glm::vec3& getOrigin() const { return origin; }
	const glm::vec3& getDirection() const { return direction; }
	//MODIFIERS
	void setOrigin(glm::vec3 org) {
		this->origin = org;

	}
	void setDirection(glm::vec3 dir) {
		this->direction = dir;

	}
	glm::vec3 pointAtParameter(float t) const {
		return origin + direction * t;
	}
	void Print() {
		printf("org<%.2f,%.2f,%.2f>,dir<%.2f,%.2f,%.2f>\n", origin.x, origin.y, origin.z, direction.x, direction.y, direction.z);
	}

	
private:

	// REPRESENTATION
	glm::vec3 origin;
	glm::vec3 direction;
	
};

//inline ostream &operator<<(ostream &os, const Ray &r) {
//	os << "Ray <o:" << r.getOrigin() << ", d:" << r.getDirection() << ">";
//	return os;
//}

// ====================================================================
// ====================================================================

#endif

