#pragma once

#include <vector>

#include "Turtle/Rendering/Mesh/SimpleMesh.h"
#include "Turtle/Rendering/Vertex.h"


namespace Turtle
{
	class ArrowMesh : public SimpleMesh
	{
	public:
		//TODO: avoid copying here
		ArrowMesh(glm::vec3 color) : 
			SimpleMesh(
				{
					// position normal color texuv
					// top
					{ glm::vec3(0.0f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.0f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					{ glm::vec3(0.0f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// bottom
					{ glm::vec3(0.0f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.0f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
									  
					{ glm::vec3(0.0f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// left
					{ glm::vec3(0.0f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.0f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					{ glm::vec3(0.0f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// right
					{ glm::vec3(0.0f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.0f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					{ glm::vec3(0.0f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.05f,  0.05f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// arrow top
					{ glm::vec3(0.8f, 0.2f,  -0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.2f,  0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// arrow bottom
					{ glm::vec3(0.8f, -0.2f,  -0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, -0.2f,  0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// arrow left
					{ glm::vec3(0.8f, -0.2f,  -0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.2f,  -0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },

					// arrow right
					{ glm::vec3(0.8f, -0.2f,  0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(0.8f, 0.2f,  0.2f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
					{ glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f), color, glm::vec2() },
				}) {}
	};
}