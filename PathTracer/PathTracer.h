#pragma once
#include <glm/glm.hpp>
#include "SceneParser.h"
#include "ray.h"
#include "hit.h"
#include "Path.h"
#define PI 3.14159265358979323846
class PathTracer
{
public:
	PathTracer(SceneParser *s, int maxbounces) :m_scene(s), m_maxbounces(maxbounces) {}
	glm::vec3 TraceRay(Ray &ray,int bounces,Hit &hit,Path& path);
	glm::vec3 TracePath(Ray &ray, int bounces, Hit &hit, Path& path, float tmin);
	glm::vec3 CosweightSampling(Hit hit);
	~PathTracer() {}
private:
	SceneParser * m_scene;
	int m_maxbounces;
};

