#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;
in vec3 FragmentPosition;

uniform sampler2D bTexture;

uniform vec3 lightingColor;
uniform vec3 lightingPosition;
uniform vec3 cameraPosition;

void main()
{
      // ambient Lighting
      float ambientStrength = 0.25;
      vec3 ambient = ambientStrength * lightingColor;

      // diffuse lighting
      vec3 norm = normalize(Normal);
      vec3 lightDirection = normalize(lightingPosition - FragmentPosition);
      float diff = max(dot(norm, lightDirection), 0.1);
      vec3 diffuse = diff * lightingColor;

      // specular lighting
      float specularStrength = 2;

      vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
      vec3 reflectionDirection = reflect(-lightDirection, norm);
      float spec = pow(max(dot(cameraPosition, reflectionDirection), 0.0), 256);
      vec3 specular = specularStrength * spec * lightingColor;

      vec4 result = vec4((ambient + diffuse + specular), 1)  * texture(bTexture, TexCoords);

      FragColor = result;
}