//
//  utils.h
//  Logger
//
//  Created by Albert Bode on 9/15/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef utils_h
#define utils_h

// See
// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
static std::istream &safeGetline(std::istream &is, std::string &t) {
	t.clear();
	
	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.
	
	std::istream::sentry se(is, true);
	std::streambuf *sb = is.rdbuf();
	
	if (se) {
		for (;;) {
			int c = sb->sbumpc();
			switch (c) {
				case '\n':
					return is;
				case '\r':
					if (sb->sgetc() == '\n') sb->sbumpc();
					return is;
				case EOF:
					// Also handle the case when the last line has no line ending
					if (t.empty()) is.setstate(std::ios::eofbit);
					return is;
				default:
					t += static_cast<char>(c);
			}
		}
	}
	
	return is;
}



#endif /* utils_h */
