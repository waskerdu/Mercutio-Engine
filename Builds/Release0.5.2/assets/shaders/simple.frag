out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
    FragColor.rgb*=FragColor.a;
    //if(FragColor.a==0.0){discard;}
}