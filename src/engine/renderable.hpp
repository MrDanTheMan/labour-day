#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "shaderprog.hpp"
#include <glm/vec3.hpp>
#include <memory>

namespace Engine
{
    class Renderable
    {
        public:

        Renderable();
        void Init(glm::vec3 *vertices, uint32_t *indices, const uint32_t vCount, const uint32_t iCount);
        void Free();
        void BindShader(ShaderProg* shader);
        const ShaderProg* GetShader() const;
        const uint32_t VertexCount() const;
        const uint32_t IndexCount() const;

        private:

        void InitBuffers();
        void BuffersGood();

        std::unique_ptr<glm::vec3[]> m_vertices;
        std::unique_ptr<uint32_t[]> m_indices;
        ShaderProg* m_shader;
        uint32_t m_vertexCount;
        uint32_t m_indexCount;

        GLuint m_vbo;
        GLuint m_ibo;

    };
}

#endif