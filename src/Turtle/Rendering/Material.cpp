#include "Turtle/Rendering/Material.h"
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Rendering/Texture.h"

Turtle::Material::Material(Texture* InDiffuseMap, Texture* InSpecularMap, Turtle::Shader& InShader)
    : DiffuseMap(InDiffuseMap), SpecularMap(InSpecularMap), Shader(&InShader)
{
    if (DiffuseMap)
    {
        Shader->AssignDiffuseMap(*DiffuseMap);
    }

    if (SpecularMap)
    {
        Shader->AssignSpecularMap(*SpecularMap);
    }
}

void Turtle::Material::Bind()
{
    if (Shader)
    {
        Shader->Bind();
    }

    if (DiffuseMap)
    {
        DiffuseMap->Bind();
    }

    if (SpecularMap)
    {
        SpecularMap->Bind();
    }
}
