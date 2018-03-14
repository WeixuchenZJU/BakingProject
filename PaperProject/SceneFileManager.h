#pragma once
#include <glm/glm.hpp>
#include "Light.h"
namespace scenemanager {
	static const char* scenefile[7] = { "../Models/triangle.obj" ,//0
		
	"../Models/cube.obj" ,//1
	"../Models/sphere.obj" ,//2
	"../Models/happybudda_high.obj" ,//3
	"../Models/Sponza/Sponza.obj" ,//4
	"../Models/happybudda_low.obj",//5
		"../Models/Plane.obj" ,//6

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
	static int sceneindex =1;
	static glm::vec3 CAMERA_POS = glm::vec3(0.0f, 0.0f, 2.0f);

	//Light Info
	static LightType lighttype = POINTLIGHT;
	static int lightnum = 1;
	static glm::vec3 lightpos[1] = { glm::vec3(1.0f,1.0f,1.0f) };
	static glm::vec3 lightcolor[1] = { glm::vec3(1.0f,0.0f,0.0f) };
}