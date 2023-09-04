#include <glm/glm.hpp>

class PointLight
{
public:
	glm::vec3 Position;
	float ConstantArg;
	float LinearArg;
	float QuadraticArg;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	glm::vec4 Specular;
	PointLight(glm::vec3 position,float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f, glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
		Position = position;
		ConstantArg = constant;
		LinearArg = linear;
		QuadraticArg = quadratic;
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
	}

private:

};

class DirectionLight
{
public:
	glm::vec3 Direction;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	glm::vec4 Specular;
	DirectionLight(glm::vec3 direction, glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		, glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
		Direction = direction;
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
	}

private:

};

class SpotLight
{
public:
	glm::vec3 Position;
	glm::vec3 Direction;
	float CutOff;
	float OuterCutOff;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	glm::vec4 Specular;
	
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant = 1.0f, glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		, glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
		Position = position;
		Direction = direction;
		CutOff = cutOff;
		OuterCutOff = outerCutOff;
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
	}

private:

};