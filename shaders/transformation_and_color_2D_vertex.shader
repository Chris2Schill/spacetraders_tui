 //#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

//out vec3 theColor;
out vec3 thePosition;
out vec3 theNormal;
out vec3 theColor;

uniform mat4 u_MVP;
uniform mat4 u_MV;
uniform mat4 u_Rotation;
uniform vec3 u_AmbientLight;


void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);

    // TODO: Move the calculation of the normal matrix to the CPU because its expensive here
    mat4 normalMatrix = transpose(inverse(u_MV));
    vec3 normal = normalize(vec3(normalMatrix * vec4(vertexNormal, 0)));

    thePosition = vec3(u_MV * vec4(position, 1));
    theNormal = normal;
    theColor = vertexColor;
}
