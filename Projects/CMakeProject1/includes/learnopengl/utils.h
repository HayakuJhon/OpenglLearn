#ifndef UTILS
#define UTILS
#include <imgui.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <learnopengl/filesystem.h>
class Utils
{
public:
	static void ImVecToGlmVec(ImVec4& imVec,glm::vec4& glmVec) {
		glmVec.r = imVec.x;
		glmVec.g = imVec.y;
		glmVec.b = imVec.z;
		glmVec.a = imVec.w;
	}

	static unsigned int loadTexture(const std::string& path) {
		unsigned int textureID;
		glGenTextures(1, &textureID);
		int width, height, channel;
		unsigned char* data;
		data = stbi_load(FileSystem::getPath(path).c_str(), &width, &height, &channel, 0);
		if (data) {
			GLenum format;
			//channel表示颜色的通道
			if (channel == 1) {
				format = GL_RED;
			}
			else if (channel == 3) {
				format = GL_RGB;
			}
			else if (channel == 4) {
				format = GL_RGBA;
			}
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else {
			std::cout << "fail to load texture:" << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}
private:

};
#endif // !UTILS
