//
//  Header.h
//  Filereader
//
//  Created by Albert Bode on 9/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef filereader_h
#define filereader_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <fstream>

#include "vec.h"

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

// See
// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
inline std::istream& safeGetline(std::istream& is, std::string& t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::istream::sentry se(is, true);
	std::streambuf* sb = is.rdbuf();

	for(;;) {
		int c = sb->sbumpc();
		switch (c) {
			case '\n':
				return is;
			case '\r':
				if(sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case std::streambuf::traits_type::eof():
				// Also handle the case when the last line has no line ending
				if(t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += (char)c;
		}
	}
}

static inline GLint parse_int(const char **token, GLint default_value = 0){
	std::string token_cp = (*token);
	std::string::size_type sz;
	GLint val = default_value;

	val = std::stoi(token_cp, &sz);

	(*token) += sz;
	return val;
}

static inline GLfloat parse_float(const char **token, GLfloat default_value = 0.0f){
	std::string token_cp = (*token);
	std::string::size_type sz;
	GLfloat val = default_value;

	val = std::stof(token_cp, &sz);
	(*token) += sz;
	/*
	 try {
		val = std::stof(token_cp, &sz);
		token += sz;
	 }
	 catch (const std::invalid_argument& ia) {
		std::string err_msg = "Invalid argument: ";
		err_msg.append(ia.what());
		err_msg.append("\n");
		logger->log_msg(LOG_MSG_ERROR, err_msg);
	 }
	 */

	return val;
};

static inline vec2 parse_float2(const char **token){
	vec2 vec;

	vec.x = parse_float(token);
	vec.y = parse_float(token);

	return vec;
}

static inline vec3 parse_float3(const char **token){
	vec3 vec;

	vec.x = parse_float(token);
	vec.y = parse_float(token);
	vec.z = parse_float(token);

	return vec;
}



class fileReader {

};



#endif /* Header_h */
