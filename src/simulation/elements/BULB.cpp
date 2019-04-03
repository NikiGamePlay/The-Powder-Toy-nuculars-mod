#include "simulation/Elements.h"
#include "simulation/Air.h"
//#TPT-Directive ElementClass Element_BULB PT_BULB 197
Element_BULB::Element_BULB()
{
	Identifier = "DEFAULT_PT_BULB";
	Name = "BULB";
	Colour = PIXPACK(0xAABBFF);
	MenuVisible = 1;
	MenuSection = SC_POWERED;
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
	Hardness = 30;

	Weight = 100;

	Temperature = R_TEMP+0.0f +273.15f;
	HeatConduct = 100;
	Description = "Light bulb. Decorator, glows when constantly sparked.";

	Properties = TYPE_SOLID|PROP_HOT_GLOW|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1800.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_BULB::update;
	Graphics = &Element_BULB::graphics;
	
}

//#TPT-Directive ElementHeader Element_BULB static int update(UPDATE_FUNC_ARGS)
int Element_BULB::update(UPDATE_FUNC_ARGS)
 {
 	int r, rx, ry, nb;

	parts[i].pavg[0] = parts[i].pavg[1];
	parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
	if (parts[i].pavg[1]-parts[i].pavg[0] > 0.25f || parts[i].pavg[1]-parts[i].pavg[0] < -0.25f)
	{
		if (!(rand()%2))
			sim->part_change_type(i,x,y,PT_BGLA);
		else
			sim->part_change_type(i,x,y,PT_BREC);
	}

	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				int newlife = 15;
				if (!r)
					continue;
				if (parts[r>>8].type == PT_SPRK && parts[r>>8].life == 3)
				{
					PropertyValue value;
					value.Integer = newlife;
					sim->flood_prop(x,y,offsetof(Particle,life),value,StructProperty::Integer);
				}
			}
	return 0;
}

//#TPT-Directive ElementHeader Element_BULB static int graphics(GRAPHICS_FUNC_ARGS)
int Element_BULB::graphics(GRAPHICS_FUNC_ARGS)
{
	*pixel_mode |= FIRE_BLEND;
	*pixel_mode |= DECO_FIRE;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb;
	
	if (cpart->life > 0)
	{
		*firea = (cpart->life / 15.0f) * 255.0f;
	} 	
	else
	{
		*firea = 0;
	}
	return 0;
}

Element_BULB::~Element_BULB() {}
