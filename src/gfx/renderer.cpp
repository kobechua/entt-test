#include "renderer.h"
#include <algorithm>

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::queue(Mesh* mesh, const glm::mat4& model = glm::mat4(1.0f))
{
    auto it = std::find_if(r_bucket.begin(), r_bucket.end(),
            [&](const Renderable& b) {
                return b.mesh == mesh;
            });

    if (it == r_bucket.end()) {
        Renderable renderable;
        renderable.mesh = mesh;
        r_bucket.push_back(std::move(renderable));
        it = std::prev(r_bucket.end());
    }

    InstanceData id;
    id.model = model;
    it->instances.push_back(id);
    
}

void Renderer::draw(const glm::mat4& viewProj)
{    
    for (auto& bucket : r_bucket) {
        Shader* shader = bucket.material->shader;
        shader->use();
        shader->SetMat4("u_ViewProjection", viewProj);

        // bind material textures, uniforms
        bucket.material->Bind();

        // bind VAO (already configured with instance attributes)
        bucket.mesh->vertexArray->Bind();

        // upload instance data to instanceVBO
        GLuint instanceVBO = bucket.mesh->instanceVBO; // stored in Mesh
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     bucket.instances.size() * sizeof(InstanceData),
                     bucket.instances.data(),
                     GL_DYNAMIC_DRAW);

        glDrawElementsInstanced(
            GL_TRIANGLES,
            bucket.mesh->indexCount,
            GL_UNSIGNED_INT,
            nullptr,
            static_cast<GLsizei>(bucket.instances.size())
        );
    }

    m_Buckets.clear();
}
