#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    // bone indexes which will influence this vertex
    int   m_BoneIDs[MAX_BONE_INFLUENCE];
    // weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int instanceVBO = 0; // for per-instance model matrices

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = std::move(vertices);
        this->indices  = std::move(indices);
        this->textures = std::move(textures);

        setupMesh();
    }

    // Bind VAO (geometry)
    void Bind() const
    {
        glBindVertexArray(VAO);
    }

    // Bind textures and set sampler uniforms on the shader
    void BindTextures(const Shader &shader) const
    {
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // set sampler to the correct texture unit
            int loc = glGetUniformLocation(shader.ID, (name + number).c_str());
            if (loc != -1)
                glUniform1i(loc, i);

            // bind texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // Reset active texture to 0 (optional)
        glActiveTexture(GL_TEXTURE0);
    }

    unsigned int IndexCount() const { return static_cast<unsigned int>(indices.size()); }

private:
    // initializes all the buffer objects/arrays, including instance attributes
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &instanceVBO); // instance buffer

        glBindVertexArray(VAO);

        // vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices.size() * sizeof(Vertex),
                     vertices.data(),
                     GL_STATIC_DRAW);

        // index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int),
                     indices.data(),
                     GL_STATIC_DRAW);

        // vertex attribute pointers
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // texcoords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        // tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        // bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        // bone IDs
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

        // --- Instance data: mat4 per instance (locations 7,8,9,10) ---
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        // we allocate no storage yet; renderer will fill with glBufferData / glBufferSubData

        constexpr std::size_t vec4Size = sizeof(glm::vec4);
        GLsizei stride = sizeof(glm::mat4);

        // a mat4 is 4 vec4s → 4 attribute locations
        for (int i = 0; i < 4; ++i)
        {
            GLuint attribLocation = 7 + i;
            glEnableVertexAttribArray(attribLocation);
            glVertexAttribPointer(
                attribLocation,
                4,
                GL_FLOAT,
                GL_FALSE,
                stride,
                (void*)(vec4Size * i)
            );
            // this says "advance this attribute per instance, not per vertex"
            glVertexAttribDivisor(attribLocation, 1);
        }

        glBindVertexArray(0);
    }
};

#endif
