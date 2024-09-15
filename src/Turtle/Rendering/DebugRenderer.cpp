#include <glad/glad.h>

#include "Turtle/Rendering/DebugRenderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Turtle/Core/EventSystem.h"
#include "Turtle/Core/Logger.h"

#include "Turtle/Core/Engine.h"

bool Turtle::DebugRenderer::Init()
{
    _shader = std::make_unique<Shader>("Shaders/debug.frag", "Shaders/debug.vert");
    _shader->Bind();

    _lineVao = std::make_unique<VertexArrayObject>();
    _lineVao->Bind();
    _lineVbo = std::make_unique<VertexBufferObject>((float*)_lineVertices, MAX_LINE_COUNT * 6 * 4);
    _lineEbo = std::make_unique<ElementBufferObject>(_lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    _lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    _lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    DrawNet(100, 1.0f, 100.0f, glm::vec3(0.6f, 0.6f, 0.6f));
    DrawNet(1000, 0.1f, 100.0f, glm::vec3(0.3f, 0.3f, 0.3f));

    return true;
}

void Turtle::DebugRenderer::Render()
{
    _shader->Bind();
    _shader->SetModelMatrix(glm::mat4(1.0f));
    _shader->SetVPMatrix(Engine::Camera->GetVPMatrix());
    _lineVao->Bind();
    glDrawElements(GL_LINES, sizeof(_lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Turtle::DebugRenderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
    if (_lineCount == MAX_LINE_COUNT)
    {
        TURTLE_LOG_ERROR("Exceeded maximum debug line count of %d Can't draw any more lines", MAX_LINE_COUNT)
            return;
    }

    _lineVertices[_lineCount * 2] = { start, color };
    _lineVertices[_lineCount * 2 + 1] = { end, color };
    
    _lineIndices[_lineCount * 2] = _lineCount * 2;
    _lineIndices[_lineCount * 2 + 1] = _lineCount * 2 + 1;
    
    _lineCount++;
}

void Turtle::DebugRenderer::DrawNet(unsigned count, float stride, float size, glm::vec3 color)
{
    //TODO: Allow adding lines in batch
    for (int i = 0; i <= count; i++)
    {
        AddLine(glm::vec3(size / 2, 0.0f, i * stride - count * stride / 2), glm::vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
        AddLine(glm::vec3(i * stride - count * stride / 2, 0.0f, size / 2), glm::vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
    }

    _lineVao->Bind();
    _lineVbo->Init((float*)_lineVertices, _lineCount * 2 * 6 * 4);
    _lineEbo->Init(_lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    _lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    _lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}
