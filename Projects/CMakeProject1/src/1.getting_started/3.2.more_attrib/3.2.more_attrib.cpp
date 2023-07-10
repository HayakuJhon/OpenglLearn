#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/shader_s.h>
#include <glm/glm.hpp>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

void inputPress(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3.2.more_attrib°¡", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create window" << std::endl;
		scanf("a");
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Fail to get OpenGL API address" << std::endl;
		scanf("a");
		return -1;
	}

	float vertices[] = {
		0.0,0.5f,0.0f, 1.0f,0.0f,0.0f,
		0.5f,0.0f,0.0f,0.0f,1.0f,0.0f,
		-0.5f,0.0f,0.0f,0.0f,0.0f,1.0f
	};

	/*float offset[] = {
		0.5f,0.5f,0.0f
	};*/
	glm::vec3 offset = glm::vec3(0.5f, 0.5f, 0.0f);

	Shader shader("3.2.shader.vs", "3.2.shader.fs");

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int aPosLocation = glGetAttribLocation(shader.ID, "aPos");
	glVertexAttribPointer(/*0*/aPosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	unsigned int aColorLocation = glGetAttribLocation(shader.ID, "aColor");
	glVertexAttribPointer(/*1*/aColorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		inputPress(window);
		shader.use();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		double time = glfwGetTime();
		float x = glm::sin(time) / 2;
		float y = glm::cos(time) * 3 / 4 - 0.25f;
		offset.x = x;
		offset.y = y;
		shader.setVec3("offset", offset);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();

	return 0;
}

void inputPress(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);
	}
}