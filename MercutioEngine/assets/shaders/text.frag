out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, TexCoord).r);
    FragColor = vec4(textColor,1.0)*sampled;
    if(FragColor.a==0.0){discard;}
}