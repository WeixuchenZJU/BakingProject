#include "Shader.h"
#include "GLCanvas.h"
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "OutputTriData.h"
extern bool DrawColorScene;
bool DoBaking =0;
void Precompute();
const char *OutTriRoot = "../BakingData/";
int main() {
	printf("%.4f,%.4f,%.4f\n", scenemanager::sceneCam[scenemanager::sceneindex].pos.x, scenemanager::sceneCam[scenemanager::sceneindex].pos.y, scenemanager::sceneCam[scenemanager::sceneindex].pos.z);


	if (!DoBaking) {
		GLCanvas *canvas = new GLCanvas();
		canvas->Initialize(1024, 768);
		Shader *ourShader;
		if (DrawColorScene) {
			ourShader = new Shader("./Shaders/colorshader.vs", "./Shaders/colorshader.fs");
			canvas->LoadColorScene(scenemanager::outputscenefile[scenemanager::sceneindex]);
		}
		else {
			//Simple diffuse light shader
			//ourShader = new Shader("./Shaders/simpleshader.vs", "./Shaders/simpleshader.fs");
			//Diffuse texture shader
			//ourShader = new Shader("./Shaders/diffuseshader.vs", "./Shaders/diffuseshader.fs");
			ourShader = new Shader("./Shaders/VertexComputeShader.vs", "./Shaders/VertexComputeShader.fs");
			canvas->LoadScene(scenemanager::scenefile[scenemanager::sceneindex]);
			//canvas->LoadScene("../Models/test.obj");
		}

		//canvas->SetCamera(camera);
		canvas->SetShader(ourShader);
		//

		canvas->Render();
		canvas->Quit();
		OutputTriData out(OutTriRoot,canvas->GetScene());
	}
	else {
		Precompute();
	}
	
	return 0;
}
void Precompute()
{
	//Read obj file
	Mesh *mesh = new Mesh(scenemanager::scenefile[scenemanager::sceneindex]);
	printf("Vertex:%d Faces:%d\n", mesh->GetVertexNum(),mesh->GetFacesNum());
	//mesh->PrintGraph();
	mesh->TessFace();
	//mesh->PrintGraph();
	mesh->OutPutOBJFile(scenemanager::outrefinescenefile[scenemanager::sceneindex]);
	/*std::vector<int> testvec;
	testvec.push_back(1);
	testvec.push_back(2);
	testvec.push_back(3);
	testvec.push_back(4);
	int a = testvec.at(3);
	printf("%d\n", a);
	testvec.pop_back();
	testvec.push_back(5);
	testvec.push_back(6);

	testvec.pop_back();
	testvec.pop_back();*/
	////Percompute Color per vertex
	//mesh->ComputeColorVertices();
	////Write cobj file
	//mesh->OutPutColorFile(scenemanager::outputscenefile[scenemanager::sceneindex]);
	//return 0;
}
