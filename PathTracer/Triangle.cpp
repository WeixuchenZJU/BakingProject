#include "Triangle.h"



Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
	this->m_v0 = v0;
	this->m_v1 = v1;
	this->m_v2 = v2;
	glm::vec3 e1 = m_v1.pos - m_v0.pos;
	glm::vec3 e2 = m_v2.pos - m_v0.pos;
	this->m_normal = glm::cross(e1, e2);
	this->m_normal=glm::normalize(this->m_normal);
	this->m_mat = NULL;
	this->m_matindex = -1;
}


Triangle::~Triangle()
{
}
bool Triangle::intersect(const Ray &r, Hit &h, float tmin) {
	
	glm::vec3 e1 = m_v1.pos - m_v0.pos;
	glm::vec3 e2 = m_v2.pos - m_v0.pos;
	glm::vec3 p;
	p = glm::cross(r.getDirection(), e2);
	float a = glm::dot(e1,p);
	if (a == 0.0) return false;
	double f = 1.0 / a;
	glm::vec3 s = r.getOrigin() - m_v0.pos;
	double beta = f * glm::dot(s,p);
	if (beta < 0.0 || beta > 1.0) return false;

	glm::vec3 q;
	q=glm::cross(s, e1);
	double gamma = f * glm::dot(r.getDirection(),q);
	if (gamma < 0.0 || beta + gamma > 1.0) return false;

	double t = f * glm::dot(e2,q);

	if (t >= tmin && t <h.getT())
	{
		// We have a hit -- populat hit record. 
		h.set(t, this->m_mat, this->m_normal, r);
		return true;
	}
	return false;
}