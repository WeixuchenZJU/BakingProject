#include "PathTracer.h"
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/vector_relational.hpp>
#include <random>
#define EPS 0.001f
glm::vec3 PathTracer::TraceRay(Ray &ray, int bounces, Hit &hit) {
	glm::vec3 Color(0.0f, 0.0f, 0.0f);
	glm::vec3 LightPos(250.0f, 548.8f, 250.0f);
	//���������ȳ���������
	if (bounces>m_maxbounces) {
		return Color;
	}
	bool intersect = m_scene->Intersect(ray, hit,0.0f);
	if (!intersect) {
		return Color;
	}
	else {
		//������ߺ͹�Դ�ཻ
		if (m_scene->getLight().IntersectAreaLight(ray)) {
			return glm::vec3(1.0f, 1.0f, 1.0f);
		}
		else {
			return hit.getMaterial()->GetKd()*glm::max(0.0f,glm::dot(hit.getNormal(),glm::normalize(LightPos-hit.getIntersectionPoint())));
		}
	}
}
glm::vec3 PathTracer::TracePath(Ray &ray, int bounces, Hit &hit, Path& path,float tmin) {
	glm::vec3 Color(0.0f, 0.0f, 0.0f);
	//���������ȳ���������
	if (bounces>m_maxbounces) {
		return Color;
	}
	bool intersect = m_scene->Intersect(ray, hit,tmin);
	if (!intersect) {
		return Color;
	}
	else {
		path.AddHitToPath(hit);
		//������ߺ͹�Դ�ཻ���򹹳���һ��������·��
		if (m_scene->getLight().IntersectAreaLight(ray)) {
			//����Դ�ϵ�hit��ӵ����ߵ�·����
			//��־��ǰ·����������
			path.SetValidPath();
			return glm::vec3(1.0f, 1.0f, 1.0f);
		}
		//����ݹ��������
		else
		{
			Hit hit2(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
			glm::vec3 sampledir = CosweightSampling(hit);
			//printf("Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
			Ray ray2(hit.getIntersectionPoint(), sampledir);
			TracePath(ray2, bounces + 1, hit2, path,EPS);
			return Color;
		}
	}
}
glm::vec3 PathTracer::CosweightSampling(Hit hit) {
	glm::vec3 sampledir;
	// generate sample kernel
	// ----------------------
	std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
	std::default_random_engine generator;
	float theta, phi;
	float U1, U2;
	U1 = rand()*1.0f/RAND_MAX;
	U2 = rand()*1.0f/RAND_MAX;
	//U1 = 0.275887f;
	//U2 = 0.272896f;
	//printf("%.6f,%.6f\n", U1, U2);
	//��Ҫ�Ȳ���
	phi = 2 * PI*U1;
	theta = asin(sqrt(U2));
	//printf("%.2f,%.2f,%.2f,%.2f\n", sin(theta), cos(theta), sin(phi), cos(phi));
	sampledir=glm::vec3(cos(phi)*sin(theta), cos(theta), sin(phi)*sin(theta));
	//printf("Org Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	//�������߿ռ�
	glm::vec3 N,T,B;
	N = hit.getNormal();
	//printf("Normal:<%.6f,%.6f,%.6f>\n", N.x, N.y, N.z);
	glm::vec3 V(1, 0, 0);
	//printf("dotvn %.4f\n", glm::dot(V, N));
	if (fabs(fabs(glm::dot(V,N))-1.0f)<1e-3){
		V=glm::vec3(0, 1, 0);
		//printf("Normal:<%.6f,%.6f,%.6f>\n", N.x, N.y, N.z);
	}
	T = glm::normalize(glm::cross(V, N));
	B = glm::normalize(glm::cross(N, T));
	//printf("Tan:<%.2f,%.2f,%.2f>\n", T.x, T.y, T.z);
	//printf("Bitan:<%.2f,%.2f,%.2f>\n", B.x, B.y, B.z);
	glm::mat3x3 TBN( T,N, B);
	sampledir = glm::normalize(TBN * sampledir);
	//printf("Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	return sampledir;

}
/*
//����Ƿ���й�Դ
if (getLight().IntersectAreaLight(ray)) {
color = glm::vec3(1.0f, 1.0f, 1.0f);
//������һ������·������������·���Ĺ���

return true;
}
//�����ǰ����û�л��й�Դ
else {
//1.����ﵽ�����ݹ����
if (1) {

}
else {
//���ݻ��б�����BRDF��������
//�ݹ��²����Ĺ���
}
}

*/