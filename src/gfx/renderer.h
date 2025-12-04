#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "model.h"
#include "mesh.h"
#include "shader.h"

class Renderer
{
public:
    static void BeginScene(const glm::mat4& view, const glm::mat4& projection);

    // submit a whole model (all its meshes share the same model matrix)
    static void Submit(Model* model, Shader* shader, const glm::mat4& modelMatrix);

    // submit a single mesh (if you want more direct control)
    static void SubmitMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

    static void EndScene();

private:
    struct InstanceData {
        glm::mat4 model;
    };

    struct BatchKey {
        Mesh*   mesh;
        Shader* shader;

        bool operator<(const BatchKey& other) const
        {
            if (shader != other.shader)
                return shader < other.shader;
            return mesh < other.mesh;
        }
    };

    struct SceneData {
        glm::mat4 View;
        glm::mat4 Projection;
    };

    static SceneData s_SceneData;
    static std::map<BatchKey, std::vector<InstanceData>> s_Batches;

    static void Flush();
};

#endif