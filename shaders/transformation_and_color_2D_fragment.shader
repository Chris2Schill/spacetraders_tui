//#version 410 core

in vec3 thePosition;
in vec3 theNormal;
in vec3 theColor;

out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_LightPosition;
uniform mat4 u_MV;
uniform vec3 u_AmbientLight;

void main()
{
    vec3 lightColor = vec3(0.7, 0.7, 0.7);

    //vec3 normal = vec3(u_MV * vec4(theNormal, 0));

    vec3 lightVector = u_LightPosition - thePosition;
    float diff = max(dot(normalize(lightVector), theNormal), 0.0);
    float maxLightDistance = 10;
    float lightAttenuation = min(max(maxLightDistance - length(lightVector), 0), maxLightDistance) / maxLightDistance;

    vec3 ambient = u_AmbientLight * lightColor;
    vec3 diffuse = diff * lightColor;
    

    vec4 result = vec4((ambient + diffuse)*lightAttenuation,1) * u_Color;
    color = result;
//    color = vec4(1,1,1, 1.0) * brightness * u_Color;
}