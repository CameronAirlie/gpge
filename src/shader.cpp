#include <GL/glew.h>
#include "shader.h"
#include <iostream>
#include <string.h>

void add_shader(GLuint program, const char *shader_code, GLenum type)
{
    GLuint current_shader = glCreateShader(type);

    const GLchar *code[1];
    code[0] = shader_code;

    GLint code_length[1];
    code_length[0] = strlen(shader_code);

    glShaderSource(current_shader, 1, code, code_length);
    glCompileShader(current_shader);

    GLint result = 0;
    GLchar log[1024] = {0};

    glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
        std::cout << "Error compiling " << type << " shader: " << log << "\n";
        return;
    }

    glAttachShader(program, current_shader);
}

void create_shaders()
{
    shader = glCreateProgram();
    if (!shader)
    {
        std::cout << "Error creating shader program!\n";
        exit(1);
    }
    add_shader(shader, vertex_shader_code, GL_VERTEX_SHADER);
    add_shader(shader, fragment_shader_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar log[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error linking program:\n"
                  << log << '\n';
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error validating program:\n"
                  << log << '\n';
        return;
    }
}

void create_triangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, // 1. vertex x, y, z
        1.0f, -1.0f, 0.0f,  // 2. vertex ...
        0.0f, 1.0f, 0.0f    // etc...
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void compile_shaders()
{
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}
