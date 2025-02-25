#version 330 core
out vec4 FragColor;
  
uniform float greenColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = vec4(0.0, greenColor, 0.0, 1.0);
} 