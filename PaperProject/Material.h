#pragma once
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
class Material
{
public:
	Material(glm::vec3 kd = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 ka = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Tf = glm::vec3(1.0f, 1.0f, 1.0f)
		, glm::vec3 ks = glm::vec3(0.0f, 0.0f, 0.0f), float Ni = 1.0f, float Ns = 0.0f) {
		this->m_Ka = ka;
		this->m_Kd = kd;
		this->m_Ks = ks;
		this->m_Tf = Tf;
		this->m_Ni = Ni;
		this->m_Ns = Ns;
	}
	~Material() {}
	void SetKd(glm::vec3 kd) {
		this->m_Kd = kd;
	}
	void SetKa(glm::vec3 ka) {
		this->m_Ka = ka;
	}
	void SetKs(glm::vec3 ks) {
		this->m_Ks = ks;
	}
	void SetTf(glm::vec3 tf) {
		this->m_Tf = tf;
	}
	void SetNi(float ni) {
		this->m_Ni = ni;
	}
	void SetNs(float ns) {
		this->m_Ns = ns;
	}
	void SetName(char* name) {
		m_matname = name;
	}
	void SetMapKd(const char* name) {
		m_map_Kd = name;
	}
	void SetMapKa(const char* name) {
		m_map_Ka = name;
	}
	glm::vec3 GetKd() {
		return m_Kd;
	}
	glm::vec3 GetKa() {
		return m_Ka;
	}
	const char* GetName() {
		return this->m_matname.c_str();
	}
	const char* GetKdName() {
		return this->m_map_Kd.c_str();
	}
private:
	glm::vec3 m_Kd;
	glm::vec3 m_Ka;
	glm::vec3 m_Tf;
	float m_Ni;
	glm::vec3 m_Ks;
	float m_Ns;
	std::string m_matname;
	std::string m_map_Kd;
	std::string m_map_Ka;
};


