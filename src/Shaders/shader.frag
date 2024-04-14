#version 330

in vec4 vCol;
out vec4 color;
uniform vec4 varColor;

void main()
{
   color = vCol + varColor;
}