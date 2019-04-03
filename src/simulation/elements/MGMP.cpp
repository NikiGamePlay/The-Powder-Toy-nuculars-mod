#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MGMP PT_MGMP 192
Element_MGMP::Element_MGMP()
{
	Identifier = "DEFAULT_PT_MGMP";
	Name = "MGMP";
	Colour = PIXPACK(0xBBBBBB);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
	Enabled = 1;
	
	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;
	
	Flammable = 9999;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;
	
	Weight = 90;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 211;
	Description = "Magnesium Powder. It's much easier to ignite than MGSM and also burns hotter.";
	
	Properties = TYPE_PART|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 3000.0f;
	HighTemperatureTransition = PT_PLSM;
	
	Update = &Element_MGMP::update;
	
}

//#TPT-Directive ElementHeader Element_MGMP static int update(UPDATE_FUNC_ARGS)
int Element_MGMP::update(UPDATE_FUNC_ARGS)
 {
	int r, rx, ry;
	rx = rand()%2 -1;
	ry = rand()%2 -1;
	r = pmap[y+ry][x+rx];
	if (!r)
		return 0;
	if (parts[r>>8].type == PT_WATR || parts[r>>8].type == PT_DSTW || parts[r>>8].type == PT_SLTW)
	{
		int chance = rand()%10;
		if (chance == 0)
			return 1;
	}
	return 0;
}


Element_MGMP::~Element_MGMP() {}
