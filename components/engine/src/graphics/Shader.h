//
// Created by BlackFlage on 19.10.2021.
//

#ifndef MAIN_SHADER_H
#define MAIN_SHADER_H

#include "GL/glew.h"
#include <string>
#include <fstream>
#include <Logger.h>
#include "Macro.h"

namespace vis
{
    class Shader
    {
    public:
        ~Shader();

        inline void bind() const { glUseProgram(m_id); }
        inline void unbind() const { glUseProgram(0); }

        void set_uniform_2f(const char* a_name, float f1, float f2);
        void set_uniform_3f(const char* a_name, float f1, float f2, float f3);

        static Shader* create_shader(const std::string &a_vertex_path, const std::string &a_fragment_path);
    private:
        Shader();
    private:
        GLuint m_id;
    };

    struct ShaderParser
    {
        static std::string read_shader_data(const std::string& a_path)
        {
            std::ifstream file(a_path);
            std::stringstream output;

            if(!file)
            {
                std::cout << "Failed to read file: " << a_path << '\n';
                return "";
            }

            std::string line;
            while(!file.eof())
            {
                std::getline(file, line);
                output << line << '\n';
            }

            return output.str();
        }
    };
}


#endif //MAIN_SHADER_H
