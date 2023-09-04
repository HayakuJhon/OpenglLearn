#include <glm/glm.hpp>
#include <stb_image.h>
#include <iostream>

class Material
{
public:
	float Shininess;
	unsigned char* diffuse;
	unsigned char* specular;
	unsigned char* emission;
	Material(float shininess) {
		Shininess = shininess;
	}
	~Material();

private:
	
};
Material::~Material()
{
	stbi_image_free(diffuse);
	stbi_image_free(specular);
	stbi_image_free(emission);
	std::cout << "����Material" << std::endl;
}
