#ifndef _HIT_H
#define _HIT_H

#include <glm/glm.hpp>

class Material;

// ====================================================================
// ====================================================================
class Ray;
class Hit {

public:

	// CONSTRUCTOR & DESTRUCTOR
	Hit() { material = NULL; }
	Hit(float _t, Material *m, glm::vec3 n) {
		t = _t; material = m; normal = n;
	}
	Hit(const Hit &h) {
		t = h.t;
		material = h.material;
		normal = h.normal;
		intersectionPoint = h.intersectionPoint;
	}
	~Hit() {}

	// ACCESSORS
	float getT() const { return t; }
	Material* getMaterial() const { return material; }
	glm::vec3 getNormal() const { return normal; }
	glm::vec3 getIntersectionPoint() const { return intersectionPoint; }

	// MODIFIER
	void set(float _t, Material *m, glm::vec3 n, const Ray &ray);

private:

	// REPRESENTATION
	float t;
	Material *material;
	glm::vec3 normal;
	glm::vec3 intersectionPoint;

};

//inline ostream &operator<<(ostream &os, const Hit &h) {
//	os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
//	return os;
//}
// ====================================================================
// ====================================================================

#endif