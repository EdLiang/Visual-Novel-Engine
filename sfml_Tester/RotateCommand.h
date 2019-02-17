#pragma once
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "ScriptCommand.h"

using namespace std;

class RotateCommand : public ScriptCommand
{
public:

	RotateCommand(vector<string> args);
	~RotateCommand();

	void execute(ScriptLine* scriptLine);
	void skipUpdate();
	void update(float delta_t);

private:

	string objectTypeName;		//Background | Character
	string flag;				// Wait | none

	string objectName;			// name of character | Background
	string objectSubname;		// expression of character or time-of-the-day for background

	float x1, y1;
	float time;

	int objectType;
	const static int OBJECT_CHARACTER = 0;
	const static int OBJECT_BACKGROUND = 1;

	int animationType;
	const static int ANIMATION_ROTATE = 1;
	const static int ANIMATION_NONE = 0;
	float finalDegree;
	float currentRotate;
	float angleDiff;
	float tempAngle;
	string whichWay;
	bool clockwise;
	bool relative;
};