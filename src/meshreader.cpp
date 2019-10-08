//
//  meshreader.cpp
//  Filereader
//
//  Created by Albert Bode on 9/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include <stdio.h>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

#include "meshreader.h"

bool objReader::parse_file(const char *filename, mesh *m){
	// Clear any old shape data
	delete m->shape;
	
	// Structural Data
	std::vector<vec3> vertices;
	std::vector<vec2> texcoords;
	std::vector<vec3> normals;
	std::vector<vec2> parameters;
	shape_t *shape = new shape_t();
	std::string o_name = "A filename";
	
	
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
	GLint cur_smooth_id = 0;
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
		
		// Structural data
		// Vertex : x y z
		if(token[0] == 'v' && IS_SPACE(token[1])) {
			token += 2;
			
			vertices.push_back(parse_float3(&token));
			continue;
		}
		
		// Texture coordinate : u v
		if(token[0] == 'v' && token[1] == 't' && IS_SPACE(token[2])) {
			token += 3;
			
			texcoords.push_back(parse_float2(&token));
			continue;
		}
		
		// Vertex normal : xn yn zn
		if(token[0] == 'v' && token[1] == 'n' && IS_SPACE(token[2])){
			token += 3;
			
			normals.push_back(parse_float3(&token));
			continue;
		}
		
		// Vertex parameter space : x y w
		if(token[0] == 'v' && token[1] == 'p' && IS_SPACE(token[2])){
			token += 3;
			
			parameters.push_back(parse_float2(&token));
			continue;
		}
		
		// Shape orginization
		// Points : v1 v2 v3 ...
		if(token[0] == 'p' && IS_SPACE(token[1])){
			token += 2;
			
			point_t points;
			while(!IS_NEW_LINE(token[0])){
				token += strspn(token, " \t");						// Trim Whitespace
				GLint index_num = parse_int(&token);				// Parse vertex number
				index_t *index = new index_t(vertices[index_num]);	// Create index
				points.indices.push_back(index);					// Add index to points
			}
			shape->points.push_back(points);							// Add point group to shape
			continue;
		}
		
		// Line : v1/vt1 v2/vt2 v3/vt3 ...
		if(token[0] == 'l' && IS_SPACE(token[1])){
			token += 2;
			
			line_t line;
			while(!IS_NEW_LINE(token[0])){
				token += strspn(token, " \t");						// Trim Whitespace
				index_t *index;
				GLint vert_num = parse_int(&token);					// Parse vertex number
				index = new index_t(vertices[vert_num]);			// Create index;
				if (token[0] == '/'){
					token += 1;
					GLint text_num = parse_int(&token);				// Parse texture number
					vec2 texcord = texcoords[text_num];				// Add data to index
					index->u = texcord.x;
					index->v = texcord.y;
				}
				line.indices.push_back(index);						// Add index to line
			}
			shape->lines.push_back(line);							// Add line to shape
			continue;
		}
		
		// Face : v1/vt1/vn1 v2/vt2/vn2 ...
		if(token[0] == 'f' && IS_SPACE(token[1])){
			token += 2;
			
			face_t face;
			face.smooth_group_id = cur_smooth_id;
			while(!IS_NEW_LINE(token[0])){
				token += strspn(token, " \t");						// Trim Whitespace
				index_t *index;
				GLint vert_num = parse_int(&token);					// Parse vertex number
				index = new index_t(vertices[vert_num]);			// Create index;
				if (token[0] == '/'){
					token += 1;
					GLint text_num = parse_int(&token);				// Parse texture number
					vec2 texcord = texcoords[text_num];				// Add data to index
					index->u = texcord.x;
					index->v = texcord.y;
				}
				if(token[0] == '/') {
					token += 1;
					GLint norm_num = parse_int(&token);				// Parse normal number
					vec3 normal = normals[norm_num];				// Add data to index
					index->xn = normal.x;
					index->yn = normal.y;
					index->zn = normal.z;
				}
				face.indices.push_back(index);						// Add index to face
			}
			shape->faces.push_back(face);							// Add face to shape
			continue;
		}
		
		// Grouping
		// Group name : gname1 gname2 ...
		if(token[0] == 'g' && IS_SPACE(token[1])){
			std::string warn_msg = "Line Ignored : ";
			warn_msg += token;
			warn_msg += "\n\t\t\t  Group not implemented yet";
			log->log_msg(LOG_MSG_WARNING, warn_msg);
			continue;
		}
		
		// Smoothing group : off || gnumber
		if(token[0] == 's' && IS_SPACE(token[1])){
			token += 2;
			
			// skip whitespace
			token += strspn(token, " \t");
			
			// off
			if(strlen(token) >= 3){
				if(token[0] == 'o' && token[1] == 'f' && token[2] == 'f'){
					cur_smooth_id = 0;
				}
			// Number
			} else {
				cur_smooth_id = parse_int(&token);
			}
			continue;
		}
		
		// Object name : oname
		if(token[0] == 'o' && IS_SPACE(token[1])){
			token += 2;
			
			o_name.clear();
			o_name += token;
			
			continue;
		}
		
		// lod level
		
		// mtllib master.mtl
		
		// Material name : material_name
		
	}
	m->shape = shape;
	m->name = o_name;
	
	/*
	 POSSIBLE MEMORY LEAK IF INGORED
	 ANY ERROR HANDLING THAT is ADDED NEEDS TO DECIDE WEATHER TO DELETE THE "shape" POINTER!!
	*/
	
	return true;
};

bool stlReader::parse_file(const char *filename, mesh *m){
	return false;
};
