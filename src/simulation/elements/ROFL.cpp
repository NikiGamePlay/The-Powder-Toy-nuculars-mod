#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ROFL PT_ROFL 189
Element_ROFL::Element_ROFL()
{
	Identifier = "DEFAULT_PT_ROFL";
	Name = "ROFL";
	Colour = PIXPACK(0x00FFFF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.00f;
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
	Description = "Pretty weird element, moves around and transforms everything.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ROFL::update;
	Graphics = &Element_ROFL::graphics;

}

//#TPT-Directive ElementHeader Element_ROFL static int update(UPDATE_FUNC_ARGS)
int Element_ROFL::update(UPDATE_FUNC_ARGS)
{
	// Movement
	if (!(rand()%10))
	{
		parts[i].tmp = (rand()%3)-1;
		parts[i].tmp2 = (rand()%3)-1;
	}
	if (!pmap[y+parts[i].tmp2][x+parts[i].tmp])
	{
		parts[i].x = x+parts[i].tmp;
		parts[i].y = y+parts[i].tmp2;
	}
	
	// Spit out FIRE/CFLM randomly
	if (!(rand()%300))
	{
		int tx = x+rand()%3 -1;
		int ty = y+rand()%3 -1;
		switch(rand()%3)
		{
			case 0: sim->create_part(-1,tx,ty,PT_FIRE); break;
			case 1: sim->create_part(-1,tx,ty,PT_CFLM); break;
		}
	}

	// Maybe transform things into ROFL / BOYL / PHOT / ELEC / NEUT / CAUS
	if (!(rand()%300))
	{
		int tx = x+rand()%3 -1;
		int ty = y+rand()%3 -1;
		int r = pmap[ty][tx];
		if (r)
		{
			sim->kill_part(r>>8);
			switch(rand()%6)
			{
				case 0: sim->create_part(-1,tx,ty,PT_BOLT); break;
				case 1: sim->create_part(-1,tx,ty,PT_PHOT); break;
				case 2: sim->create_part(-1,tx,ty,PT_ROFL); break;
				case 3: sim->create_part(-1,tx,ty,PT_ELEC); break;
				case 4: sim->create_part(-1,tx,ty,PT_NEUT); break;
				case 5: sim->create_part(-1,tx,ty,PT_CAUS); break;
			}
		}
	}
}

//#TPT-Directive ElementHeader Element_ROFL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_ROFL::graphics(GRAPHICS_FUNC_ARGS)

{
	*colr = (int)cpart->x % 255;
	*colg = (int)cpart->y % 255;
	*colb = (int)(cpart->x * cpart->y) % 255;
	
	return 0;
}

Element_ROFL::~Element_ROFL() {}
