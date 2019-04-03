#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ANT2 PT_ANT2 187
Element_ANT2::Element_ANT2()
{
	Identifier = "DEFAULT_PT_ANT2";
	Name = "ANT2";
	Colour = PIXPACK(0xEEEEBB);
	MenuVisible = 0;
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
	Meltable = 1;
	Hardness = 1;

	Weight = 100;

	Temperature = 0.0f;
	HeatConduct = 0;
	Description = "ANT can walk on here.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = NULL;
	Graphics = &Element_ANT2::graphics;

}

//#TPT-Directive ElementHeader Element_ANT2 static int graphics(GRAPHICS_FUNC_ARGS)
int Element_ANT2::graphics(GRAPHICS_FUNC_ARGS)

{
	if (cpart->tmp && cpart->tmp2)
	{
		float i = restrict_flt(cpart->tmp / (cpart->tmp2 + 1.0f), 0.2f, 1.0f);

		if(ren->decorations_enable && cpart->dcolour && (cpart->dcolour&0xFF000000))
		{
			*colr = (cpart->dcolour>>16)&0xFF;
			*colg = (cpart->dcolour>>8)&0xFF;
			*colb = (cpart->dcolour)&0xFF;
		}
		
		*colr *= i;
		*colg *= i;
		*colb *= i;
	}

	*pixel_mode |= NO_DECO;

	return 0;
}

Element_ANT2::~Element_ANT2() {}
