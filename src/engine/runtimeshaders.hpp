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

        const ShaderProg* const FlatWhite() const;
        const ShaderProg* const Diff() const;
        const ShaderProg* const Diff1() const;
        const ShaderProg* const GetByName(const std::string &name) const;

        private:
        std::unique_ptr<ShaderProg> m_flatWhite;
        std::unique_ptr<ShaderProg> m_diff;
        std::unique_ptr<ShaderProg> m_diff1;

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
        uniform mat4 SV_SHADOW_PROJ0;

        mat4x4 MVP = SV_PROJECTION * SV_VIEW * SV_MODEL;

        layout(location = 0) in vec3 SV_VERTEX;
        layout(location = 1) in vec3 SV_NORMAL;
        layout(location = 2) in vec2 SV_TEXCOORD0;

        out vec3 vnormal;
        out vec2 texcoord0;
        out vec4 shadowcoord0;

        void main(void)
        {
            gl_Position = MVP * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
            vnormal = (SV_MODEL * vec4(SV_NORMAL.x, SV_NORMAL.y, SV_NORMAL.z, 0.0)).xyz;
            texcoord0 = SV_TEXCOORD0;
            shadowcoord0 = SV_SHADOW_PROJ0 * (SV_MODEL * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0));
        }
    )";

    const std::string DIFF_PIX_SRC = R"(
        #version 330

        in vec3 vnormal;
        in vec2 texcoord0;
        in vec4 shadowcoord0;

        uniform float SV_MAIN_LIGHT_INTENSITY;
        uniform vec3 SV_MAIN_LIGHT_DIR;
        uniform sampler2DShadow SV_SHADOW_MAP0;
        uniform float SV_SHADOW_BIAS0;
        uniform vec3 tint;
        

        out vec4 SV_OUT_COLOR;
        void main()
        {
            // Direction lambert term
            float ndotl = dot(normalize(SV_MAIN_LIGHT_DIR), normalize(vnormal));
            float hLambert = (ndotl * 0.5 + 0.5) * SV_MAIN_LIGHT_INTENSITY;

            // Calculate shadow using bias based on the slope
            float shadowBias = 0.005 * tan(acos(ndotl)) + SV_SHADOW_BIAS0;
            shadowBias = clamp(shadowBias, 0, 0.1);
            float shadow = textureProj(SV_SHADOW_MAP0, vec4(shadowcoord0.x, shadowcoord0.y, shadowcoord0.z - shadowBias, shadowcoord0.w));

            // Composite & output
            vec3 diff = hLambert * tint * shadow;
            SV_OUT_COLOR = vec4(diff.x, diff.y, diff.z, 1);
        }
    )";

    const std::string DIFF1_VERT_SRC = R"(
        #version 330

        uniform mat4 SV_PROJECTION;
        uniform mat4 SV_VIEW;
        uniform mat4 SV_MODEL;
        uniform mat4 SV_SHADOW_PROJ0;

        mat4x4 MVP = SV_PROJECTION * SV_VIEW * SV_MODEL;

        layout(location = 0) in vec3 SV_VERTEX;
        layout(location = 1) in vec3 SV_NORMAL;
        layout(location = 2) in vec2 SV_TEXCOORD0;

        out vec3 vnormal;
        out vec2 texcoord0;
        out vec4 shadowcoord0;

        void main(void)
        {
            gl_Position = MVP * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
            vnormal = (SV_MODEL * vec4(SV_NORMAL.x, SV_NORMAL.y, SV_NORMAL.z, 0.0)).xyz;
            texcoord0 = SV_TEXCOORD0;
            shadowcoord0 = SV_SHADOW_PROJ0 * (SV_MODEL * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0));
        }
    )";

    const std::string DIFF1_PIX_SRC = R"(
        #version 330

        in vec3 vnormal;
        in vec2 texcoord0;
        in vec4 shadowcoord0;

        uniform float SV_MAIN_LIGHT_INTENSITY;
        uniform vec3 SV_MAIN_LIGHT_DIR;
        uniform sampler2DShadow SV_SHADOW_MAP0;
        uniform float SV_SHADOW_BIAS0;
        uniform sampler2D diff1map;
        uniform vec2 tiling = vec2(1,1);

        out vec4 SV_OUT_COLOR;
        void main()
        {
            // Direction lambert term
            float ndotl = dot(normalize(SV_MAIN_LIGHT_DIR), normalize(vnormal));
            float hLambert = (ndotl * 0.5 + 0.5) * SV_MAIN_LIGHT_INTENSITY;
            
            // Calculate shadow using bias based on the slope
            float shadowBias = 0.005 * tan(acos(ndotl)) + SV_SHADOW_BIAS0;
            shadowBias = clamp(shadowBias, 0, 0.1);
            float shadow = textureProj(SV_SHADOW_MAP0, vec4(shadowcoord0.x, shadowcoord0.y, shadowcoord0.z - shadowBias, shadowcoord0.w));

            // Diffuse texture lookup & tiling
            vec3 tex = texture(diff1map, texcoord0 * tiling).rgb;

            // Composite & output
            vec3 diff = hLambert * tex * shadow;
            SV_OUT_COLOR = vec4(diff.x, diff.y, diff.z, 1);
        }
    )";
}

#endif