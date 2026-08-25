layout(std140, binding = 0) uniform camera {
	mat4 view;
	vec3 cPos;
    vec2 mPos;
	vec2 wSize;
};