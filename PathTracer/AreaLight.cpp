#include "AreaLight.h"



AreaLight::AreaLight(Triangle face1, Triangle face2)
{
	this->light_1 = face1;
	this->light_2 = face2;
	this->light_corner = glm::vec3(343.0f, 548.8f, 227.0f);
	this->ls1= glm::vec3(-130.0f, 0.0f, 0.0f);
	this->ls2 = glm::vec3(0.0f, 0.0f, 105.0f);
}


AreaLight::~AreaLight()
{
}
