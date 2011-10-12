#include "StdAfx.h"
#include "DF2MCXmlParser.h"


DF2MCXmlParser::DF2MCXmlParser(void)
{
	DF2MCXmlParser("settings.xml");
}

DF2MCXmlParser::DF2MCXmlParser(char* file)
{
	filename = file;
	loadedSuccessfully = false;
}

DF2MCXmlParser::~DF2MCXmlParser(void)
{
}

bool DF2MCXmlParser::loadXml()
{
	doc = TiXmlDocument(filename);
	if(doc.LoadFile())
	{
		loadedSuccessfully = true;
		return true;
	}
	else
		return false;
}

ManagerSettings DF2MCXmlParser::loadManagerSettings()
{
	ManagerSettings managerSettings;
	TiXmlElement * settings = doc.FirstChildElement("settings");

	if(settings==NULL)
	{
		printf("Could not load settings from SETTINGS.XML (corrupt xml file?)\n");
	}

	//SquareSize
	if(settings->FirstChildElement("squaresize")==NULL)
	{
		printf("Squaresize settings not found, using default of 3.\n");
		managerSettings.squareSize = 3;
	}
	else
	{
		managerSettings.squareSize = atoi(settings->FirstChildElement("squaresize")->Attribute("val"));
		
		if(managerSettings.squareSize < 1 || managerSettings.squareSize > 10)
		{
			printf("Wrong Squaresize ( 1 < x < 10), using default of 3.");
			managerSettings.squareSize = 3;
		}
	}

	//TorchInsidePercent
	if(settings->FirstChildElement("torchinsidepercent")==NULL)
	{
		printf("TorchInsidePercent settings not found, using default of 10.\n");
		managerSettings.torchInsidePercent = 10;
	}
	else
	{
		managerSettings.torchInsidePercent = atoi(settings->FirstChildElement("torchinsidepercent")->Attribute("val"));
	}

	//TorchDarkPercent
	if(settings->FirstChildElement("torchdarkpercent")==NULL)
	{
		printf("TorchDarkPercent settings not found, using default of 20.\n");
		managerSettings.torchDarkPercent = 20;
	}
	else
	{
		managerSettings.torchDarkPercent = atoi(settings->FirstChildElement("torchdarkpercent")->Attribute("val"));
	}

	//TorchSubPercent
	if(settings->FirstChildElement("torchsubterraneanpercent")==NULL)
	{
		printf("TorchSubPercent settings not found, using default of 30.\n");
		managerSettings.torchSubPercent = 30;
	}
	else
	{
		managerSettings.torchSubPercent = atoi(settings->FirstChildElement("torchsubterraneanpercent")->Attribute("val"));
	}

	//DirectionalWalls
	if(settings->FirstChildElement("directionalwalls")==NULL)
	{
		printf("DirectionalWalls settings not found, using default of false.\n");
		managerSettings.directionalWalls = false;
	}
	else
	{
		const char * tmp = settings->FirstChildElement("directionalwalls")->Attribute("val");

		if(tmp == "true")
			managerSettings.directionalWalls = true;
		else
			managerSettings.directionalWalls = false;
	}

	//SafeSand
	if(settings->FirstChildElement("safesand")==NULL)
	{
		printf("SafeSand settings not found, using default of 3.\n");
		managerSettings.safeSand = 3;
	}
	else
	{
		managerSettings.safeSand = atoi(settings->FirstChildElement("safesand")->Attribute("val"));
	}

	return managerSettings;
}

std::list<MCMaterial> DF2MCXmlParser::loadMCMaterials()
{
	std::list<MCMaterial> materials;
	printf("Loading Minecraft Materials...\n");

	char* tagname;
	tagname = "minecraftmaterialsalpha";

	TiXmlElement *elm = doc.FirstChildElement();
	while(elm!=NULL)
	{

		if(strcmp(elm->Value(),tagname)==0)
		{
			TiXmlElement *mat = elm->FirstChildElement();
			while(mat!=NULL)
			{

				if(strcmp(mat->Value(),"material")==0)
				{
					int val;
					mat->Attribute("val",&val);
					string name(mat->GetText());

					//printf("%s -> %d\n",name.c_str(),val);
					if(val>=0 && val <256)
					{

						int tmp;
						MCMaterial material;
						material.name = name;
						material.blockID = val;

						//Set Opacity
						
						if(mat->Attribute("opacity") == NULL)
						{
							material.opacity = 15;
						}
						else
						{
							material.opacity = atoi(mat->Attribute("opacity"));
						}

						//Set PartiallyLit
						if(mat->Attribute("partlit") != NULL)
						{
							tmp = atoi(mat->Attribute("partlit"));
							if(tmp == 1)
							{
								material.partiallyLit = true;
							}
							else
							{
								material.partiallyLit = false;
							}
						}
						else
							material.partiallyLit = false;

						//Set Sand
						if(mat->Attribute("sand") != NULL)
						{
							tmp = atoi(mat->Attribute("sand"));
							if(tmp == 1)
							{
								material.sand = true;
							}
							else
							{
								material.sand = false;
							}
						}
						else
							material.sand = false;

						//Set NonSupport
						if(mat->Attribute("nonsupport") != NULL)
						{
							const char* athing = mat->Attribute("nonsupport");
							if(tmp == 1)
							{
								material.nonSupport = true;
							}
							else
							{
								material.nonSupport = false;
							}
						}
						else
							material.nonSupport = false;

						materials.push_back(material);
					}
					mat=mat->NextSiblingElement();
				}
			}
		}

		elm=elm->NextSiblingElement();
	}

	printf("loaded %d materials\n\n",materials.size());
	return materials;
}
