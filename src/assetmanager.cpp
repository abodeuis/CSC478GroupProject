//
//  assetmanager.cpp
//  MergedSystem
//
//  Created by Albert Bode on 10/17/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include "assetmanager.h"

void assetmanager::load_primitives(){
	// Cube
	this->add_mesh_asset("cube.obj", "cube");
	// Cylinder
	
	// Sphere
	
	
}

bool assetmanager::change_mesh_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (meshes[new_name]){
		meshes[new_name] = meshes[cur_name];
		meshes.erase(cur_name);
		return true;
	}
	return false;
}

bool assetmanager::change_material_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (materials[new_name]){
		materials[new_name] = materials[cur_name];
		materials.erase(cur_name);
		return true;
	}
	return false;
}

bool assetmanager::change_texture_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (textures[new_name]){
		textures[new_name] = textures[cur_name];
		textures.erase(cur_name);
		return true;
	}
	return false;
}

void assetmanager::add_mesh_asset(const char *filename, std::string asset_name=""){
	std::string token = filename;
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();
	
	// obj
	if (ext[0] == 'o' && ext[1] == 'b' && ext[2] == 'j'){
		objReader mreader;
		mesh *m = new mesh();
		if (mreader.parse_file(filename, m)){
			allocatedMemory += sizeof(m);
			size_t nbegin = token.find_last_of("/\\")+1;
			size_t nend = token.find_last_of(".");
			std::string default_name = token.substr(nbegin, nend-nbegin);
			/*
				bool q = true;
				// Check if name is in use, if so will increment by one till a valid name is found
				while(q){
			 if(meshes[default_name]){
			 
			 }
				}
				*/
			// When not in use name is found assign it
			if (!asset_name.empty()){
				meshes[asset_name] = m;
			}
			else {
				meshes[default_name] = m;
			}
		}
	}
	
	// stl
	else if (ext[0] == 's' && ext[1] == 't' && ext[2] == 'l'){
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg = "stl file types are not yet implemented, but planned to be supported in a future update";
		log->log_msg(LOG_MSG_ERROR, logmsg);
		/*
			stlReader mreader;
			mesh *m = new mesh();
			if (mreader.parse_file(filename, m)){
		 
			}
			*/
	}
	
	// 3ds
	else if (ext[0] == '3' && ext[1] == 'd' && ext[2] == 's'){
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "3ds file types are not yet implemented, but planned to be supported in a future update";
		log->log_msg(LOG_MSG_ERROR, logmsg);
		/*
			threedsReader mreader;
			mesh *m = new mesh();
			if (mreader.parse_file(filename, m)){
		 
			}
			*/
	}
	
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log->log_msg(LOG_MSG_ERROR, logmsg);
	}
}

void assetmanager::add_material_asset(const char *filename, std::string asset_name){
	std::string token = filename;
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();
	
	// mtl
	if (ext[0] == 'm' && ext[1] == 't' && ext[2] == 'l'){
		mtlReader mreader;
		material *m = new material();
		if (mreader.parse_file(filename, m)){
			allocatedMemory += sizeof(m);
			size_t nbegin = token.find_last_of("/\\")+1;
			size_t nend = token.find_last_of(".");
			std::string default_name = token.substr(nbegin, nend-nbegin);
			/*
			 bool q = true;
			 // Check if name is in use, if so will increment by one till a valid name is found
			 while(q){
			 if(meshes[default_name]){
			 
			 }
			 }
			 */
			// When not in use name is found assign it
			if (!asset_name.empty()){
				materials[asset_name] = m;
			}
			else {
				materials[default_name] = m;
			}
		}
	}
	
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log->log_msg(LOG_MSG_ERROR, logmsg);
	}
}

void assetmanager::add_texture_asset(const char *filename, std::string asset_name){
	std::string token = filename;
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();
	
	// bmp
	if (ext[0] == 'b' && ext[1] == 'm' && ext[2] == 'p' && IS_SPACE(ext[3])){
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "bmp file types are not yet implemented, but planned to be supported in a future update";
		log->log_msg(LOG_MSG_ERROR, logmsg);
		/*
		 threedsReader mreader;
		 mesh *m = new mesh();
		 if (mreader.parse_file(filename, m)){
		 
		 }
		 */
	}
	
	// png
	else if (ext[0] == 'p' && ext[1] == 'n' && ext[2] == 'g'&& IS_SPACE(ext[3])){
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "png file types are not yet implemented, but planned to be supported in a future update";
		log->log_msg(LOG_MSG_ERROR, logmsg);
		/*
		 threedsReader mreader;
		 mesh *m = new mesh();
		 if (mreader.parse_file(filename, m)){
		 
		 }
		 */
	}
	
	/* The sgi format covers .bw, .sgi, .rgb, .int, .rgba and .inta exts */
	else if ((ext[0] == 'b' && ext[1] == 'w' && IS_SPACE(ext[2])) ||
			 (ext[0] == 's' && ext[1] == 'g' && ext[2] == 'i' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'r' && ext[1] == 'g' && ext[2] == 'b' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'i' && ext[1] == 'n' && ext[2] == 't' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'r' && ext[1] == 'g' && ext[2] == 'b' && ext[3] == 'a' && IS_SPACE(ext[4])) ||
			 (ext[0] == 'i' && ext[1] == 'n' && ext[2] == 't' && ext[3] == 'a' && IS_SPACE(ext[4]))){
		sgiReader treader;
		texture2D_t *t = new texture2D_t();
		if (treader.parse_file(filename, t)){
			allocatedMemory += sizeof(t);
			size_t nbegin = token.find_last_of("/\\")+1;
			size_t nend = token.find_last_of(".");
			std::string default_name = token.substr(nbegin, nend-nbegin);
			/*
			 bool q = true;
			 // Check if name is in use, if so will increment by one till a valid name is found
			 while(q){
			 if(meshes[default_name]){
			 
			 }
			 }
			 */
			// When not in use name is found assign it
			if (!asset_name.empty()){
				textures[asset_name] = t;
			}
			else {
				textures[default_name] = t;
			}
		}
	}
	
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log->log_msg(LOG_MSG_ERROR, logmsg);
	}
}

mesh* assetmanager::get_mesh_asset(std::string asset_name){
	if (meshes[asset_name]){
		return meshes[asset_name];
	}
	else {
		std::string log_msg = "Trying to access non-loaded mesh : ";
		log_msg += asset_name;
		log->log_msg(LOG_MSG_WARNING, log_msg);
		return nullptr;
	}
}

material* assetmanager::get_material_asset(std::string asset_name){
	if (materials[asset_name]){
		return materials[asset_name];
	}
	else {
		std::string log_msg = "Trying to access non-loaded material : ";
		log_msg += asset_name;
		log->log_msg(LOG_MSG_WARNING, log_msg);
		return nullptr;
	}
}


texture2D_t* assetmanager::get_texture_asset(std::string asset_name){
	if (textures[asset_name]){
		return textures[asset_name];
	}
	else {
		std::string log_msg = "Trying to access non-loaded texture : ";
		log_msg += asset_name;
		log->log_msg(LOG_MSG_WARNING, log_msg);
		return nullptr;
	}
}