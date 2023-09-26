/**/

#version 450

layout(location = 0) out vec4 OutColor;

uniform vec3 CamDir;
uniform vec3 CamLoc;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform float Ph;
uniform float Time;
uniform float Trans;

in vec4 DrawColor;
in vec3 DrawPos;
in vec2 DrawTexCoord;
in vec3 DrawNormal;

layout(binding = 0) uniform sampler2D Texture0;
layout(binding = 1) uniform sampler2D Texture1;
uniform bool IsTexture0;

vec3 Shade( vec3 P, vec3 N, vec3 L, vec3 LColor )
{
  vec3 color = vec3(0, 0, 0);
  vec3 V = normalize(P - CamLoc);

  N = faceforward(N, V, N);

  // Ambient
  color = min(Ka, vec3(0.1, 0.1, 0.1));
  
  // Duffuse
  float nl = dot(N, L);
  nl = max(nl, 0.1);
  vec3 diff = LColor * Kd * nl;
  if (IsTexture0)
    diff *= texture(Texture0, DrawTexCoord).bgr;
  color += diff;

  // Specular
  vec3 R = reflect(V, N);
//  color += Ks * min(0.1, pow(dot(L, R), Ph));

   float rl = max(dot(R, L), 0);
   color += rl * LColor * Ks * pow(rl, Ph);

  return color;
}

void main( void )
{
  if (Trans < 1)
    discard;

  OutColor = vec4(texture(Texture0, DrawTexCoord).bgr, 1);

}
