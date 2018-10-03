layout(location = POSITION_ATTRIB_LOCATION) in vec3 Position;
layout(location = TEXTURE_COORD_ATTRIB_LOCATION) in vec2 aPos;
layout(location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 transform;

out vec2 TexCoord;

void main()
{
	gl_Position = transform * vec4(Position, 1.0f);
	TexCoord = vec2(aPos.x, aPos.y);
}