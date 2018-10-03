//text render frag
layout (location = TEXT_COLOR_UNIFORM_LOCATION) uniform vec3 textColor;
out vec4 color;

void main()
{    
    color = vec4(textColor,1.0);
} 