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

	GLint cur_mesh_id;
	GLint cur_material_id;
	
	// Each asset must have a unique name, and each asset type has its own namespace
	std::map<std::string, int> mesh_id_map;
	std::map<std::string, int> material_id_map;
	std::map<std::string, int> texture_id_map;
	
	std::map<int, mesh*> meshes;
	std::map<int, material*> materials;
	std::map<int, texture2D_t*> textures;
	
	
	// Functions
private:
	void load_primitives();
	GLint next_mesh_id();
	GLint next_material_id();
	GLint next_texture_id();
	
public:
	unsigned long get_allocated_size(){return allocatedMemory;}
	
	bool change_mesh_asset_name(std::string cur_name, std::string new_name);
	bool change_material_asset_name(std::string cur_name, std::string new_name);
	bool change_texture_asset_name(std::string cur_name, std::string new_name);
	
	bool add_mesh_asset(const char *filename, std::string asset_name);
	bool add_material_asset(const char *filename, std::string asset_name);
	bool add_texture_asset(const char *filename, std::string asset_name);
	
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
