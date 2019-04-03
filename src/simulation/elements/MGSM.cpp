#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MGSM PT_MGSM 191
Element_MGSM::Element_MGSM()
{
	Identifier = "DEFAULT_PT_MGSM";
	Name = "MGSM";
	Colour = PIXPACK(0xDDDDDD);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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
	Meltable = 1;
	Hardness = 1;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 251;
	Description = "Magnesium. A flammable metal, it burns very hot but also requires significant heat to ignite.";
	
	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 3.0f;
	HighPressureTransition = PT_MGMP;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_MGSM::update;
	
}

//#TPT-Directive ElementHeader Element_MGSM static int update(UPDATE_FUNC_ARGS)
int Element_MGSM::update(UPDATE_FUNC_ARGS)
 {
	int r, rx, ry;
	rx = rand()%2 -1;
	ry = rand()%2 -1;
	r = pmap[y+ry][x+rx];
	if (!r)
		return 0;
	if (((parts[r>>8].type == PT_PLSM || parts[r>>8].type == PT_FIRE || parts[r>>8].type == PT_LAVA) && parts[r>>8].temp >= 800) || parts[r>>8].temp >= 2500)
	{
		parts[i].type = PT_PLSM;
		parts[i].life = 150;
		parts[i].temp = 4000;
	}
	return 0;
}


Element_MGSM::~Element_MGSM() {}
