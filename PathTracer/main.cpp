#include <stdio.h>
#include "Camera.h"
#include "SceneFileManager.h"
#include "SceneParser.h"
#include "image.h"
#include "PathTracer.h"
#include "Path.h"
#include "Filter.h"
#include "timer.h"
#include <random>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#define PI 3.14159265f
static std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
static std::default_random_engine generator;
#define UNIFORMDIS randomFloats(generator)
#define EPS 0.01
glm::vec3 camera_pos(278.0f, 273.0f, -800.0f);
glm::vec3 camera_dir(0.0f, 0.0f, 1.0f);
glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
int WIDTH =512;
int HEIGHT = 512;
glm::vec2 inv_ImgSize(1.0f / WIDTH, 1.0f / HEIGHT);
float camera_fovy =49.1f; 
const char* cornell_box_file_0 = "..\\Models\\scene_0_obj\\CornellBoxLight.obj";
const char* cornell_box_file_1 = "..\\Models\\scene_1_obj\\scene01.obj";
const char* cornell_box_mtl_file_0 = "..\\Models\\scene_0_obj\\CornellBoxLight.mtl";
const char* cornell_box_mtl_file_1 = "..\\Models\\scene_1_obj\\scene01.mtl";
int top_left_corner =0;
int bottom_right_corner = 512;
glm::vec3 lightemit(9.0f, 9.0f, 3.0f);
SceneParser scene_parser(cornell_box_file_0, cornell_box_mtl_file_0);
PerspectiveCamera camera(camera_pos, camera_dir, camera_up, camera_fovy);
glm::vec3 computeRadiance(Hit x, glm::vec3 dir,int depth, glm::vec3 attenuation);
struct path {
	glm::vec3 result;//路径的最终结果
	glm::vec3 radiance;//当前路径的辐射亮度
	glm::vec3 attenuation;
	glm::vec3 origin;//当前路径的起点
	glm::vec3 direction;//当前路径的方向
	int depth;//当前路径的深度
	int countEmitted;
	bool done;
};
glm::vec3 l0(213.0f, 548.79f, 227.0f);
glm::vec3 le1(130.0f, 0.0f, 0.0f);
glm::vec3 le2(0.0f, 0.0f, 105.0f);
glm::vec3 lightnormal(0.0f, -1.0f, 0.0f);
float lightarea = 13650.0f;
float inv_gamma = 1.0f / 2.2f;
glm::vec3 CosweightSampling(glm::vec3 N) {
	glm::vec3 sampledir;
	// generate sample kernel
	// ----------------------
	float theta, phi;
	float U1, U2;
	U1 = UNIFORMDIS;
	U2 = UNIFORMDIS;
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
	T = glm::normalize(glm::cross(N,V));
	B = glm::normalize(glm::cross(T,N));
	//printf("Tan:<%.2f,%.2f,%.2f>\n", T.x, T.y, T.z);
	//printf("Bitan:<%.2f,%.2f,%.2f>\n", B.x, B.y, B.z);
	glm::mat3x3 TBN(T, N, B);
	//TBN = glm::transpose(TBN);
	sampledir = glm::normalize(TBN * sampledir);
	//printf("Sampledir:<%.2f,%.2f,%.2f>\n", sampledir.x, sampledir.y, sampledir.z);
	return sampledir;

}

bool IsHitLight(Hit hit) {
	return (glm::length(hit.getMaterial()->GetKa()) > 0);
}
glm::vec3 Le(Hit hit, glm::vec3 theta) {
	if (IsHitLight(hit)) {
		//printf("Next Hit Is Light!\n");
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}
	else
		return glm::vec3(0.0f, 0.0f, 0.0f);
}
//glm::vec3 SimpleStochasticRT(Hit x, glm::vec3 theta, int depth, glm::vec3 f) {
//	glm::vec3 estimatedRadiance(0.0f, 0.0f, 0.0f);
//	
//		//if (depth < 5) {
//		//	glm::vec3 psi = CosweightSampling(x.getNormal());
//		//	Ray nextray(x.getIntersectionPoint(), psi);
//		//	Hit nexthit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
//		//	scene_parser.Intersect(nextray, nexthit, 0);
//		//	if (nexthit.getMaterial() != NULL) {
//		//		f *= x.getMaterial()->GetKd();
//		//		estimatedRadiance = SimpleStochasticRT(nexthit, -psi, ++depth, f)*x.getMaterial()->GetKd();
//		//	}
//		//}
//		//else {
//		glm::vec3 att = f * x.getMaterial()->GetKd();
//		float p = glm::max(glm::max(att.x, att.y), att.z);
//		if (DoRussianRoulette(depth, p)) {
//			if (glm::length(x.getMaterial()->GetKa()) > 0) {
//			estimatedRadiance = Le(x, theta);
//			}
//			else {
//				glm::vec3 psi = CosweightSampling(x.getNormal());
//				Ray nextray(x.getIntersectionPoint(), psi);
//				Hit nexthit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
//				scene_parser.Intersect(nextray, nexthit, 0);
//				if (nexthit.getMaterial() != NULL) {
//					estimatedRadiance = SimpleStochasticRT(nexthit, -psi, ++depth, att)*x.getMaterial()->GetKd();
//				}
//				//if (depth > 5) {
//				estimatedRadiance *= (1.0f / p);
//				//}
//			}
//		}
//		//}
//	return estimatedRadiance;
//}
//glm::vec3 ComputeRadiance(Ray primaryRay) {
//	Ray ray = primaryRay;
//	Hit hit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
//	intersecttype intersect=scene_parser.Intersect(primaryRay, hit, 0);
//	glm::vec3 Radiance(0.0f, 0.0f, 0.0f);
//	int N = 4096;
//	switch (intersect)
//	{
//	case BG:
//		break;
//	case DIFFUSE:
//		if (IsHitLight(hit)) {
//			Radiance = glm::vec3(1.0f, 1.0f, 1.0f);
//			//printf("Ray:%.3f %.3f %.3f\n", hit.getIntersectionPoint().x, hit.getIntersectionPoint().y, hit.getIntersectionPoint().z);
//			break;
//		}
//		else {
//			//printf("Ray:%.3f %.3f %.3f\n", hit.getIntersectionPoint().x, hit.getIntersectionPoint().y, hit.getIntersectionPoint().z);
//			for (int i = 0; i < N; i++) {
//				glm::vec3 psi = CosweightSampling(hit.getNormal());
//				Ray nextray(hit.getIntersectionPoint()+EPS*hit.getNormal(), psi);
//				Hit nexthit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
//				scene_parser.Intersect(nextray, nexthit, 0);
//				if (nexthit.getMaterial() != NULL) {
//					//printf("Nexthit %d:%.3f %.3f %.3f\n",i,nexthit.getIntersectionPoint().x, nexthit.getIntersectionPoint().y, nexthit.getIntersectionPoint().z);
//					Radiance += hit.getMaterial()->GetKd()*Le(nexthit, -nextray.getDirection());
//				}
//			}
//			//printf("Radiance:%.3f %.3f %.3f\n", Radiance.x, Radiance.y, Radiance.z);
//		//	Radiance *= (1.0f / 256.0f);
//		}
//		break;
//	}
//	return Radiance;
//}
glm::vec3 SampleLightPoint() {
	return(glm::vec3(l0 + UNIFORMDIS * le1 + UNIFORMDIS * le2));
}
float radianceTransfer(Hit x, glm::vec3 y) {
	glm::vec3 dir(y - x.getIntersectionPoint());
	float dis = glm::length(dir);
	dir = glm::normalize(dir);
	Ray shadowRay(x.getIntersectionPoint(), dir);
	Hit shadowHit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
	int V = 1-scene_parser.IntersectShadowRay(shadowRay, shadowHit, EPS,dis);
	float cosX = glm::dot(x.getNormal(), dir);
	float cosY = glm::dot(lightnormal, -dir);
	float G = cosX*cosY / (dis*dis);
	//printf("%d  %.8f cosX=%.4f cosY=%.4f dis=%.4f\n", V,G*lightarea,cosX,cosY,dis);
	return (G*V*lightarea);
}
glm::vec3 directIllumination(Hit x, glm::vec3 dir,int depth)
{
	glm::vec3 Radiance(0.0f, 0.0f, 0.0f);
		int numShadowray =1;
		float inv_numShadowray = 1.0f / numShadowray;
		for (int i = 0; i < numShadowray; i++) {
			glm::vec3 y = SampleLightPoint();
			Radiance += lightemit*x.getMaterial()->GetKd()*radianceTransfer(x, y);
			//Radiance += glm::vec3(34.0f, 13.0f, 5.0f)*x.getMaterial()->GetKd()*radianceTransfer(x, y);
		}
		Radiance *= inv_numShadowray;
	return Radiance;
}
glm::vec3 indirectIllumination(Hit x, glm::vec3 dir,int depth, glm::vec3 attenuation)
{
	glm::vec3 Radiance(0.0f, 0.0f, 0.0f);
	int numSamplepath = 1;
	float inv_numSamplepath = 1.0f / numSamplepath;
	glm::vec3 f = x.getMaterial()->GetKd();
	float p = glm::max(f.x, glm::max(f.y, f.z));
	if (UNIFORMDIS < p) {
		for (int i = 0; i < numSamplepath; i++) {
			glm::vec3 psi = CosweightSampling(x.getNormal());
			Ray nextray(x.getIntersectionPoint(), psi);
			Hit nexthit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
			scene_parser.Intersect(nextray, nexthit, EPS);
			if (nexthit.getMaterial() != NULL) {
				Radiance += computeRadiance(nexthit, -psi,++depth,f)*x.getMaterial()->GetKd();
			}
		}
		Radiance *= inv_numSamplepath;
	}
	Radiance *= (1.0f / p);
	return Radiance;
}
glm::vec3 computeRadiance(Hit x, glm::vec3 dir,int depth,glm::vec3 attenuation) {
	glm::vec3 Radiance(0.0f, 0.0f, 0.0f);
	if (!IsHitLight(x)) {
		Radiance += directIllumination(x, dir,depth);
		Radiance += indirectIllumination(x, dir,depth,attenuation);
	}
	return Radiance;
}
glm::vec3 rad(Ray ray) {
	Hit hit(FLT_MAX, NULL, glm::vec3(0.0f, 0.0f, 0.0f));
	scene_parser.Intersect(ray, hit, 0);
	if (hit.getMaterial() == NULL) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else {
		return (Le(hit, ray.getDirection()) + computeRadiance(hit, -ray.getDirection(),0,glm::vec3(1.0f,10.f,1.0f)));
	}

}
//Calculate Jittered sample pos in a pixel
int main()
{
	//像素网格维度
	unsigned int subpixelwidth=2;
	//总采样点个数
	unsigned int subpixelnum =4;	
	unsigned int samplenum =4096;
	unsigned int subpixelsamplenum = samplenum / subpixelnum;
	float inv_samplenum = 1.0f / samplenum;
	//路径深度
	int DEPTH =10;
	
	Image* result = new Image(WIDTH, HEIGHT);
	result->SetAllPixels(glm::vec3(0.0f, 0.0f, 0.0f));
	float totalnum = WIDTH*HEIGHT;
	float percentage = 0.0f;
	int pix_done = 0;
	float halfsubpixellength = 0.5f / subpixelwidth;
	//路径追踪器
	PathTracer pathtracer(&scene_parser, 1);	
	//滤波器
	Filter tentfilter(1.0f, 2.0f);
	float kernelsize = 3.5f;
	float halfkernelsize = kernelsize/2;
	float halfkernelradius = kernelsize/4;
	GetCPUTime();
	for (int i = top_left_corner; i < bottom_right_corner; i++) {
#pragma omp parallel for			
		for (int j = top_left_corner; j < bottom_right_corner; j++) {
			//当前像素的最终颜色
			glm::vec3 Color(0.0f, 0.0f, 0.0f);
			//float weightsum = 0.0f;
			//for (int k = 0; k < samplenum; k++) {
			//	//Random Sample in pixel
			//	glm::vec2 jitter(UNIFORMDIS - 0.5f, UNIFORMDIS - 0.5f);
			//	glm::vec2 samplepixel = inv_ImgSize*(pixelcenter + jitter);
			//	Ray ray = camera.generateRay(samplepixel);
			//	Color += rad(ray);
			//}
			//Color = Color * (inv_samplenum);

			//反走样开
			glm::vec2 pixelcenter = glm::vec2(i + 0.5f, j + 0.5f);
			float weightsum = 0.0f;
			//将kernel划分为2*2网格进行采样
			for(int x=-1;x<=1;x+=2){
				for (int y = -1; y <= 1; y += 2) {
					glm::vec2 kernelcenter = pixelcenter + glm::vec2(x*halfkernelradius, y*halfkernelradius);
					for (int k = 0; k < samplenum/4; k++) {
						//Jitter范围是[-halfkernelradius,halfkernelradius]
						glm::vec2 jitter((UNIFORMDIS*2 - 1.0f)*halfkernelradius, (UNIFORMDIS * 2 - 1.0f)*halfkernelradius);
						//printf("%.4f %.4f length=%.4f\n",jitter.x,jitter.y,glm::length(jitter));
						float weight = glm::max(0.0f, halfkernelsize - glm::length(kernelcenter+jitter-pixelcenter))/ halfkernelsize;
						//printf("%.4f\n", weight);
						weightsum += weight;
						glm::vec2 screenpos = inv_ImgSize * (kernelcenter+jitter);
						Ray ray = camera.generateRay(screenpos);
						//计算初始相机发射光线的辐射亮度
						Color +=weight*rad(ray);
					}
				}
			}
			//printf("sum=%.4f\n", weightsum);
			Color *= (1.0f/weightsum);
			//Convert Color 2 to rgb
			//
			//printf("567 %.4f %.4f %.4f\n", Color.x, Color.y, Color.z);
		//	Color = Color.x*nm700 + Color.y*nm600 + Color.z*nm500;
		//	printf("RGB %.4f %.4f %.4f\n", Color.x, Color.y, Color.z);
			Color=glm::clamp(Color,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
			//Do GammaCorrection
			Color = glm::vec3(pow(Color.x, inv_gamma), pow(Color.y, inv_gamma), pow(Color.z, inv_gamma) );
			result->SetPixel(i, j, Color);
		}
		printf("\rProgress:%.5f\%", (i*1.0f) / WIDTH);
	}
	printf("\nTotal time:\n%lfs\n", GetCPUTime() / 1000);
	//Save Result
	string name = "test_pathtracer";
	char spp[20] = "";
	sprintf(spp, "%dspp.tga", samplenum);
	name = name + spp;
	result->SaveTGA(name.c_str());
	delete result;
	return 0;
}