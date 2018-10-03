layout(location = TEXT_COLOR_UNIFORM_LOCATION) uniform vec3 color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(color,1.0);
}