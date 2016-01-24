#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec3 u_bokehColor;
uniform float u_blurAmount;
uniform sampler2D u_gradient;

void main()
{
    float bokehLight = texture2D(CC_Texture0, vec2(v_texCoord.x * 0.5 + u_blurAmount * 0.5, v_texCoord.y)).r;
//    float bokehBlur = texture2D(CC_Texture0, vec2(v_texCoord.x * 0.5 + 0.5, v_texCoord.y)).r;
//    float bokehLight = mix(bokehSharp, bokehBlur, u_blurAmount);
    vec3 color = texture2D(u_gradient, vec2(1.-bokehLight, 0.)).rgb;
//    vec3 color = vec3(1.);
    
    gl_FragColor = vec4(color, v_fragmentColor.a * bokehLight);
//    gl_FragColor = texture2D(u_gradient, v_texCoord);
//    gl_FragColor = vec4(1., 0., 0., 1.);
}