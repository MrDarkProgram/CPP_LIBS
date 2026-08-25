#version 450
#include "UBO_camera.glsl"

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTex;
layout (location = 4) in uint aData;
layout (location = 5) in uint aID;

out vec3 pos;
out vec3 norm;
out vec4 color;
out vec2 tex;
out flat uint data;
out flat uint id;
out vec4 glPos;

void main() {

	pos = aPos;
	norm = aNorm;
	color = aColor;
	tex = aTex;
	data = aData;
	id = aID;

	if((data & 128) == 128) {
		gl_Position = glPos = vec4(aPos, 1);
	}
	else {
		gl_Position = glPos = view * vec4(aPos, 1);
		if(norm != vec3(0)) {
			vec3 to_player = normalize(cPos - pos);
			float angle = abs(dot(norm, to_player)); // abs(...) => max(..., 0)
			color.rgb *= angle;
		}
	}
}