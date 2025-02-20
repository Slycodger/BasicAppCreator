#version 460 core

uniform sampler2D texTarget;
uniform float gamma;
uniform float exposure;

in vec2 uvCoord;

out vec4 fragColor;

void main() {
		vec3 hdrColor = texture(texTarget, uvCoord).rgb;

  vec3 mapped = 1 - exp(-hdrColor * exposure);

  mapped = pow(mapped, vec3(1 / gamma));

  fragColor = vec4(mapped, 1);
}