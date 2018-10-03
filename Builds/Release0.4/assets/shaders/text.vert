layout(location = POSITION_ATTRIB_LOCATION) in vec4 Position;
layout(location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 transform;

out vec2 TexCoord;

void main()
{
	gl_Position = transform * vec4(Position.xy, 0.0, 1.0f);
	TexCoord = vec2(Position.zw);
}