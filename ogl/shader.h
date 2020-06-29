#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader() {}

    void compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);
    Shader loadFromFiles(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

    Shader& use(); 

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;


    void    SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
    void    SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);
    void    SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
    void    SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
    void    SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
    void    SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint object, std::string type);

};
