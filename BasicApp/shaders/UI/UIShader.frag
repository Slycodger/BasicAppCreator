#version 460 core

uniform sampler2D texTarget;

in vec2 uvCoord;

out vec4 fragColor;

void main() {
		fragColor = texture(texTarget, uvCoord);
}