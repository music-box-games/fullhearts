#version 430 core

in vec2 position;
uniform vec4 color;
uniform mat4 transform;

out vec4 Color;

void main()
{
  Color = color;
  gl_Position = transform * vec4(position, 1.0, 1.0);
}