#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_PLDM PT_PLDM 204
Element_PLDM::Element_PLDM()
{
	Identifier = "DEFAULT_PT_PLDM";
	Name = "PLDM";
	Colour = PIXPACK(0x909090);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
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
	Hardness = 50;

	Weight = 100;

	Temperature = R_TEMP+0.0f +273.15f;
	HeatConduct = 251;
	Description = "Palladium. Can absorb HYGN, converts it into CO2, NBLE and OXYG if sparked.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_HOT_GLOW|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1941.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_PLDM::update;
	Graphics = &Element_PLDM::graphics;

}

//#TPT-Directive ElementHeader Element_PLDM static int update(UPDATE_FUNC_ARGS)
int Element_PLDM::update(UPDATE_FUNC_ARGS)
{
    // Put out the gasses if sparked
    if (parts[i].life == 2 && parts[i].tmp > 0) {
        for (int rx=-1; rx<2; rx++)
            for (int ry=-1; ry<2; ry++)
                if (BOUNDS_CHECK && (rx || ry) && (pmap[y+ry][x+rx]&0xFF) == PT_NONE)
                {
                    int eltype = rand() % 20;
                    if (eltype < 2)
                        sim->create_part(-1, x+rx, y+ry, PT_CO2);
                    if (eltype == 2)
                        sim->create_part(-1, x+rx, y+ry, PT_NBLE);
                    if (eltype == 3)
                        sim->create_part(-1, x+rx, y+ry, PT_O2);
                    if (parts[i].tmp > 0)
                        parts[i].tmp--;
                    ry = 2;
                    rx = 2;
                }
    }

    // Suck in HYGN
    int r, trade, rx, ry, np;
    for (int rx=-1; rx<2; rx++) {
        for (int ry=-1; ry<2; ry++) {
            r = pmap[y+ry][x+rx];
            if ((r&0xFF)==PT_H2 && parts[i].tmp<18) {
                sim->kill_part(r>>8);
                parts[i].tmp++;
            }
            if ((r&0xFF)==PT_STOR || (r&0xFF)==PT_PIPE || (r&0xFF)==PT_PPIP) {
                if (parts[r>>8].tmp==PT_H2 && parts[i].tmp<18) {
                    parts[r>>8].tmp = 0;
                    parts[i].tmp++;
                }
            }
        }
    }

    // Shared tmp thingy ripped off SPNG
    for ( trade = 0; trade<9; trade ++)
	{
		rx = rand()%5-2;
		ry = rand()%5-2;
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y+ry][x+rx];
			if (!r)
				continue;
			if ((r&0xFF)==PT_PLDM && (parts[i].tmp>parts[r>>8].tmp) && parts[i].tmp>0)//diffusion
			{
				parts[r>>8].tmp ++;
				parts[i].tmp --;
				trade = 9;
			}
		}
	}
}

//#TPT-Directive ElementHeader Element_PLDM static int graphics(GRAPHICS_FUNC_ARGS)
int Element_PLDM::graphics(GRAPHICS_FUNC_ARGS)
{
	*colr -= cpart->tmp*3;
	*colg -= cpart->tmp*3;
	*colb -= cpart->tmp*3;
	if (*colr<=20)
		*colr = 20;
	if (*colg<=20)
		*colg = 20;
	if (*colb<=20)
		*colb = 20;
	return 0;
}

Element_PLDM::~Element_PLDM() {}
