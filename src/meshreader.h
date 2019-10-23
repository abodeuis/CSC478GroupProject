//
//  meshreader.h
//  Filereader
//
//  Created by Albert Bode on 9/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef meshreader_h
#define meshreader_h

#include "filereader.h"
#include "mesh.h"
#include "logger.h"

#include <string>

extern logger *log_f;

class meshReader : fileReader {
public:
	bool triangulate;		// Should the file be reduced to triangles?

	virtual bool parse_file(const char *filename, mesh *m){return false;};
};

class objReader : meshReader {
public:
	bool parse_file(const char *filename, mesh *m);
};

class stlReader : meshReader {
public:
	bool parse_file(const char *filename, mesh *m);
};

#endif /* meshreader_h */
