#version 330

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform bool invertVertical;

void main(){
    //    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

    if (invertVertical)
        FragColor = texture(texture1, vec2(TexCoord.x, 1.0 - TexCoord.y));
    else
        FragColor = texture(texture1, TexCoord);
}