#version 150

//there's no rules about the prefixes but they do help
//keep track of things
uniform mat4 u_modelMatrix;
uniform mat4 u_projMatrix;

uniform vec3 lightPos;

in vec4 vs_normal;
in vec4 vs_position;
in vec4 vs_color;

out vec4 fs_normal;
out vec4 fs_position;
out vec4 fs_light_vector;
out vec4 fs_light_position;
out vec4 fs_color;
out mat4 mModel;

void main() { 
    
    // Set the color and normal as just the input from the VBOs,
	// they only get interesting after they've been interpolated by the rasterizer
    
	fs_color = vs_color;
    
	//fs_normal = (transpose(inverse(u_modelMatrix)) * vs_normal).xyz;
	fs_normal = (u_modelMatrix * vs_normal);
	fs_position = vs_position;
	mModel = u_modelMatrix;
    
    // Set up our vector for the light
    vec4 lightPos2 = vec4(lightPos.x,lightPos.y,lightPos.z,1.0);
	fs_light_position = lightPos2;
    fs_light_vector = -(lightPos2 - (u_modelMatrix * vs_position));

	//fs_color = fs_light_vector;

	//built-in things to pass down the pipeline
    gl_Position = u_projMatrix * u_modelMatrix * vs_position;
}