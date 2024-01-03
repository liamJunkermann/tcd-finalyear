#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


struct Material {
    sampler2D texture_diffuse1;
    float shininess;
}; 

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensityVal;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensityVal;
};

uniform Material material;
//uniform PointLight pointLight;
//uniform SpotLight spotLight;

//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 //viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), //material.shininess);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance /+ /light.quadratic * (distance *distance));
//    // spotlight intensity
//    float theta = dot(lightDir, normalize(-light.direction));
//    float epsilon = light.cutOff - light.outerCutOff;
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, /0.0, /1.0);
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture/(material.texture_diffuse1, /TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture//(material.texture_diffuse1, TexCoords))*light.intensityVal;
//    vec3 specular = light.specular * spec * vec3(texture//(material.texture_specular1, TexCoords))*light.intensityVal;
//    ambient *= attenuation * intensity;
//    diffuse *= attenuation * intensity;
//    specular *= attenuation * intensity;
//    return (ambient + diffuse + specular);
//}

//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 //viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), //material.shininess);
//
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance /+ /light.quadratic *(distance * distance));
//
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture/(material.texture_diffuse1, /TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture//(material.texture_diffuse1, TexCoords))*light.intensityVal;
//    vec3 specular = light.specular * spec * vec3(texture//(material.texture_specular1, TexCoords))*light.intensityVal;
//    
//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;
//
//    return (ambient + diffuse + specular);
//}

void main()
{
    //vec3 color = texture(material.texture_diffuse1, TexCoords).rgb;
    //// ambient
    //vec3 ambient = 0.05 * color;
    //// diffuse
    //vec3 lightDir = normalize(lightPos - FragPos);
    //vec3 normal = normalize(Normal);
    //float diff = max(dot(lightDir, normal), 0.0);
    //vec3 diffuse = diff * color;
    //// specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    //vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    //FragColor = vec4(ambient + diffuse + specular, 1.0);
    //FragColor = vec4(color, 1.0);
    FragColor = texture(material.texture_diffuse1, TexCoords);
}