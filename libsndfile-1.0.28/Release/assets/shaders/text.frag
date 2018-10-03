//text render frag
in vec2 TexCoords;
out vec4 color;

layout (binding = TEXTURE_UNIFORM_LOCATION) uniform sampler2D text;
layout (location = TEXT_COLOR_UNIFORM_LOCATION) uniform vec3 textColor;
//uniform sampler2D text;
//uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    if(sampled.a==0.0){discard;}
    color = vec4(textColor, 1.0) * sampled;
} 