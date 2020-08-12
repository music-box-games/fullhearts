#version 330 core

in vec2 position;
in vec3 color;

uniform float alpha;

out vec4 aColor;

void main()
{
  aColor = vec4(color, alpha);
  gl_Position = vec4(position, 0.0, 1.0);
}