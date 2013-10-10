#include "simulation/Elements.h"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
//#TPT-Directive ElementClass Element_ANT PT_ANT 188
Element_ANT::Element_ANT()
{
	Identifier = "DEFAULT_PT_ANT";
	Name = "ANT";
	Colour = PIXPACK(0x544741);
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

	State = ST_GAS;
	Properties = TYPE_ENERGY;

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

//#TPT-Directive ElementHeader Element_ANT static int update(UPDATE_FUNC_ARGS)
int Element_ANT::update(UPDATE_FUNC_ARGS)
{
	int newPart;
	int r = sim->pmap[y][x];
	if ((r&0xFF) == PT_ANT2) {
		// On active cell
		sim->kill_part(r>>8);
		if (--parts[i].tmp < NORTH) parts[i].tmp = WEST;
	} else {
		newPart = sim->create_part(-1,x,y,PT_ANT2);
		if (parts[i].dcolour)
			parts[newPart].dcolour = parts[i].dcolour;
		if (++parts[i].tmp > WEST) parts[i].tmp = NORTH;
	}

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
