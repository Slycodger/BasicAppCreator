#version 460 core
out vec4 fragColor;
in vec2 uvCoord;
uniform sampler2D texTarget;

void main() {
				if (texture(texTarget, vec2(uvCoord.x, uvCoord.y)).r > 0)
								fragColor = vec4(1);
				else
								fragColor = vec4(0);
}