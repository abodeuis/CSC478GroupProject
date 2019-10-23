//
//  assetmanager.h
//  MergedSystem
//
//  Created by Albert Bode on 10/17/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef assetmanager_h
#define assetmanager_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <map>
#include <string>

#include "logger.h"
#include "mesh.h"
#include "meshreader.h"
#include "material.h"
#include "materialreader.h"
#include "texture.h"
#include "texturereader.h"

class assetmanager{
private:
	// Attributes
	unsigned long allocatedMemory;
	GLint cur_text_id;
	
	// Each asset must have a unique id, and each asset type has its own idspace
	std::map<std::string, mesh*> meshes;
	std::map<std::string, material*> materials;
	std::map<std::string, texture2D_t*> textures;
	
	
	// Functions
private:
	void load_primitives();
	GLint next_text_id();
	
public:
	unsigned long get_allocated_size(){return allocatedMemory;}
	
	bool change_mesh_asset_name(std::string cur_name, std::string new_name);
	bool change_material_asset_name(std::string cur_name, std::string new_name);
	bool change_texture_asset_name(std::string cur_name, std::string new_name);
	
	void add_mesh_asset(const char *filename, std::string asset_name);
	void add_material_asset(const char *filename, std::string asset_name);
	void add_texture_asset(const char *filename, std::string asset_name);
	
	mesh* get_mesh_asset(std::string asset_name);
	material* get_material_asset(std::string asset_name);
	texture2D_t* get_texture_asset(std::string asset_name);
	
	// Default Constructor
	assetmanager(){
		allocatedMemory = 0;
		
		load_primitives();
	}
};


#endif /* assetmanager_h */
