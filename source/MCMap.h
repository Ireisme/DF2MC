#pragma once
#include "structs.h"

class MCMap
{
private:
	std::list<MCMaterial> materials;
public:
	MCMap(void);
	~MCMap(void);
	bool setMaterials(std::list<MCMaterial>);
};

