#include "Scene.h"
#include <string>
#include <iostream>


Scene::Scene()
{
}


Scene::~Scene()
{
}
void Scene::LoadMTLList(std::string mtlfilepath) {
	std::string root = mtlfilepath;
	int position = root.rfind("/");
	root = root.substr(0, position + 1);
	//加载材质列表
	printf("Loading MTL file %s...\n", mtlfilepath.c_str());
	FILE * mtl_file = fopen(mtlfilepath.c_str(), "r");
	if (mtl_file == NULL) {
		printf("Impossible to open the MTL file !\n");
		return;
	}
	int mat_num = 0;
	Material current_mat = Material();
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(mtl_file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "newmtl") == 0) {
			if (mat_num != 0) {
				material_list.push_back(current_mat);
				current_mat = Material();
			}
			char matname[128];
			int res = fscanf(mtl_file, "%s", matname);
			current_mat.SetName(matname);
			mat_num++;
		}
		if (strcmp(lineHeader, "Kd") == 0) {
			glm::vec3 Kd;
			fscanf(mtl_file, "%f %f %f\n", &Kd.x, &Kd.y, &Kd.z);
			current_mat.SetKd(Kd);
		}
		if (strcmp(lineHeader, "Ka") == 0) {
			glm::vec3 Ka;
			fscanf(mtl_file, "%f %f %f\n", &Ka.x, &Ka.y, &Ka.z);
			current_mat.SetKa(Ka);
		}
		if (strcmp(lineHeader, "Ks") == 0) {
			glm::vec3 Ks;
			fscanf(mtl_file, "%f %f %f\n", &Ks.x, &Ks.y, &Ks.z);
			current_mat.SetKs(Ks);
		}
		if (strcmp(lineHeader, "Ni") == 0) {
			float Ni;
			fscanf(mtl_file, "%f\n",&Ni);
			current_mat.SetNi(Ni);
		}
		if (strcmp(lineHeader, "Ns") == 0) {
			float Ns;
			fscanf(mtl_file, "%f\n", &Ns);
			current_mat.SetNs(Ns);
		}
		if (strcmp(lineHeader, "map_Kd") == 0) {
			
			char name[128];
			fscanf(mtl_file, "%s\n", name);
			std::string mapkdname = root + name;
			current_mat.SetMapKd(mapkdname.c_str());
		}
		if (strcmp(lineHeader, "map_Ka") == 0) {
			char name[128];
			fscanf(mtl_file, "%s\n", name);
			std::string mapkaname = root + name;
			current_mat.SetMapKa(mapkaname.c_str());
		}
	}
	material_list.push_back(current_mat);

	printf("%d\n", material_list.size());
	for (int i = 0; i < material_list.size(); i++) {
		printf("%s\n", material_list[i].GetName());
	}

	fclose(mtl_file);
}