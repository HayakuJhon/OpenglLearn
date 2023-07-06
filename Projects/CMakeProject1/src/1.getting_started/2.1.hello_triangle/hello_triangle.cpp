#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 600;
const unsigned int SCREEN_HEIGHT = 600;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hello_triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "��������ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		return -1;
	}

	//std::ofstream ct; ct.open("bla.txt"); ct << "klaf";	//����ȷ������Ŀ¼����������Ŀ¼����һ��bla.txt�ļ�

	/*const std::string vsFile = "shader.vs";
	const std::string fsFile = "shader.fs";*/
	//Shader shader(vsFile.c_str(), fsFile.c_str());
	Shader shader("1.1.shader.vs", "1.1.shader.fs");
	shader.use();

	//OpenGL�ĺ���ģʽҪ������ʹ��VAO��������֪������δ������ǵĶ������롣������ǰ�VAOʧ�ܣ�OpenGL��ܾ������κζ�����
	unsigned int VBO, VAO;//vertex buffer object
	glGenVertexArrays(1, &VAO);	//����VAO�������������
	glGenBuffers(1,&VBO);	//����VBO�����㻺�����
	glBindVertexArray(VAO);	//�Ȱ�VAO���ٰ�VBO������VBO�Ķ�ȡ�����
	std::cout << VBO << "," << &VBO << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//��VBO��Ŀ��GL_ARRAY_BUFFER������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//�������������뵽��ǰ����GL_ARRAY_BUFFER�ϵ�VBO��

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//���ö�ȡVBO�������ݵĹ���
	glEnableVertexAttribArray(0);	//���õ�ǰ�󶨵�VAO��Ĭ�����еĶ��ǽ��õ�

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//���ǰ����GL_ARRAY_BUFFER�ϵ�VBO

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);	//�󶨵�ǰ��Ҫ�õ���VAO����ֻ��һ����ʱ����Բ����ٴΰ�
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);	//������Ļ��Ⱦbuffer��GPU�ڴ��е�buffer
		glfwPollEvents();	//�׳������¼�
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}