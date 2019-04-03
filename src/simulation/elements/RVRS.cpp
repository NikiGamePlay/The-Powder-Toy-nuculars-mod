#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RVRS PT_RVRS 196
Element_RVRS::Element_RVRS()
{
	// Suggestion from www.tpt.io/16804
	Identifier = "DEFAULT_PT_RVRS";
	Name = "RVRS";
	Colour = PIXPACK(0x8922FF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;
	
	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.5f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 5;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;
	
	Weight = 99;
	
	Temperature = 80.0f;
	HeatConduct = 70;
	Description = "Reversium, reverses changes to elements. Explodes extremely powerful on contact with GRVT! Also the heaviest liquid.";

	Properties = TYPE_LIQUID;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_RVRS::update;
	
}

//#TPT-Directive ElementHeader Element_RVRS static int update(UPDATE_FUNC_ARGS)
int Element_RVRS::update(UPDATE_FUNC_ARGS)
 {
	int rx, ry, r, ct, j;
	int life = 10;
	rx = rand()%5 -2;
	ry = rand()%5 -2;
	r = pmap[y+ry][x+rx];
	if (!r)
		r = sim->photons[y+ry][x+rx];
	ct = 0;
	if (r)
	{
		switch(r&0xFF)
		{
			case PT_URAN:
				ct = PT_PLUT;
				break;
			case PT_BREC:
				switch(rand()%11)
				{
					case 0:
						ct = PT_WIRE;
						break;
					case 1:
						ct = PT_ARAY;
						break;
					case 2:
						ct = PT_WIFI;
						break;
					case 3:
						ct = PT_INST;
						break;
					case 4:
						ct = PT_TESC;
						break;
					case 5:
						ct = PT_SWCH;
						break;
					case 6:
						ct = PT_PTCT;
						break;
					case 7:
						ct = PT_NTCT;
						break;
					case 8:
						ct = PT_NSCN;
						break;
					case 9:
						ct = PT_PSCN;
						break;
					case 10:
						ct = PT_LITH;
						break;
				}
				break;
			case PT_STNE:
				ct = PT_CLST;
				break;
			case PT_BRMT:
				ct = PT_IRON;
				break;
			case PT_BGLA:
			case PT_GLAS:
				ct = PT_SAND;
				break;
			case PT_DYST:
				ct = PT_YEST;
				break;
			case PT_BANG:
				ct = PT_NITR;
				break;
			case PT_DSTW:
				ct = PT_WATR;
				break;
			case PT_FOG:
				ct = PT_BOYL;
				break;
			case PT_ISOZ:
				ct = PT_ACID;
				break;
			case PT_FWRK:
				ct = PT_GUNP;
				break;
			case PT_PLNT:
				ct = PT_SEED;
				break;
			case PT_VIBR:
			case PT_BVBR:
				ct = PT_BOLT;
				break;
			case PT_GRVT:
				PropertyValue value;
				value.Integer = life;
				sim->flood_prop(x,y,offsetof(Particle,life),value,StructProperty::Integer);
				break;
		}
		if (ct)
			sim->part_change_type(r>>8,x+rx,y+ry, ct);
		if (parts[i].life == 10)
		{
			// BOOM!
			for (int k = 0; k < 5; k++)
			{
				j = sim->create_part(-3,x+rand()%6-2,y+rand()%6-2,PT_PROT);
				if (j>-1)
					parts[j].temp = MAX_TEMP;
			}
			j = sim->create_part(-3,x+rand()%3-1,y+rand()%3-1,PT_NEUT);
			if (j>-1)
				parts[j].temp = MAX_TEMP;
			j = sim->create_part(-3,x+rand()%3-1,y+rand()%3-1,PT_PHOT);
			if (j>-1)
				parts[j].temp = MAX_TEMP;
			j = sim->create_part(-3,x+rand()%3-1,y+rand()%3-1,PT_ELEC);
			if (j>-1)
				parts[j].temp = MAX_TEMP;
			j = sim->create_part(-3,x+rand()%3-1,y+rand()%3-1,PT_BOLT);
			if (j>-1)
				parts[j].temp = MAX_TEMP;
			j = sim->create_part(-3,x+rand()%3-1,y+rand()%3-1,PT_GRVT);
			if (j != -1)
			{
				parts[j].temp = MAX_TEMP;
				parts[j].tmp = rand()%255 - rand()%255;
			}
			if (!(rand()%5))
			{
				sim->part_change_type(i,x,y, PT_PLSM);
				parts[i].life = rand()%100 +50;
			}
			parts[i].temp = MAX_TEMP;
			sim->pv[y/CELL][x/CELL] += 30;
		}
	}
	return 0;
}

Element_RVRS::~Element_RVRS() {}
