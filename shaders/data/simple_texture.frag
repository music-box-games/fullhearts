#version 430 core

out vec4 FragColor;
in  vec2 TexCoords;
  
uniform sampler2D framebuffer_attachment;
  
void main()
{
    FragColor = texture(framebuffer_attachment, TexCoords);
} 