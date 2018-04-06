#include "SceneParser.h"
#include <string.h>
#define EPS 1e-2f
SceneParser::SceneParser(const char *filename, const char *mtl_filename) {
	//Read MTL
	printf("Loading MTL file %s\n", mtl_filename);
	FILE * mtl_file = fopen(mtl_filename, "r");
	if (mtl_file == NULL) {
		printf("Impossible to read materials \n");	
	}
	int mat_num = 0;
	Material current_mat=Material();
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(mtl_file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "newmtl") == 0) {
			if (mat_num != 0) {
				materials.push_back(current_mat);
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
	}
	materials.push_back(current_mat);
	fclose(mtl_file);

	printf("%d\n", materials.size());
	for (int i = 0; i < materials.size(); i++) {
		printf("%s\n", materials[i].GetName());
	}
	//Read OBJ
	printf("Loading OBJ file %s...\n", filename);
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;//顶点容器
	std::vector<glm::vec3> temp_normals;//法线容器
	std::vector<glm::vec2> temp_uvs;//纹理坐标容器
	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? \n");
		return;
	}
	int current_matindex=-1;
	while (1) {
		
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

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
		//读取每个面
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			Vertex v0, v1, v2;
			v0.pos = temp_vertices[vertexIndex[0] - 1];
			v0.normal = temp_normals[normalIndex[0] - 1];
			v0.TexCoord = temp_uvs[uvIndex[0] - 1];
			v1.pos = temp_vertices[vertexIndex[1] - 1];
			v1.normal = temp_normals[normalIndex[1] - 1];
			v1.TexCoord = temp_uvs[uvIndex[1] - 1];
			v2.pos = temp_vertices[vertexIndex[2] - 1];
			v2.normal = temp_normals[normalIndex[2] - 1];
			v2.TexCoord = temp_uvs[uvIndex[2] - 1];
			Triangle face(v0, v1, v2);
			face.SetMatIndex(current_matindex);
			face.SetMaterial(&materials[current_matindex]);
			triangles.push_back(face);
			if (matches == 12) {
				Vertex v3;
				v3.pos = temp_vertices[vertexIndex[3] - 1];
				v3.normal = temp_normals[normalIndex[3] - 1];
				v3.TexCoord = temp_uvs[uvIndex[3] - 1];
				Triangle face2(v0, v2, v3);
				face2.SetMatIndex(current_matindex);
				face2.SetMaterial(&materials[current_matindex]);
				triangles.push_back(face2);
			}
			else if (matches == 9) {
			}
			else {
				printf("False!\n");
			}

		}
		else if (strcmp(lineHeader, "usemtl") == 0) {
			char currentmat[128];
			int res = fscanf(file, "%s", currentmat);
			current_matindex = FindMaterials(currentmat);

		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	fclose(file);
}
SceneParser::~SceneParser() {

}
intersecttype SceneParser::Intersect(Ray &ray,Hit &hit,float tmin) {
	for (int i = 0; i < triangles.size(); i++) {
		triangles[i].intersect(ray, hit, tmin);
	}
	if (hit.getMaterial() == NULL) {
		return BG;
	}
	else {
	    return DIFFUSE;
	}

}
bool SceneParser::IntersectShadowRay(Ray &ray, Hit &hit, float tmin,float lightdis) {
	for (int i = 0; i < triangles.size(); i++) {
		triangles[i].intersect(ray, hit, tmin);
		if (hit.getT()<lightdis-0.01) {
			return true;
		}
	}
	return false;
}