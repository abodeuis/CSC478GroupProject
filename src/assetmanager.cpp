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

GLint assetmanager::next_mesh_id(){
	return this->cur_mesh_id++;
}

GLint assetmanager::next_material_id(){
	return this->cur_material_id++;
}

bool assetmanager::add_mesh_asset(const char *filename, std::string asset_name=""){
	std::string token = filename;
	token += "    "; // Add to test if at end of extension and so that if no extension exists ext[] access doesn't fail.
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();

	bool valid_reader = false;
	meshReader *mreader;
	mesh *m = new mesh();

	// obj file
	if (ext[0] == 'o' && ext[1] == 'b' && ext[2] == 'j'){
		mreader = new objReader();
		valid_reader = true;
	}
	// stl
	else if (ext[0] == 's' && ext[1] == 't' && ext[2] == 'l'){
		// stlReader mreader;
		// valid_reader = true;
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg = "stl file types are not yet implemented, but planned to be supported in a future update";
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete m;
		return false;	// Take out once implemented.
	}
	// 3ds
	else if (ext[0] == '3' && ext[1] == 'd' && ext[2] == 's'){
		// threedsReader mreader;
		// valid_reader = true;
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "3ds file types are not yet implemented, but planned to be supported in a future update";
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete m;
		return false;	// Take out once implemented.
	}
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete m;
		return false;
	}

	// Once reader is estiblished
	if (valid_reader){
		// Attempt to read mesh in
		if (mreader->parse_file(filename, m)){
			// Mesh was read succesfully
			allocatedMemory += sizeof(m);

			// Create internal id for the mesh
			GLint id = this->next_mesh_id();

			// Attempt to allocate with user provided name first if applicable
			std::string log_msg;
			bool invalid_name = true;
			if (!asset_name.empty()){
				// Check if user name is not currently in use
				if (this->mesh_id_map.find(asset_name) == this->mesh_id_map.end()){
					// The user name was not found, so okay to set it
					this->mesh_id_map[asset_name] = id;
					this->meshes[id] = m;
					invalid_name = false;
				}
				else {
					// The new name was found, so do not overwrite. Log as user error
					log_msg = "Could not allocate resource ";
					log_msg += filename;
					log_msg += " as ";
					log_msg += asset_name;
					log_msg += " : Name already in use, ";
					// log_msg is sent when valid name is found.
				}
			}
			if (invalid_name) {
				// Try default name till valid one is found
				size_t nbegin = token.find_last_of("/\\")+1;
				size_t nend = token.find_last_of(".");
				std::string default_name = token.substr(nbegin, nend-nbegin);
				std::string test_name = default_name;
				int name_count = 0;
				while(invalid_name){
					if (this->mesh_id_map.find(test_name) == this->mesh_id_map.end()){
						// Valid name
						this->mesh_id_map[asset_name] = id;
						this->meshes[id] = m;
						invalid_name = false;

						// Send log msg that resource was allocated under default name if user name was invalid.
						if (!asset_name.empty()){
							log_msg += "resource named \"";
							log_msg += test_name;
							log_msg += "\" instead";
							log_f->log_msg(LOG_MSG_ERROR, log_msg);
						}
					}
					else {
						// Invalid name, increment and try again
						name_count++;
						test_name = default_name + '_' + std::to_string(name_count);
					}
				}
			}
		}
		// File had issue reading in
		else {
			delete m;
			delete mreader;
			return false;
		}
	}
	delete mreader;
	return true;
}

bool assetmanager::add_material_asset(const char *filename, std::string asset_name=""){
	std::string token = filename;
	token += "    "; // Add to test if at end of extension and so that if no extension exists ext[] access doesn't fail.
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();

	bool valid_reader = false;
	materialReader *mreader;
	material *m = new material();

	// mtl
	if (ext[0] == 'm' && ext[1] == 't' && ext[2] == 'l' && IS_SPACE(ext[3])){
		mreader = new mtlReader();
		valid_reader = true;
	}
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete m;
		return false;
	}

	// Once reader is estiblished
	if (valid_reader){
		// Attempt to read material in
		if (mreader->parse_file(filename, m)){
			// Material was read succesfully
			allocatedMemory += sizeof(m);

			// Create internal id for the material
			GLint id = this->next_material_id();

			// Attempt to allocate with user provided name first if applicable
			std::string log_msg;
			bool invalid_name = true;
			if (!asset_name.empty()){
				// Check if user name is not currently in use
				if (this->material_id_map.find(asset_name) == this->material_id_map.end()){
					// The user name was not found, so okay to set it
					this->material_id_map[asset_name] = id;
					this->materials[id] = m;
					invalid_name = false;
				}
				else {
					// The new name was found, so do not overwrite. Log as user error
					log_msg = "Could not allocate resource ";
					log_msg += filename;
					log_msg += " as ";
					log_msg += asset_name;
					log_msg += " : Name already in use, ";
					// log_msg is sent when valid name is found.
				}
			}
			if (invalid_name) {
				// Try default name till valid one is found
				size_t nbegin = token.find_last_of("/\\")+1;
				size_t nend = token.find_last_of(".");
				std::string default_name = token.substr(nbegin, nend-nbegin);
				std::string test_name = default_name;
				int name_count = 0;
				while(invalid_name){
					if (this->material_id_map.find(test_name) == this->material_id_map.end()){
						// Valid name
						this->material_id_map[asset_name] = id;
						this->materials[id] = m;
						invalid_name = false;

						// Send log msg that resource was allocated under default name if user name was invalid.
						if (!asset_name.empty()){
							log_msg += "resource named \"";
							log_msg += test_name;
							log_msg += "\" instead";
							log_f->log_msg(LOG_MSG_ERROR, log_msg);
						}
					}
					else {
						// Invalid name, increment and try again
						name_count++;
						test_name = default_name + '_' + std::to_string(name_count);
					}
				}
			}
		}
		// File had issue reading in
		else {
			delete m;
			delete mreader;
			return false;
		}
	}
	delete mreader;
	return true;
}

bool assetmanager::add_texture_asset(const char *filename, std::string asset_name){
	std::string token = filename;
	token += "    "; // Add to test if at end of extension and so that if no extension exists ext[] access doesn't fail.
	const char *ext = token.substr(token.find_last_of(".")+1).c_str();

	bool valid_reader = false;
	textureReader *treader;
	texture2D_t *t = new texture2D_t();

	// bmp
	if (ext[0] == 'b' && ext[1] == 'm' && ext[2] == 'p' && IS_SPACE(ext[3])){
		// bmpReader treader;
		// valid_reader = true;
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "bmp file types are not yet implemented, but planned to be supported in a future update";
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete t;
		return false;	// Take out once implemented.
	}
	// png
	else if (ext[0] == 'p' && ext[1] == 'n' && ext[2] == 'g'&& IS_SPACE(ext[3])){
		// pngReader treader;
		// valid_reader = true;
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "png file types are not yet implemented, but planned to be supported in a future update";
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete t;
		return false;	// Take out once implemented.
	}
	/* The sgi format covers .bw, .sgi, .rgb, .int, .rgba and .inta exts */
	else if ((ext[0] == 'b' && ext[1] == 'w' && IS_SPACE(ext[2])) ||
			 (ext[0] == 's' && ext[1] == 'g' && ext[2] == 'i' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'r' && ext[1] == 'g' && ext[2] == 'b' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'i' && ext[1] == 'n' && ext[2] == 't' && IS_SPACE(ext[3])) ||
			 (ext[0] == 'r' && ext[1] == 'g' && ext[2] == 'b' && ext[3] == 'a' && IS_SPACE(ext[4])) ||
			 (ext[0] == 'i' && ext[1] == 'n' && ext[2] == 't' && ext[3] == 'a' && IS_SPACE(ext[4]))){
		treader = new sgiReader();
		valid_reader = true;
	}
	// Unsupported file type
	else {
		std::string logmsg = filename;
		logmsg += " was not read\n";
		logmsg += "Unsupported file type : ";
		logmsg += ext;
		log_f->log_msg(LOG_MSG_ERROR, logmsg);

		delete t;
		return false;
	}

	// Once reader is estiblished
	if (valid_reader){
		// Attempt to read texture in
		if (treader->parse_file(filename, t)){
			// texture was read succesfully
			allocatedMemory += sizeof(t);

			// Create internal id for the texture
			GLuint id;
			glGenTextures(1, &id);

			// Make the texture avaliable for GL
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t->texels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glGenerateMipmap( GL_TEXTURE_2D );
			t->texture_id = id;

			// Attempt to allocate with user provided name first if applicable
			std::string log_msg;
			bool invalid_name = true;
			if (!asset_name.empty()){
				// Check if user name is not currently in use
				if (this->texture_id_map.find(asset_name) == this->texture_id_map.end()){
					// The user name was not found, so okay to set it
					this->texture_id_map[asset_name] = id;
					this->textures[id] = t;
					invalid_name = false;
				}
				else {
					// The new name was found, so do not overwrite. Log as user error
					log_msg = "Could not allocate resource ";
					log_msg += filename;
					log_msg += " as ";
					log_msg += asset_name;
					log_msg += " : Name already in use, ";
					// log_msg is sent when valid name is found.
				}
			}
			if (invalid_name) {
				// Try default name till valid one is found
				size_t nbegin = token.find_last_of("/\\")+1;
				size_t nend = token.find_last_of(".");
				std::string default_name = token.substr(nbegin, nend-nbegin);
				std::string test_name = default_name;
				int name_count = 0;
				while(invalid_name){
					if (this->texture_id_map.find(test_name) == this->texture_id_map.end()){
						// Valid name
						this->texture_id_map[asset_name] = id;
						this->textures[id] = t;
						invalid_name = false;

						// Send log msg that resource was allocated under default name if user name was invalid.
						if (!asset_name.empty()){
							log_msg += "resource named \"";
							log_msg += test_name;
							log_msg += "\" instead";
							log_f->log_msg(LOG_MSG_ERROR, log_msg);
						}
					}
					else {
						// Invalid name, increment and try again
						name_count++;
						test_name = default_name + '_' + std::to_string(name_count);
					}
				}
			}
		}
		// File had issue reading in
		else {
			delete t;
			delete treader;
			return false;
		}
	}
	delete treader;
	return true;
}

mesh* assetmanager::get_mesh_asset(std::string asset_name){
	if (mesh_id_map.find(asset_name) != mesh_id_map.end()){
		return meshes[mesh_id_map[asset_name]];
	}
	else {
		std::string log_msg = "Trying to access non-loaded mesh : ";
		log_msg += asset_name;
		log_f->log_msg(LOG_MSG_WARNING, log_msg);
		return NULL;
	}
}

material* assetmanager::get_material_asset(std::string asset_name){
	if (material_id_map.find(asset_name) != mesh_id_map.end()){
		return materials[material_id_map[asset_name]];
	}
	else {
		std::string log_msg = "Trying to access non-loaded material : ";
		log_msg += asset_name;
		log_f->log_msg(LOG_MSG_WARNING, log_msg);
		return NULL;
	}
}


texture2D_t* assetmanager::get_texture_asset(std::string asset_name){
	if (texture_id_map.find(asset_name) != texture_id_map.end()){
		return textures[texture_id_map[asset_name]];
	}
	else {
		std::string log_msg = "Trying to access non-loaded texture : ";
		log_msg += asset_name;
		log_f->log_msg(LOG_MSG_WARNING, log_msg);
		return NULL;
	}
}

bool assetmanager::change_mesh_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (mesh_id_map.find(new_name) == mesh_id_map.end()){
		mesh_id_map[new_name] = mesh_id_map[cur_name];
		mesh_id_map.erase(cur_name);
		return true;
	}
	return false;
}

bool assetmanager::change_material_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (material_id_map.find(new_name) == mesh_id_map.end()){
		material_id_map[new_name] = material_id_map[cur_name];
		material_id_map.erase(cur_name);
		return true;
	}
	return false;
}

bool assetmanager::change_texture_asset_name(std::string cur_name, std::string new_name){
	// Check if new name is not in use, if so go ahead and change it
	if (texture_id_map.find(new_name) == texture_id_map.end()){
		texture_id_map[new_name] = texture_id_map[cur_name];
		texture_id_map.erase(cur_name);
		return true;
	}
	return false;
}

void assetmanager::erase_mesh_asset(std::string asset_name){
	mesh *m;
	m = get_mesh_asset(asset_name);
	if (m != NULL){delete m; m = NULL;}
	meshes.erase(mesh_id_map[asset_name]);
	mesh_id_map.erase(asset_name);
}

void assetmanager::erase_material_asset(std::string asset_name){
	material *m;
	m = get_material_asset(asset_name);
	if (m != NULL){delete m; m = NULL;}
	materials.erase(material_id_map[asset_name]);
	material_id_map.erase(asset_name);
}

void assetmanager::erase_texture_asset(std::string asset_name){
	texture2D_t *t;
	t = get_texture_asset(asset_name);
	if (t != NULL){delete t; t = NULL;}
	textures.erase(texture_id_map[asset_name]);
	texture_id_map.erase(asset_name);
}
