#version 430 core

in vec2 position; // Vlocal
in vec3 color; // texel color
in vec2 texcoord; // texel coordinates

out vec3 Color;
out vec2 Texcoord;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  Color = color;
  Texcoord = texcoord;
  gl_Position = transform * vec4(position, 0.0, 1.0);
  // gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}