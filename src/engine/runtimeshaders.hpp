#ifndef RUNTIME_SHADERS_HPP_
#define RUNTIME_SHADERS_HPP_

#include "shaderprog.hpp"
#include <memory>

namespace Engine
{
    class RuntimeShaders
    {
        public:
        void Init();
        void Free();
        const bool Ready() const ;

        const ShaderProg* FlatWhite() const;
        const ShaderProg* Diff() const;

        private:
        std::unique_ptr<ShaderProg> m_flatWhite;
        std::unique_ptr<ShaderProg> m_diff;

    };

    const std::string FLAT_WHITE_VERT_SRC = R"(
        #version 330

        uniform mat4 SV_PROJECTION;
        uniform mat4 SV_VIEW;
        uniform mat4 SV_MODEL;

        mat4x4 MVP = SV_PROJECTION * SV_VIEW * SV_MODEL;

        layout(location = 0) in vec3 SV_VERTEX;
        layout(location = 1) in vec3 SV_NORMAL;

        out vec3 vnormal;

        void main(void)
        {
            gl_Position = MVP * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
            vnormal = (SV_MODEL * vec4(SV_NORMAL.x, SV_NORMAL.y, SV_NORMAL.z, 0.0)).xyz;
        }
    )";

    const std::string FLAT_WHITE_PIX_SRC = R"(
        #version 330

        in vec3 vnormal;

        out vec4 SV_OUT_COLOR;
        void main()
        {
            SV_OUT_COLOR = vec4(0, 1, 0, 1);
        }
    )";

    const std::string DIFF_VERT_SRC = R"(
        #version 330

        uniform mat4 SV_PROJECTION;
        uniform mat4 SV_VIEW;
        uniform mat4 SV_MODEL;

        mat4x4 MVP = SV_PROJECTION * SV_VIEW * SV_MODEL;

        layout(location = 0) in vec3 SV_VERTEX;
        layout(location = 1) in vec3 SV_NORMAL;

        out vec3 vnormal;

        void main(void)
        {
            gl_Position = MVP * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
            vnormal = (SV_MODEL * vec4(SV_NORMAL.x, SV_NORMAL.y, SV_NORMAL.z, 0.0)).xyz;
        }
    )";

    const std::string DIFF_PIX_SRC = R"(
        #version 330

        in vec3 vnormal;

        out vec4 SV_OUT_COLOR;
        void main()
        {
            vec3 lightdir = vec3(0, 1, 0);
            float ndotl = dot(lightdir, normalize(vnormal));
            float hLambert = ndotl * 0.5 + 0.5;
            vec3 diff = hLambert * vec3(1, 1, 1);
            SV_OUT_COLOR = vec4(diff.x, diff.y, diff.z, 1);
        }
    )";
}

#endif