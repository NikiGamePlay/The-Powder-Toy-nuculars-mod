#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_OTWR PT_OTWR 203
Element_OTWR::Element_OTWR()
{
	Identifier = "DEFAULT_PT_OTWR";
	Name = "OTWR";
	Colour = PIXPACK(0x505060);
	MenuVisible = 1;
	MenuSection = SC_ELEC;
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
	Description = "One time wire. Since every mod seems to have one.";
	
	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1273.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_OTWR::update;
}

//#TPT-Directive ElementHeader Element_OTWR static int update(UPDATE_FUNC_ARGS)
int Element_OTWR::update(UPDATE_FUNC_ARGS)
{
    if (parts[i].life <= 4 && parts[i].life > 0) {
        sim->kill_part(i);
    }
}

Element_OTWR::~Element_OTWR() {}
