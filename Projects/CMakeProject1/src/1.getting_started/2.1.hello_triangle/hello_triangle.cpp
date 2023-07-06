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
		std::cout << "创建窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		return -1;
	}

	//std::ofstream ct; ct.open("bla.txt"); ct << "klaf";	//用来确认运行目录，会在运行目录生成一个bla.txt文件

	/*const std::string vsFile = "shader.vs";
	const std::string fsFile = "shader.fs";*/
	//Shader shader(vsFile.c_str(), fsFile.c_str());
	Shader shader("1.1.shader.vs", "1.1.shader.fs");
	shader.use();

	//OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西。
	unsigned int VBO, VAO;//vertex buffer object
	glGenVertexArrays(1, &VAO);	//定义VAO（顶点数组对象）
	glGenBuffers(1,&VBO);	//定义VBO（顶点缓冲对象）
	glBindVertexArray(VAO);	//先绑定VAO，再绑定VBO和配置VBO的读取规则等
	std::cout << VBO << "," << &VBO << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//绑定VBO到目标GL_ARRAY_BUFFER类型上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//将顶点数据输入到当前绑定在GL_ARRAY_BUFFER上的VBO上

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//配置读取VBO顶点数据的规则
	glEnableVertexAttribArray(0);	//启用当前绑定的VAO，默认所有的都是禁用的

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//解绑当前绑定在GL_ARRAY_BUFFER上的VBO

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);	//绑定当前需要用到的VAO，当只有一个的时候可以不用再次绑定
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);	//交换屏幕渲染buffer和GPU内存中的buffer
		glfwPollEvents();	//抛出窗口事件
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