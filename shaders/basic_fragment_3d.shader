//#version 410 core

out vec4 fColor;

//uniform vec2 fPosition;

uniform vec4 u_Color;

float det(vec2 a, vec2 b) { return a.x * b.y - b.x * a.y; }

vec2 closestPointInSegment(vec2 a, vec2 b)
{
    vec2 ba = b - a;
    return a + ba * clamp(-dot(a, ba) / dot(ba, ba), 0.0, 1.0);
}


vec2 get_distance_vector(vec2 b0, vec2 b1, vec2 b2) {

    float a = det(b0, b2), b = 2.0 * det(b1, b0), d = 2.0 * det(b2, b1); // 𝛼,𝛽,𝛿(𝑝)

    if (abs(2.0 * a + b + d) < 1000.0) return closestPointInSegment(b0, b2);

    float f = b * d - a * a; // 𝑓(𝑝)
    vec2 d21 = b2 - b1, d10 = b1 - b0, d20 = b2 - b0;
    vec2 gf = 2.0 * (b * d21 + d * d10 + a * d20);
    gf = vec2(gf.y, -gf.x); // ∇𝑓(𝑝)
    vec2 pp = -f * gf / dot(gf, gf); // 𝑝′
    vec2 d0p = b0 - pp; // 𝑝′ to origin
    float ap = det(d0p, d20), bp = 2.0 * det(d10, d0p); // 𝛼,𝛽(𝑝′)
    // (note that 2*ap+bp+dp=2*a+b+d=4*area(b0,b1,b2))
    float t = clamp((ap + bp) / (2.0 * a + b + d), 0.0, 1.0); // 𝑡̅
    return mix(mix(b0, b1, t), mix(b1, b2, t), t); // 𝑣𝑖= 𝑏(𝑡̅)

}

void main()
{
    vec4 colors[4] = vec4[](
        vec4(1.0, 0.0, 0.0, 1.0),
        vec4(0.0, 1.0, 0.0, 1.0),
        vec4(0.0, 0.0, 1.0, 0.4),
        vec4(0.0, 0.0, 0.0, 1.0)
        );

    fColor = vec4(1.0);

    float radius = 0.2;
    vec2 fPosition = ((gl_FragCoord.xy / 1200) - 0.5) * 2.0;
    //for (int row = 0; row < 2; row++) {
     //   for (int col = 0; col < 2; col++) {
            float dist = distance(fPosition, vec2(0,0));
            //float alpha = step(radius, dist);
            float delta = 0.008;
            float alpha = smoothstep(radius-delta, radius, dist);
            fColor = mix(colors[0 * 2 + 0], fColor, alpha);
      //  }
   // }

    if (fPosition.y > 0)
    {
        //fColor = vec4(1.0,1.0,0.0,0.0);
    }

}
