#version 330 core

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 transform;

void main()
{
  Color = color;
  Texcoord = texcoord;
  gl_Position = transform * vec4(position, 0.0, 1.0);
}