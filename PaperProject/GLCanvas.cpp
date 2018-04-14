

#include "GLCanvas.h"
#include "image.h"

#include <iostream>

double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;
double lastTime = 0.0f;
double lastX = 400.0f;
double lastY = 400.0f;
bool firstLeftMouse = true;
bool firstRightMouse = true;
bool DrawColorScene = 0;

int SCR_WIDTH=1920;
int SCR_HEIGHT=1080;
Camera camera(scenemanager::sceneCam[scenemanager::sceneindex].pos, scenemanager::sceneCam[scenemanager::sceneindex].dir, scenemanager::sceneCam[scenemanager::sceneindex].yaw, scenemanager::sceneCam[scenemanager::sceneindex].pitch);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window, int key, int scnacode, int action, int bit) {
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		printf("Snapshot!\n");
		GLubyte *bits;//定义指向位图数据的指针
		bits = (unsigned char *)malloc(SCR_WIDTH*SCR_HEIGHT * 3);//为位图分配内存空间并赋值给bits
		Image* img = new Image(SCR_WIDTH, SCR_HEIGHT);
		glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, bits);
		for (int y = 0; y < SCR_HEIGHT; y++) {
			for (int x = 0; x < SCR_WIDTH; x++) {
				int index = (y*SCR_WIDTH + x) * 3;
				//printf("Pixel<%d,%d> %d,%d,%d\n", x, y, bits[index], bits[index + 1], bits[index + 2]);
				img->SetPixel(x, y, glm::vec3((int)bits[index] * 1.0f / 255.0f, (int)bits[index + 1] * 1.0f / 255.0f, (int)bits[index + 2] * 1.0f / 255.0f));
			}
		}
		img->SaveTGA("Snapshot.tga");
		delete(img);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{

		camera.PrintCameraAttributes();
	}
}

GLCanvas::GLCanvas()
{
	m_scene = new Scene();
}


GLCanvas::~GLCanvas()
{
}
void GLCanvas::Initialize(int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	windowtitle = "OpenGLViewer";
	window= glfwCreateWindow(width,height, windowtitle.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	//Set up Callback Functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyboard_callback);

	//glfwSetMouseButtonCallback(window, mouse_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	lightpos = scenemanager::lightpos[0];
}
void GLCanvas::Render()
{
	while (!glfwWindowShouldClose(window))
	{
		
		ComputeFPS();
		processInput(window);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shader->use();
		//Set Light
		m_shader->setVec3("lightPos",lightpos);
		m_shader->setVec3("lightColor", scenemanager::lightcolor[0]);
		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		m_shader->setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		m_shader->setMat4("view", view);
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;
		//model=glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_shader->setMat4("model", model);
		m_scene->Draw(m_shader);
		//
		

		//glBindVertexArray(VAO);
		//
		//if (DrawColorScene) {
		//	glDrawArrays(GL_TRIANGLES, 0, colorvertices.size());
		//}
		//else {
		//	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		//}
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void GLCanvas::Quit() 
{
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/
	//glDeleteBuffers(1, &EBO);
	glfwTerminate();
}
void GLCanvas::LoadScene(const char* file) {
	
	ModelFileLoader scene_loader;
	scene_loader.OBJLoader(file,m_scene);
	m_scene->PrintGroup();
	m_scene->SetUpScene();
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//glEnableVertexAttribArray(0);
	//// vertex normals
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); 
	//// uv Coordinate
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//glBindVertexArray(0);
}
void GLCanvas::LoadColorScene(const char* file) {
	//ModelFileLoader scene_loader;
	//scene_loader.COBJLoader(file, colorvertices);
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, colorvertices.size() * sizeof(ColorVertex), &colorvertices[0], GL_STATIC_DRAW);
	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	//glEnableVertexAttribArray(0);
	//// vertex colors
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, Color));
	//glBindVertexArray(0);
}
void GLCanvas::ComputeFPS() {
	// per-frame time logic
	// --------------------
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	double FPS = 1.0f / deltaTime;
	char FPSARRAY[100] = "";
	sprintf(FPSARRAY, "OpenglViewer FPS:%.2f", FPS);
	windowtitle = FPSARRAY;
	if(currentFrame-lastTime>1.0f){
		glfwSetWindowTitle(window, windowtitle.c_str());
		lastTime = currentFrame;
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void GLCanvas::processInput(GLFWwindow *window)
{
	//Keyboard Input
	//CameraControl
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWNWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		//Mouse Input
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		//Left Button control view direction
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (firstLeftMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstLeftMouse = false;
			}

			double xoffset = xpos - lastX;
			double yoffset = lastY - ypos; 
			//std::cout << " " << xpos << " " << ypos << " " << xoffset << " " << yoffset << std::endl;
			camera.ProcessMouseMovement(xoffset, yoffset);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
			firstLeftMouse = true;
		}
		//Right Button Control near/far
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (firstRightMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstRightMouse = false;
			}
			double xoffset = xpos - lastX;
			double yoffset = lastY - ypos;
			double offset = fabs(xoffset) > fabs(yoffset) ? xoffset : yoffset;
			camera.ProcessRightButtonPressed(offset);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
			firstRightMouse = true;
		}
	}

	//Light
}
