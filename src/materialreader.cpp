//
//  materialreader.cpp
//  Filereader
//
//  Created by Albert Bode on 10/6/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include "materialreader.h"
#include <iostream>

static inline bool parse_OnOff(const char **token, bool default_value = true){
	(*token) += strspn((*token), " \t");		// Trim Whitespace
	bool output = default_value;
	if((0 == strncmp((*token), "on", 2))){
		(*token) += 3;
		output = true;
	}
	else if((0 == strncmp((*token), "off", 3))){
		(*token) += 4;
		output = false;
	}
	return output;
}

bool parseTextureNameAndOption(const char *token, std::string *m_filename, texture_option_t *m_texoption){
	
	while(!IS_NEW_LINE(token[0])){
		token += strspn(token, " \t");						// Trim Whitespace
		
		// Blending in the horizontal direction
		// -blendu on | off
		if (0 == strncmp(token, "-blendu", 7) && IS_SPACE(token[7])){
			token += 8;
			
			m_texoption->blendu = parse_OnOff(&token);
			continue;
		}
		// Blending in the vertical direction on/off
		// -blendv on | off
		if (0 == strncmp(token, "-blendv", 7) && IS_SPACE(token[7])){
			token += 8;
			
			m_texoption->blendv = parse_OnOff(&token);
			continue;
		}
		// Bump map multiplier
		// -bm mult
		if (0 == strncmp(token, "-bm", 3) && IS_SPACE(token[3])){
			token += 4;
			
			m_texoption->bump_multiplier = parse_float(&token);
			continue;
		}
		// Boost increases sharpness of mip-mapped texture files.
		// -boost value
		if (0 == strncmp(token, "-boost", 6) && IS_SPACE(token[6])){
			token += 7;
			
			m_texoption->sharpness = parse_float(&token);
			continue;
		}
		// Color Correction
		// -cc on | off
		if (0 == strncmp(token, "-cc", 3) && IS_SPACE(token[3])){
			token += 4;
			
			m_texoption->color_correction = parse_OnOff(&token);
			continue;
		}
		// Clamp? ¯\_(ツ)_/¯, something to do with uv values range
		// -clamp on | off
		if (0 == strncmp(token, "-clamp", 6) && IS_SPACE(token[6])){
			token += 7;
			
			m_texoption->clamp = parse_OnOff(&token);
			continue;
		}
		// Specifies which channel to apply the scalar texture to
		// -imfchan r | g | b | m | l | z
		if (0 == strncmp(token, "-imfchan", 8) && IS_SPACE(token[8])){
			token += 9;
			
			token += strspn(token, " \t");				// Trim Whitespace
			m_texoption->imfchan = token[0];
			token += 1;
			continue;
		}
		// Modifies range of color values such that [base .. gain] is the valid values.
		// -mm base gain
		if (0 == strncmp(token, "-mm", 3) && IS_SPACE(token[3])){
			token += 4;
			
			m_texoption->brightness = parse_float(&token);
			m_texoption->contrast = parse_float(&token);
			continue;
		}
		// Offset texture map
		// -o u v w
		if (0 == strncmp(token, "-o", 2) && IS_SPACE(token[2])){
			token += 3;
			
			m_texoption->origin_offset = parse_float3(&token);
			continue;
		}
		// Scale texture map
		// -s u v w
		if (0 == strncmp(token, "-s", 2) && IS_SPACE(token[2])){
			token += 3;
			
			m_texoption->scale = parse_float3(&token);
			continue;
		}
		// Turbulence, adds varience to texture map to reduce effects of tiling
		// -t u v w
		if (0 == strncmp(token, "-t", 2) && IS_SPACE(token[2])){
			token += 3;
			
			m_texoption->turbulence = parse_float3(&token);
			continue;
		}
		// Texture Resolution, specifies the resolution of texture
		// -texres resolution
		/*
		if (0 == strncmp(token, "-texres", 7) && IS_SPACE(token[7])){
			token += 8;
			
			m_texoption->texture_resolution = ?
			continue;
		}
		 */
		// Filename
		else {
			// Make sure not an argument
			if(token[0] != '-'){
				token += strspn(token, " \t");				// Trim Whitespace
				std::string convert(token);
				(*m_filename) = convert;
				token += m_filename->length();
			}
			continue;
		}
	}
	
	
	return true;
};

bool mtlReader::parse_file(const char *filename, material *m) {
	std::string mtl_name = "A filename";
	
	std::ifstream in(filename);
	
	if (!in) {
		std::string error_msg = "Problem opening : ";
		error_msg += filename;
		log->log_msg(LOG_MSG_ERROR, error_msg);
		return false;
	}
	
	std::string status_msg = "Started reading : ";
	status_msg += filename;
	log->log_msg(LOG_MSG_STATUS, status_msg);
	
	// Read File
	std::string linebuf;
	while(in.peek() != -1) {
		safeGetline(in, linebuf);
		
		// Empty line
		if(linebuf.empty()) continue;
		
		const char *token = linebuf.c_str();
		token += strspn(token, " \t");
		
		// Skip line
		if(token[0] == '\0') continue;
		if(token[0] == '#') continue;
		
		/* ### Material name statement ### */
		// newmtl : name
		if(0 == strncmp(token,"newmtl", 6) && token[6]){
			token += 7;
			
			token += strspn(token, " \t");				// Trim Whitespace
			std::string convert(token);
			m->name = convert;
			token += m->name.length();
			continue;
		}
		
		/* ### Material color and illumination statements ### */
		// Ambient
		// Ka : r g b [0.0 .. 1.0]
		// Ka spectral : file.rfl factor
		// Ka : xyz x y z
		if(token[0] == 'K' && token[1] == 'a' && IS_SPACE(token[2])){
			token += 3;
			
			m->ambient = parse_float3(&token);
			continue;
		}
		
		// Diffuse
		// Kd : r g b [0.0 .. 1.0]
		// Kd spectral : file.rfl factor
		// Kd : xyz x y z
		if(token[0] == 'K' && token[1] == 'd' && IS_SPACE(token[2])){
			token += 3;
			
			m->diffuse = parse_float3(&token);
			continue;
		}
		
		// Specular
		// Ks : r g b [0.0 .. 1.0]
		// Ks spectral : file.rfl factor
		// Ks : xyz x y z
		if(token[0] == 'K' && token[1] == 's' && IS_SPACE(token[2])){
			token += 3;
			
			m->specular = parse_float3(&token);
			continue;
		}
		
		// Transmittance
		// Tf : r g b [0.0 .. 1.0]
		// Tf spectral : file.rfl factor
		// Tf : xyz x y z
		if((token[0] == 'K' && token[1] == 't' && IS_SPACE(token[2])) ||
		   (token[0] == 'T' && token[1] == 'f' && IS_SPACE(token[2]))){
			token += 3;
			
			m->transmittance = parse_float3(&token);
			continue;
		}
		
		// Illumination model
		// illum : illum_#
		/* 0		Color on and Ambient off
		 1		Color on and Ambient on
		 2		Highlight on
		 3		Reflection on and Ray trace on
		 4		Transparency: Glass on
		 Reflection: Ray trace on
		 5		Reflection: Fresnel on and Ray trace on
		 6		Transparency: Refraction on
		 Reflection: Fresnel off and Ray trace on
		 7		Transparency: Refraction on
		 Reflection: Fresnel on and Ray trace on
		 8		Reflection on and Ray trace off
		 9		Transparency: Glass on
		 Reflection: Ray trace off
		 10		Casts shadows onto invisible surfaces
		 */
		if(0 == strncmp(token, "illum", 5) && IS_SPACE(token[5])){
			token += 6;
			
			m->illum = parse_int(&token);
			continue;
		}
		
		// Dissolve
		// d : factor [0 .. 1.0]
		// d -halo : factor
		if (token[0] == 'd' && IS_SPACE(token[1])){
			token += 2;
			
			m->dissolve = parse_float(&token);
			continue;
		}
		
		// Shininess
		// Ns : exponent [0 .. 1000]
		if(token[0] == 'N' && token[1] == 's' && IS_SPACE(token[2])){
			token += 3;
			
			m->shininess = parse_float(&token);
			continue;
		}
		
		// Sharpness
		// sharpness : [0 .. 100]
		if(0 == strncmp(token, "sharpness", 9) && IS_SPACE(token[9])){
			token += 10;
			
			m->sharpness = parse_int(&token);
			continue;
		}
		
		// Index of refraction
		// Ni : optical_density [0.001 .. 10]
		if(token[0] == 'N' && token[1] == 'i' && IS_SPACE(token[2])){
			token += 3;
			
			m->ior = parse_float(&token);
			continue;
		}
		
		/* ### Texture map statements ### */
		/* Options for texture maps
		 -blendu on | off
		 -blendv on | off
		 -cc on | off
		 -clamp on | off
		 -mm base gain
		 -o u v w
		 -s u v w
		 -t u v w
		 -texres value
		 */
		
		// Ambient color map
		// map_Ka -options arg filename
		if (0 == strncmp(token, "map_Ka", 6) && IS_SPACE(token[6])){
			token +=7;
			
			parseTextureNameAndOption(token, &(m->ambient_filename), &(m->ambient_texopt));
			continue;
		}
		
		// Diffuse color map
		// map_Kd -options arg filename
		if (0 == strncmp(token, "map_Kd", 6) && IS_SPACE(token[6])){
			token +=7;
			
			parseTextureNameAndOption(token, &(m->diffuse_filename), &(m->diffuse_texopt));
			continue;
		}
		
		// Specular color map
		// map_Ks -options arg filename
		if (0 == strncmp(token, "map_Ks", 6) && IS_SPACE(token[6])){
			token +=7;
			
			parseTextureNameAndOption(token, &(m->specular_filename), &(m->specular_texopt));
			continue;
		}
		
		// Shineness scaler map
		// map_Ns -options arg filename
		if (0 == strncmp(token, "map_Ns", 6) && IS_SPACE(token[6])){
			token +=7;
			
			parseTextureNameAndOption(token, &(m->shininess_filename), &(m->shininess_texopt));
			continue;
		}
		
		// Dissolve scaler map
		// map_d -options arg filename
		if (0 == strncmp(token, "map_d", 6) && IS_SPACE(token[6])){
			token +=7;
			
			parseTextureNameAndOption(token, &(m->alpha_filename), &(m->alpha_texopt));
			continue;
		}
		
		// Bump map
		// map_bump -options arg filename
		// map_Bump -options arg filename
		// bump -options arg filename
		if ((0 == strncmp(token, "map_bump", 7) && IS_SPACE(token[7])) ||
			(0 == strncmp(token, "map_Bump", 7) && IS_SPACE(token[7]))){
			token +=8;
			
			parseTextureNameAndOption(token, &(m->bump_filename), &(m->bump_texopt));
			continue;
		}
		if (0 == strncmp(token, "bump", 4) && IS_SPACE(token[4])){
			token +=5;
			
			parseTextureNameAndOption(token, &(m->bump_filename), &(m->bump_texopt));
			continue;
		}
		
		// Deformation scaler map
		// disp -options arg filename
		if (0 == strncmp(token, "disp", 4) && IS_SPACE(token[4])){
			token +=5;
			
			parseTextureNameAndOption(token, &(m->displacement_filename), &(m->displacement_texopt));
			continue;
		}
		
		/* ################# PBR Extension elements ################# */
		/* I'm reading these in for right now just to be safe, but not
		   sure if we will actually implement Physically Based Rendering.
		 */
		/* PBR: Material color and illumination statements */
		// Emission
		// Ke :
		if(token[0] == 'K' && token[1] == 'e' && IS_SPACE(token[2])){
			token += 3;
			
			m->emission = parse_float3(&token);
			continue;
		}
		
		// Roughness
		// Pr : [0.0 .. 1.0]
		if(token[0] == 'P' && token[1] == 'r' && IS_SPACE(token[2])){
			token += 3;
			
			m->roughness = parse_float(&token);
			continue;
		}
		
		// Metallic
		// Pm : [0.0 .. 1.0]
		if(token[0] == 'P' && token[1] == 'm' && IS_SPACE(token[2])){
			token += 3;
			
			m->metallic = parse_float(&token);
			continue;
		}
		
		// Sheen
		// Ps : [0.0 .. 1.0]
		if(token[0] == 'P' && token[1] == 's' && IS_SPACE(token[2])){
			token += 3;
			
			m->sheen = parse_float(&token);
			continue;
		}
		
		// Clearcoat thickness
		// Pc :
		if(token[0] == 'P' && token[1] == 'c' && IS_SPACE(token[3])){
			token += 3;
			
			m->clearcoat_thickness = parse_float(&token);
			continue;
		}
		
		// Clearcoat roughness
		// Pcr :
		if(token[0] == 'P' && token[1] == 'c' && token[2] == 'r' && IS_SPACE(token[3])){
			token += 4;
			
			m->clearcoat_roughness = parse_float(&token);
			continue;
		}
		
		// Anisotropy
		// aniso :
		if(0 == strncmp(token, "aniso", 5) && IS_SPACE(token[5])){
			token += 6;
			
			m->anisotropy = parse_int(&token);
			continue;
		}
		
		// Anisotropy rotation
		// anisor :
		if(0 == strncmp(token, "anisor", 6) && IS_SPACE(token[6])){
			token += 7;
			
			m->anisotropy_rotation = parse_int(&token);
			continue;
		}
		
		/* PBR: ### Texture map statements ### */
		
		// Emission color map
		// map_Ke -options arg filename
		if (0 == strncmp(token, "map_Ke", 5) && IS_SPACE(token[5])){
			token +=6;
			
			parseTextureNameAndOption(token, &(m->emissive_texname), &(m->emissive_texopt));
			continue;
		}
		
		// Roughness scaler map
		// map_Pr -options arg filename
		if (0 == strncmp(token, "map_Pr", 5) && IS_SPACE(token[5])){
			token +=6;
			
			parseTextureNameAndOption(token, &(m->roughness_texname), &(m->roughness_texopt));
			continue;
		}
		
		// Metalic scaler map
		// map_Pm -options arg filename
		if (0 == strncmp(token, "map_Pm", 5) && IS_SPACE(token[5])){
			token +=6;
			
			parseTextureNameAndOption(token, &(m->metallic_texname), &(m->metallic_texopt));
			continue;
		}
		
		// Sheen scaler map
		// map_Ps -options arg filename
		if (0 == strncmp(token, "map_Ps", 5) && IS_SPACE(token[5])){
			token +=6;
			
			parseTextureNameAndOption(token, &(m->sheen_texname), &(m->sheen_texopt));
			continue;
		}
		
		// Normal scaler map
		// norm -options arg filename
		if (0 == strncmp(token, "norm", 4) && IS_SPACE(token[4])){
			token +=5;
			
			parseTextureNameAndOption(token, &(m->normal_texname), &(m->normal_texopt));
			continue;
		}
		
	}
	
	return true;
}