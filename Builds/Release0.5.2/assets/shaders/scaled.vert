//scaled.vert
layout(location = POSITION_ATTRIB_LOCATION) in vec3 Position;
layout(location = TEXTURE_COORD_ATTRIB_LOCATION) in vec2 aPos;
layout(location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 transform;
layout(location = WORLD_MATRIX_ATTRIB_LOCATION) uniform mat4 worldTransform;

out vec2 TexCoord;

void main()
{
	gl_Position = transform * vec4(Position, 1.0f);
	vec4 uvVec = worldTransform * vec4(aPos, 0, 1.0f);
	//TexCoord = vec2(aPos.x, aPos.y);
	TexCoord = vec2(uvVec.x, uvVec.y);
}