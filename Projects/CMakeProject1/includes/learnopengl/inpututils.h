#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <learnopengl/camera.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <learnopengl/camera.h>

float static deltaTime = 0.0f;
float static lastTime = 0.0f;
static glm::vec2 lastPos(0.0f);

bool static isPress = false;
bool static isFirst = false;
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
	static void cursorPosCallback(GLFWwindow* window, Camera* camera, double posX, double posY) {
		if (!isPress) {
			isFirst = true;
			return;
		}
		//std::cout << "posX:" << posX << ",posY:" << posY << "lastPos:" << lastPos.x << lastPos.y << std::endl;
		float deltaX = posX - lastPos.x;
		float deltaY = lastPos.y - posY;	//��Ϊ�Ӵ������ԭ�������Ͻǣ����ϻ���ʱY�ǵݼ���
		lastPos.x = (float)posX;
		lastPos.y = (float)posY;
		if (isFirst) {
			isFirst = false;
			return;
		}
		(*camera).ProcessMouseMovement(deltaX, deltaY);
		//std::cout << "x:" << camera.Front.x << ",y:" << camera.Front.y << ",z:" << camera.Front.z << std::endl;
	}

	static void scrollCallback(GLFWwindow* window, Camera* camera, double offsetX, double offsetY) {
		(*camera).ProcessMouseScroll(offsetY);
	}

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			if (!isPress) {
				isPress = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}
		else {
			if (isPress) {
				isPress = false;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
	}
private:
	
};




#endif // !INPUTUTILS_H

