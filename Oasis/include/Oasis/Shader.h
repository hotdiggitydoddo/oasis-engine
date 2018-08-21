#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Oasis
{
// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.
    class Shader
    {
    public:
        // State
        GLuint ID;

        // Constructor
        Shader() : _numAttributes(0)
        {}

        // Sets the current shader as active
        Shader& Use();
        // Deactivates the current shader
        void Unuse();
        // Compiles and links the shader from given source code
        void CompileAndLink(const GLchar* vertexSource, const GLchar* fragmentSource,
                            const GLchar* geometrySource = nullptr); // Note: geometry source code is optional
        // Utility functions
        void SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);

        void SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);

        void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);

        void SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);

        void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);

        void SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);

        void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);

        void SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);

        void SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);

        void AddAttribute(const std::string& attributeName);
    private:
        // Checks if compilation or linking failed and if so, print the error logs
        void checkCompileErrors(GLuint object, std::string type);

        int _numAttributes;
    };
}