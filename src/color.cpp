//
//  color.cpp
//  MergedSystem
//
//  Created by Albert Bode on 10/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include "color.h"

void color::HEXtoRGB(const char *hex){
	/// Sets the color to a provided hex number, should only be called by set_color()
	std::string str_hex = hex;
	std::stringstream redss, greenss, bluess;
	int redval, greenval, blueval;
	
	// Convert hex to integer number
	redss << std::hex << str_hex.substr(1,2);
	greenss << std::hex << str_hex.substr(3,2);
	bluess << std::hex << str_hex.substr(5,2);
	
	redss >> redval;
	greenss >> greenval;
	bluess >> blueval;
	
	this->red = GLfloat(redval/256.0f);
	this->green = GLfloat(greenval/256.0f);
	this->blue = GLfloat(blueval/256.0f);
}

/*
 CSS COLOR LIST:
 Color Name              HEX
 Aliceblue           |   #F0F8FF
 Antiquewhite        |   #FAEBD7
 Aqua                |   #00FFFF
 Aquamarine          |   #7FFFD4
 Azure               |   #F0FFFF
 Beige               |   #F5F5DC
 Bisque              |   #FFE4C4
 Black               |   #000000
 BlanchedAlmond      |   #FFEBCD
 Blue                |   #0000FF
 BlueViolet          |   #8A2BE2
 Brown               |   #A52A2A
 BurlyWood           |   #DEB887
 CadetBlue           |   #5F9EA0
 Chartreuse          |   #7FFF00
 Chocolate           |   #D2691E
 Coral               |   #FF7F50
 CornflowerBlue      |   #6495ED
 Cornsilk            |   #FFF8DC
 Crimson             |   #DC143C
 Cyan                |   #00FFFF
 DarkBlue            |   #00008B
 DarkCyan            |   #008B8B
 DarkGoldenRod       |   #B8860B
 DarkGray            |   #A9A9A9
 DarkGrey            |
 DarkGreen           |   #006400
 DarkKhaki           |   #BDB76B
 DarkMagenta         |   #8B008B
 DarkOliveGreen      |   #556B2F
 DarkOrange          |   #FF8C00
 DarkOrchid          |   #9932CC
 DarkRed             |   #8B0000
 DarkSalmon          |   #E9967A
 DarkSeaGreen        |   #8FBC8F
 DarkSlateBlue       |   #483D8B
 DarkSlateGray       |   #2F4F4F
 DarkSlateGrey       |
 DarkTurquoise       |   #00CED1
 DarkViolet          |   #9400D3
 DeepPink            |   #FF1493
 DeepSkyBlue         |   #00BFFF
 DimGray             |   #696969
 DimGrey             |
 DodgerBlue          |   #1E90FF
 FireBrick           |   #B22222
 FloralWhite         |   #FFFAF0
 ForestGreen         |   #228B22
 Fuchsia             |   #FF00FF
 Gainsboro           |   #DCDCDC
 GhostWhite          |   #F8F8FF
 Gold                |   #FFD700
 GoldenRod           |   #DAA520
 Gray                |   #808080
 Grey                |
 Green               |   #008000
 GreenYellow         |   #ADFF2F
 HoneyDew            |   #F0FFF0
 HotPink             |   #FF69B4
 IndianRed           |   #CD5C5C
 Indigo              |   #4B0082
 Ivory               |   #FFFFF0
 Khaki               |   #F0E68C
 Lavender            |   #E6E6FA
 LavenderBlush       |   #FFF0F5
 LawnGreen           |   #7CFC00
 LemonChiffon        |   #FFFACD
 LightBlue           |   #ADD8E6
 LightCoral          |   #F08080
 LightCyan           |   #E0FFFF
 LightGoldenRodYellow|   #FAFAD2
 LightGray           |   #D3D3D3
 LightGrey           |
 LightGreen          |   #90EE90
 LightPink           |   #FFB6C1
 LightSalmon         |   #FFA07A
 LightSeaGreen       |   #20B2AA
 LightSkyBlue        |   #87CEFA
 LightSlateGray      |   #778899
 LightSlateGrey      |
 LightSteelBlue      |   #B0C4DE
 LightYellow         |   #FFFFE0
 Lime                |   #00FF00
 LimeGreen           |   #32CD32
 Linen               |   #FAF0E6
 Magenta             |   #FF00FF
 Maroon              |   #800000
 MediumAquaMarine    |   #66CDAA
 MediumBlue          |   #0000CD
 MediumOrchid        |   #BA55D3
 MediumPurple        |   #9370DB
 MediumSeaGreen      |   #3CB371
 MediumSlateBlue     |   #7B68EE
 MediumSpringGreen   |   #00FA9A
 MediumTurquoise     |   #48D1CC
 MediumVioletRed     |   #C71585
 MidnightBlue        |   #191970
 MintCream           |   #F5FFFA
 MistyRose           |   #FFE4E1
 Moccasin            |   #FFE4B5
 NavajoWhite         |   #FFDEAD
 Navy                |   #000080
 OldLace             |   #FDF5E6
 Olive               |   #808000
 OliveDrab           |   #6B8E23
 Orange              |   #FFA500
 OrangeRed           |   #FF4500
 Orchid              |   #DA70D6
 PaleGoldenRod       |   #EEE8AA
 PaleGreen           |   #98FB98
 PaleTurquoise       |   #AFEEEE
 PaleVioletRed       |   #DB7093
 PapayaWhip          |   #FFEFD5
 PeachPuff           |   #FFDAB9
 Peru                |   #CD853F
 Pink                |   #FFC0CB
 Plum                |   #DDA0DD
 PowderBlue          |   #B0E0E6
 Purple              |   #800080
 RebeccaPurple       |   #663399
 Red                 |   #FF0000
 RosyBrown           |   #BC8F8F
 RoyalBlue           |   #4169E1
 SaddleBrown         |   #8B4513
 Salmon              |   #FA8072
 SandyBrown          |   #F4A460
 SeaGreen            |   #2E8B57
 SeaShell            |   #FFF5EE
 Sienna              |   #A0522D
 Silver              |   #C0C0C0
 SkyBlue             |   #87CEEB
 SlateBlue           |   #6A5ACD
 SlateGray           |   #708090
 SlateGrey           |
 Snow                |   #FFFAFA
 SpringGreen         |   #00FF7F
 SteelBlue           |   #4682B4
 Tan                 |   #D2B48C
 Teal                |   #008080
 Thistle             |   #D8BFD8
 Tomato              |   #FF6347
 Turquoise           |   #40E0D0
 Violet              |   #EE82EE
 Wheat               |   #F5DEB3
 White               |   #FFFFFF
 WhiteSmoke          |   #F5F5F5
 Yellow              |   #FFFF00
 YellowGreen         |   #9ACD32
 */

void color::set_color(const char *color_or_hex, GLfloat alpha=1.0f){
	/// Expects a color name the standard css colors (listed above) or a hex value starting with #
	// Hex value
	if (color_or_hex[0] == '#'){
		this->HEXtoRGB(color_or_hex);
	}
	// Name
	else{
		std::string name = color_or_hex;
		// Convert to lower case
		std::transform(name.begin(), name.end(),name.begin(), [](unsigned char c){ return std::tolower(c);});
		const char *c = name.c_str();
		bool found = false;
		switch(c[0]){
			case 'a':
				if(name == "aliceblue"){
					this->HEXtoRGB("#F0F8FF");
					found = true;
					break;
				}
				if(name == "antiquewhite"){
					this->HEXtoRGB("#FAEBD7");
					found = true;
					break;
				}
				if(name == "aqua"){
					this->HEXtoRGB("#00FFFF");
					found = true;
					break;
				}
				if(name == "aquamarine"){
					this->HEXtoRGB("#7FFFD4");
					found = true;
					break;
				}
				if(name == "azure"){
					this->HEXtoRGB("#F0FFFF");
					found = true;
					break;
				}
				found = true;
				break;
			case 'b':
				if(name == "beige"){
					this->HEXtoRGB("#F5F5DC");
					found = true;
					break;
				}
				if(name == "bisque"){
					this->HEXtoRGB("#FFE4C4");
					found = true;
					break;
				}
				if(name == "black"){
					this->HEXtoRGB("#000000");
					found = true;
					break;
				}
				if(name == "blanchedalmond"){
					this->HEXtoRGB("#FFEBCD");
					found = true;
					break;
				}
				if(name == "blue"){
					this->HEXtoRGB("#0000FF");
					found = true;
					break;
				}
				if(name == "blueviolet"){
					this->HEXtoRGB("#8A2BE2");
					found = true;
					break;
				}
				if(name == "brown"){
					this->HEXtoRGB("#A52A2A");
					found = true;
					break;
				}
				if(name == "blue"){
					this->HEXtoRGB("#DEB887");
					found = true;
					break;
				}
				found = true;
				break;
			case 'c':
				if(name == "cadetblue"){
					this->HEXtoRGB("#5F9EA0");
					found = true;
					break;
				}
				if(name == "chartreuse"){
					this->HEXtoRGB("#7FFF00");
					found = true;
					break;
				}
				if(name == "chocolate"){
					this->HEXtoRGB("#D2691E");
					found = true;
					break;
				}
				if(name == "coral"){
					this->HEXtoRGB("#FF7F50");
					found = true;
					break;
				}
				if(name == "cornflowerblue"){
					this->HEXtoRGB("#6495ED");
					found = true;
					break;
				}
				if(name == "cornsilk"){
					this->HEXtoRGB("#FFF8DC");
					found = true;
					break;
				}
				if(name == "crimson"){
					this->HEXtoRGB("#DC143C");
					found = true;
					break;
				}
				if(name == "cyan"){
					this->HEXtoRGB("#00FFFF");
					found = true;
					break;
				}
			case 'd':
				if(name == "darkblue"){
					this->HEXtoRGB("#00008B");
					found = true;
					break;
				}
				if(name == "darkcyan"){
					this->HEXtoRGB("#008B8B");
					found = true;
					break;
				}
				if(name == "darkgoldenrod"){
					this->HEXtoRGB("#B8860B");
					found = true;
					break;
				}
				if(name == "darkgray" || name == "darkgrey"){
					this->HEXtoRGB("#A9A9A9");
					found = true;
					break;
				}
				if(name == "darkgreen"){
					this->HEXtoRGB("#006400");
					found = true;
					break;
				}
				if(name == "darkkhaki"){
					this->HEXtoRGB("#BDB76B");
					found = true;
					break;
				}
				if(name == "darkmagenta"){
					this->HEXtoRGB("#8B008B");
					found = true;
					break;
				}
				if(name == "darkolivegreen"){
					this->HEXtoRGB("#556B2F");
					found = true;
					break;
				}
				if(name == "darkorange"){
					this->HEXtoRGB("#FF8C00");
					found = true;
					break;
				}
				if(name == "darkorchid"){
					this->HEXtoRGB("#9932CC");
					found = true;
					break;
				}
				if(name == "darkred"){
					this->HEXtoRGB("#8B0000");
					found = true;
					break;
				}
				if(name == "darksalmon"){
					this->HEXtoRGB("#E9967A");
					found = true;
					break;
				}
				if(name == "darkseagreen"){
					this->HEXtoRGB("#8FBC8F");
					found = true;
					break;
				}
				if(name == "darkslateblue"){
					this->HEXtoRGB("#483D8B");
					found = true;
					break;
				}
				if(name == "darkslategray" || name == "darkslategrey"){
					this->HEXtoRGB("#2F4F4F");
					found = true;
					break;
				}
				if(name == "darkturquoise"){
					this->HEXtoRGB("#00CED1");
					found = true;
					break;
				}
				if(name == "darkviolet"){
					this->HEXtoRGB("#9400D3");
					found = true;
					break;
				}
				if(name == "darkpink"){
					this->HEXtoRGB("#FF1493");
					found = true;
					break;
				}
				if(name == "darkskyblue"){
					this->HEXtoRGB("#00BFFF");
					found = true;
					break;
				}
				if(name == "dimgray" || name == "dimgrey"){
					this->HEXtoRGB("#696969");
					found = true;
					break;
				}
				if(name == "dodgerblue"){
					this->HEXtoRGB("#1E90FF");
					found = true;
					break;
				}
			case 'f':
				if(name == "firebrick"){
					this->HEXtoRGB("#B22222");
					found = true;
					break;
				}
				if(name == "floralwhite"){
					this->HEXtoRGB("#FFFAF0");
					found = true;
					break;
				}
				if(name == "forestgreen"){
					this->HEXtoRGB("#228B22");
					found = true;
					break;
				}
				if(name == "fuchsia"){
					this->HEXtoRGB("#FF00FF");
					found = true;
					break;
				}
			case 'g':
				if(name == "gainsboro"){
					this->HEXtoRGB("#DCDCDC");
					found = true;
					break;
				}
				if(name == "ghostwhite"){
					this->HEXtoRGB("#F8F8FF");
					found = true;
					break;
				}
				if(name == "gold"){
					this->HEXtoRGB("#FFD700");
					found = true;
					break;
				}
				if(name == "goldenrod"){
					this->HEXtoRGB("#DAA520");
					found = true;
					break;
				}
				if(name == "gray" || name == "grey"){
					this->HEXtoRGB("#808080");
					found = true;
					break;
				}
				if(name == "green"){
					this->HEXtoRGB("#008000");
					found = true;
					break;
				}
				if(name == "greenyellow"){
					this->HEXtoRGB("#ADFF2F");
					found = true;
					break;
				}
			case 'h':
				if(name == "honeydew"){
					this->HEXtoRGB("#F0FFF0");
					found = true;
					break;
				}
				if(name == "hotpink"){
					this->HEXtoRGB("#FF69B4");
					found = true;
					break;
				}
			case 'i':
				if(name == "indianred"){
					this->HEXtoRGB("#CD5C5C");
					found = true;
					break;
				}
				if(name == "indigo"){
					this->HEXtoRGB("#4B0082");
					found = true;
					break;
				}
				if(name == "ivory"){
					this->HEXtoRGB("#FFFFF0");
					found = true;
					break;
				}
			case 'k':
				if(name == "khaki"){
					this->HEXtoRGB("#F0E68C");
					found = true;
					break;
				}
			case 'l':
				if(name == "lavender"){
					this->HEXtoRGB("#E6E6FA");
					found = true;
					break;
				}
				if(name == "lavenderblush"){
					this->HEXtoRGB("#FFF0F5");
					found = true;
					break;
				}
				if(name == "lawngreen"){
					this->HEXtoRGB("#7CFC00");
					found = true;
					break;
				}
				if(name == "lemonchiffon"){
					this->HEXtoRGB("#FFFACD");
					found = true;
					break;
				}
				if(name == "lightblue"){
					this->HEXtoRGB("#ADD8E6");
					found = true;
					break;
				}
				if(name == "lightcoral"){
					this->HEXtoRGB("#F08080");
					found = true;
					break;
				}
				if(name == "lightcyan"){
					this->HEXtoRGB("#E0FFFF");
					found = true;
					break;
				}
				if(name == "lightgoldenrodyellow"){
					this->HEXtoRGB("#FAFAD2");
					found = true;
					break;
				}
				if(name == "lightgray" || name == "lightgrey"){
					this->HEXtoRGB("#D3D3D3");
					found = true;
					break;
				}
				if(name == "lightgreen"){
					this->HEXtoRGB("#90EE90");
					found = true;
					break;
				}
				if(name == "lightpink"){
					this->HEXtoRGB("#FFB6C1");
					found = true;
					break;
				}
				if(name == "lightsalmon"){
					this->HEXtoRGB("#FFA07A");
					found = true;
					break;
				}
				if(name == "lightseagreen"){
					this->HEXtoRGB("#20B2AA");
					found = true;
					break;
				}
				if(name == "lightskyblue"){
					this->HEXtoRGB("#87CEFA");
					found = true;
					break;
				}
				if(name == "lightslategray" || name == "lightslategrey"){
					this->HEXtoRGB("#778899");
					found = true;
					break;
				}
				if(name == "lightsteelblue"){
					this->HEXtoRGB("#B0C4DE");
					found = true;
					break;
				}
				if(name == "lightyellow"){
					this->HEXtoRGB("#FFFFE0");
					found = true;
					break;
				}
				if(name == "lime"){
					this->HEXtoRGB("#00FF00");
					found = true;
					break;
				}
				if(name == "limegree"){
					this->HEXtoRGB("#32CD32");
					found = true;
					break;
				}
				if(name == "linen"){
					this->HEXtoRGB("#FAF0E6");
					found = true;
					break;
				}
			case 'm':
				if(name == "magenta"){
					this->HEXtoRGB("#FF00FF");
					found = true;
					break;
				}
				if(name == "maroon"){
					this->HEXtoRGB("#800000");
					found = true;
					break;
				}
				if(name == "mediumaquamarine"){
					this->HEXtoRGB("#66CDAA");
					found = true;
					break;
				}
				if(name == "mediumblue"){
					this->HEXtoRGB("#0000CD");
					found = true;
					break;
				}
				if(name == "mediumorchid"){
					this->HEXtoRGB("#BA55D3");
					found = true;
					break;
				}
				if(name == "mediumpurple"){
					this->HEXtoRGB("#9370DB");
					found = true;
					break;
				}
				if(name == "mediumseagreen"){
					this->HEXtoRGB("#3CB371");
					found = true;
					break;
				}
				if(name == "mediumslateblue"){
					this->HEXtoRGB("#7B68EE");
					found = true;
					break;
				}
				if(name == "mediumspringgreen"){
					this->HEXtoRGB("#00FA9A");
					found = true;
					break;
				}
				if(name == "mediumturquoise"){
					this->HEXtoRGB("#48D1CC");
					found = true;
					break;
				}
				if(name == "mediumvioletred"){
					this->HEXtoRGB("#C71585");
					found = true;
					break;
				}
				if(name == "midnightblue"){
					this->HEXtoRGB("#191970");
					found = true;
					break;
				}
				if(name == "mintcream"){
					this->HEXtoRGB("#F5FFFA");
					found = true;
					break;
				}
				if(name == "mistyrose"){
					this->HEXtoRGB("#FFE4E1");
					found = true;
					break;
				}
				if(name == "moccasin"){
					this->HEXtoRGB("#FFE4B5");
					found = true;
					break;
				}
			case 'n':
				if(name == "navajowhite"){
					this->HEXtoRGB("#FFDEAD");
					found = true;
					break;
				}
				if(name == "navy"){
					this->HEXtoRGB("#000080");
					found = true;
					break;
				}
			case 'o':
				if(name == "oldlace"){
					this->HEXtoRGB("#FDF5E6");
					found = true;
					break;
				}
				if(name == "olive"){
					this->HEXtoRGB("#808000");
					found = true;
					break;
				}
				if(name == "olivedrab"){
					this->HEXtoRGB("#6B8E23");
					found = true;
					break;
				}
				if(name == "orange"){
					this->HEXtoRGB("#FFA500");
					found = true;
					break;
				}
				if(name == "orangered"){
					this->HEXtoRGB("#FF4500");
					found = true;
					break;
				}
				if(name == "orchid"){
					this->HEXtoRGB("#DA70D6");
					found = true;
					break;
				}
			case 'p':
				if(name == "palegoldenrod"){
					this->HEXtoRGB("#EEE8AA");
					found = true;
					break;
				}
				if(name == "palegreen"){
					this->HEXtoRGB("#98FB98");
					found = true;
					break;
				}
				if(name == "paleturquoise"){
					this->HEXtoRGB("#AFEEEE");
					found = true;
					break;
				}
				if(name == "palevioletred"){
					this->HEXtoRGB("#DB7093");
					found = true;
					break;
				}
				if(name == "papayawhip"){
					this->HEXtoRGB("#FFEFD5");
					found = true;
					break;
				}
				if(name == "peachpuff"){
					this->HEXtoRGB("#FFDAB9");
					found = true;
					break;
				}
				if(name == "peru"){
					this->HEXtoRGB("#CD853F");
					found = true;
					break;
				}
				if(name == "pink"){
					this->HEXtoRGB("#FFC0CB");
					found = true;
					break;
				}
				if(name == "plum"){
					this->HEXtoRGB("#DDA0DD");
					found = true;
					break;
				}
				if(name == "powderblue"){
					this->HEXtoRGB("#B0E0E6");
					found = true;
					break;
				}
				if(name == "purple"){
					this->HEXtoRGB("#800080");
					found = true;
					break;
				}
			case 'r':
				if(name == "rebeccapurple"){
					this->HEXtoRGB("#663399");
					found = true;
					break;
				}
				if(name == "red"){
					this->HEXtoRGB("#FF0000");
					found = true;
					break;
				}
				if(name == "rosybrown"){
					this->HEXtoRGB("#BC8F8F");
					found = true;
					break;
				}
				if(name == "royalblue"){
					this->HEXtoRGB("#4169E1");
					found = true;
					break;
				}
			case 's':
				if(name == "saddlebrown"){
					this->HEXtoRGB("#8B4513");
					found = true;
					break;
				}
				if(name == "salmon"){
					this->HEXtoRGB("#FA8072");
					found = true;
					break;
				}
				if(name == "sandybrown"){
					this->HEXtoRGB("#F4A460");
					found = true;
					break;
				}
				if(name == "seagreen"){
					this->HEXtoRGB("#2E8B57");
					found = true;
					break;
				}
				if(name == "seashell"){
					this->HEXtoRGB("#FFF5EE");
					found = true;
					break;
				}
				if(name == "sienna"){
					this->HEXtoRGB("#A0522D");
					found = true;
					break;
				}
				if(name == "silver"){
					this->HEXtoRGB("#C0C0C0");
					found = true;
					break;
				}
				if(name == "skyblue"){
					this->HEXtoRGB("#87CEEB");
					found = true;
					break;
				}
				if(name == "slateblue"){
					this->HEXtoRGB("#6A5ACD");
					found = true;
					break;
				}
				if(name == "slategray" || name == "slategrey"){
					this->HEXtoRGB("#708090");
					found = true;
					break;
				}
				if(name == "snow"){
					this->HEXtoRGB("#FFFAFA");
					found = true;
					break;
				}
				if(name == "springgreen"){
					this->HEXtoRGB("#00FF7F");
					found = true;
					break;
				}
				if(name == "steelblue"){
					this->HEXtoRGB("#4682B4");
					found = true;
					break;
				}
			case 't':
				if(name == "tan"){
					this->HEXtoRGB("#D2B48C");
					found = true;
					break;
				}
				if(name == "teal"){
					this->HEXtoRGB("#008080");
					found = true;
					break;
				}
				if(name == "thistle"){
					this->HEXtoRGB("#D8BFD8");
					found = true;
					break;
				}
				if(name == "tomato"){
					this->HEXtoRGB("#FF6347");
					found = true;
					break;
				}
				if(name == "turquoise"){
					this->HEXtoRGB("#40E0D0");
					found = true;
					break;
				}
			case 'v':
				if(name == "violet"){
					this->HEXtoRGB("#EE82EE");
					found = true;
					break;
				}
			case 'w':
				if(name == "wheat"){
					this->HEXtoRGB("#F5DEB3");
					found = true;
					break;
				}
				if(name == "white"){
					this->HEXtoRGB("#FFFFFF");
					found = true;
					break;
				}
				if(name == "whitesmoke"){
					this->HEXtoRGB("#F5F5F5");
					found = true;
					break;
				}
			case 'y':
				if(name == "yellow"){
					this->HEXtoRGB("#FFFF00");
					found = true;
					break;
				}
				if(name == "yellowgreen"){
					this->HEXtoRGB("#9ACD32");
					found = true;
					break;
				}
		}
		if (!found){
			std::string log_msg = name;
			log_msg += " is not in the list of colors; color is unchanged";
			log->log_msg(LOG_MSG_WARNING, log_msg);
		}
	}
	
	// Set alpha in either case
	this->alpha = alpha;
};
