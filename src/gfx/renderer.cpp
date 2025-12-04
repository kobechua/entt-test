// renderer.cpp
#include "renderer.h"

#include <glad/glad.h>

// static definitions
Renderer::SceneData Renderer::s_SceneData{};
std::map<Renderer::BatchKey, std::vector<Renderer::InstanceData>> Renderer::s_Batches;

void Renderer::BeginScene(const glm::mat4& view, const glm::mat4& projection)
{
    s_SceneData.View       = view;
    s_SceneData.Projection = projection;
    s_Batches.clear();
}

void Renderer::Submit(Model* model, Shader* shader, const glm::mat4& modelMatrix)
{
    // Every mesh in the model uses the same model matrix for now (like LearnOpenGL)
    const auto& meshes = model->GetMeshes();
    for (const auto& m : meshes)
    {
        SubmitMesh(const_cast<Mesh*>(&m), shader, modelMatrix);
    }
}

void Renderer::SubmitMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    BatchKey key{ mesh, shader };
    InstanceData instance{ modelMatrix };
    s_Batches[key].push_back(instance);
}

void Renderer::EndScene()
{
    Flush();
    s_Batches.clear();
}

void Renderer::Flush()
{
    Shader* lastShader = nullptr;

    for (auto& pair : s_Batches)
    {
        BatchKey key         = pair.first;
        auto&    instances   = pair.second;
        Mesh*    mesh        = key.mesh;
        Shader*  shader      = key.shader;

        if (instances.empty())
            continue;

        // bind shader only if changed
        if (shader != lastShader)
        {
            shader->use(); // or shader->Use()
            shader->setMat4("view",       s_SceneData.View);
            shader->setMat4("projection", s_SceneData.Projection);
            lastShader = shader;
        }

        // bind mesh geometry + textures
        mesh->Bind();
        mesh->BindTextures(*shader);

        // upload instance data to instanceVBO
        glBindBuffer(GL_ARRAY_BUFFER, mesh->instanceVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     instances.size() * sizeof(InstanceData),
                     instances.data(),
                     GL_DYNAMIC_DRAW);

        // draw all instances of this mesh in one call
        glDrawElementsInstanced(
            GL_TRIANGLES,
            mesh->IndexCount(),
            GL_UNSIGNED_INT,
            0,
            static_cast<GLsizei>(instances.size())
        );
    }

    // unbind VAO
    glBindVertexArray(0);
}
