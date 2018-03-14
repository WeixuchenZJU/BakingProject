#ifndef _SceneParser_H_
#define _SceneParser_H_

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <assert.h>
#include <vector>
#include "Triangle.h"
#include "Material.h"
#include "AreaLight.h"
// ====================================================================
// ====================================================================
enum intersecttype {
	BG, DIFFUSE, LIGHT
};
class SceneParser {

public:

	// CONSTRUCTOR & DESTRUCTOR
	SceneParser(const char *filename, const char *mtl_filename);
	~SceneParser();
	AreaLight getLight() {
		return this->arealight;
	}
	int FindMaterials(const char* matname) {
		printf("current material is %s\n", matname);
		int index = -1;
		for (int i = 0; i < materials.size(); i++) {
			if (strcmp(materials[i].GetName(), matname) == 0) {
				index = i;
				break;
			}
		}
		return index;
	}
	intersecttype Intersect(Ray &ray, Hit &hit,float tmin);
	bool IntersectShadowRay(Ray &ray, Hit &hit, float tmin, float lightdis);
private:
	std::vector<Triangle> triangles;
	std::vector<Material> materials;
	AreaLight arealight;
};

// ====================================================================
// ====================================================================

#endif
