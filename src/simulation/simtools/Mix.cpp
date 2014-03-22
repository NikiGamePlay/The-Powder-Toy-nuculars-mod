#include "ToolClasses.h"
//#TPT-Directive ToolClass Tool_Mix TOOL_MIX 4
Tool_Mix::Tool_Mix()
{
	Identifier = "DEFAULT_TOOL_MIX";
	Name = "MIX";
	Colour = PIXPACK(0x00FFDD);
	Description = "Mixes the affected particles by randomly moving them.";
}

int Tool_Mix::Perform(Simulation * sim, Particle * cpart, int x, int y, float strength)
{
	int newx, newy;
	if(!cpart)
		return 0;

	newx = x + rand()%3*strength -strength;
	newy = y + rand()%3*strength -strength;

	if (!sim->pmap[newy][newx])
	{
		cpart->x = newx;
		cpart->y = newy;
	}
	return 1;
}

Tool_Mix::~Tool_Mix() {}
