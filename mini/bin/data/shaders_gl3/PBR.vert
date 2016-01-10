#version 120

uniform mat4    viewMatrix;
uniform mat4    projectionMatrix;
uniform mat4    modelViewMatrix;

uniform vec3    uLightPosition;

varying vec4  position;
varying vec2  texcoord;
varying vec4  color;
varying vec3  normal;

out vec3		vNormal;
out vec3		vLightPosition;
out vec3		vPosition;


void main(){
    vec4 worldSpacePosition	= ftransform();//modelViewMatrix * position;
    vec4 viewSpacePosition	= viewMatrix * worldSpacePosition;

    vNormal					= gl_NormalMatrix * gl_Normal;
    vLightPosition			= uLightPosition;
    vPosition				= worldSpacePosition.xyz;

    gl_Position				= ftransform();//projectionMatrix * viewSpacePosition;
}
