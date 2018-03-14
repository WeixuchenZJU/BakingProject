#include "OutputTriData.h"
#include "ModelFileLoader.h"
#include "SceneFileManager.h"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <io.h>  
#include <direct.h> 
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
	//Shading Info
	int lightnum = scenemanager::lightnum;
	glm::vec3 lightpos = scenemanager::lightpos[0];
	glm::vec3 lightcolor = scenemanager::lightcolor[0];
	glm::vec3 objcolor(1.0f, 1.0f, 1.0f);


	for (int ig = 0; ig < g.size(); ig++) {
		std::vector<Vertex> vertices = g[ig].GetVertices();
			for (int i = 0; i < vertices.size()/3; i++) {
				std::string datafile = datadir;
				datafile += "/t" + std::to_string(i) + ".txt";
				printf("Output Triangle %d,%s\n", i, datafile.c_str());
				FILE *file = fopen(datafile.c_str(), "w");
				//fprintf(file, "#Triangle %d\n", i);
				//输出顶点 前三行为顶点重心坐标和坐标
				fprintf(file, "%f %f %f %f %f\n", 1.0f,0.0f,vertices[i * 3 + 0].Position.x, vertices[i * 3 + 0].Position.y, vertices[i * 3 + 0].Position.z);
				fprintf(file, "%f %f %f %f %f\n", 0.0f,1.0f,vertices[i * 3 + 1].Position.x, vertices[i * 3 + 1].Position.y, vertices[i * 3 + 1].Position.z);
				fprintf(file, "%f %f %f %f %f\n", 0.0f,0.0f,vertices[i * 3 + 2].Position.x, vertices[i * 3 + 2].Position.y, vertices[i * 3 + 2].Position.z);
				//输出采样点 后几行为采样点
				//fprintf(file, "#sp(s,t) r g b\n");
				for (float s = 0; s <= 1; s += 0.01) {
					for (float t = 0; t <= 1; t += 0.01) {
						float a = 1 - sqrtf(t);
						float b = (1 - s)*sqrtf(t);
						float c = s * sqrtf(t);
						Vertex sp;
						sp.Position = a * vertices[i * 3 + 0].Position + b * vertices[i * 3 + 1].Position + c* vertices[i * 3 + 2].Position;
						sp.Normal = a * vertices[i * 3 + 0].Normal + b * vertices[i * 3 + 1].Normal +c* vertices[i * 3 + 2].Normal;
						sp.TexCoords = a * vertices[i * 3 + 0].TexCoords + b * vertices[i * 3 + 1].TexCoords + c* vertices[i * 3 + 2].TexCoords;
						glm::vec3 color = glm::max(0.0f,glm::dot(glm::normalize(sp.Normal), glm::normalize(lightpos - sp.Position)))*lightcolor*objcolor;
						fprintf(file, "%f %f %f %f %f\n", a, b, color.r, color.g, color.b);
					}
				}
				fclose(file);
			}
	}
}


OutputTriData::~OutputTriData()
{
}
