#include "OutputTriData.h"
#include "ModelFileLoader.h"
#include "SceneFileManager.h"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <io.h>  
#include <direct.h> 
#include <stb_image.h>
#include "image.h"
#include <random>
#define SAMPLENUM 5000
static std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
static std::default_random_engine generator;
#define UNIFORMDIS randomFloats(generator)
OutputTriData::OutputTriData(const char* root, Scene *scene)
{
	std::string datadir =scenemanager::scenefile[scenemanager::sceneindex];
	int len = datadir.length();
	datadir = datadir.substr(10);
	int pos=datadir.rfind(".");
	datadir = datadir.substr(0, pos);
	datadir = root + datadir;
	mkdir(datadir.c_str());
	std::vector<Group> g = scene->GetGroup();
	//Lighting Info
	int lightnum = scenemanager::lightnum;
	glm::vec3 lightpos = scenemanager::lightpos[0];
	glm::vec3 lightcolor = scenemanager::lightcolor[0];

	//每个三角形上存储三个顶点的颜色值
	for (int ig = 0; ig < g.size(); ig++) {
		std::vector<Vertex> vertices = g[ig].GetVertices();
		//读取当前Group的贴图
		// load image, create texture and generate mipmaps
		//int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		//const char *kdpath = scene->GetMTLlist()[g[ig].GetMTLIndex()].GetKdName();
		/*const char *kdpath = "../Models/Sponza/liontest.png";
		unsigned char *data = stbi_load(kdpath, &width, &height, &nrChannels, STBI_rgb_alpha);
		printf("This is a test:\n");
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
				printf("%d %d %d\n", data[(y*width+x)*4], data[(y*width + x) * 4 +1], data[(y*width + x) * 4 +2]);
			}
		}*/
			for (int i = 0; i < vertices.size()/3; i++) {
				std::string datafile = datadir;
				datafile += "/t" + std::to_string(ig)+"_" + std::to_string(i) + ".txt";
				printf("Output Triangle %d,%s\n", i, datafile.c_str());
				FILE *file = fopen(datafile.c_str(), "w");
				//fprintf(file, "#Triangle %d\n", i);
				//输出顶点 前三行为顶点重心坐标和坐标
				fprintf(file, "%f %f %f %f %f\n", 1.0f,0.0f,vertices[i * 3 + 0].Position.x, vertices[i * 3 + 0].Position.y, vertices[i * 3 + 0].Position.z);
				fprintf(file, "%f %f %f %f %f\n", 0.0f,1.0f,vertices[i * 3 + 1].Position.x, vertices[i * 3 + 1].Position.y, vertices[i * 3 + 1].Position.z);
				fprintf(file, "%f %f %f %f %f\n", 0.0f,0.0f,vertices[i * 3 + 2].Position.x, vertices[i * 3 + 2].Position.y, vertices[i * 3 + 2].Position.z);
				////输出顶点的颜色
				//for (int pi = 0; pi < 3; pi++) {
				//	int u = (vertices[i * 3 + i].TexCoords.x)*width;
				//	int v = (vertices[i * 3 + i].TexCoords.y)*height;
				//	glm::uvec4 color(data[v*height+u], data[v*height + u+1], data[v*height + u+2], data[v*height + u + 3]);
				//	//fprintf(file, "%f %f %f %f %f\n",)
				//}
				//输出采样点 后几行为采样点
				/*for (float s = 0; s <= 1; s += 0.01) {
					for (float t = 0; t <= 1; t += 0.01) {
						float a = 1 - sqrtf(t);
						float b = (1 - s)*sqrtf(t);
						float c = s * sqrtf(t);
						Vertex sp;
						sp.Position = a * vertices[i * 3 + 0].Position + b * vertices[i * 3 + 1].Position + c* vertices[i * 3 + 2].Position;
						sp.Normal = a * vertices[i * 3 + 0].Normal + b * vertices[i * 3 + 1].Normal +c* vertices[i * 3 + 2].Normal;
						sp.TexCoords = a * vertices[i * 3 + 0].TexCoords + b * vertices[i * 3 + 1].TexCoords + c* vertices[i * 3 + 2].TexCoords;
						glm::vec3 color = glm::max(0.0f,glm::dot(glm::normalize(sp.Normal), glm::normalize(lightpos - sp.Position)))*lightcolor;
						fprintf(file, "%f %f %f %f %f\n", a, b, color.r, color.g, color.b);
					}
				}*/
				for (int s = 0; s < SAMPLENUM; s++) {
					glm::vec3 bc = RandomSampleonTri(vertices[i * 3 + 0], vertices[i * 3 + 1], vertices[i * 3 + 2]);
					Vertex sp;
					sp.Position = bc.x*vertices[i * 3 + 0].Position + bc.y*vertices[i * 3 + 1].Position + bc.z*vertices[i * 3 + 2].Position;
					sp.Normal= bc.x*vertices[i * 3 + 0].Normal + bc.y*vertices[i * 3 + 1].Normal + bc.z*vertices[i * 3 + 2].Normal;
					glm::vec3 color = glm::max(0.0f, glm::dot(glm::normalize(sp.Normal), glm::normalize(lightpos - sp.Position)))*lightcolor;
					fprintf(file, "%f %f %f %f %f\n", bc.x,bc.y, color.r, color.g, color.b);
				}
				fclose(file);
			}
	}
}


OutputTriData::~OutputTriData()
{
}

glm::vec3 OutputTriData::RandomSampleonTri(Vertex v0, Vertex v1, Vertex v2) {
	float s =UNIFORMDIS, t = UNIFORMDIS;
	if (s + t > 1) {
		s = 1 - s;
		t = 1 - t;
	}
	float a = 1 - s - t;
	float b = s;
	float c = t;
	//glm::vec3 pos = a * v0.Position +b * v1.Position +c * v2.Position;
	glm::vec3 pos(a, b, c);
	return pos;
}
glm::vec3 OutputTriData::GetLightSignal(glm::vec3 sp) {
	glm::vec3 signal(0.0f, 0.0f, 0.0f);
	return signal;
}