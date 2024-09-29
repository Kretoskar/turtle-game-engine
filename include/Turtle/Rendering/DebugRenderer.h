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
            : X(pos.x), Y(pos.y), Z(pos.z), R(color.r), G(color.g), B(color.b) {}
        LineVertex(float x, float y, float z, float r, float g, float b)
            : X(x), Y(y), Z(z), R(r), G(g), B(b) {}

        float X{}, Y{}, Z{};
        float R{}, G{}, B{};
    };

    class DebugRenderer
    {
    public:
        DebugRenderer() {}
        
        bool Init();
        void Render();
        void AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
        void DrawNet(unsigned count, float stride, float size, glm::vec3 color);

    private:
        Shader* _shader;
        std::unique_ptr<VertexBufferObject> _lineVbo;
        std::unique_ptr<ElementBufferObject> _lineEbo;
        std::unique_ptr<VertexArrayObject> _lineVao;

        static constexpr unsigned MAX_LINE_COUNT = 4096;
        uint32_t _lineCount = 0;
        LineVertex _lineVertices[MAX_LINE_COUNT * 2];

        unsigned _lineIndices[MAX_LINE_COUNT * 2];
    };

}