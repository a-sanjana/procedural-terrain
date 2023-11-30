/**
 * @file
 * @brief Defines the Shader class for handling OpenGL shader programs.
 */

#ifndef SHADER_H
#define SHADER_H

#include "include\glad\glad.h"
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief The Shader class represents a shader program in OpenGL.
 * 
 * This class provides functionality to create, activate, and set uniforms for a shader program.
 * It also includes utility functions for checking shader compilation and linking errors.
 */
class Shader{
public:
    unsigned int ID;
    
    /**
     * @brief Constructs a Shader object by loading and compiling the vertex and fragment shaders from file paths.
     * 
     * @param vertexPath The file path of the vertex shader source code.
     * @param fragmentPath The file path of the fragment shader source code.
     */
    Shader(const char* vertexPath, const char* fragmentPath);
    
    /**
     * @brief Constructs a Shader object with an existing shader program ID.
     * 
     * @param idcp The ID of the existing shader program.
     */
    Shader(unsigned int idcp);
    
    /**
     * @brief Activates the shader program.
     */
    void use();
    
    /**
     * @brief Sets a boolean uniform in the shader program.
     * 
     * @param name The name of the boolean uniform.
     * @param value The value to set for the boolean uniform.
     */
    void setBool(const std::string &name, bool value) const;
    
    /**
     * @brief Sets an integer uniform in the shader program.
     * 
     * @param name The name of the integer uniform.
     * @param value The value to set for the integer uniform.
     */
    void setInt(const std::string &name, int value) const;
    
    /**
     * @brief Sets a float uniform in the shader program.
     * 
     * @param name The name of the float uniform.
     * @param value The value to set for the float uniform.
     */
    void setFloat(const std::string &name, float value) const;
    
    /**
     * @brief Sets a 2D vector uniform in the shader program.
     * 
     * @param name The name of the 2D vector uniform.
     * @param value The value to set for the 2D vector uniform.
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    
    /**
     * @brief Sets a 2D vector uniform in the shader program.
     * 
     * @param name The name of the 2D vector uniform.
     * @param x The x component of the 2D vector.
     * @param y The y component of the 2D vector.
     */
    void setVec2(const std::string &name, float x, float y) const;
    
    /**
     * @brief Sets a 3D vector uniform in the shader program.
     * 
     * @param name The name of the 3D vector uniform.
     * @param value The value to set for the 3D vector uniform.
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    
    /**
     * @brief Sets a 3D vector uniform in the shader program.
     * 
     * @param name The name of the 3D vector uniform.
     * @param x The x component of the 3D vector.
     * @param y The y component of the 3D vector.
     * @param z The z component of the 3D vector.
     */
    void setVec3(const std::string &name, float x, float y, float z) const;
    
    /**
     * @brief Sets a 4D vector uniform in the shader program.
     * 
     * @param name The name of the 4D vector uniform.
     * @param value The value to set for the 4D vector uniform.
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    
    /**
     * @brief Sets a 4D vector uniform in the shader program.
     * 
     * @param name The name of the 4D vector uniform.
     * @param x The x component of the 4D vector.
     * @param y The y component of the 4D vector.
     * @param z The z component of the 4D vector.
     * @param w The w component of the 4D vector.
     */
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    
    /**
     * @brief Sets a 2x2 matrix uniform in the shader program.
     * 
     * @param name The name of the 2x2 matrix uniform.
     * @param mat The matrix to set for the uniform.
     */
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    
    /**
     * @brief Sets a 3x3 matrix uniform in the shader program.
     * 
     * @param name The name of the 3x3 matrix uniform.
     * @param mat The matrix to set for the uniform.
     */
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    
    /**
     * @brief Sets a 4x4 matrix uniform in the shader program.
     * 
     * @param name The name of the 4x4 matrix uniform.
     * @param mat The matrix to set for the uniform.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * @brief Utility function for checking shader compilation and linking errors.
     * 
     * @param shader The ID of the shader to check.
     * @param type The type of the shader (e.g., "VERTEX" or "FRAGMENT").
     */
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif