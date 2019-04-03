#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SEED PT_SEED 185
Element_SEED::Element_SEED()
{
	Identifier = "DEFAULT_PT_SEED";
	Name = "SEED";
	Colour = PIXPACK(0xA3B808);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;
	
	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;
	
	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;
	
	Weight = 60;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 70;
	Description = "Drop it on SOIL and watch it grow!";
	
	Properties = TYPE_PART;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 100.0f +273.15f;
	HighTemperatureTransition = PT_FIRE;
	
	Update = NULL;
	Graphics = NULL;
}

Element_SEED::~Element_SEED() {}
