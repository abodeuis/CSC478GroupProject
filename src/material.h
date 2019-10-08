//
//  material.h
//  Filereader
//
//  Created by Albert Bode on 10/6/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef material_h
#define material_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <sstream>

typedef enum {
	TEXTURE_TYPE_NONE,  // default
	TEXTURE_TYPE_SPHERE,
	TEXTURE_TYPE_CUBE_TOP,
	TEXTURE_TYPE_CUBE_BOTTOM,
	TEXTURE_TYPE_CUBE_FRONT,
	TEXTURE_TYPE_CUBE_BACK,
	TEXTURE_TYPE_CUBE_LEFT,
	TEXTURE_TYPE_CUBE_RIGHT
} texture_type_t;

typedef struct texture_option_t{
	bool blendu;					// -blendu (default on)
	bool blendv;					// -blendv (default on)
	GLfloat bump_multiplier;		// -bm (for bump maps only, default 1.0)
	GLfloat sharpness;				// -boost (default 1.0?)
	bool color_correction;			// -cc (default false)
	bool clamp;						// -clamp (default false)
	char imfchan;					// -imfchan (the default for bump is 'l' and for decal is 'm')
	GLfloat brightness;				// base_value in -mm option (default 0)
	GLfloat contrast;				// gain_value in -mm option (default 1)
	vec3 origin_offset;				// -o u [v [w]] (default 0 0 0)
	vec3 scale;						// -s u [v [w]] (default 1 1 1)
	vec3 turbulence;				// -t u [v [w]] (default 0 0 0)
	//int texture_resolution;			// -texres resolution (default = -1, meaning off)
	
	std::string to_string(){
		std::stringstream output;
		output << "blendu : " << this->blendu << std::endl;
		output << "blendv : " << this->blendv << std::endl;
		output << "bm : " << this->bump_multiplier << std::endl;
		output << "boost : " << this->sharpness << std::endl;
		output << "cc : " << this->color_correction << std::endl;
		output << "clamp : " << this->clamp << std::endl;
		output << "imfchan : " << this->imfchan << std::endl;
		output << "mm : " << this->brightness << " " << this->contrast << std::endl;
		output << "o : " << this->origin_offset.x << " " << this->origin_offset.y << " " << this->origin_offset.z << std::endl;
		output << "s : " << this->scale.x << " " << this->scale.y << " " << this->scale.z << std::endl;
		output << "t : " << this->turbulence.x << " " << this->turbulence.y << " " << this->turbulence.z << std::endl;
		return output.str();
	}
	
	texture_option_t(){
		this->blendu = true;
		this->blendv = true;
		this->bump_multiplier = 1.0f;
		this->sharpness = 1.0f;
		this->color_correction = false;
		this->clamp = false;
		this->imfchan = '\0';
		this->brightness = 0.0f;
		this->contrast = 1.0;
		this->origin_offset = vec3(0,0,0);
		this->scale = vec3(1,1,1);
		this->turbulence = vec3(0,0,0);
		//this->texture_resolution = -1;
	}
} texture_option_t;

class material {
public:
	// Material name
	std::string name;
	
	// Material color and illumination statements
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 transmittance;
	int illum;
	GLfloat ior;
	GLfloat shininess;
	GLint sharpness;
	GLfloat dissolve;
	
	// Texture map statements
	std::string ambient_filename;
	std::string diffuse_filename;
	std::string specular_filename;
	std::string shininess_filename;
	std::string bump_filename;
	std::string displacement_filename;
	std::string alpha_filename;
	std::string reflection_filename;
	
	texture_option_t ambient_texopt;
	texture_option_t diffuse_texopt;
	texture_option_t specular_texopt;
	texture_option_t shininess_texopt;
	texture_option_t bump_texopt;
	texture_option_t displacement_texopt;
	texture_option_t alpha_texopt;
	texture_option_t reflection_texopt;
	
	// PBR Extension values
	// see http://exocortex.com/blog/extending_wavefront_mtl_to_support_pbr for documentation
	vec3 emission;
	GLfloat roughness;
	GLfloat metallic;
	GLfloat sheen;
	GLfloat clearcoat_thickness;
	GLfloat clearcoat_roughness;
	GLfloat anisotropy;
	GLfloat anisotropy_rotation;
	
	std::string roughness_texname;  // map_Pr
	std::string metallic_texname;   // map_Pm
	std::string sheen_texname;      // map_Ps
	std::string emissive_texname;   // map_Ke
	std::string normal_texname;     // norm. For normal mapping.
	
	texture_option_t roughness_texopt;
	texture_option_t metallic_texopt;
	texture_option_t sheen_texopt;
	texture_option_t emissive_texopt;
	texture_option_t normal_texopt;
	
	std::string to_string(){
		std::stringstream output;
		output << this->name << std::endl;
		output << "Color and Illumination" << std::endl;
		output << "\t Ambient              :" << this->ambient.x << ", " << this->ambient.y << ", " << this->ambient.z << std::endl;
		output << "\t Diffuse              :" << this->diffuse.x << ", " << this->diffuse.y << ", " << this->diffuse.z << std::endl;
		output << "\t Specular             :" << this->specular.x << ", " << this->specular.y << ", " << this->specular.z << std::endl;
		output << "\t Transmittance        :" << this->transmittance.x << ", " << this->transmittance.y << ", " << this->transmittance.z << std::endl;
		output << "\t Illumination         :" << this->illum << std::endl;
		output << "\t Index of Refraction  :" << this->ior << std::endl;
		output << "\t Shininess            :" << this->shininess << std::endl;
		output << "\t Sharpness            :" << this->sharpness << std::endl;
		output << "\t Alpha                :" << this->dissolve << std::endl;
		
		output << "Texture Maps" << std::endl;
		if (!ambient_filename.empty()){
			output << "\tAmbient texture map      : " << this->ambient_filename << std::endl;
		}
		if (!diffuse_filename.empty()){
			output << "\tDiffuse texture map      : " << this->diffuse_filename << std::endl;
		}
		if (!specular_filename.empty()){
			output << "\tSpecular texture map     : " << this->specular_filename << std::endl;
		}
		if (!shininess_filename.empty()){
			output << "\tShininess texture map    : " << this->shininess_filename << std::endl;
		}
		if (!bump_filename.empty()){
			output << "\tBump texture map         : " << this->bump_filename << std::endl;
		}
		if (!displacement_filename.empty()){
			output << "\tDisplacement texture map : " << this->displacement_filename << std::endl;
		}
		if (!alpha_filename.empty()){
			output << "\tAlpha texture map        : " << this->alpha_filename << std::endl;
		}
		if (!reflection_filename.empty()){
			output << "\tReflection texture map   : " << this->reflection_filename << std::endl;
		}
		return output.str();
	}
	
	material(){
		this->name = "Untitled_Material";
	}
	
};

#endif /* material_h */
