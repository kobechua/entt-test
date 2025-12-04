#version 330 core

// Vertex attributes (must match mesh.h)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 aBoneIDs;
layout (location = 6) in vec4 aWeights;

// Per-instance model matrix (mat4 = 4x vec4 attributes)
layout (location = 7) in mat4 aInstanceModel;

uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
    vec3 FragPos;    // world-space position
    vec3 Normal;     // world-space normal
    vec2 TexCoords;
} vs_out;

void main()
{
    mat4 model = aInstanceModel;

    vec4 worldPos = model * vec4(aPos, 1.0);
    vs_out.FragPos = worldPos.xyz;

    // normal matrix (ignoring bones for now; just use instance model)
    mat3 normalMatrix = mat3(transpose(inverse(model)));
    vs_out.Normal = normalize(normalMatrix * aNormal);

    vs_out.TexCoords = aTexCoords;

    gl_Position = projection * view * worldPos;
}
