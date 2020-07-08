#version 460 core
in vec2 position;
uniform vec4 color;
out vec4 Color;

uniform float c_alpha;

void main()
{
  Color = color;
  Color.a = c_alpha;
  gl_Position = vec4(position, 1.0, 1.0);
}