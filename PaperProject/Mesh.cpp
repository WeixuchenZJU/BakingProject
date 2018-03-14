#include "Mesh.h"
#include "SceneFileManager.h"
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
Mesh::Mesh(const char* filepath) {
	ModelFileLoader loader;
	//loader.OBJLoader(filepath, vertices, indices);
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;
	G = new MeshGraph(0);
	int vertexnum = 0;
	printf("Loading OBJ file and Constructing Graph %s...\n", filepath);
	FILE * file = fopen(filepath, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return;
	}
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0) {
			
			glm::vec3 pos;
			fscanf(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			Vertex v;
			v.Position = pos;
			v.Normal = glm::vec3(0.0f,0.0f,0.0f);
			v.TexCoords = glm::vec2(0.0f, 0.0f);
			GNode Node=(GNode)malloc(sizeof(struct GraphNode));
			Node->next = NULL;
			Node->vertex = v;
			Node->vert_id = vertexnum;
			this->G->AddVertexIntoGraph(Node);
			temp_positions.push_back(pos);
			vertices.push_back(v);
			//printf("V%d(%.2f,%.2f,%.2f)\n", vertexnum, pos.x, pos.y, pos.z);
			vertexnum++;
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
			TriangleFace face1;
			face1.v0_id = vertexIndex[0] - 1;
			face1.v1_id = vertexIndex[1] - 1;
			face1.v2_id = vertexIndex[2] - 1;
			faces.push_back(face1);
			Vertex v0;
			Vertex v1;
			Vertex v2;
			v0.Position = temp_positions[vertexIndex[0]-1];
			v1.Position = temp_positions[vertexIndex[1] - 1];
			v2.Position = temp_positions[vertexIndex[2] - 1];
			v0.Normal = temp_normals[normalIndex[0] - 1];
			v1.Normal = temp_normals[normalIndex[1] - 1];
			v2.Normal = temp_normals[normalIndex[2] - 1];
			v0.TexCoords = temp_uvs[uvIndex[0] - 1];
			v1.TexCoords = temp_uvs[uvIndex[1] - 1];
			v2.TexCoords = temp_uvs[uvIndex[2] - 1];
			G->InsertEdge(vertexIndex[0] - 1, vertexIndex[1] - 1);
			G->InsertEdge(vertexIndex[1] - 1, vertexIndex[2] - 1);
			G->InsertEdge(vertexIndex[2] - 1, vertexIndex[0] - 1);
			if (matches == 12) {
				Vertex v3;
				v3.Position = temp_positions[vertexIndex[3] - 1];
				v3.Normal = temp_normals[normalIndex[3] - 1];
				v3.TexCoords = temp_uvs[uvIndex[3] - 1];
				G->InsertEdge(vertexIndex[0] - 1, vertexIndex[2] - 1);
				G->InsertEdge(vertexIndex[2] - 1, vertexIndex[3] - 1);
				G->InsertEdge(vertexIndex[3] - 1, vertexIndex[0] - 1);
				TriangleFace face2;
				face2.v0_id = vertexIndex[0] - 1;
				face2.v1_id = vertexIndex[2] - 1;
				face2.v2_id = vertexIndex[3] - 1;
				faces.push_back(face2);

			}
			else if (matches == 9) {
			}
			else {
				printf("False!\n");
			}

		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
}
void Mesh::ComputeColorVertices() {
	for (int i = 0; i <vertices.size(); i++) {
		ColorVertex cv;
		cv.Position = vertices[i].Position;
		glm::vec3 color = glm::dot(vertices[i].Normal,glm::normalize(scenemanager::lightpos[0]-cv.Position))*scenemanager::lightcolor[0];
		cv.Color =color;
		colorvertices.push_back(cv);
	}
}
void Mesh::OutPutColorFile(const char*  outputfile) {
	FILE *file = fopen(outputfile, "w");
	for (int i = 0; i < colorvertices.size(); i++) {
		fprintf(file, "v %f %f %f %f %f %f\n", colorvertices[i].Position.x, colorvertices[i].Position.y, colorvertices[i].Position.z,
			colorvertices[i].Color.x, colorvertices[i].Color.y, colorvertices[i].Color.z);
	}
	fclose(file);
}
Mesh::~Mesh() {

}
//向图中插入边
int MeshGraph::InsertEdge(int v0_id, int vt_id) {
	GNode temp = (GNode)malloc(sizeof( struct GraphNode));
	temp->next = NULL;
	temp->vert_id = vt_id;
	temp->vertex = m_Graph[vt_id]->vertex;
	if (m_Graph[v0_id]->next != NULL) {
		temp->next = m_Graph[v0_id]->next;
		m_Graph[v0_id]->next = temp;
	}
	else {
		m_Graph[v0_id]->next = temp;
	}
	return 1;
}
int MeshGraph::DeleteEdge(int v0_id, int vt_id) {
	//首先判断这条边是否存在
	GNode p = m_Graph[v0_id];
	if (p->next == NULL) {
		printf("不存在！\n");
		return 0;
	}
	else {
		while (p->next != NULL) {
			if (p->next->vert_id == vt_id) {
				//找到要删除的有向边
				//执行删除
				GNode temp = p->next;
				p->next = temp->next;
				temp->next = NULL;
				free(temp);
				return 1;
			}
			else { p = p->next; }
		}
		printf("不存在！\n");
		return 0;
	}

}
//在三角形内部插入一个顶点
int MeshGraph::InsertVertexInFace(TriangleFace targetface) {
	glm::vec3 v0 = m_Graph[targetface.v0_id]->vertex.Position;
	glm::vec3 v1 = m_Graph[targetface.v1_id]->vertex.Position;
	glm::vec3 v2 = m_Graph[targetface.v2_id]->vertex.Position;
	float alpha, beta, gamma;
	alpha = 0.3f, beta = 0.3f;
	gamma = 1 - alpha - beta;
	glm::vec3 insertpos = alpha * v0 + beta * v1 + gamma * v2;
	Vertex v;
	v.Position = insertpos;
	v.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
	v.TexCoords = glm::vec2(0.0f, 0.0f);
	GNode Node = (GNode)malloc(sizeof(struct GraphNode));
	Node->next = NULL;
	Node->vertex = v;
	Node->vert_id = m_Graph.size();
	AddVertexIntoGraph(Node);
	//新顶点和原三个顶点之间双向插入边
	InsertEdge(targetface.v0_id, Node->vert_id);
	InsertEdge(targetface.v1_id, Node->vert_id);
	InsertEdge(targetface.v2_id, Node->vert_id);
	InsertEdge(Node->vert_id, targetface.v0_id);
	InsertEdge(Node->vert_id,targetface.v1_id);
	InsertEdge(Node->vert_id, targetface.v2_id);
	return 1;
}
//遍历有向图生成面
void MeshGraph::GenFaceIndices() {
	std::vector<int> Stack1;
	std::vector<int> Stack2;
	for (int i = 0; i < m_Graph.size(); i++) {
		int v0 = i;
		//从图中第一个顶点开始
		GNode p0 = m_Graph[i];
		//确保该顶点不是孤立点
		//将起点的所有儿子节点压栈1
		while (p0->next != NULL) {	
			Stack1.push_back(p0->next->vert_id);
			p0 = p0->next;
		}
		//当栈1非空时，不断Pop内部元素
		while (Stack1.size() > 0) {
			int v1 = Stack1.at(Stack1.size()-1);
			Stack1.pop_back();
			GNode p1 = m_Graph[v1];
			//将中点的所有儿子节点压栈2
			while (p1->next != NULL) {
				Stack2.push_back(p1->next->vert_id);
				p1 = p1->next;
			}
			//当栈2非空时，Pop内部元素
			while (Stack2.size() > 0) {
				int v2 = Stack2.at(Stack2.size()-1);
				Stack2.pop_back();
				GNode p2 = m_Graph[v2];
				//判断p2能否构成回路
				while (p2->next != NULL) {
					//找到回路
					if (p2->next->vert_id == v0) {
						//添加进面索引中
						TriangleFace face;
						face.v0_id = v0+ 1;
						face.v1_id = v1+ 1;
						face.v2_id = v2+ 1;
						m_faceindices.push_back(face);
						DeleteEdge(v2, v0);
						break;
					}
					else
						p2 = p2->next;
				}
			}
			//2号栈已空，可以将v0->v1这条边删除
			DeleteEdge(v0, v1);
		}

	}
//
	/*	TriangleFace face;
		face.v0_id = i;
		face.v1_id = i + 1;
		face.v2_id = i + 2;
		m_faceindices.push_back(face);*/
	
}
//根据图输出OBJ文件
void MeshGraph::GenOBJFromGraph(const char* outfile)
{
	FILE *file = fopen(outfile, "w");
	for (int i = 0; i < m_Graph.size(); i++) {
		fprintf(file, "v %f %f %f\n", m_Graph[i]->vertex.Position.x, m_Graph[i]->vertex.Position.y, m_Graph[i]->vertex.Position.z);
	}
	for (int i = 0; i < m_faceindices.size(); i++) {
		fprintf(file, "f %d %d %d\n",m_faceindices[i].v0_id, m_faceindices[i].v1_id, m_faceindices[i].v2_id);
	}
	fclose(file);
}