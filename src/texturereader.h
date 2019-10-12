//
//  texturereader.h
//  Filereader
//
//  Created by Albert Bode on 10/9/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef texturereader_h
#define texturereader_h

#include "filereader.h"
#include "texture.h"
#include "logger.h"

extern logger *log;

static inline void bwtorgba(unsigned char *bw_buf, unsigned char *rgba_buf, int bw_buf_size){
	while(bw_buf_size--) {
		rgba_buf[0] = *bw_buf;
		rgba_buf[1] = *bw_buf;
		rgba_buf[2] = *bw_buf;
		rgba_buf[3] = 0xff;
		rgba_buf += 4;
		bw_buf++;
	}
}

static inline void rgbtorgba(unsigned char *r_buf,unsigned char *g_buf,unsigned char *b_buf,unsigned char *rgba_buf,int rgb_buf_size) {
	while(rgb_buf_size--) {
		rgba_buf[0] = r_buf[0];
		rgba_buf[1] = g_buf[0];
		rgba_buf[2] = b_buf[0];
		rgba_buf[3] = 0xff;
		rgba_buf += 4;
		r_buf++;
		g_buf++;
		b_buf++;
	}
}

static inline void rgbatorgba(unsigned char *r_buf,unsigned char *g_buf,unsigned char *b_buf,unsigned char *a_buf,unsigned char *rgba_buf,int rgb_buf_size) {
	while(rgb_buf_size--) {
		rgba_buf[0] = r_buf[0];
		rgba_buf[1] = g_buf[0];
		rgba_buf[2] = b_buf[0];
		rgba_buf[3] = a_buf[0];
		rgba_buf += 4;
		r_buf++;
		g_buf++;
		b_buf++;
		a_buf++;
	}
}

class texturereader : fileReader {
public:
	virtual bool parse_file(const char *filename, texture2D_t *t){return false;};
};

class pngreader : texturereader {
public:
	bool parse_file(const char *filename, texture2D_t *t);
};

/* The sgi format coves .sgi, .rgb, .rgba, .bw, .int and .inta extensions */
class sgireader : texturereader {
public:
	bool parse_file(const char *filename, texture2D_t *t);
};

class bmpreader : texturereader {
public:
	bool parse_file(const char *filename, texture2D_t *t);
};

#endif /* texturereader_h */
