#include <glm/glm.hpp>

#include "Core/Coordinator.hpp"
#include "Components/Transform.hpp"
#include "Components/MeshRenderer.hpp"
#include "Systems/RenderSystem.hpp"

Coordinator coordinator;
bool quittingGame = false;

int main()
{
    coordinator.Init();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<MeshRenderer>();

    auto renderSystem = coordinator.RegisterSystem<RenderSystem>();
    Signature signature;
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<MeshRenderer>());
	coordinator.SetSystemSignature<RenderSystem>(signature);
    renderSystem -> Init();

    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent(
        entity,
        Transform{
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        }
    );

    coordinator.AddComponent(
        entity,
        MeshRenderer{
            Shader("resources/shaders/sh1.vs", "resources/shaders/sh1.fs"),
            Texture("resources/example_textures/container.jpg")
        }
    );

    while (!quittingGame)
    {
        renderSystem -> Update(0);
    }

    renderSystem -> Finish();

}

void Quit()
{
    quittingGame = true;
}