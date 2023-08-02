#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/shader_s.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 800;

void inputProcess(GLFWwindow* window);
void cursorPosCallback(GLFWwindow* window, double posX, double posY);
void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);

template <class T>
int ArrayLength(const T& arr) {
	return sizeof(arr) / sizeof(arr[0]);
}

glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
float moveSpeed = 1.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;
glm::vec2 lastPos(0.0f, 0.0f);
bool isFirst = true;
float fovy = 45.0f;
float yaw = 0.0f;
float pitch = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "7.1.camera_circle", NULL, NULL);
	if (window == NULL) {
		std::cout << "fail to create window" << std::endl;
		scanf("c");
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, scrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "fail to get opengl api address" << std::endl;
		glfwTerminate();
		scanf("c");
		return -1;
	}

	float vertices[] = {
		//front
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 //bihend
		 -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		  //left
		  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  //right
		   0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		   //up
		   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			//bottom
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	};
	unsigned int indices[] = {
		//front
		0, 1, 3, // first triangle
		0, 3, 2, // second triangle
		//behind
		4, 7, 5,
		4, 6, 7,
		//left
		8, 9, 11,
		8, 11, 10,
		//right
		12, 13, 15,
		12, 15, 14,
		//up
		16, 17, 19,
		16, 19, 18,
		//bottom
		20, 21, 23,
		20, 23, 22
	};

	glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader shader("7.2.shader.vs", "7.2.shader.fs");

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//texture
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture1, texture2;
	int width, height, channel;
	unsigned char* data;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &channel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "fail to load texture1" << std::endl;
		glfwTerminate();
		scanf("c");
		return -1;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &channel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "fail to load texture1" << std::endl;
		glfwTerminate();
		scanf("c");
		return -1;
	}
	stbi_image_free(data);

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);
	glEnable(GL_DEPTH_TEST);

	float radius = 10.0f;
	glm::mat4 view(1.0);
	isFirst = true;

	glm::mat4 projection(1.0);
	

	while (!glfwWindowShouldClose(window))
	{
		inputProcess(window);

		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);
		shader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		float time = glfwGetTime();
		deltaTime = time - lastTime;
		lastTime = time;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		for (int i = 0; i < ArrayLength(cubePositions); i++)
		{
			glm::mat4 model(1.0);
			model = glm::translate(model, cubePositions[i]);
			if (i % 3 == 0) {

				model = glm::rotate(model, time * glm::radians(50.0f) + 20.0f * i, glm::vec3(1.0, 1.0, 0.0));
			}

			projection = glm::perspective(glm::radians(fovy), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

			

			shader.setMat4("model", model);
			shader.setMat4("view", view);
			shader.setMat4("projection", projection);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();

	return 0;
}
void inputProcess(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraFront * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraFront * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed * deltaTime;
	}
}

void cursorPosCallback(GLFWwindow* window, double posX, double posY) {
	std::cout << "posX:" << posX << ",posY:" << posY << "lastPos:" << lastPos.x << lastPos.y << std::endl;
	float deltaX = posX - lastPos.x;
	float deltaY = lastPos.y - posY;	//因为视窗坐标的原点在坐上角，往上滑动时Y是递减的
	lastPos.x = (float)posX;
	lastPos.y = (float)posY;
	if (isFirst) {
		isFirst = false;
		return;
	}
	float sensitivity = 0.05f;
	yaw += deltaX * sensitivity;
	pitch += deltaY * sensitivity;
	if (pitch >= 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch <= -89.0f) {
		pitch = -89.0f;
	}
	//直接sin(x)可以得到方向向量绕Y轴旋转x度之后在XY平面的投影的x分量
	//sin(y)同理得到在YZ平面上的投影的y分量
	//z分量可以通过先投影到YZ屏幕的余弦，用这个余弦投影再投影到XZ屏幕就得到了z分量
	cameraFront.x = glm::sin(glm::radians(yaw));
	cameraFront.y = glm::sin(glm::radians(pitch));
	cameraFront.z = -glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));	//由于右手坐标系，摄像机的方向z分量和坐标系的z分量相反
	cameraFront = glm::normalize(cameraFront);
	std::cout << "x:" << cameraFront.x << ",y:" << cameraFront.y << ",z:" << cameraFront.z << std::endl;
}

void scrollCallback(GLFWwindow* window, double offsetX, double offsetY) {
	fovy -= (float)offsetY;
}