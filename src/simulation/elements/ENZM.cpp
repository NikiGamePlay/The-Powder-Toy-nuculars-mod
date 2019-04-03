#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ENZM PT_ENZM 194
Element_ENZM::Element_ENZM()
{
	Identifier = "DEFAULT_PT_ENZM";
	Name = "ENZM";
	Colour = PIXPACK(0xA3A37C);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;
	
	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.00f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 90;
	
	Weight = 65;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 150;
	Description = "Enzyme, breaks down things into OIL, grows with GOO, cures VIRS like SOAP does.";
	
	Properties = TYPE_PART;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = R_TEMP+100.0f	+273.15f;
	HighTemperatureTransition = PT_WTRV;
	
	Update = &Element_ENZM::update;
}

//#TPT-Directive ElementHeader Element_ENZM static int update(UPDATE_FUNC_ARGS)
int Element_ENZM::update(UPDATE_FUNC_ARGS)
 {
 	int r, rx, ry, trade, np;
 	bool enzm = false;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (((r&0xFF) == PT_COAL || (r&0xFF) == PT_BCOL) && !(rand()%10))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_OIL);
				}
				else if ((r&0xFF) == PT_BANG && !(rand()%10))
				{
					if (rand()%2)
						sim->part_change_type(r>>8,x+rx,y+ry, PT_NITR);
					else
						sim->part_change_type(r>>8,x+rx,y+ry, PT_CLST);
				}
				else if (((r&0xFF) == PT_PLNT || (r&0xFF) == PT_SEED) && !(rand()%60))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_OIL);
				}
				else if ((r&0xFF) == PT_YEST && !(rand()%70))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_DYST);
				}
				else if ((r&0xFF) == PT_DYST && !(rand()%20))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_OIL);
				}
				else if ((r&0xFF) == PT_WOOD && !(rand()%130))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_DYST);
				}
				else if (((r&0xFF) == PT_PLST || (r&0xFF) == PT_LPLS) && !(rand()%200))
				{
					sim->part_change_type(r>>8,x+rx,y+ry, PT_OIL);
				}
				// TODO: Add more things to break down.
				else if ((r&0xFF) == PT_GOO && !(rand()%10))
				{
					parts[i].life--;
					sim->kill_part(r>>8);
				}
			}

	if (parts[i].life <= 0)
 	{
 		for (rx=-1; rx<2 && !enzm; rx++)
			for (ry=-1; ry<2 && !enzm; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
					{
 						sim->create_part(-1, x+rx, y+ry, PT_ENZM);
 						enzm = true;
 					}
 				}
 		if (enzm)
 		{
 			parts[i].life = rand()%70 +10;
 		}
 	}

 	if (!(rand()%100))
 	{
 		if (!(rand()%5))
 			for (rx=-10; rx<10; rx++)
 				for (ry=-10; ry<10; ry++)
 					if (BOUNDS_CHECK && (rx || ry))
					{
						r = pmap[y+ry][x+rx];
						if (!r)
							continue;
						if ((r&0xFF) == PT_ENZM)
						{
							parts[i].vx += rx / 10.0;
							parts[i].vy += ry / 10.0;
						}
					}
 		parts[i].vx = rand()%3 -1;
 		parts[i].vy = rand()%3 -1;
 	}
	return 0;
}

Element_ENZM::~Element_ENZM() {}
