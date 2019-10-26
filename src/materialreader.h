//
//  materialreader.hpp
//  Filereader
//
//  Created by Albert Bode on 10/6/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef materialreader_hpp
#define materialreader_hpp

#include "filereader.h"
#include "material.h"
#include "logger.h"

#include <string>

extern logger *log_f;

class materialReader : public fileReader {
public:
	virtual bool parse_file(const char *filename, material *m){return false;};
};

class mtlReader : public materialReader {
public:
	bool parse_file(const char *filename, material *m);
};

#endif /* materialreader_hpp */
