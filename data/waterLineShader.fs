uniform sampler2D maskImage;		//front texture
uniform sampler2D mainImage;		//background texture
varying vec4 colorByHeight;			//
const float colorByHeightPercent = 0.2;





void main()
{
    vec4 color=texture2D(baseImage, gl_TexCoord[0].st);
    vec4 filter=texture2D(secondImage, gl_TexCoord[0].st);
    
    //when the blue color of secondImage is > .5, set color as orange
    if (filter.b > 0.5)
        color=vec4(0.52,0.18,0.11,1.0);
    
    gl_FragColor = color * (1.0-colorByHeightPercent) +colorByHeight * colorByHeightPercent;
}
