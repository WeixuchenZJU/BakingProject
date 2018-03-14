#include "OutputTriData.h"
#include "ModelFileLoader.h"
#include "SceneFileManager.h"
#include <string>
#include <iostream>

OutputTriData::OutputTriData(const char* root, Scene *scene)
{
	std::vector<Group> g = scene->GetGroup();
	for (int ig = 0; ig < g.size(); ig++) {
		std::vector<Vertex> vertices = g[ig].GetVertices();
			for (int i = 0; i < vertices.size()/3; i++) {
				std::string datafile = root;
				datafile += "t" + std::to_string(i) + ".txt";
				printf("Output Triangle %d,%s\n", i, datafile.c_str());
				FILE *file = fopen(datafile.c_str(), "w");
				fprintf(file, "#Triangle %d\n", i);
				//输出顶点
				fprintf(file, "v0 %f %f %f\n", vertices[i * 3 + 0].Position.x, vertices[i * 3 + 0].Position.y, vertices[i * 3 + 0].Position.z);
				fprintf(file, "v1 %f %f %f\n", vertices[i * 3 + 1].Position.x, vertices[i * 3 + 1].Position.y, vertices[i * 3 + 1].Position.z);
				fprintf(file, "v2 %f %f %f\n", vertices[i * 3 + 2].Position.x, vertices[i * 3 + 2].Position.y, vertices[i * 3 + 2].Position.z);
				//输出采样点

				fclose(file);
			}
	}
}


OutputTriData::~OutputTriData()
{
}
