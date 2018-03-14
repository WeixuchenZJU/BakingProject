#include "Path.h"
#include "Material.h"
#define PI 3.14159265358979323846f

Path::Path(int length)
{
	this->m_maxlength = length;
}


Path::~Path()
{
	this->m_IsValid = false;
}
void Path::AddHitToPath(Hit hit) {
	path_vertices.push_back(hit);
}
std::vector<Hit> Path::GetPath() {
	return path_vertices;
}
void Path::PrintPath() {
	printf("V0:Pixel->");
	for (int i = 0; i < path_vertices.size(); i++) {
		printf("V%d:(%.2f,%.2f,%.2f)->", i + 1, path_vertices[i].getIntersectionPoint().x, path_vertices[i].getIntersectionPoint().y, path_vertices[i].getIntersectionPoint().z);
	}
	printf("End\n");
}
float Path::GeometryTerm(Hit ps, Hit pt) {
	float G = 0.0f;
	glm::vec3 dir = pt.getIntersectionPoint() - ps.getIntersectionPoint();
	float dis = glm::length(dir);
	float cos1 = glm::dot(ps.getNormal(), glm::normalize(dir));
	float cos2 = glm::dot(pt.getNormal(), glm::normalize(-dir));
	G=fabs(cos1 * cos2 / (dis*dis));
	return G;
}
glm::vec3 Path::TransportTerm() {
	glm::vec3 result(1.0f, 1.0f, 1.0f);
	float pdf = 0.0f;//计算该路径的pdf
	//PrintPath();
	for (int i = 0; i < this->path_vertices.size()-1; i++) {
		Hit pi1 = path_vertices[i + 1];
		Hit pi0 = path_vertices[i];
		glm::vec3 w = glm::normalize(pi1.getIntersectionPoint() - pi0.getIntersectionPoint());
		float costheta = glm::dot(pi0.getNormal(), w);
		float sintheta = sqrtf(1 - costheta * costheta);
		pdf = sintheta*costheta;
		//printf("%.6f\n", pdf);
	//printf("dir:<%.4f,%.4f,%.4f>,normal:<%.4f,%.4f,%.4f>\n", w.x, w.y, w.z, pi0.getNormal().x, pi0.getNormal().y, pi0.getNormal().z);
		result = result * pi0.getMaterial()->GetKd();
	}
	return result;
}