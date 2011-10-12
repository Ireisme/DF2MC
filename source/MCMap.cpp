#include "StdAfx.h"
#include "MCMap.h"


MCMap::MCMap(void)
{
}


MCMap::~MCMap(void)
{
}

bool MCMap::setMaterials(std::list<MCMaterial> mats)
{
	materials.swap(mats);

	return true;
}
