//
//  uicomponents.h
//  Scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef uicomponents_h
#define uicomponents_h

#include <string>

class baseUIComponent {
	bool visible;
	bool enabled;
	std::string tooltip;
	
	virtual void onHover() = 0;
	virtual void onClick() = 0;
};

#endif /* uicomponents_h */
