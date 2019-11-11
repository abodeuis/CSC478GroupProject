//
//  cvar.h
//  MergedSystem
//
//  Created by Albert Bode on 10/29/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef cvar_h
#define cvar_h

class cvarInterface {
	int m_Size;
protected:
	~cvarInterface() = default;
};

template <typename T>
class cvar : public cvarInterface{
	T var;
	
public:
	T get_value(){return var;};
	void set_value(T val){this->var=val;}
	
	// Default Constructor
	cvar(){
		this->var = NULL;
	}
	
	cvar(T val){
		this->var = val;
	}
};

#endif /* cvar_h */
