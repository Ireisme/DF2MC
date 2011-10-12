#pragma once
#include "tinyxml.h"
#include "tinystr.h"

class DF2MCXmlParser
{
private:
	TiXmlDocument doc;
	bool loadedSuccessfully;
	char* filename;

public:
	DF2MCXmlParser(void);
	DF2MCXmlParser(char*);
	~DF2MCXmlParser(void);

	bool loadXml();
	ManagerSettings loadManagerSettings();
	std::list<MCMaterial> loadMCMaterials();
};

