#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform vec3 viewPos;

// Simple directional light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

// Texture samplers (matching Mesh::BindTextures naming)
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D texture_specular4;

// (normal/height maps are ignored for now, but you can add them later)

vec3 SampleAlbedo()
{
    // Start with white; multiply in textures
    vec3 color = vec3(1.0);

    // Use first diffuse as primary; others can be blended in if needed
    color *= texture(texture_diffuse1, fs_in.TexCoords).rgb;

    // If you want to support multiple diffuse layers, you can blend:
    // color = mix(color, texture(texture_diffuse2, fs_in.TexCoords).rgb, 0.5);

    return color;
}

vec3 SampleSpecular()
{
    // Basic: use first specular map if present, else fall back to white
    vec3 spec = texture(texture_specular1, fs_in.TexCoords).rgb;
    // If no specular texture is bound, this will usually be (0,0,0)
    // and you can override with vec3(1.0) if you want a default.
    return spec;
}

void main()
{
    vec3 albedo = SampleAlbedo();
    vec3 norm   = normalize(fs_in.Normal);

    // Directional light
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    // View direction
    vec3 viewDir    = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float shininess    = 32.0;
    float specStrength = 1.0;
    float spec         = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 specularMap = SampleSpecular();

    vec3 ambient  = dirLight.ambient  * albedo;
    vec3 diffuse  = dirLight.diffuse  * diff * albedo;
    vec3 specular = dirLight.specular * specStrength * spec * specularMap;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
