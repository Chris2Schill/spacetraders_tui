//#version 410 core

out vec4 color;
in vec3 theColor;


void main()
{
    color = vec4(theColor, 1.0);
}