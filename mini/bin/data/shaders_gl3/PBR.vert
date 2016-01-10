#version 120

uniform mat4    vMatrix;
uniform mat4    projectionMatrix;
uniform mat4    modelViewMatrix;
uniform mat4    modelMatrix;
uniform mat4    modelViewProjectionMatrix;

uniform vec3    uLightPosition;

varying vec4  position;
varying vec2  texcoord;
varying vec4  color;
varying vec3  normal;

out vec3		vNormal;
out vec3		vLightPosition;
out vec3		vPosition;


void main(){
    vec4 worldSpacePosition	= modelMatrix * gl_Vertex;
    vec4 viewSpacePosition	= vMatrix * worldSpacePosition;

    vNormal					= gl_NormalMatrix * gl_Normal;
    vLightPosition			= ( vMatrix * vec4( uLightPosition, 1.0 ) ).xyz;
    vPosition				= worldSpacePosition.xyz;

    gl_Position				= gl_ProjectionMatrix * viewSpacePosition;
}
