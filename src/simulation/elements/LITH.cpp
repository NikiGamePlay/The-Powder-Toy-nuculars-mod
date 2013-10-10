#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_LITH PT_LITH 195
Element_LITH::Element_LITH()
{
	Identifier = "DEFAULT_PT_LITH";
	Name = "LITH";
	Colour = PIXPACK(0xADBEC9);
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
	Meltable = 0;
	Hardness = 3;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 50;
	Description = "Lithium, rusts in empty space, explosive, produces ELEC when in contact to BIZR. Recharges when sparked with GOLD.";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID|PROP_HOT_GLOW;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_LITH::update;
	
}

//#TPT-Directive ElementHeader Element_LITH static int update(UPDATE_FUNC_ARGS)
int Element_LITH::update(UPDATE_FUNC_ARGS)
 {
 	if (parts[i].tmp2 == 0 && rand()%2)
 	{
 		sim->part_change_type(i,x,y, PT_BRMT);
 		return 0;
 	}
	int r, rt, rx, ry, trade;
	int r2, rt2, rx2, ry2;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
				{
					if (parts[i].tmp2 > 0)
						parts[i].tmp2--;
					continue;
				}
				if ((r&0xFF) == PT_WATR || (r&0xFF) == PT_SLTW || (r&0xFF) == PT_DSTW)
				{
					if (!(rand()%10))
						sim->part_change_type(i,x,y, PT_ISOZ);
				}
				else if ((r&0xFF) == PT_BIZR || (r&0xFF) == PT_BIZRS || (r&0xFF) == PT_BIZRG)
				{
					if (parts[i].tmp > 0 && !(rand()%3))
					{
						sim->create_part(-1,x+rx,y+ry, PT_ELEC);
						parts[i].tmp--;
					}
				}
				else if ((r&0xFF) == PT_SPRK && parts[r>>8].life==3 && parts[r>>8].ctype==PT_GOLD && parts[i].tmp < 20)
				{
					parts[i].tmp++;
				}
				else if (parts[r>>8].temp > 500.0f+273.15f)
				{
					sim->kill_part(i);
					if (rand()%4 == 0)
						sim->create_part(-1,x,y, PT_PLSM);
					else
						sim->create_part(-1,x,y, PT_FIRE);
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
            if ((r&0xFF)==PT_LITH && (parts[i].tmp>parts[r>>8].tmp) && parts[i].tmp>0)//diffusion
            {
                parts[r>>8].tmp ++;
                parts[i].tmp --;
                trade = 9;
            }
        }
    }

	return 0;
}

//#TPT-Directive ElementHeader Element_LITH static int graphics(GRAPHICS_FUNC_ARGS)
int Element_LITH::graphics(GRAPHICS_FUNC_ARGS)

{
    int z = cpart->tmp / 20;
    *colr -= z * 20;
    *colg -= z * 20;
    *colb -= z * 20;
    return 0;
}

Element_LITH::~Element_LITH() {}
