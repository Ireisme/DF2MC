#pragma once
#include <string>
#include "stdafx.h"

struct ManagerSettings
{
	int squareSize;
	int torchInsidePercent;
	int torchDarkPercent;
	int torchSubPercent;
	bool directionalWalls;
	int safeSand;
};

struct MCMaterial
{
	std::string name;
	int blockID;
	int opacity;
	bool partiallyLit;
	bool nonSupport;
	bool sand;
};