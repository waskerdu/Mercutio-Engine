layout(location = POSITION_ATTRIB_LOCATION) in vec3 Position;
layout(location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(Position, 1.0f);
}