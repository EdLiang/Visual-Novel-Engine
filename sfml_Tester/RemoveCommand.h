#pragma once
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include "ScriptCommand.h"
using namespace std;

class RemoveCommand : public ScriptCommand
{
public:
	RemoveCommand(std::vector<std::string> args);
	~RemoveCommand();

	void execute(ScriptLine* scriptLine);
	void skipUpdate();
	void update(float delta_t);

private:

	std::string objectTypeName;
	std::string flag;

	std::string objectName;
	std::string objectSubname;

	float time;

	int animationType;
	float alpha;

	int objectType;

	const static int ANIMATION_FADEOUT = 1;
	const static int ANIMATION_NONE = 0;

	const static int OBJECT_CHARACTER = 0;
	const static int OBJECT_BACKGROUND = 1;
};