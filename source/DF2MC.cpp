// DF2MC.cpp : main project file.

#include "stdafx.h"
#include "DF2MCManager.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	DF2MCManager manager;

	if(manager.loadSettings("settings.xml"))
	{
		printf("Loaded settings!\n");
	}
	else
	{
		printf("Fuck You it failed!\n");
	}

	return 0;
}