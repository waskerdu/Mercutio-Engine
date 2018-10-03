out vec4 FragColor;
in vec3 vertColor;
in vec2 TexCoord;
layout (binding = TEXTURE_UNIFORM_LOCATION) uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(vertColor, 1.0);//vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor=texture(ourTexture,TexCoord);
    if(FragColor.a!=1.0){discard;}
}