#version 460 core
out vec4 fragColor;
in vec2 uvCoord;
uniform sampler2D texTarget;
uniform vec3 color;
in vec3 vertColor;

void main() {
				fragColor = vec4(vertColor * color, 1) * texture(texTarget, uvCoord);
}