#pragma once
#include "Group.h"
#include "Shader.h"
#include "Material.h"
#include <vector>
#include <string>
class Scene
{
public:
	Scene();
	~Scene();
	void Draw(Shader* shader) {
		for (int i = 0; i < mesh_group.size(); i++) {
			mesh_group[i].Draw(shader);
			//printf("Group %d is Draw\n", i);
		}
	}
	void AddToGroup(Group &g) {
		mesh_group.push_back(g);
	}
	//加载材质列表
	void LoadMTLList(std::string mtlfilepath);
	//查找材质索引
	int FindMTLIndex(char* mtlname) { 
		//printf("%s\n", mtlname);
		int index = -1;
		for (int i = 0; i < material_list.size(); i++) {
			if (strcmp(mtlname, material_list[i].GetName()) == 0) {
				index = i;
				break;
			}
		}
		return index;
	}
	void SetUpScene() {
		for (int i = 0; i < mesh_group.size(); i++) {
			mesh_group[i].Set(material_list);
			//printf("Group %d is SET\n", i);
		}
	}
	void PrintGroup() {
		for (int i = 0; i < mesh_group.size(); i++) {
			printf("Group %d: index=%d\n", i, mesh_group[i].GetMTLIndex());
		}
	}
	std::vector<Group>& GetGroup() { return mesh_group; }
private:
	std::vector<Group> mesh_group;//曲面组
	std::vector<Material> material_list;//材质列表
};

