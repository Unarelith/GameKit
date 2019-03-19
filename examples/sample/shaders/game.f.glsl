#version 120

varying vec2 v_texCoord;
varying vec4 v_color;

uniform sampler2D u_tex;
uniform int u_paletteID;

vec4 colorInPalette(int paletteID, vec4 color);

void main() {
	vec4 color = v_color;
	if (v_texCoord.x != -1 && v_texCoord.y != -1) {
		vec4 texColor = texture2D(u_tex, v_texCoord);
		color = vec4(texColor.rgb - (1 - color.rgb), min(texColor.a, color.a));
	}

	gl_FragColor = color;
}

// vim:ft=glsl
