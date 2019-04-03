#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MUD PT_MUD 202
Element_MUD::Element_MUD()
{
	Identifier = "DEFAULT_PT_MUD";
	Name = "MUD";
	Colour = PIXPACK(0x493804);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;
	
	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f  * CFDS;
	Falldown = 2;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;
	
	Weight = 35;
	
	Temperature = R_TEMP-2.0f  +273.15f;
	HeatConduct = 29;
	Description = "Mud. Can be heated into BRCK.";
	
	Properties = TYPE_LIQUID|PROP_LIFE_DEC|PROP_NEUTPENETRATE;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = R_TEMP+ 500 +275.15;
	HighTemperatureTransition = PT_BRCK;
	
	Update = &Element_MUD::update;
	Graphics = &Element_MUD::graphics;
}

//#TPT-Directive ElementHeader Element_MUD static int update(UPDATE_FUNC_ARGS)
int Element_MUD::update(UPDATE_FUNC_ARGS)
 {
	int r, rx, ry, rt, trade;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (((r&0xFF) == PT_WATR || (r&0xFF) == PT_SLTW || (r&0xFF) == PT_DSTW) && rand()%3 && parts[i].tmp < 20)
				{
					sim->kill_part(r>>8);
					parts[i].tmp++;
				}
			}

	// Shared tmp thingy ripped off SPNG
    for ( trade = 0; trade<9; trade ++)
	{
		rx = rand()%3-1;
		ry = rand()%3-1;
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y+ry][x+rx];
			if (!r)
				continue;
			if (((r&0xFF)==PT_MUD || (r&0xFF)==PT_SOIL) && (parts[i].tmp>parts[r>>8].tmp) && parts[i].tmp>0)//diffusion
			{
				parts[r>>8].tmp ++;
				parts[i].tmp --;
				trade = 9;
			}
		}
	}

	if (parts[i].tmp <= 9)
		sim->part_change_type(i,x,y, PT_SOIL);
	return 0;
}


//#TPT-Directive ElementHeader Element_MUD static int graphics(GRAPHICS_FUNC_ARGS)
int Element_MUD::graphics(GRAPHICS_FUNC_ARGS)

{
	int z = cpart->tmp / 20.0f;
    *colr -= z * 20.0f;
    *colg -= z * 20.0f;
    *colb -= z * 20.0f;
    *pixel_mode |= PMODE_BLUR;
    return 0;
}



Element_MUD::~Element_MUD() {}
