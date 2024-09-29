#pragma once
#include <memory>
#include <string>

namespace Turtle
{
    struct Material;
    class Shader;
    class Mesh;
    class Texture;
    
    class AssetsRegistry
    {
    public:
        AssetsRegistry() {}
        
        void Init();
        void Cleanup();

        std::shared_ptr<Shader> PbrShader;
        std::shared_ptr<Shader> DebugShader;
        std::shared_ptr<Texture> MeshDiffuseMap;
        std::shared_ptr<Mesh> Mesh;
        std::shared_ptr<Material> MeshMaterial;
        std::shared_ptr<Material> DebugMaterial;
    };
}