#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ModelFileLoader.h"
struct GraphNode
{
	int vert_id;
	Vertex vertex;
	struct GraphNode* next;
};
typedef struct GraphNode* GNode;
class MeshGraph
{
public:
	MeshGraph(int n) { this->m_vertexnum = n;}
	~MeshGraph() {}
	int GetVertexNum() { return m_Graph.size(); }

	//向图中插入有向边
	int InsertEdge(int v0_id,int vt_id);
	//删除有向图中的一条有向边
	int DeleteEdge(int v0_id, int vt_id);
	//在三角形内部插入顶点
	int InsertVertexInFace(TriangleFace targetface);
	/*
	int InsertVertexOnEdge();*/
	void AddVertexIntoGraph(GNode Node) {
		m_Graph.push_back(Node);
	};
	//根据有向图生成面顶点索引
	void GenFaceIndices();
	//根据图输出OBJ文件
	void GenOBJFromGraph(const char* outfile);
	void printOneRingNeighbor(int vert_index) {
		GNode p=m_Graph[vert_index];
		while (p->next != NULL) {
			printf("E(v%d->v%d)\n", vert_index, p->next->vert_id);
			p = p->next;
		}
	};
	void printGraph() {
		for (int i = 0; i < m_Graph.size(); i++) {
			GNode p = m_Graph[i];
			printf("V%d->", i);
			while (p->next != NULL) {
				printf("V%d->",p->next->vert_id);
				p = p->next;
			}
			printf("NULL\n");
		}
	}
private:
	int m_vertexnum;
	std::vector<GNode> m_Graph;
	std::vector<TriangleFace> m_faceindices;

};
class Mesh
{
public:
	Mesh(const char* filepath);
	~Mesh();
	void TessFace() {
		printvert();
		for (int i = 0; i < faces.size(); i++) {
			printf("%d,%d,%d\n", faces[i].v0_id, faces[i].v1_id, faces[i].v2_id);
			glm::vec3 v0 = vertices[faces[i].v0_id].Position;
			glm::vec3 v1 = vertices[faces[i].v1_id].Position;
			glm::vec3 v2 = vertices[faces[i].v2_id].Position;

			float a, b, c;
			a = 1.0 / 3;
			b = a; c = a;
			glm::vec3 v3 =(v0 + v1 + v2)*a;

			Vertex v;
			v.Position = v3;
			v.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
			v.TexCoords = glm::vec2(0.0f, 0.0f);

			int v3_id = vertices.size();
			vertices.push_back(v);
			
			TriangleFace face1 = { faces[i].v0_id, faces[i].v1_id,v3_id};
			TriangleFace face2 = { v3_id, faces[i].v1_id, faces[i].v2_id};
			TriangleFace face3 = { faces[i].v0_id,v3_id, faces[i].v2_id };
			refine_faces.push_back(face1);
			refine_faces.push_back(face2);
			refine_faces.push_back(face3);
		}
		printf("\n");
		for (int i = 0; i < refine_faces.size(); i++) {
			printf("%d,%d,%d\n", refine_faces[i].v0_id, refine_faces[i].v1_id, refine_faces[i].v2_id);
		}
	}
	void ComputeColorVertices();
	//输出顶点位置+颜色格式文件
	void OutPutColorFile(const char*  outputfile);
	//输出正常OBJ格式文件
	void OutPutOBJFile(const char*  outputfile) {
		FILE *file = fopen(outputfile, "w");
		for (int i = 0; i < vertices.size(); i++) {
			fprintf(file, "v %f %f %f\n", vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
		}
		for (int i = 0; i < refine_faces.size(); i++) {
			fprintf(file, "f %d %d %d\n", refine_faces[i].v0_id+1, refine_faces[i].v1_id + 1, refine_faces[i].v2_id + 1);
		}
		fclose(file);
	
	
	}
	int GetVertexNum() { return G->GetVertexNum(); }
	int GetFacesNum() { return faces.size(); }
	void PrintGraph() { G->printGraph(); }
	MeshGraph* GetGraph() { return G; }
	
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TriangleFace> faces;
	std::vector<TriangleFace> refine_faces;
	std::vector<ColorVertex> colorvertices;
	MeshGraph *G;
	void printvert() {
		for (int i = 0; i < vertices.size(); i++) {
			printf("vertex[%d]:(%.2f,%.2f,%.2f)\n", i, vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
		}
	}
	void printcolorvert() {
		for (int i = 0; i < vertices.size(); i++) {
			printf("vertex[%d]:Pos(%.4f,%.4f,%.4f),Col(%.4f,%.4f,%.4f)\n", i, colorvertices[i].Position.x, colorvertices[i].Position.y, colorvertices[i].Position.z, colorvertices[i].Color.x, colorvertices[i].Color.y, colorvertices[i].Color.z);
		}
	}
};

