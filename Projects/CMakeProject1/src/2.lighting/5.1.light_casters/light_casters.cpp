#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/camera.h>
#include <learnopengl/inpututils.h>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <learnopengl/utils.h>

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 800;

void cursorPosCallback(GLFWwindow* window, double posX, double posY);
void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);
void showMyImGui();

//glm::vec2 lastPos(0.0f, 0.0f);
//bool isFirst = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);
glm::vec4 lightAmbient(0.1f, 0.1f, 0.1f, 1.0f);
glm::vec4 lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 lightSpecular(1.0f, 1.0f, 1.0f, 1.0);
float Shininess = 128.0f;
float constant = 1.0f;
float linear = 0.09f;
float quadratic = 0.032f;
glm::vec4 spotColor(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 spotDir(0.0f, 0.0f, -1.0f);
float spotInnerDot = 0.91f;
float spotOuterDot = 0.82f;

bool* p_open;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1.colors", NULL, NULL);
	if (window == NULL) {
		std::cout << "fail to create window" << std::endl;
		scanf("c");
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, InputUtils::frameBufferSizeCallback);
	glfwSetMouseButtonCallback(window, InputUtils::mouseButtonCallback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, scrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "fail to get opengl api address" << std::endl;
		glfwTerminate();
		scanf("c");
		return -1;
	}

	//imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiIO& io1 = io;
	std::cout << &io << "," << &io1 << std::endl;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_DEPTH_TEST);
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// positions all containers
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

	Shader lightingShader("5.1.light_casters.vs", "5.1.light_casters.fs");
	Shader lightCubeShader("5.1.light_cube.vs", "5.1.light_cube.fs");

	unsigned int VBO, VAO, lightVAO;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//textures
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture1 = Utils::loadTexture("resources/textures/container2.png");
	unsigned int texture2 = Utils::loadTexture("resources/textures/container2_specular.png");
	unsigned int texture3 = Utils::loadTexture("resources/textures/matrix.jpg");

	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);
	lightingShader.setInt("material.emission", 2);

	while (!glfwWindowShouldClose(window))
	{
		InputUtils::inputProcess(window, camera, lightPos);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		showMyImGui();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw cubes
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);
		//point light
		lightingShader.setVec3("pointLight.lightPos", lightPos);
		lightingShader.setVec4("pointLight.ambient", lightAmbient);
		lightingShader.setVec4("pointLight.diffuse", lightDiffuse);
		lightingShader.setVec4("pointLight.specular", lightSpecular);
		lightingShader.setFloat("pointLight.constant", constant);
		lightingShader.setFloat("pointLight.linear", linear);
		lightingShader.setFloat("pointLight.quadratic", quadratic);
		
		//direction light
		lightingShader.setVec3("dirLight.lightDir", lightDir);
		lightingShader.setVec4("dirLight.ambient", lightAmbient);
		lightingShader.setVec4("dirLight.diffuse", lightDiffuse);
		lightingShader.setVec4("dirLight.specular", lightSpecular);

		//spot light
		lightingShader.setVec3("spotLight.position", camera.Position);
		lightingShader.setVec3("spotLight.spotDir", camera.Front);
		lightingShader.setVec4("spotLight.lightColor", spotColor);
		lightingShader.setFloat("spotLight.spotInnerDot", spotInnerDot);
		lightingShader.setFloat("spotLight.spotOuterDot", spotOuterDot);

		lightingShader.setFloat("material.shininess", 0.4 * Shininess);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture3);
		for (int i = 0; i < Utils::ArrayLength(cubePositions); i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			glm::mat3 normalMat(model);
			normalMat = glm::transpose(glm::inverse(normalMat));
			lightingShader.setMat3("normalMat", normalMat);
			lightingShader.setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//draw light cube
		lightCubeShader.use();
		glBindVertexArray(lightVAO);
		glm::mat4 model(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.setMat4("model", model);
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setVec4("lightColor", lightDiffuse);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glfwTerminate();

	return 0;
}


void cursorPosCallback(GLFWwindow* window, double posX, double posY) {
	InputUtils::cursorPosCallback(window, camera, posX, posY);
}

void scrollCallback(GLFWwindow* window, double offsetX, double offsetY) {
	InputUtils::scrollCallback(window, &camera, offsetX, offsetY);
}

void showMyImGui() {
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("parameter", p_open)) {
		ImGui::End();
		return;
	}
	ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
	ImGui::Spacing();
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);


	//if (ImGui::TreeNode("colors")) {
	static ImVec4 ambient = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	static ImVec4 diffuse = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	static ImVec4 specular = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	static ImVec4 spot_Color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	static float lightDirection[] = { -0.2f, -1.0f, -0.3f };
	static float pointContants[] = { 1.0f ,0.09f ,0.032f };
	static float cutOff[] = { 0.91f,0.82f };
	ImGui::ColorEdit4("ambient", (float*)&ambient, ImGuiColorEditFlags_Float);
	Utils::ImVecToGlmVec(ambient, lightAmbient);
	ImGui::ColorEdit4("diffuse", (float*)&diffuse, ImGuiColorEditFlags_Float);
	Utils::ImVecToGlmVec(diffuse, lightDiffuse);
	ImGui::ColorEdit4("specular", (float*)&specular, ImGuiColorEditFlags_Float);
	Utils::ImVecToGlmVec(specular, lightSpecular);
	ImGui::DragFloat3("lightDir", lightDirection, 0.01f, -1.0f, 1.0f);
	lightDir.x = lightDirection[0];
	lightDir.y = lightDirection[1];
	lightDir.z = lightDirection[2];
	ImGui::DragFloat3("constants", pointContants, 0.001f, -1.0f, 1.0f);
	constant = pointContants[0];
	linear = pointContants[1];
	quadratic = pointContants[2];
	ImGui::ColorEdit4("spotColor", (float*)&spot_Color);
	Utils::ImVecToGlmVec(spot_Color, spotColor);
	ImGui::DragFloat2("cutoff", cutOff, 0.001f, 0.0f, 1.0f);
	spotInnerDot = cutOff[0];
	spotOuterDot = cutOff[1];
	//	ImGui::TreePop();
	//}

	ImGui::PopItemWidth();
	ImGui::End();
}