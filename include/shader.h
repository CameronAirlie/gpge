#include <GL/glew.h>

const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;

GLuint VAO;
GLuint VBO;
GLuint FBO;
GLuint RBO;
GLuint texture_id;

GLuint shader;

const char *vertex_shader_code = R"*(
#version 330

layout (location = 0) in vec3 pos;

void main()
{
	gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
}
)*";

const char *fragment_shader_code = R"*(
#version 330

out vec4 color;

void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
}
)*";

void create_triangle();

void add_shader(GLuint program, const char *shader_code, GLenum type);

void create_shaders();

void compile_shaders();
