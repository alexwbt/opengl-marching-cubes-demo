#include "shader.h"

#include <glad/glad.h>
#include <fstream>
#include <iostream>

std::string readFile(const char* path)
{
    std::string line;
    std::ifstream file(path);

    std::string out = "";

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            out += line + "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "Failed to open file: " << path << std::endl;
    }

    return out;
}

Shader::Shader(std::vector<std::string> paths, std::vector<int> types)
{
    size_t size = paths.size();
    unsigned int* ids = new unsigned int[size];

    programId = glCreateProgram();

    int success;
    char infoLog[512];

    for (int i = 0; i < size; i++)
    {
        std::string source = readFile(&paths[i][0]);
        const char* code = source.c_str();
        ids[i] = glCreateShader(types[i]);
        glShaderSource(ids[i], 1, &code, NULL);
        glCompileShader(ids[i]);
        glGetShaderiv(ids[i], GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(ids[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED (" << paths[i]
                << ")" << std::endl << infoLog << std::endl;
        }

        glAttachShader(programId, ids[i]);
    }
    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    for (int i = 0; i < size; i++)
    {
        glDeleteShader(ids[i]);
    }
    delete[] ids;
}

void Shader::use()
{
    glUseProgram(programId);
}

void Shader::setBool(const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(programId, name), (int)value);
}
void Shader::setInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(programId, name), value);
}
void Shader::setFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(programId, name), value);
}
void Shader::setVec2(const char* name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(programId, name), 1, &value[0]);
}
void Shader::setVec2(const char* name, float x, float y)
{
    glUniform2f(glGetUniformLocation(programId, name), x, y);
}
void Shader::setVec3(const char* name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(programId, name), 1, &value[0]);
}
void Shader::setVec3(const char* name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(programId, name), x, y, z);
}
void Shader::setVec4(const char* name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(programId, name), 1, &value[0]);
}
void Shader::setVec4(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(programId, name), x, y, z, w);
}
void Shader::setMat2(const char* name, const glm::mat2& mat)
{
    glUniformMatrix2fv(glGetUniformLocation(programId, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const char* name, const glm::mat3& mat)
{
    glUniformMatrix3fv(glGetUniformLocation(programId, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const char* name, const glm::mat4& mat)
{
    glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, &mat[0][0]);
}
