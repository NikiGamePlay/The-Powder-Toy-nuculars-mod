#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_LPLS PT_LPLS 208
Element_LPLS::Element_LPLS()
{
	Identifier = "DEFAULT_PT_LPLS";
	Name = "LPLS";
	Colour = PIXPACK(0x008B8B);
	MenuVisible = 0;
	MenuSection = SC_LIQUID;
	Enabled = 1;
	
	Advection = 0.3f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.95f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.15f;
	Diffusion = 0.00f;
	HotAir = 0.0003f	* CFDS;
	Falldown = 2;
	
	Flammable = 1;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;
	
	Weight = 45;
	
	Temperature = R_TEMP+300.0f+273.15f;
	HeatConduct = 60;
	Description = "Liquid Plastic. Not THAT useful. Slightly flammable.";
	
	State = ST_LIQUID;
	Properties = TYPE_LIQUID|PROP_LIFE_DEC;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = R_TEMP+200.0f +273.15f;
	LowTemperatureTransition = PT_PLST;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = NULL;
	Graphics = NULL;
}

Element_LPLS::~Element_LPLS() {}
