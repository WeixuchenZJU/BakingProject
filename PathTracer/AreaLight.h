#pragma once
#include <glm/glm.hpp>
#include "Triangle.h"
#include "ray.h"
#include "hit.h"
class AreaLight
{
public:
	AreaLight() {}
	AreaLight(Triangle face1,Triangle face2);
	~AreaLight();
	//�жϹ����Ƿ������Դ�ཻ
	bool IntersectAreaLight(Ray r) {
		Hit hit1(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
		Hit hit2(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
		return(light_1.intersect(r, hit1, 0) || light_2.intersect(r, hit2, 0));
	}
	float getArea(){
		return light_1.area()+light_2.area();
	}
	glm::vec3 getLightPos(float z1, float z2) {
		return light_corner + z1 * ls1 + z2 * ls2;
	}
private:
	//���Դ��һ�����μ��������������
	Triangle light_1;
	Triangle light_2;
	glm::vec3 light_corner;
	glm::vec3 ls1;
	glm::vec3 ls2;
};

