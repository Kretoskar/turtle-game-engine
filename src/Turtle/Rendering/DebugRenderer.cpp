#include "Turtle/Rendering/DebugRenderer.h"

#include "Turtle/Rendering/Renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Turtle/Core/EventSystem.h"
#include "Turtle/Core/Logger.h"

#include "Turtle/Core/Engine.h"

bool Turtle::DebugRenderer::Init()
{
    shader = std::make_unique<Shader>("Shaders/debug.frag", "Shaders/debug.vert");
    shader->Bind();

    lineVao = std::make_unique<VertexArrayObject>();
    lineVao->Bind();
    lineVbo = std::make_unique<VertexBufferObject>((float*)lineVertices, MAX_LINE_COUNT * 6 * 4);
    lineEbo = std::make_unique<ElementBufferObject>(lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    DrawNet(100, 1.0f, 100.0f, glm::vec3(0.6f, 0.6f, 0.6f));
    DrawNet(1000, 0.1f, 100.0f, glm::vec3(0.3f, 0.3f, 0.3f));

    return true;
}

void Turtle::DebugRenderer::Render()
{
    shader->Bind();
    shader->SetModelMatrix(glm::mat4(1.0f));
    shader->SetVPMatrix(Engine::Camera->GetVPMatrix());
    lineVao->Bind();
    glDrawElements(GL_LINES, sizeof(lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Turtle::DebugRenderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
    if (lineCount == MAX_LINE_COUNT)
    {
        TURTLE_LOG_ERROR("Exceeded maximum debug line count of %d Can't draw any more lines", MAX_LINE_COUNT)
            return;
    }

    lineVertices[lineCount * 2] = { start, color };
    lineVertices[lineCount * 2 + 1] = { end, color };

    lineIndices[lineCount * 2] = lineCount * 2;
    lineIndices[lineCount * 2 + 1] = lineCount * 2 + 1;

    lineCount++;
}

void Turtle::DebugRenderer::DrawNet(unsigned count, float stride, float size, glm::vec3 color)
{
    //TODO: Allow adding lines in batch
    for (int i = 0; i <= count; i++)
    {
        AddLine(glm::vec3(size / 2, 0.0f, i * stride - count * stride / 2), glm::vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
        AddLine(glm::vec3(i * stride - count * stride / 2, 0.0f, size / 2), glm::vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
    }

    lineVao->Bind();
    lineVbo->Init((float*)lineVertices, lineCount * 2 * 6 * 4);
    lineEbo->Init(lineIndices, MAX_LINE_COUNT * 2 * 4);
    // position
    lineVao->LinkAttrib(*lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // color
    lineVao->LinkAttrib(*lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}
