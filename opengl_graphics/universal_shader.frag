#version 450
#include "UBO_camera.glsl"
#include "SBO_feedback.glsl"

out vec4 outColor;

in vec3 pos;
in vec3 norm;
in vec4 color;
in vec2 tex;
in flat uint data;
in flat uint id;
in vec4 glPos;

layout(binding = 0) uniform sampler2D texture0;
layout(binding = 1) uniform sampler2D texture1;

void main(){
	if((data & 64) == 64) {
		outColor = texture(texture0, tex);
		outColor *= color;
	}
	else if((data & 32) == 32) {
		outColor = texture(texture1, tex);
		outColor *= color;
	}
	else {
		outColor = color;
	}
	if(gl_FragCoord.x < mPos.x + 1 && gl_FragCoord.x > mPos.x - 1 && gl_FragCoord.y < mPos.y + 1 && gl_FragCoord.y > mPos.y - 1 && gl_FragDepth < fb_depth){
		fb_depth = gl_FragDepth;
		fb_id = id;
	}
}