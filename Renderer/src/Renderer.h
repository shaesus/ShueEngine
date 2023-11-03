#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Assertion.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace Shue {

    class Renderer
    {
    public:
        int InitGLFW();
        int InitGLAD();
        int InitFreeType();
        void GLFWSetOpenGLVersionAndProfile(int major = 4, int minor = 6, int profile = GLFW_OPENGL_CORE_PROFILE);
        void Clear() const;
        void ClearColor(float r, float g, float b, float a) const;
        void DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
        void DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count);
        void SetBlending(bool blending, unsigned int sfactor = GL_SRC_ALPHA, unsigned int dfactor = GL_ONE_MINUS_SRC_ALPHA);
    };

}