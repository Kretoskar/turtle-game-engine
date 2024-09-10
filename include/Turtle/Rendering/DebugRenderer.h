#pragma once
#include <memory>

#include "Turtle/Rendering/Camera.h"
#include "Turtle/Rendering/ElementBufferObject.h"
#include "Turtle/Rendering/VertexArrayObject.h"
#include "Turtle/Rendering/VertexBufferObject.h"
#include "Turtle/Rendering/Shader.h"

namespace Turtle
{
    struct LineVertex
    {
        LineVertex() = default;

        LineVertex(glm::vec3 pos, glm::vec3 color)
            : x(pos.x), y(pos.y), z(pos.z), r(color.r), g(color.g), b(color.b) {}
        LineVertex(float x, float y, float z, float r, float g, float b)
            : x(x), y(y), z(z), r(r), g(g), b(b) {}

        float x{}, y{}, z{};
        float r{}, g{}, b{};
    };

    class DebugRenderer
    {
    public:
        DebugRenderer() {}
        
        bool Init();
        void Render();
        void AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
        void DrawNet(unsigned count, float stride, float size, glm::vec3 color);

        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexBufferObject> lineVbo;
        std::unique_ptr<ElementBufferObject> lineEbo;
        std::unique_ptr<VertexArrayObject> lineVao;

        static constexpr unsigned MAX_LINE_COUNT = 4096;
        unsigned lineCount = 0;
        LineVertex lineVertices[MAX_LINE_COUNT * 2];

        unsigned lineIndices[MAX_LINE_COUNT * 2];
    };

}