//#version 410 core

vec3 computeLightVector(vec3 lightPosition, vec3 fragmentPosition)
{
    return lightPosition - fragmentPosition;
}

float computeDiffuseLighting(vec3 lightVector, vec3 fragNormal)
{
    return max(dot(normalize(lightVector), fragNormal), 0.0);
}

float computeLightAttenuation(vec3 lightVector, const float maxLightDistance)
{
    return min(max(maxLightDistance - length(lightVector), 0), maxLightDistance) / maxLightDistance;
}

vec3 computeLightFactor(const vec3 ambientStrength,
                         const float diffuseStrength,
                         const float lightAttenuation)
{
    return (ambientStrength + diffuseStrength) * lightAttenuation;
}
