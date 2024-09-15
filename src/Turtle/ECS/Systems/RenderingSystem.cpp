#include <glad/glad.h>
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/ECS/Systems/RenderingSystem.h"
#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Components/MeshComponent.h"
#include "Turtle/Rendering/Mesh.h"
#include "Turtle/Rendering/Material.h"
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Rendering/Camera.h"

#include <glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

void Turtle::RenderingSystem::Render()
{
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		MeshComponent& meshComp = _ecs->GetComponent<MeshComponent>(entity);

		// TODO: get model matrix from transform component
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(transformComp.x, transformComp.y, transformComp.z));

		meshComp.Mesh->GetMaterial()->Shader->SetModelMatrix(model);
		meshComp.Mesh->GetMaterial()->Shader->SetVPMatrix(Engine::Camera->GetVPMatrix());
		meshComp.Mesh->Draw();
	}
}
