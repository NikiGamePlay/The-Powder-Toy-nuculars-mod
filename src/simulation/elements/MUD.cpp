#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MUD PT_MUD 186
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
	
	State = ST_LIQUID;
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
	int r, rx, ry, rt;
	bool gel;
	if (parts[i].tmp>100) parts[i].tmp = 100;
	if (parts[i].tmp<0) parts[i].tmp = 0;
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				gel=false;
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				rt = r&0xFF;
				
				/*
				float dx, dy;
				dx = parts[i].x - parts[r>>8].x;
				dy = parts[i].y - parts[r>>8].y;

				//Stickiness
				//Fix this so MUD doesn't jump around!
				if ((dx*dx + dy*dy)>1.5 && (gel || !sim->elements[rt].Falldown || (fabs((float)rx)<2 && fabs((float)ry)<2)))
				{
					float per, nd;
					nd = dx*dx + dy*dy - 0.5;
					per = 10*(1 - parts[i].tmp/100)*(nd/(dx*dx + dy*dy + nd) - 0.5);
					if (sim->elements[rt].State==ST_LIQUID)
						per *= 0.1;
					dx *= per; dy *= per;
					parts[i].vx += dx;
					parts[i].vy += dy;
					if ((sim->elements[rt].Properties&TYPE_PART) || rt==PT_GOO)
					{
						parts[r>>8].vx -= dx;
						parts[r>>8].vy -= dy;
					}
				}
				*/
			}
	return 0;
}



//#TPT-Directive ElementHeader Element_MUD static int graphics(GRAPHICS_FUNC_ARGS)
int Element_MUD::graphics(GRAPHICS_FUNC_ARGS)

{
	*pixel_mode |= PMODE_BLUR;
	return 0;
}



Element_MUD::~Element_MUD() {}
