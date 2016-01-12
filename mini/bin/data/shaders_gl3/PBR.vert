#version 120

uniform mat4    vMatrix;
uniform mat4    projectionMatrix;
uniform mat4    modelViewMatrix;
uniform mat4    modelMatrix;
uniform mat4    modelViewProjectionMatrix;
uniform mat3	normalMatrix;
uniform mat4	viewMatrixInverse;

uniform vec3    uLightPosition;

varying vec4  position;
varying vec2  texcoord;
varying vec4  color;
varying vec3  normal;

out vec3		vNormal;
out vec3		vLightPosition;
out vec3		vPosition;
out vec3		vWsNormal;
out vec3		vEyePosition;
out vec3		vWsPosition;


void main(){
    vec4 worldSpacePosition	= modelMatrix * gl_Vertex;
    vec4 viewSpacePosition	= vMatrix * worldSpacePosition;

    vNormal					= normalMatrix * gl_Normal;
    vLightPosition			= ( vMatrix * vec4( uLightPosition, 1.0 ) ).xyz;
    vPosition				= viewSpacePosition.xyz;
    vWsPosition = worldSpacePosition.xyz;

    vec4 eyeDirViewSpace	= viewSpacePosition - vec4( 0, 0, 0, 1 );
	vEyePosition			= -vec3( viewMatrixInverse * eyeDirViewSpace );
	vWsNormal				= vec3( viewMatrixInverse * vec4( vNormal, 0.0 ) );

    gl_Position				= gl_ProjectionMatrix * viewSpacePosition;
}
