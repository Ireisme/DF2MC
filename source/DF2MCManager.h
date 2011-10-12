#pragma once

#include "DF2MCXmlParser.h"
#include "DFMap.h"
#include "MCMap.h"

class DF2MCManager
{
private:
	DF2MCXmlParser parser;
	DFMap dfMap;
	MCMap mcMap;
	ManagerSettings settings;

public:
	DF2MCManager(void);
	~DF2MCManager(void);
	bool loadSettings();
	bool loadSettings(char*);
};

