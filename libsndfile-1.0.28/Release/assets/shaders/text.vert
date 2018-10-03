//text vertex shader
layout (location = POSITION_ATTRIB_LOCATION) in vec4 vertex;// <vec2 pos, vec2 tex>
out vec2 TexCoords;

//uniform mat4 projection;
layout (location = TEXTURE_COORD_ATTRIB_LOCATION) uniform sampler2D ourTexture;
layout (location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
} 