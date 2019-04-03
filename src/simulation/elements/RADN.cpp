#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RADN PT_RADN 190
Element_RADN::Element_RADN()
{
	Identifier = "DEFAULT_PT_RADN";
	Name = "RADN";
	Colour = PIXPACK(0x003344);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.001f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 2;

	Temperature = R_TEMP+2.0f	+273.15f;
	HeatConduct = 100;
	Description = "Radon, emits NEUT, decays into DEUT and HYGN. Fusionates to BOLT around 6500 C.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 6500.0f +273.15f;
	HighTemperatureTransition = PT_BOLT;

	Update = &Element_RADN::update;

}

//#TPT-Directive ElementHeader Element_RADN static int update(UPDATE_FUNC_ARGS)
int Element_RADN::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt, newId;
	bool neut=false;
	if (parts[i].temp < -50.0f+273.15f)
		return 0;
	if (parts[i].tmp > 0)
		parts[i].tmp--;
	if (parts[i].life == 0)
	{
		if (!(rand()%4))
			sim->part_change_type(i,x,y, PT_DEUT);
		else
			sim->part_change_type(i,x,y, PT_H2);
		return 0;
	}
	if (parts[i].tmp == 0)
	{
		parts[i].tmp = (int)((1.0f-(parts[i].temp/(6500.0f +273.15f)))*300);
		for (rx=-1; rx<2 && neut==false; rx++)
			for (ry=-1; ry<2 && neut==false; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
					{
						newId = sim->create_part(-1,x+rx,y+ry, PT_NEUT);
						parts[newId].temp = parts[i].temp + 2.0f;
						neut = true;
					}
				}
		if (neut)
			parts[i].life--;
	}
	return 0;
}

Element_RADN::~Element_RADN() {}
