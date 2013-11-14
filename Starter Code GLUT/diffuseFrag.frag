#version 150 

//these are the interpolated values out of the rasterizer, so you can't know
//their specific values without knowing the vertices that contributed to them
uniform vec3 ambient;
in vec4 fs_normal;
in vec4 fs_position;
in vec4 fs_light_vector;
in vec4 fs_color;
in vec4 fs_light_position;
in mat4 mModel;

uniform vec4 vEyePosition;
uniform vec3 vSpecularMaterial;

out vec4 out_Color;

vec4 GetAmbientColor() {
	return vec4( 0.1, 0.1, 0.1, 1.0 );
    //return vAmbientMaterial;
}

vec4 GetSpecularColor() {
    vec4 vTransformedNormal = mModel * vec4(fs_normal);
    vec4 vTransformedVertex = mModel * fs_position;
 
    vec3 vLightDirection = normalize(fs_light_position.xyz - vTransformedVertex.xyz);
    vec3 vCameraDirection = normalize(vEyePosition.xyz - vTransformedVertex.xyz);
	
	// Also, reflect normalized light position by normalized normal 
	vec3 vReflection = normalize(reflect(normalize(vTransformedVertex.xyz - fs_light_position.xyz), normalize(vTransformedNormal.xyz)));

	float specHardness = 1;
    float spec = pow( clamp(dot(normalize(vEyePosition.xyz - vTransformedVertex.xyz), vReflection ),0.0,1.0), specHardness);
 
    return vec4( vSpecularMaterial.r * spec, vSpecularMaterial.g * spec, vSpecularMaterial.b * spec, 1.0 );
}

vec4 GetDiffuseColor() {
	//base colors for materials
	vec4 diffuseColor = fs_color;
    
	//calculate diffuse term and clamp to the range [0, 1]
	float diffuseTerm = clamp(dot(normalize(fs_normal), normalize(fs_light_vector)), 0.0, 1.0);

    return (diffuseColor * (diffuseTerm + .5));
}

void main() {
	vec4 ambientColorA = GetAmbientColor();
	vec4 diffuseColorA = GetDiffuseColor();
	vec4 specularColorA = GetSpecularColor();
	out_Color = (ambientColorA + diffuseColorA + specularColorA);
}