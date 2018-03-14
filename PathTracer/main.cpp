#include <stdio.h>
#include "Camera.h"
#include "SceneFileManager.h"
#include "SceneParser.h"
#include "image.h"
#include "PathTracer.h"
#include "Path.h"
#include <random>
#define PI 3.14159265358979323846
glm::vec3 camera_pos(278.0f, 273.0f, -800.0f);
glm::vec3 camera_dir(0.0f, 0.0f, 1.0f);
glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
int WIDTH =512;
int HEIGHT =512;
float camera_fovy =49.1f; 
const char* cornell_box_file_0 = "F:\\FinalProject\\PaperProject\\Models\\scene_0_obj\\CornellBox.obj";
const char* cornell_box_file_1 = "F:\\FinalProject\\PaperProject\\Models\\scene_1_obj\\scene01.obj";
const char* cornell_box_mtl_file_0 = "F:\\FinalProject\\PaperProject\\Models\\scene_0_obj\\CornellBox.mtl";
const char* cornell_box_mtl_file_1 = "F:\\FinalProject\\PaperProject\\Models\\scene_1_obj\\scene01.mtl";
int top_left_corner = 0;
int bottom_right_corner =512;
struct path {
	glm::vec3 result;
	glm::vec3 radiance;
	glm::vec3 attenuation;
	glm::vec3 origin;
	glm::vec3 direction;
	unsigned int seed;
	int depth;
	int countEmitted;
	bool done;
};
glm::vec3 CosweightSampling(glm::vec3 N) {
	glm::vec3 sampledir;
	// generate sample kernel
	// ----------------------
	//std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
	//std::default_random_engine generator;
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
	glm::mat3x3 TBN(T, N, B);
	sampledir = glm::normalize(TBN * sampledir);
	//printf("Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	return sampledir;

}
int main()
{
	//声明采样数
	unsigned int sqrt_num_samples =64;
	unsigned int samples_per_pixel = sqrt_num_samples * sqrt_num_samples;
	//路径深度
	int DEPTH =5;
	float inv_samples = 1.0f / samples_per_pixel;
	SceneParser scene_parser(cornell_box_file_0, cornell_box_mtl_file_0);
	//SceneParser scene_parser("../Models/plane.obj","../Models/plane.mtl");
	PerspectiveCamera camera(camera_pos, camera_dir, camera_up, camera_fovy);
	Image* result = new Image(WIDTH, HEIGHT);
	PathTracer pathtracer(&scene_parser, DEPTH);
	result->SetAllPixels(glm::vec3(0.0f, 0.0f, 0.0f));
	for (int i =top_left_corner; i <bottom_right_corner; i++) {
		for (int j = top_left_corner;j <bottom_right_corner; j++) {
			glm::vec3 color(0.0f, 0.0f, 0.0f);//当前像素点的最终颜色
			
			for (int k = 0; k <samples_per_pixel ; k++) {
				//
				// Sample pixel using jittering
				//
				unsigned int x = k % sqrt_num_samples;
				unsigned int y = k / sqrt_num_samples;
				glm::vec2 samplepixel(i, j);
				samplepixel = samplepixel +glm::vec2(x, y)*(1.0f/sqrt_num_samples)+glm::vec2(1.0f / samples_per_pixel, 1.0f / samples_per_pixel);
				glm::vec2 jitter = glm::vec2((rand()*2.0f/RAND_MAX- 1.0f)/ samples_per_pixel, (rand()*2.0f / RAND_MAX - 1.0f) / samples_per_pixel);
				/*printf("x=%.2f,y=%.2f\n", jitter.x, jitter.y);
				printf("%.2f,%.2f\n", samplepixel.x, samplepixel.y);*/
				samplepixel = samplepixel;
				glm::vec2 screenpnt(samplepixel.x / WIDTH, samplepixel.y/ HEIGHT);
				//从相机发出一条光线
				Ray ray= camera.generateRay(screenpnt);
				Hit hit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
				intersecttype intersect = BG;
				//初始化当前路径
				path current_path;
				current_path.attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
				current_path.radiance = glm::vec3(0.0f, 0.0f, 0.0f);
				current_path.result= glm::vec3(0.0f, 0.0f, 0.0f);
				current_path.depth = 0;
				current_path.done = false;
				current_path.countEmitted = true;
				AreaLight al = scene_parser.getLight();
				//Path Tracing
				for (;;) {
					//当前光线与场景求交
					intersect = scene_parser.Intersect(ray, hit, 0);
					switch (intersect)
					{
					case BG:
						current_path.done = true;
						current_path.radiance= glm::vec3(0.0f, 0.0f, 0.0f);
						break;
					case LIGHT:
						current_path.done = true;
						current_path.radiance= current_path.countEmitted? glm::vec3(15.0f, 15.0f, 5.0f): glm::vec3(0.0f, 0.0f, 0.0f);
						break;
					case DIFFUSE:
						current_path.origin = hit.getIntersectionPoint();
						//Sample a direction
						current_path.direction = CosweightSampling(hit.getNormal());
						current_path.attenuation = current_path.attenuation * hit.getMaterial()->GetKd();
						current_path.countEmitted = false;
						//Compute Direct Lighting
						 glm::vec3 dresult(0.0f, 0.0f, 0.0f); 
						 //Random choose a point on light
						 float z1 = rand()*1.0f / RAND_MAX;
						 float z2 = rand()*1.0f / RAND_MAX;
						 glm::vec3 light_pos = al.getLightPos(z1, z2);
						
						 float  Ldist = glm::length(light_pos - current_path.origin);
						 glm::vec3 L = glm::normalize(light_pos - current_path.origin);
						 float  nDl = glm::dot(hit.getNormal(), L);
						 float  LnDl = glm::dot(glm::vec3(0.0f,-1.0f,0.0f), -L);

						 // cast shadow ray
						 if (nDl > 0.0f && LnDl > 0.0f)
						 {
							 // Note: bias both ends of the shadow ray, in case the light is also present as geometry in the scene.
							 Ray shadowray(current_path.origin, L);
							 Hit shadowhit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
							 bool intersectshadow = scene_parser.IntersectShadowRay(shadowray, shadowhit, 1e-3f,Ldist);
							 if (!intersectshadow)
							 {
								 float A = al.getArea();
								// printf("%.4f\n", A);
								 // convert area based pdf to solid angle
								 float weight = nDl * LnDl * A /( PI * Ldist * Ldist);
								 dresult += glm::vec3(15.0f, 15.0f, 5.0f) * weight;
							 }
						 }
						 current_path.radiance = dresult;
						break;
					}
					//if we have hit bg or light source
					if (current_path.done) {
						current_path.result += current_path.radiance*current_path.attenuation;
						break;
					}
					//Russian roulette termination
					if (current_path.depth >= DEPTH) {
						float pcont = glm::max(glm::max(current_path.attenuation.x, current_path.attenuation.y), current_path.attenuation.z);
						float p= rand()*1.0f / RAND_MAX;
						if (p >= pcont)
							break;
						current_path.attenuation /= pcont;
					}
					current_path.depth++;
					current_path.result+= current_path.radiance*current_path.attenuation;
					ray.setOrigin(current_path.origin);
					ray.setDirection(current_path.direction);
					hit=Hit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
				}
				color += current_path.result*inv_samples;
			}
			printf("<%d %d> is OK\n", i, j);
			result->SetPixel(i, j,color);
		}
	}
	result->SaveTGA("test2.tga");
	free(result);
	
	return 0;
}