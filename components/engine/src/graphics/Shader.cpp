//
// Created by BlackFlage on 19.10.2021.
//

#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

namespace vis
{
    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    Shader::Shader()
    {

    }

    Shader* Shader::create_shader(const std::string &a_vertex_path, const std::string &a_fragment_path)
    {
        Shader* shader = new Shader();

        GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
        std::string vertex_source = ShaderParser::read_shader_data(a_vertex_path);
        const char* v_src = vertex_source.c_str();
        glShaderSource(vertex_id, 1, &v_src, nullptr);
        glCompileShader(vertex_id);

        GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fragment_source = ShaderParser::read_shader_data(a_fragment_path);
        const char* f_src = fragment_source.c_str();
        glShaderSource(fragment_id, 1, &f_src, nullptr);
        glCompileShader(fragment_id);

        int success;
        char infoLog[512];
        glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertex_id, 512, nullptr, infoLog);
            std::cout << "OpenGL error: failed to compile shader: " << infoLog << '\n';

            delete shader;
            return nullptr;
        }


        shader->m_id = glCreateProgram();
        glAttachShader(shader->m_id, vertex_id);
        glAttachShader(shader->m_id, fragment_id);
        glLinkProgram(shader->m_id);

        glGetProgramiv(shader->m_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader->m_id, 512, nullptr, infoLog);

            std::cout << "Failed linking shader: " << infoLog << '\n';

            delete shader;
            return nullptr;
        }

        glUseProgram(shader->m_id);
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);

        LOG_INFO("Shader compiled successfully!");

        return shader;
    }

    void Shader::set_uniform_2f(const char* a_name, float f1, float f2)
    {
        glUseProgram(m_id);

        GLuint location = glGetUniformLocation(m_id, a_name);
        glUniform2f(location, f1, f2);

        glUseProgram(0);
    }

    void Shader::set_uniform_3f(const char *a_name, float f1, float f2, float f3)
    {
        glUseProgram(m_id);

        GLuint location = glGetUniformLocation(m_id, a_name);
        glUniform3f(location, f1, f2, f3);

        glUseProgram(0);
    }

    void Shader::set_uniform_mat4(const char *a_name, glm::mat4 mat4)
    {
        glUseProgram(m_id);

        GLuint location = glGetUniformLocation(m_id, a_name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));

        glUseProgram(0);
    }
}
