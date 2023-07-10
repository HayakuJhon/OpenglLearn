#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
uniform vec3 offset;

void main(){
	gl_Position = vec4(aPos.xyz + offset,1);
	//vertexColor = vec4(aColor.rgb,1);
	vertexColor = gl_Position;
}