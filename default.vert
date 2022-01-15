#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;
uniform float moveX;
uniform float moveY;
uniform float myColor;

void main()
{
	gl_Position = vec4(aPos.x + moveX, aPos.y - moveY, aPos.z, 1.0);

   color = aColor + myColor;
}
