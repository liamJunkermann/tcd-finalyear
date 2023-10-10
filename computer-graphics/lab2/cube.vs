#version 330 core
in vec4 vPosition;
in vec4 vColor;
out vec4 color;

void main() {
    gl_Position = 0.5 * vPosition;
    color = vColor;
}
