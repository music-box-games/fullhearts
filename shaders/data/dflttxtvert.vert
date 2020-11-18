#version 430 core

in vec2 position; // Vlocal
in vec3 color; // color
in vec2 texcoord; // tex coordinates

out vec3 Color;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  Color = color;
  Texcoord = texcoord;
  gl_Position = model * vec4(position, 0.0, 1.0);
}