//
// Created by BlackFlage on 19.10.2021.
//

#include "Shader.h"

vis::Shader::Shader(const std::string &a_vertex_path, const std::string &a_fragment_path)
{
    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_source = ShaderParser::read_shader_data(a_vertex_path);
    std::string fragment_source = ShaderParser::read_shader_data(a_fragment_path);

    glShaderSource(vertex_id, 1, (const GLchar**)vertex_source.c_str(), nullptr);
    glCompileShader(vertex_id);

    glShaderSource(fragment_id, 1, (const GLchar**)vertex_source.c_str(), nullptr);
    glCompileShader(fragment_id);

    int success;
    char infoLog[512];
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex_id, 512, nullptr, infoLog);
        std::cout << "OpenGL error: failed to compile shader: " << infoLog << '\n';
        return;
    }


    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_id);
    glAttachShader(m_id, fragment_id);
    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);

        std::cout << "Failed linking shader: " << infoLog << '\n';
    }

    glUseProgram(m_id);
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    LOG_INFO("Shader compiled successfully!");
}
