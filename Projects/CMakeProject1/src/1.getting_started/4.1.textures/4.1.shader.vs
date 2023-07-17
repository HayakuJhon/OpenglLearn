#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 vertexCoord;

void main(){
	gl_Position = vec4(aPos.xyz,1.0);
	vertexColor = vec4(aColor.rgb,1.0);
	vertexCoord = aTexCoord;
}