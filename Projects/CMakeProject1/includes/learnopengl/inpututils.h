#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <learnopengl/camera.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

float static deltaTime = 0.0f;
float static lastTime = 0.0f;
class InputUtils
{
public:
	
	static void inputProcess(GLFWwindow* window, Camera* camera, glm::vec3* lightPos) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(RIGHT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(UP, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			(*camera).ProcessKeyboard(DOWN, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			(*lightPos).z -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			(*lightPos).z += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			(*lightPos).x -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			(*lightPos).x += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			(*lightPos).y += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			(*lightPos).y -= 0.1f;
		}

		float time = glfwGetTime();
		deltaTime = time - lastTime;
		lastTime = time;
	}
private:
	
};




#endif // !INPUTUTILS_H

