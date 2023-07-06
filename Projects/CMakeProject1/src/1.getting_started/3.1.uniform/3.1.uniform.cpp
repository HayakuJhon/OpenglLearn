#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/shader_s.h>
#include <glm/glm.hpp>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3.3.uniform", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	float vertices[] = {
		0.0f,0.5f,0.0f,
		0.5f,0.0f,0.0f,
		-0.5f,0.0f,0.0f
	};

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Fail to get OpenGL API address" << std::endl;
		return -1;
	}

	Shader shader("3.1.shader.vs", "3.1.shader.fs");

	
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int location = glGetUniformLocation(shader.ID, "aColor");

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		shader.use();
		glBindVertexArray(VAO);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		double time = glfwGetTime();
		float r = glm::cos(time) / 2.0 + 0.5;
		float g = glm::sin(time) / 2.0 + 0.5;
		float b = 0.0f;
		glm::vec4 color = glm::vec4(r, g, b, 1.0f);
		glUniform4fv(location, 1, &color[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebufferSizeCallback(GLFWwindow* window,int width,int height) {
	glViewport(0, 0, width, height);
}