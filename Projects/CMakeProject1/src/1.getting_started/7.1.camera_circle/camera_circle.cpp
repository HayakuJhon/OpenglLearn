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

template <class T>
int ArrayLength(const T& arr) {
	return sizeof(arr) / sizeof(arr[0]);
}

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "fail to get opengl api address" << std::endl;
		glfwTerminate();
		scanf("c");
		return -1;
	}

	//float vertices[] = {
	//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	// 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	//};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f
	};
	unsigned int indices[] = {
		//front
		0, 1, 3, // first triangle
		0, 3, 2, // second triangle
		//behind
		4, 7, 5,
		4, 6, 7,
		//left
		4, 0, 2,
		4, 2, 6,
		//right
		5, 1, 3,
		5, 3, 7,
		//up
		2, 6, 7,
		2, 7, 3,
		//bottom
		0, 5, 1,
		0, 4, 5
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

	Shader shader("7.1.shader.vs", "7.1.shader.fs");

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
	data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &channel,0);
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
	data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &channel,0);
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
		for (int i = 0; i < ArrayLength(cubePositions); i++)
		{
			glm::mat4 model(1.0);
			model = glm::translate(model, cubePositions[i]);
			if (i % 3 == 0) {
				
				model = glm::rotate(model, time*glm::radians(50.0f)+20.0f*i, glm::vec3(1.0, 1.0, 0.0));
			}

			glm::mat4 view(1.0);
			view = glm::lookAt(glm::vec3(radius * glm::cos(glm::radians(time * 45.0f - 90.0f)), 0.0, radius * glm::sin(glm::radians(time * 45.0f - 90.0f))), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

			glm::mat4 projection(1.0);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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
}