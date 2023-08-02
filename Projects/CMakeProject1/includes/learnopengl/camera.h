#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

glm::mat4 getLookAtMatrix(glm::vec3 position, glm::vec3 center, glm::vec3 up);

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		//return glm::lookAt(Position, Position + Front, Up);
		return getLookAtMatrix(Position, Position + Front, Up);
	}

	void ProcessKeyboard(Camera_Movement direction,float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD) {
			Position += Front * velocity;
		}
		if (direction == BACKWARD) {
			Position -= Front * velocity;
		}
		if (direction == LEFT) {
			Position -= Right * velocity;
		}
		if (direction == RIGHT) {
			Position += Right * velocity;
		}
		if (direction == UP) {
			Position += Up * velocity;
		}
		if (direction == DOWN) {
			Position -= Up * velocity;
		}
	}

	void ProcessMouseMovement(float offsetX, float offsetY, bool constrainPitch = true) {
		offsetX *= MouseSensitivity;
		offsetY *= MouseSensitivity;

		Yaw += offsetX;
		Pitch += offsetY;

		if (constrainPitch) {
			if (Pitch >= 89.0f) {
				Pitch = 89.0f;
			}
			else if (Pitch <= -89.0f) {
				Pitch = -89.0f;
			}
		}
		updateCameraVectors();
	}

	void ProcessMouseScroll(float offsetY) {
		Zoom -= offsetY;
		/*if (Zoom < 1.0f) {
			Zoom = 1.0f;
		}
		else if (Zoom > 45.0f) {
			Zoom = 45.0f;
		}*/
	}

private:
	void updateCameraVectors() {
		glm::vec3 front;
		front.x = glm::sin(glm::radians(Yaw));
		front.y = glm::sin(glm::radians(Pitch));
		front.z = -glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

//推到公式：https://zhuanlan.zhihu.com/p/552252893
// ( 1 0 0 )                    ( ax bx cx )
// ( 0 1 0 ) = MatrixRotation * ( ay by cy )
// ( 0 0 -1)                    ( az bz cz )
//通过旋转矩阵将摄像机的三个基向量变换到标准坐标系
glm::mat4 getLookAtMatrix(glm::vec3 position, glm::vec3 center, glm::vec3 up) {
	//摄像机的前向量
	glm::vec3 zaxis = glm::normalize(center - position);	//摄像机的坐标系z轴基向量
	glm::vec3 xaxis = glm::normalize(glm::cross(zaxis, up));
	glm::vec3 yaxis = glm::normalize(glm::cross(xaxis, zaxis));
	glm::mat4 translation(1.0f);
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;
	glm::mat4 rotation(1.0f);
	rotation[0][0] = xaxis.x;	//第一列第一行
	rotation[1][0] = xaxis.y;	//第二列第一行
	rotation[2][0] = xaxis.z;
	rotation[0][1] = up.x;		//第一列第二行
	rotation[1][1] = up.y;
	rotation[2][1] = up.z;
	rotation[0][2] = -zaxis.x;
	rotation[1][2] = -zaxis.y;
	rotation[2][2] = -zaxis.z;

	return rotation * translation;
}
#endif