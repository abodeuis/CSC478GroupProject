//
//  asset.h
//  MergedSystem
//
//  Created by Albert Bode on 11/4/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef asset_h
#define asset_h

class asset {
	/// Parent of all assets that contains metadata fields about assets
	std::string filePath;
	int filesize;
	bool loaded;
	int lastaccess;
};

#endif /* asset_h */
