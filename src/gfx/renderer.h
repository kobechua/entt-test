#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "mesh.h"

#include <vector>

struct InstanceData {
    glm::mat4 model;
};

struct Renderable
{
    Mesh* mesh;
    std::vector<InstanceData> instances;
};

class Renderer
{
    public:
        Renderer();
        ~Renderer();
        void queue(Mesh* mesh, const glm::mat4& model);
        void draw(); //draw everything in r_bucket

    private:
        std::vector<Renderable> r_bucket;
};  

#endif