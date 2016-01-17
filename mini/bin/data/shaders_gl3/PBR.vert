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

uniform vec3 sphere0;
uniform vec3 sphere1;
uniform vec3 sphere2;
uniform vec3 sphere3;
uniform vec3 sphere4;
uniform vec3 sphere5;
uniform vec3 sphere6;
uniform vec3 sphere7;
uniform int uDistort;

out vec3		vNormal;
out vec3		vLightPosition;
out vec3		vPosition;
out vec3		vWsNormal;
out vec3		vEyePosition;
out vec3		vWsPosition;

vec4 distort(vec3 p, vec3 d)
{
    vec4 ret = vec4(p, 0);
    vec3 dp = d - p;
    float len = dp.x * dp.x + dp.y * dp.y + dp.z * dp.z;
    float threshold = 2;
    if( len < threshold * threshold && len > 0.0  ){

        //lets get the distance into 0-1 ranges
        float pct = len / threshold / threshold;

        //this turns our linear 0-1 value into a curved 0-1 value
        //pct *= pct;

        //flip it so the closer we are the greater the repulsion
        //pct = 1.0 - pct;

        //normalize our repulsion vector
        dp /= len;

        //apply the repulsion to our position
        float amp = 0.5;
        ret.x = p.x + dp.x * pct * amp;
        ret.y = p.y + dp.y * pct * amp;
        ret.z = p.z + dp.z * pct * amp;
        ret.w = 1;
    }
    return ret;
}

void main(){
    vec4 worldSpacePosition	= modelMatrix * gl_Vertex;

    if(uDistort > 0)
    {
        vec4 v;
        v = worldSpacePosition;
        v = distort(worldSpacePosition.xyz, sphere0);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere1);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere2);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere3);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere4);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere5);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere6);
        if(v.w == 0)
            v = distort(worldSpacePosition.xyz, sphere7);
        worldSpacePosition.xyz = v.xyz;
    }

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
