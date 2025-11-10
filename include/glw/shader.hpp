// TODO:
// - Add the option of loading from memory

#ifndef SHADER_HPP
#define SHADER_HPP

#include <expected>
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
    std::expected<GraphicsShader, bool> CreateGraphicsShader(
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
        
        static ivec3 GetMaxWorkGroupCount();
        static int GetMaxInvocationCount();
    };
    std::expected<ComputeShader, bool> CreateComputeShader(const std::string& path);
}

#endif // SHADER_HPP

