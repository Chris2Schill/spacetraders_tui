//#version 410 core
// This shader file uses symbols from lighting_fragment.shader

in vec3 thePosition;
in vec3 theNormal;
in vec3 theColor;

out vec4 color;

uniform vec3 u_LightPosition;
uniform mat4 u_MV;
uniform vec3 u_AmbientLight;

void main()
{
    vec3 lightColor = vec3(0.7, 0.7, 0.7);
    float maxLightDistance = 10;

    vec3 lightVector = u_LightPosition - thePosition;
    vec3 lightFactor = computeLightFactor(u_AmbientLight,
                                          computeDiffuseLighting(lightVector, theNormal),
                                          computeLightAttenuation(lightVector, maxLightDistance));
                 
    vec3 result = lightFactor * lightColor * theColor;
    color = vec4(result, 1.0);
}