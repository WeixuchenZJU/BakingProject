#pragma once
#include <glm/glm.hpp>
#include "Light.h"
namespace scenemanager {
	static const char* scenefile[8] = { "../Models/triangle.obj" ,//0
		
	"../Models/cube.obj" ,//1
	"../Models/sphere.obj" ,//2
	"../Models/happybudda_high.obj" ,//3
	"../Models/Sponza/Sponza.obj" ,//4
	"../Models/happybudda_low.obj",//5
		"../Models/Plane.obj" ,//6
	"../Models/Sponza/lion.obj" //7
	};
	static const char* outputscenefile[7] = { "../Models/triangle.cobj" , 
	"../Models/cube.cobj" ,
	"../Models/sphere.cobj" ,
	"../Models/happybudda_high.cobj" ,
	"../Models/Sponza/Sponza.cobj" ,
	"../Models/happybudda_low.cobj",
		"../Models/Plane.cobj" ,//6

	};
	static const char* outrefinescenefile[7] = { "../Models/triangle_r.obj" ,
		"../Models/cube_r.obj" ,
		"../Models/sphere_r.obj" ,
		"../Models/happybudda_high_r.obj" ,
		"../Models/Sponza/Sponza_r.obj" ,
		"../Models/happybudda_low_r.obj",
		"../Models/Plane_r.obj" ,//6

	};
	static int sceneindex =7;
	//Camera Attributes
	static glm::vec3 CAMERA_POS = glm::vec3(1048.30f,172.56f,-35.42f);
	static glm::vec3 CAMERA_DIR = glm::vec3(1.0f,0.0f,0.0f);
	static glm::vec3 CAMERA_HOR = glm::vec3(0.0f, 0.0f,1.0f);

	/*<Pos:939.10 154.18 - 29.81>
		<Direction:1.00 0.03 0.02>
		<Horizon:-0.02 0.00 1.00>
		<Up:-0.03 1.00 - 0.00>
		<Yaw:0.87>
		<Pitch:1.62
		>*/
	//Light Info
	static LightType lighttype = POINTLIGHT;
	static int lightnum = 1;
	static glm::vec3 lightpos[1] = { glm::vec3(1.0f,1.0f,1.0f) };
	static glm::vec3 lightcolor[1] = { glm::vec3(1.0f,0.0f,0.0f) };
}