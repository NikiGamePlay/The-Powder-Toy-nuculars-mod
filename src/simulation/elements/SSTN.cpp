#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SSTN PT_SSTN 193
Element_SSTN::Element_SSTN()
{
	Identifier = "DEFAULT_PT_SSTN";
	Name = "SSTN";
	Colour = PIXPACK(0xF1BD82);
	MenuVisible = 0;
	MenuSection = SC_SOLIDS;
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
	Meltable = 5;
	Hardness = 20;

	Weight = 100;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 150;
	Description = "Sandstone. Erodes easily with ACID or BASE.";

	Properties = TYPE_SOLID|PROP_HOT_GLOW;

	LowPressure = -7.0f;
	LowPressureTransition = PT_SAND;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1223.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = NULL;
}

Element_SSTN::~Element_SSTN() {}
