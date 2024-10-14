#pragma once

namespace JoD {
inline const GLchar *shaderImagesFragment =
    R"(
    #version 330 core
    precision mediump float;

    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    in vec2 ex_Pos;
    uniform sampler2D TexUnit;
    uniform float noPixelEffect;

    out vec4 fragColor;

    void main() {
	float r = 0.8;
	float xs = 1600*1.5;
	float ys = 900*1.5;
	int axis = 0;
	vec2 pos = ex_Pos;
	float x,y,rr=r*r,d,w,w0;
	vec2 p=0.5*(vec2(1.0,1.0)+pos);
	p = ex_TexCoord;
	vec4 col=vec4(0.0,0.0,0.0,0.0);
	w0=0.5135/pow(r,0.96);

	if (noPixelEffect == 0.0 && 1.0 == 0.0) {
	    for (d=1.0/xs,x=-r,p.x+=x*d;x<=r;x++,p.x+=d){
		w=w0*exp((-x*x)/(2.0*rr));
		col+=texture(TexUnit,floor(p*300)/300)*w/2;
	    }

	    for (d=1.0/ys,y=-r,p.y+=y*d;y<=r;y++,p.y+=d){
		w=w0*exp((-y*y)/(2.0*rr));
		col+=texture(TexUnit,floor(p*300)/300)*w/2;
	    }
	}
	else {
	    for (d=1.0/xs,x=-r,p.x+=x*d;x<=r;x++,p.x+=d){
		w=w0*exp((-x*x)/(2.0*rr));
		col+=texture(TexUnit,p)*w/2;
	    }

	    for (d=1.0/ys,y=-r,p.y+=y*d;y<=r;y++,p.y+=d){
		w=w0*exp((-y*y)/(2.0*rr));
		col+=texture(TexUnit,p)*w/2;
	    }
	}

	fragColor = col;
    }
)";
}
