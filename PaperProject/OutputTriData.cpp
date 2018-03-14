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
	for (int ig = 0; ig < g.size(); ig++) {
		std::vector<Vertex> vertices = g[ig].GetVertices();
			for (int i = 0; i < vertices.size()/3; i++) {
				std::string datafile = datadir;
				datafile += "/t" + std::to_string(i) + ".txt";
				printf("Output Triangle %d,%s\n", i, datafile.c_str());
				FILE *file = fopen(datafile.c_str(), "w");
				fprintf(file, "#Triangle %d\n", i);
				//输出顶点
				fprintf(file, "v0 %f %f %f\n", vertices[i * 3 + 0].Position.x, vertices[i * 3 + 0].Position.y, vertices[i * 3 + 0].Position.z);
				fprintf(file, "v1 %f %f %f\n", vertices[i * 3 + 1].Position.x, vertices[i * 3 + 1].Position.y, vertices[i * 3 + 1].Position.z);
				fprintf(file, "v2 %f %f %f\n", vertices[i * 3 + 2].Position.x, vertices[i * 3 + 2].Position.y, vertices[i * 3 + 2].Position.z);
				//输出采样点
				fprintf(file, "#sp(s,t) r g b\n");
				float s = 0.3, t = 0.3;
				Vertex sp;
				sp.Position = s * vertices[i * 3 + 0].Position + t * vertices[i * 3 + 1].Position +(1 - s - t)* vertices[i * 3 + 2].Position;
				sp.Normal = s * vertices[i * 3 + 0].Normal + t * vertices[i * 3 + 1].Normal + (1 - s - t)* vertices[i * 3 + 2].Normal;
				sp.TexCoords = s * vertices[i * 3 + 0].TexCoords + t * vertices[i * 3 + 1].TexCoords + (1 - s - t)* vertices[i * 3 + 2].TexCoords;


				fclose(file);
			}
	}
}


OutputTriData::~OutputTriData()
{
}
