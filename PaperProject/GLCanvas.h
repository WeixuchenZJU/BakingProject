#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "ModelFileLoader.h"
#include <vector>
#include <string>
#include "SceneFileManager.h"
#include "Scene.h"
class GLCanvas
{
public:
	GLCanvas();
	~GLCanvas();
	void Initialize(int width,int height);
	void Render();
	void Quit();
	void SetShader(Shader* shader) { this->m_shader = shader; }
	//void SetCamera(Camera* camera) { GLCanvas::m_camera = camera; }
	void LoadScene(const char* file);
	Scene* GetScene() { return m_scene; }
	void LoadColorScene(const char* file);
	void processInput(GLFWwindow *window);
	//static Camera* GetCamera() { return m_camera; }
	//static Camera* m_camera;
	glm::vec3 lightpos;
private:
	void ComputeFPS();
//	GLuint VBO, VAO, EBO;
	//std::vector<Vertex> vertices;
	//std::vector<ColorVertex> colorvertices;
	//std::vector<unsigned int> indices;
	GLFWwindow* window;
	std::string windowtitle;
	
	Shader* m_shader;
	Scene* m_scene;
};

