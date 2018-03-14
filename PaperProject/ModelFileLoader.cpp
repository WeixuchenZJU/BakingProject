#include "ModelFileLoader.h"
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
ModelFileLoader::ModelFileLoader()
{
}


ModelFileLoader::~ModelFileLoader()
{
}
void ModelFileLoader::OBJLoader(const char* OBJ_FILE,Scene* scene) {
	//��ȡģ������
	printf("Loading OBJ file %s...\n", OBJ_FILE);
	std::vector<glm::vec3> temp_vertices;//��������
	std::vector<glm::vec3> temp_normals;//��������
	std::vector<glm::vec2> temp_uvs;//������������
	int numoffaces = 0;
	int numofgroup = 0;//��ǰ����������
	Group currentgroup;//��ǰ����
	FILE * file = fopen(OBJ_FILE, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return;
	}
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
				   // else : parse lineHeader
	    //���ȼ��س����Ĳ����б�
		if (strcmp(lineHeader, "mtllib") == 0) {
			std::string root = OBJ_FILE;
			char mtlname[128];
			int res = fscanf(file, "%s", mtlname);
			int position=root.rfind("/");
			root = root.substr(0, position+1);
			root = root + mtlname;
			scene->LoadMTLList(root);
		}
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//��ȡÿ����
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			Vertex v[4];
			for (int i = 0; i < 3; i++) {
				v[i].Position = temp_vertices[vertexIndex[i] - 1];
				v[i].Normal = temp_normals[normalIndex[i] - 1];
				v[i].TexCoords = temp_uvs[uvIndex[i] - 1];
				currentgroup.AddVertex(v[i]);
			}
			numoffaces++;
			if (matches == 12) {
				v[3].Position = temp_vertices[vertexIndex[3] - 1];
				v[3].Normal = temp_normals[normalIndex[3] - 1];
				v[3].TexCoords = temp_uvs[uvIndex[3] - 1];
				currentgroup.AddVertex(v[0]);
				currentgroup.AddVertex(v[2]);
				currentgroup.AddVertex(v[3]);
				numoffaces++;
			}
			else if (matches == 9) {
			}
			else {
				printf("False number of face vertex!\n");
			}

		}
		//����������µĲ��ʣ���������Ҫ���ɵ�Group���ӵ������У�ͬʱ�����µ�Group
		else if (strcmp(lineHeader, "usemtl") == 0) {
			char currentmat[128];
			int res = fscanf(file, "%s", currentmat);
			if (numofgroup != 0) {
				scene->AddToGroup(currentgroup);
				currentgroup = Group();
			}
			numofgroup++;
			//���ҵ�ǰ�����ڲ����б��е�����
			int mtlindex = scene->FindMTLIndex(currentmat);
			currentgroup.SetMTLIndex(mtlindex);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	//�����һ������볡����
	scene->AddToGroup(currentgroup);
	printf("Faces:%d Vertex:%d Normals:%d UVs:%d\n", numoffaces,temp_vertices.size(),temp_normals.size(),temp_uvs.size());
	fclose(file);
}
void ModelFileLoader::OBJColorLoader(const char* OBJ_FILE, std::vector<ColorVertex> &vertices) {
	//printf("Loading OBJ Color file %s...\n", OBJ_FILE);

	//std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	//std::vector<glm::vec3> temp_vertices;//��������
	//std::vector<glm::vec3> temp_normals;//��������
	//std::vector<glm::vec2> temp_uvs;//������������
	//std::vector<glm::uvec3> temp_vertex_indices;//�涥��������������������������������λ�õ�����
	//std::vector<glm::uvec3> temp_normal_indices;//�淨�������������������������������㷨�������
	//std::vector<glm::uvec3> temp_uv_indices;//��UV�������������������������������������������
	//int numoffaces = 0;

	////������Ϣ
	//glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);
	//glm::vec3 lightPos = glm::vec3(3.0, 3.0, 3.0);
	//glm::vec3 objectColor = glm::vec3(1.0, 1.0, 1.0);

	//// ambient
	//float ambientStrength = 0.0;
	//glm::vec3 ambient = ambientStrength * lightColor;

	//FILE * file = fopen(OBJ_FILE, "r");
	//if (file == NULL) {
	//	printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
	//	return;
	//}
	//while (1) {

	//	char lineHeader[128];
	//	// read the first word of the line
	//	int res = fscanf(file, "%s", lineHeader);
	//	if (res == EOF)
	//		break; // EOF = End Of File. Quit the loop.

	//			   // else : parse lineHeader

	//	if (strcmp(lineHeader, "v") == 0) {
	//		glm::vec3 vertex;
	//		fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
	//		temp_vertices.push_back(vertex);
	//	}
	//	else if (strcmp(lineHeader, "vt") == 0) {
	//		glm::vec2 uv;
	//		fscanf(file, "%f %f\n", &uv.x, &uv.y);
	//		uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
	//		temp_uvs.push_back(uv);
	//	}
	//	else if (strcmp(lineHeader, "vn") == 0) {
	//		glm::vec3 normal;
	//		fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	//		temp_normals.push_back(normal);
	//	}
	//	//��ȡÿ����
	//	else if (strcmp(lineHeader, "f") == 0) {
	//		ColorVertex colorvertex[4];
	//		unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
	//		//Ϊÿ������������������ɫ
	//		glm::vec3 vertexcolor[4];
	//		glm::vec3 lightDir[4];
	//		int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
	//		temp_vertex_indices.push_back(glm::uvec3(vertexIndex[0], vertexIndex[1], vertexIndex[2]));
	//		temp_normal_indices.push_back(glm::uvec3(normalIndex[0], normalIndex[1], normalIndex[2]));
	//		temp_uv_indices.push_back(glm::uvec3(uvIndex[0], uvIndex[1], uvIndex[2]));
	//		//�𶥵������ɫ
	//		for (int i = 0; i < 3; i++) {
	//			lightDir[i] = glm::normalize(lightPos - temp_vertices[vertexIndex[i] - 1]);
	//			//lightDir[i] = glm::normalize(glm::vec3(1.0, 1.0, 1.0));
	//			glm::vec3 diffuse=glm::max(glm::dot(temp_normals[normalIndex[i]-1],lightDir[i]),0.0f)*lightColor;
	//			vertexcolor[i] = (ambient + diffuse) * objectColor;
	//			colorvertex[i].Position = temp_vertices[vertexIndex[i] - 1];
	//			colorvertex[i].Color = vertexcolor[i];
	//			vertices.push_back(colorvertex[i]);
	//		}
	//		numoffaces++;
	//		if (matches == 12) {
	//			temp_vertex_indices.push_back(glm::uvec3(vertexIndex[0], vertexIndex[2], vertexIndex[3]));
	//			temp_normal_indices.push_back(glm::uvec3(normalIndex[0], normalIndex[2], normalIndex[3]));
	//			temp_uv_indices.push_back(glm::uvec3(uvIndex[0], uvIndex[2], uvIndex[3]));

	//			//�𶥵������ɫ
	//			for (int i = 0; i < 4; i++) {
	//				if (i != 1) {
	//					lightDir[i] = glm::normalize(lightPos - temp_vertices[vertexIndex[i] - 1]);
	//					//lightDir[i] = glm::normalize(glm::vec3(1.0, 1.0, 1.0));
	//					glm::vec3 diffuse = glm::max(glm::dot(temp_normals[normalIndex[i] - 1], lightDir[i]), 0.0f)*lightColor;
	//					vertexcolor[i] = (ambient + diffuse) * objectColor;
	//					colorvertex[i].Position = temp_vertices[vertexIndex[i] - 1];
	//					colorvertex[i].Color = vertexcolor[i];
	//					vertices.push_back(colorvertex[i]);
	//				}
	//			}
	//			numoffaces++;
	//		}
	//		else if (matches == 9) {
	//		}
	//		else {
	//			printf("False!\n");
	//			//return;
	//		}

	//	}
	//	else if (strcmp(lineHeader, "usemtl") == 0) {
	//		char currentmat[128];
	//		int res = fscanf(file, "%s", currentmat);
	//	}
	//	else {
	//		// Probably a comment, eat up the rest of the line
	//		char stupidBuffer[1000];
	//		fgets(stupidBuffer, 1000, file);
	//	}
	//}
	//printf("Faces:%d Vertex:%d Normals:%d UVs:%d\n", numoffaces, temp_vertices.size(), temp_normals.size(), temp_uvs.size());

}
void ModelFileLoader::COBJLoader(const char* COBJ_FILE, std::vector<ColorVertex> &vertices) {
	FILE * file = fopen(COBJ_FILE, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 pos;
			glm::vec3 col;
			fscanf(file, "%f %f %f %f %f %f\n", &pos.x, &pos.y, &pos.z, &col.x, &col.y, &col.z);
			ColorVertex vertex;
			vertex.Position = pos;
			vertex.Color = col;
			vertices.push_back(vertex);
		}
	}

}