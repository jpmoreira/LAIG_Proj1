uniform float normScale;
uniform sampler2D maskImage;
uniform sampler2D mainImage;
uniform sampler2D heightImage;
uniform float time;					//well...
uniform int wind;					//user input that messes with the flag
varying vec4 colorByHeight;			//
const float PI = 3.14159265;		//
const float height = 0.1;			//the max y coordinate offset
const float freqWindRatio = 0.3;	//like the example, for wind=10 it has 3 waves
const float windAttenuation = 1;	//values between 0.0 and 1.0
void main()
{
    
    
    vec4 colorOfMask=texture2D(maskImage, gl_MultiTexCoord2.st);
    vec4 colorOfHeight=texture2D(maskImage, gl_MultiTexCoord1.st);
    vec4 colorOfMain=texture2D(mainImage,gl_MultiTexCoord0.st);
    
    
    
    if (colorOfMask.r<0.2) {//black part
        
    }
    
    
    
    vec4 offset=vec4(0.0,0.0,0.0,0.0);
    float sin_result = float(0);
    
    if (texture2D(secondImage, vec2(1.0,1.0)-gl_MultiTexCoord0.st).b > 0.5)
        offset.xyz=gl_Normal*normScale*0.1;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    if(wind > 0)
    {
        float tmp_wind = float(wind);
        float freq = tmp_wind * freqWindRatio;
        sin_result = sin(gl_MultiTexCoord0.s*2.0*PI*freq - time*tmp_wind*windAttenuation);
        offset.y = float(offset.y + sin_result*height);
    }
    
    colorByHeight = vec4(sin_result, sin_result, sin_result, 1.0);
    
    gl_Position = gl_ModelViewProjectionMatrix * (vec4(gl_Vertex.xyz+offset.rgb, 1.0));
}