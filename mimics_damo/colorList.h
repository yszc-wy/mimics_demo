#pragma once
#include "qstring.h"
struct ColorList
{
	QString colorName;
	int color[3];
};

ColorList colorList[16] = {
	{"Green",{0,255,0}},
	{"Yellow",{255,255,0}},
	{"Cyan",{0,255,255}},
	{"Fuchsia",{255,0,255}},
	{"Orange",{255,165,0}},
	{"Red",{255,0,0}},
	{"Blue",{0,0,255}},
	{"Magenta",{255,169,255}},
	{"GreenYellow",{ 173,255,47 }},
	{"Purple",{160,32,240}},
	{"Violet",{238,130,238}},
	{"Pink",{ 255,192,203 }},
	{"Turquoise",{ 0,229,238 }},
	{"Peach",{ 255,218,185 }},
	{"PaleGreen",{ 154,255,154 }},
	{"SkyBlue",{ 135,206,235 }}
};
int colorID = 0;