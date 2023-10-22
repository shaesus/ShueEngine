#pragma once

#include "glad/glad.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void ClearColor(float r, float g, float b, float a) const;
    void DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count);
    void SetBlending(bool blending, unsigned int sfactor = GL_SRC_ALPHA, unsigned int dfactor = GL_ONE_MINUS_SRC_ALPHA);
};