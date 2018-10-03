//text vertex shader
layout (location = POSITION_ATTRIB_LOCATION) in vec3 vertex;
layout (location = CAMERA_MATRIX_ATTRIB_LOCATION) uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(vertex.x, vertex.y, vertex.z , 1.0);
    //gl_Position = vec4(vertex.x, vertex.y, vertex.z , 1.0);
} 