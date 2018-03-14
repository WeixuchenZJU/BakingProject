#include <stdio.h>
#include <glm/glm.hpp>
#include <random>
#define SAMPLENNUM 256
#define PI 3.1415926536f
void PrintVec3(glm::vec3 v) {
	printf("<%.4f,%.4f,%.4f>\n", v.x, v.y, v.z);
}
glm::vec3 CosweightSampling(glm::vec3 N) {
	glm::vec3 sampledir;
	// generate sample kernel
	// ----------------------
	std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
	std::default_random_engine generator;
	float theta, phi;
	float U1, U2;
	U1 = rand()*1.0f / RAND_MAX;
	U2 = rand()*1.0f / RAND_MAX;
	//U1 = 0.275887f;
	//U2 = 0.272896f;
	//printf("%.6f,%.6f\n", U1, U2);
	//重要度采样
	phi = 2 * PI*U1;
	theta = asin(sqrt(U2));
	//printf("%.2f,%.2f,%.2f,%.2f\n", sin(theta), cos(theta), sin(phi), cos(phi));
	sampledir = glm::vec3(cos(phi)*sin(theta), cos(theta), sin(phi)*sin(theta));
	//printf("Org Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	//计算切线空间
	glm::vec3 T, B;
	//printf("Normal:<%.6f,%.6f,%.6f>\n", N.x, N.y, N.z);
	glm::vec3 V(1, 0, 0);
	//printf("dotvn %.4f\n", glm::dot(V, N));
	if (fabs(fabs(glm::dot(V, N)) - 1.0f)<1e-3) {
		V = glm::vec3(0, 1, 0);
		//printf("Normal:<%.6f,%.6f,%.6f>\n", N.x, N.y, N.z);
	}
	T = glm::normalize(glm::cross(V, N));
	B = glm::normalize(glm::cross(N, T));
	//printf("Tan:<%.2f,%.2f,%.2f>\n", T.x, T.y, T.z);
	//printf("Bitan:<%.2f,%.2f,%.2f>\n", B.x, B.y, B.z);
	glm::mat3x3 TBN(T,N,  B);
	sampledir = glm::normalize(TBN * sampledir);
	//printf("Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	return sampledir;

}
int main() {
	
	glm::vec3 N(1.0f, 0.0f, 0.0f);
	glm::vec3 sampledir;
	for (int i = 0; i < SAMPLENNUM; i++) {
		sampledir = CosweightSampling(N);
		printf("p=%.4f\n",glm::dot(sampledir,N));
	}
	return 0;
}