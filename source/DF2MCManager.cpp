#include "StdAfx.h"
#include "DF2MCManager.h"
#include "DF2MCXmlParser.h"
#include "DFMap.h"
#include "MCMap.h"

DF2MCManager::DF2MCManager(void)
{
	
}


DF2MCManager::~DF2MCManager(void)
{
}

bool DF2MCManager::loadSettings()
{
	return loadSettings("settings.xml");
}

bool DF2MCManager::loadSettings(char* xmlFile)
{
	parser = DF2MCXmlParser(xmlFile);

	if(parser.loadXml())
	{
		settings = parser.loadManagerSettings();
		mcMap.setMaterials(parser.loadMCMaterials());

		return true;
	}
	else
		return false;
}