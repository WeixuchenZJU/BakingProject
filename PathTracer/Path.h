#pragma once
#include "hit.h"
#include <glm\glm.hpp>
#include <vector>
class Path
{
public:
	Path(int length);
	~Path();
	void AddHitToPath(Hit hit);
	std::vector<Hit> GetPath();
	void PrintPath();
	void SetValidPath() {
		this->m_IsValid = true;
	}
	int IsValid() {
		return m_IsValid;
	}
	//��������Hit֮���Geometryterm
	float GeometryTerm(Hit ps, Hit pt);
	glm::vec3 TransportTerm();
private:
	std::vector<Hit> path_vertices;//·���л�洢���������ص����ڵ�N������
	int m_IsValid;//��־��·���Ƿ���Ч
	int m_maxlength;
};

