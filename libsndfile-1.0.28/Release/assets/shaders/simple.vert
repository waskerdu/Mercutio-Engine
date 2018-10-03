layout (location = POSITION_ATTRIB_LOCATION) in vec3 aPos;
layout (location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 camMatrix;
layout (location = COLOR_ATTRIB_LOCATION) in vec3 aColor;
layout (location = TEXTURE_COORD_ATTRIB_LOCATION) in vec2 aTextCoord;

out vec3 vertColor;
out vec2 TexCoord;

//layout (location = ENTITY _MATRIX_ATTRIB_LOCATION) in mat4 entityMatrix;

void main()
{
    gl_Position = camMatrix * vec4(aPos, 1.0);
    vertColor = aColor;
    TexCoord = aTextCoord;
    //gl_Position = vec4(aPos, 1.0);
}