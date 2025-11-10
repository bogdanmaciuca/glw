#include "glw/shader.hpp"

#include <expected>
#include <string>

#include "glad.h"

#include "glw/types.hpp"
#include "glw/debug.hpp"

namespace glw {
    std::expected<std::string, bool> ReadFile(const std::string& path);
    void CheckErrors(u32 shader, GLenum type);
    u32 CreateShader(GLenum type, const std::string& filename);

    void Shader::Release() {
        glDeleteProgram(program_id);
    }
    void Shader::Bind() {
        glUseProgram(program_id);
    }
    void Shader::SetInt(const std::string& name, i32 value) {
        glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
    }
    void Shader::SetIntVec(const std::string& name, const std::span<const i32>& value) {
        glUniform1iv(glGetUniformLocation(program_id, name.c_str()), value.size(), value.data());
    }
    void Shader::SetFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
    }
    void Shader::SetFloatVec(const std::string& name, const std::span<const float>& value) {
        glUniform1fv(glGetUniformLocation(program_id, name.c_str()), value.size(), value.data());
    }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value) {
        glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
    }
    void Shader::SetVec3Vec(const std::string& name, const std::span<const glm::vec3>& value) {
        glUniform3fv(
            glGetUniformLocation(program_id, name.c_str()),
            value.size(), reinterpret_cast<const float*>(value.data())
        );
    }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) {
        glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
    }
    void Shader::SetVec4Vec(const std::string& name, const std::span<const glm::vec4>& value) {
        glUniform4fv(
            glGetUniformLocation(program_id, name.c_str()),
            value.size(), reinterpret_cast<const float*>(value.data())
        );
    }
    void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
        glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    std::expected<GraphicsShader, bool> LoadGraphicsShader(
        const std::string& vertex_path,
        const std::string& fragment_path
    ) {
        auto vertex_source = ReadFile(vertex_path);
        if (!vertex_source) {
            Debug::Print("Could not load vertex shader source from: {}", vertex_path);
            return std::unexpected(false);
        }

        auto fragment_source = ReadFile(fragment_path);
        if (!fragment_source) {
            Debug::Print("Could not load fragment shader source from: {}", fragment_path);
            return std::unexpected(false);
        }

        auto vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_source.value());
        if (!vertex_shader) {
            Debug::Print("Could not compile vertex shader.");
            return std::unexpected(false);
        }

        auto fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_source.value());
        if (!fragment_shader) {
            Debug::Print("Could not compile fragment shader.");
            return std::unexpected(false);
        }

        GraphicsShader result;
        result.vertex_path = vertex_path;
        result.fragment_path = fragment_path;
        result.program_id = glCreateProgram();
        glAttachShader(result.program_id, vertex_shader);
        glAttachShader(result.program_id, fragment_shader);
        glLinkProgram(result.program_id);

        int success;
        char infoLog[1024];
        glGetProgramiv(result.program_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(result.program_id, 1024, NULL, infoLog);
            Debug::Print("Shader linking error: \n{}", infoLog);
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        
        return result;
    }

    bool GraphicsShader::Reload() {
        auto new_shader = LoadGraphicsShader(vertex_path, fragment_path);
        if (!new_shader)
            return false;

        Release();
        *this = new_shader.value();
        return true;
    }

    std::expected<ComputeShader, bool> LoadComputeShader(const std::string& path) {
        auto source = ReadFile(path);
        if (!source) {
            Debug::Print("Could not load shader source from: {}", path);
            return std::unexpected(false);
        }

        auto compute_shader = CreateShader(GL_COMPUTE_SHADER, source.value());

        ComputeShader result;
        result.path = path;
        result.program_id = glCreateProgram();
        glAttachShader(result.program_id, compute_shader);
        glLinkProgram(result.program_id);
        glDetachShader(result.program_id, compute_shader);
        glDeleteShader(compute_shader);

        return result;
    }

    bool ComputeShader::Reload() {
        auto new_shader = LoadComputeShader(path);
        if (!new_shader)
            return false;

        Release();
        *this = new_shader.value();
        return true;
    }

    std::expected<std::string, bool> ReadFile(const std::string& path) {
        FILE* file = fopen(path.c_str(), "rb");
        if (file == nullptr) {
            Debug::Print("Failed to open file: {}", path);
            return std::unexpected(false);
        }

        fseek(file, 0, SEEK_END);
        long length = ftell(file);
        fseek(file, 0, SEEK_SET);

        if (length < 0) {
            fclose(file);
            Debug::Print("Failed to determine file size: {}", path);
            return std::unexpected(false);
        }

        std::string content(length, '\0');

        if (fread(&content[0], 1, length, file) != (size_t)length) {
            fclose(file);
            Debug::Print("Failed to read file: {}", path);
            return std::unexpected(false);
        }

        fclose(file);
        return content;
    }
    void CheckErrors(u32 shader, GLenum type) {
        i32 success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            i32 error_len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_len);
            char* error_msg = static_cast<char*>(malloc(error_len * sizeof(char)));
            glGetShaderInfoLog(shader, error_len, nullptr, error_msg);
            std::string type_str;
            switch(type) {
                case GL_VERTEX_SHADER: type_str = "GL_VERTEX_SHADER"; break;
                case GL_FRAGMENT_SHADER: type_str = "GL_FRAGMENT_SHADER"; break;
                case GL_COMPUTE_SHADER: type_str = "GL_COMPUTE_SHADER"; break;
            }
            Debug::Print("Error in {} shader {}:\n{}\n", type_str.c_str(), shader, error_msg);
        }
    }
    u32 CreateShader(GLenum type, const std::string& source) {
        u32 shader = glCreateShader(type);
        const char* source_c_str = source.c_str();
        glShaderSource(shader, 1, &source_c_str, nullptr);
        glCompileShader(shader);
        CheckErrors(shader, type);
        return shader;
    }
}

