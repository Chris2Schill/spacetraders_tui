 //#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 theColor;

uniform mat4 u_Transformation;

void main()
{
    gl_Position = u_Transformation * vec4(position, 1.0);
    theColor = vertexColor;
}
