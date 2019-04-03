#include "simulation/Elements.h"
#include <bitset>
#include <algorithm>
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//#TPT-Directive ElementClass Element_ANT PT_ANT 188
Element_ANT::Element_ANT()
{
	Identifier = "DEFAULT_PT_ANT";
	Name = "ANT";
	Colour = PIXPACK(0x773029);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = 0.0f;
	HeatConduct = 0;
	Description = "Langton's Ant. Turing machine. Basically LIFE, but better. If you color the ANT, it will leave a colored trail.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ANT::update;

}

// Actually, this only returns the bits 1..n
std::vector<int> get_bits(int x)
{
	std::vector<int> ret;
	while(x)
	{
		if (x&1)
			ret.push_back(1);
		else
			ret.push_back(0);
		x>>=1;
	}
	ret.pop_back();
	std::reverse(ret.begin(), ret.end());
	return ret;
}


/*
tmp: The current moving direction of the ant
tmp2: The ruleset as a positive integer

A cell without a particle of ANT2 is considered state 0;
a cell with one is considered state cell.tmp.
*/

//#TPT-Directive ElementHeader Element_ANT static int update(UPDATE_FUNC_ARGS)
int Element_ANT::update(UPDATE_FUNC_ARGS)
{
	int r;

	if (parts[i].tmp2 < 4)
		parts[i].tmp2 = 4;
	std::vector<int> states = get_bits((unsigned int)parts[i].tmp2);

	// Get the state of the current cell and turn in the right direction
	r = sim->pmap[y][x];

	if ((r&0xFF) == PT_ANT2) // state = cell.tmp
	{
		Particle n = parts[r>>8];

		if (n.tmp < 0 || n.tmp >= states.size())
			n.tmp = 0;

		parts[i].tmp += (states[n.tmp] * 2) - 1;
		
		parts[r>>8].tmp++;

		if (parts[r>>8].tmp >= states.size() || parts[r>>8].tmp < 0)
			sim->kill_part(r>>8);
	}
	else // state = 0
	{
		parts[i].tmp += states[0] * 2 - 1;
		int newPart = sim->create_part(-1,x,y,PT_ANT2);
		parts[newPart].tmp = 1;
		parts[newPart].tmp2 = states.size() - 1;
		if (parts[i].dcolour && (parts[i].dcolour&0xFF000000))
			parts[newPart].dcolour = parts[i].dcolour;
	}

	// Be sure that our tmp is right
	if (parts[i].tmp < NORTH) parts[i].tmp = WEST;
	if (parts[i].tmp > WEST) parts[i].tmp = NORTH;

	// Set tx and ty to the new position
	int tx = parts[i].x, ty = parts[i].y;
	switch(parts[i].tmp) {
		case NORTH:
			ty -= 1; break;
		case EAST:
			tx += 1; break;
		case SOUTH:
			ty += 1; break;
		case WEST:
			tx -= 1;
	}
	
	if (tx >= 0 && tx < XRES && ty >= 0 && ty < YRES && (!pmap[ty][tx] || (pmap[ty][tx]&0xFF)==PT_ANT2)) {
		parts[i].x = tx;
		parts[i].y = ty;
	}
	return 0;
}

Element_ANT::~Element_ANT() {}
