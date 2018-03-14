#include "hit.h"
#include "ray.h"
// MODIFIER
void Hit::set(float _t, Material *m, glm::vec3 n, const Ray &ray) {
	t = _t; material = m; normal = n;
	intersectionPoint = ray.pointAtParameter(t);
}