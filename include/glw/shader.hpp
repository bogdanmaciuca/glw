// TODO:
// - Add the option of loading from memory

#ifndef SHADER_HPP
#define SHADER_HPP

#include <optional>
#include <string>
#include <span>
#include <bitset>

#include "types.hpp"

namespace glw {
    struct Shader {
        u32 program_id;
        void Release();
        void Bind();
        void SetInt(const std::string& name, i32 value);
        void SetIntVec(const std::string& name, const std::span<const i32>& value);
        void SetFloat(const std::string& name, float value);
        void SetFloatVec(const std::string& name, const std::span<const float>& value);
        void SetVec3(const std::string& name, const glm::vec3& value);
        void SetVec3Vec(const std::string& name, const std::span<const glm::vec3>& value);
        void SetVec4(const std::string& name, const glm::vec4& value);
        void SetVec4Vec(const std::string& name, const std::span<const glm::vec4>& value);
        void SetMat4(const std::string& name, const glm::mat4& value);
    };

    struct GraphicsShader : public Shader {
        std::string vertex_path;
        std::string fragment_path;
        bool Reload();
    };

    /**
    * @brief Creates a graphics shader program
    * 
    * @param [in] vertex_path Path of the vertex shader
    * @param [in] fragment_path Path of the fragment shader
    *
    * @return An std::optional object containing the GraphicsShader
    * on success or std::nullopt on failure
    */
    std::optional<GraphicsShader> CreateGraphicsShader(
        const std::string& vertex_path,
        const std::string& fragment_path
    );
    
    // TODO: Do for all barriers
    enum ComputeMemoryBarrier {
        MEM_BARRIER_IMG_ACCESS,

        MEM_BARRIER_COUNT
    };

    struct ComputeShader : public Shader {
        std::string path;
        bool Reload();
        void Dispatch(
            unsigned int num_groups_x,
            unsigned int num_groups_y,
            unsigned int num_groups_z
        );
        void MemoryBarrier(std::bitset<MEM_BARRIER_COUNT> barriers);
        
        /**
         * @brief Gets the maximum work group number in each direction
         */
        static ivec3 GetMaxWorkGroupCount();
        /**
         * @brief Gets the maximum number of invocation in ONE work group
         */
        static int GetMaxInvocationCount();
    };

    /**
    * @brief Creates a compute shader program
    * 
    * @param [in] path Path of the compute shader
    *
    * @return An std::optional object containing the ComputeShader
    * on success or std::nullopt on failure
    */
    std::optional<ComputeShader> CreateComputeShader(const std::string& path);
}

#endif // SHADER_HPP

