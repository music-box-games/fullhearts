#version 460 core

in vec2 position;
in vec3 color;

uniform float u_alpha;

out vec4 Color;

void main()
{
  Color = vec4(color, u_alpha);
  gl_Position = vec4(position, 0.0, 1.0);
}