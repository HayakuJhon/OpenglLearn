#ifndef UTILS
#define UTILS
#include <imgui.h>
#include <glm/glm.hpp>
class Utils
{
public:
	static void ImVecToGlmVec(ImVec4& imVec,glm::vec4& glmVec) {
		glmVec.r = imVec.x;
		glmVec.g = imVec.y;
		glmVec.b = imVec.z;
		glmVec.a = imVec.w;
	}
private:

};
#endif // !UTILS
