//
//  texturereader.cpp
//  Filereader
//
//  Created by Albert Bode on 10/9/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include "texturereader.h"

union {
	int testWord;
	char testByte[4];
} endianTest;

typedef struct _sgiheader {
	unsigned short magic;		// 16 bits, Check code should always be 474
	unsigned short type;		// 2 8 bit values,
	unsigned short dim;			// 16 bits, Number of axises; allowed values are 1, 2 and 3
	unsigned short xsize;		// 16 bits, Width of the image in pixels
	unsigned short ysize;		// 16 bits, Height of the image in pixels
	unsigned short zsize;		// 16 bits, Depth (aka number of values per pixel)
								//			Greyscale images would be 1
								//			RGB images would be 3
	unsigned int pixmin;		// 32 bits, Minium pixel value of the image
	unsigned int pixmax;		// 32 bits, Maxium pixel value of the image

	// Everything below this can be safely ingored but i'm leaving it in as it is part of
	// the specification.
	/*
	wchar_t dummy;				// 32 bits, Separator, always ingored
	char *image_name;			// 640 bits, Image name we will ingore it as it is not
								//          commonly used anymore
	long colormap;				// 32 bits, Controls how pixels should be interpreted,
								//			Will always be 0 as other values are obsolete
	unsigned *dummy2;			// 404 bytes, Separator that brings the header size
								//			to exactly 512 bytes
	*/

	// RLE encodeing offset table (if file is rle encoded)
	unsigned int *row_start;
	int *row_size;
	unsigned long rleEnd;

} sgiheader;

static void convert_short(unsigned short *array, unsigned int length) {
	unsigned short b1, b2;
	unsigned char *ptr;

	ptr = (unsigned char *)array;
	while (length--) {
		b1 = *ptr++;
		b2 = *ptr++;
		*array++ = (b1 << 8) | (b2);
	}
}

static void convert_Uint(unsigned *array, unsigned int length) {
	unsigned int b1, b2, b3, b4;
	unsigned char *ptr;

	ptr = (unsigned char *)array;
	while (length--) {
		b1 = *ptr++;
		b2 = *ptr++;
		b3 = *ptr++;
		b4 = *ptr++;
		*array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
	}
}

//my convert uint
/*
static void convert_Uint(unsigned int *array, unsigned int length) {
	unsigned char *ptr;

	ptr = (unsigned char *)array;
	while (length--) {
		*array++ = (ptr[3]<<0) | (ptr[2]<<8) | (ptr[1]<<16) | (ptr[0]<<24);
	}
}
*/

static void get_row(FILE *in, sgiheader *h, unsigned char *buf, int y, int z){
	// File is run line encoded
	if ((h->type & 0xFF00) == 0x0100) {
		unsigned char *iPtr, *oPtr, pixel;
		unsigned char *rle_buf = (unsigned char *)malloc(h->xsize*256);
		int count;

		fseek(in, (long)h->row_start[y+z*h->ysize], SEEK_SET);
		fread(rle_buf, 1, (unsigned int)h->row_size[y+z*h->ysize],in);

		iPtr = rle_buf;
		oPtr = buf;

		for(;;){
			pixel = *iPtr++;
			count = (int)(pixel & 0x7F);
			if (!count) {
				delete rle_buf;
				return;
			}
			if (pixel & 0x80) {
				while (count--) {
					*oPtr++ = *iPtr++;
				}
			} else {
				pixel = *iPtr++;
				while (count--) {
					*oPtr++ = pixel;
				}
			}
		}

	}

	// File has no encoding
	else {
		// Find line start
		fseek(in, 512+(y*h->xsize)+(z*h->xsize*h->ysize), SEEK_SET);
		// Read line into buf
		fread(buf, 1, h->xsize, in);
	}
}

bool sgiReader::parse_file(const char *filename, texture2D_t *t){
	// Clear any old shape data
	delete t->texels;

	std::string text_name = "A filename";

	// Test for big or little endian
	int swapFlag;
	endianTest.testWord = 1;
	if (endianTest.testByte[0] == 1) {
		swapFlag = 1;
	} else {
		swapFlag = 0;
	}

	// Open the file
	FILE *in;
	in = fopen(filename, "rb");
	if (in == NULL) {
		std::string error_msg = "Problem opening : ";
		error_msg += filename;
		log_f->log_msg(LOG_MSG_ERROR, error_msg);
		return false;
	}

	std::string status_msg = "Started reading : ";
	status_msg += filename;
	log_f->log_msg(LOG_MSG_STATUS, status_msg);

	// Read in File Header
	sgiheader *header = (sgiheader *)malloc(sizeof(sgiheader));
	fread(header, 1, 20, in);
	int x;

	// Convert Header values if needed
	if (swapFlag) {
		convert_short(&header->magic, 6);
		convert_Uint(&header->pixmin, 1);
		convert_Uint(&header->pixmax, 1);
	}

	// Check file has correct checknum before proceding (aka is a real sgi file)
	unsigned short checknum = 474;	// Will always be 474 for real sgi files
	if (header->magic != checknum){
		std::string log_msg = filename;
		log_msg += " could not be read as an sgi formatted file\n";
		log_msg += "Possibly Corrupted";
		log_f->log_msg(LOG_MSG_ERROR, log_msg);
		return false;
	}

	// If RLE encoding is present read in offset data
	if((header->type & 0xFF00) == 0x0100){
		// Allocate offset table
		x = header->ysize * header->zsize * (int) sizeof(unsigned);
		header->row_start = (unsigned *)malloc(x);
		header->row_size = (int *)malloc(x);
		header->rleEnd = 512 + (2 * x);
		if (header->row_start == NULL || header->row_size == NULL) {
			log_f->log_msg(LOG_MSG_FATAL, "Out of memory!");
			exit(1);
		}

		// Read offset table
		fseek(in, 512, SEEK_SET);
		fread(header->row_start, 1, x, in);
		fread(header->row_size, 1, x, in);
		// Convert Offset table values if needed
		if (swapFlag){
			convert_Uint(header->row_start, x/(int)sizeof(unsigned));
			convert_Uint((unsigned *)header->row_size, x/(int) sizeof(int));
		}
	}

	// For debugging bad sgi files
	std::stringstream ss;
	ss << "\n\tMagic : " << header->magic << std::endl;
	ss << "\tType    : " << header->type << std::endl;
	ss << "\tDim     : " << header->dim << std::endl;
	ss << "\tWidth   : " << header->xsize << ", Height : "<< header->ysize << std::endl;
	ss << "\tZ size  : " << header->zsize << std::endl;
	ss << "\tPixmin  : " << header->pixmin << std::endl;
	ss << "\tPixmax  : " << header->pixmax << std::endl;
	if ((header->type & 0xFF00) == 0x0100){
		ss << "\tRLE Encoding information" << std::endl;
		ss << "\tRow Start : " << (*header->row_start) << std::endl;
		ss << "\tRow Size  : " << (*header->row_size) << std::endl;
		ss << "\tRLE End   : " << header->rleEnd << std::endl;
	}
	log_f->log_msg(LOG_MSG_DEBUG2, ss.str());
	log_f->writeLog();

	// Pixel data reading
	// Initalize line buffers
	//int glsize = header->xsize*header->ysize*sizeof(unsigned);
	t->texels = (unsigned *)malloc(header->xsize*header->ysize*sizeof(unsigned));
	unsigned char *r_buf = (unsigned char *)malloc(header->xsize*256);
	unsigned char *b_buf = (unsigned char *)malloc(header->xsize*256);
	unsigned char *g_buf = (unsigned char *)malloc(header->xsize*256);
	unsigned char *a_buf = (unsigned char *)malloc(header->xsize*256);
	// Check memory was properly allocated
	if (r_buf == NULL || b_buf == NULL || g_buf == NULL || a_buf == NULL){
		log_f->log_msg(LOG_MSG_FATAL, "Out of memory!");
		exit(1);
	}
	unsigned *line_ptr = t->texels;
	for (int y=0; y<header->ysize; y++){
		// RGBA image
		if(header->zsize >= 4) {
			get_row(in, header, r_buf, y, 0);
			get_row(in, header, b_buf, y, 1);
			get_row(in, header, g_buf, y, 2);
			get_row(in, header, a_buf, y, 3);

			rgbatorgba(r_buf, g_buf, b_buf, a_buf, (unsigned char *)line_ptr, header->xsize);
			line_ptr += header->xsize;
		}
		// RGB
		else if(header->zsize==3){
			get_row(in, header, r_buf, y, 0);
			get_row(in, header, b_buf, y, 1);
			get_row(in, header, g_buf, y, 2);

			rgbtorgba(r_buf, g_buf, b_buf, (unsigned char *)line_ptr, header->xsize);
			line_ptr += header->xsize;
		}
		// BW
		else {
			get_row(in, header, a_buf, y, 0);

			bwtorgba(a_buf, (unsigned char *)line_ptr, header->xsize);
			line_ptr += header->xsize;
		}
	}
	t->width = header->xsize;
	t->height = header->ysize;
	t->pixeltype = header->dim;
	t->pixelformat = GL_RGBA;

	/*
	line_ptr = t->texels;
	for (int y=0;y<header->ysize; y++){
		for (int x=0;x<header->xsize; x++){
			std::cout << y << "," << x << " : " << (*line_ptr) << std::endl;
			line_ptr++;
		}
	}
	 */
	
	fclose(in);

	free(header);
	free(r_buf);
	free(b_buf);
	free(g_buf);
	free(a_buf);
	//free(texels);
	
	status_msg = "Finished reading : ";
	status_msg += filename;
	log_f->log_msg(LOG_MSG_STATUS, status_msg);

	return true;
};
