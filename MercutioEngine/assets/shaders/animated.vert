//animated.vert
layout(location = POSITION_ATTRIB_LOCATION) in vec3 Position;
layout(location = TEXTURE_COORD_ATTRIB_LOCATION) in vec2 aPos;
layout(location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 transform;
layout(location = CURRENT_FRAME_LOCATION) uniform float currentFrame;
layout(location = TOTAL_FRAMES_LOCATION) uniform float frameCount;

out vec2 TexCoord;

void main()
{
	gl_Position = transform * vec4(Position, 1.0f);
	float xCoord = aPos.x / frameCount * currentFrame;
	TexCoord = vec2(xCoord , aPos.y);
}