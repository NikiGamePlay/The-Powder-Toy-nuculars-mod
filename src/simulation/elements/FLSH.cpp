#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FLSH PT_FLSH 200
Element_FLSH::Element_FLSH()
{
	Identifier = "DEFAULT_PT_FLSH";
	Name = "FLSH";
	Colour = PIXPACK(0xC0C0D0);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.80f;
	Collision = -0.1f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 85;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 97;
	Description = "Flash Powder. Explodes with a flame coloured like itself, and small pressure.";

	State = ST_SOLID;
	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 673.0f;
	HighTemperatureTransition = PT_FIRE;

	Update = &Element_FLSH::update;

}

//#TPT-Directive ElementHeader Element_FLSH static int update(UPDATE_FUNC_ARGS)
int Element_FLSH::update(UPDATE_FUNC_ARGS)
 {
 	int r, rx, ry;
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if ((r&0xFF)==PT_FIRE || (r&0xFF)==PT_PLSM || (r&0xFF)==PT_SPRK || parts[r>>8].temp>R_TEMP+400)
				{
					if (!(rand()%2))
					{
						sim->part_change_type(i,x,y, PT_FIRE);
						parts[i].life = 70 + (rand() % 20);
						parts[i].tmp2 = 1337;
						parts[i].temp = R_TEMP + 1200.0f + 273.15f;
					}
					else
					{
						sim->part_change_type(i,x,y, PT_EMBR);
						parts[i].life = 50 + (rand() % 20);
					}
				}
			}
	return 0;
}

Element_FLSH::~Element_FLSH() {}
