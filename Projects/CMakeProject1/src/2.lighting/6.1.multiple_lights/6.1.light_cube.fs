#version 330 core
out vec4 FragColor;
in vec4 aColor;

void main()
{
    FragColor = aColor;//vec4(1.0); // set all 4 vector values to 1.0
}