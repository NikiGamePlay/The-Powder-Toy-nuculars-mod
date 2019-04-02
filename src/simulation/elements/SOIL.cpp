#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SOIL PT_SOIL 210
Element_SOIL::Element_SOIL()
{
    Identifier = "DEFAULT_PT_SOIL";
    Name = "SOIL";
    Colour = PIXPACK(0x9F7616);
    MenuVisible = 1;
    MenuSection = SC_POWDERS;
    Enabled = 1;
    
    Advection = 0.7f;
    AirDrag = 0.02f * CFDS;
    AirLoss = 0.94f;
    Loss = 0.95f;
    Collision = 0.0f;
    Gravity = 0.2f;
    Diffusion = 0.00f;
    HotAir = 0.000f * CFDS;
    Falldown = 1;
    
    Flammable = 0;
    Explosive = 0;
    Meltable = 2;
    Hardness = 2;
    
    Weight = 70;
    
    Temperature = R_TEMP+0.0f   +273.15f;
    HeatConduct = 70;
    Description = "Soil. SEED can grow to PLNT on this. Mix with WATR to produce MUD.";
    
    State = ST_SOLID;
    Properties = TYPE_PART;
    
    LowPressure = IPL;
    LowPressureTransition = NT;
    HighPressure = IPH;
    HighPressureTransition = NT;
    LowTemperature = ITL;
    LowTemperatureTransition = NT;
    HighTemperature = 2000.0f;
    HighTemperatureTransition = PT_LAVA;
    
    Update = &Element_SOIL::update;
    Graphics = &Element_SOIL::graphics;
}

//#TPT-Directive ElementHeader Element_SOIL static int update(UPDATE_FUNC_ARGS)
int Element_SOIL::update(UPDATE_FUNC_ARGS)
 {
    int r, rx, ry, trade;
    float spd, cxy = 0;
    for (rx=-2; rx<3; rx++)
        for (ry=-2; ry<3; ry++)
            if (BOUNDS_CHECK && (rx || ry))
            {
                r = pmap[y+ry][x+rx];
                if (!r)
                    continue;
                if (((r&0xFF) == PT_WATR || (r&0xFF) == PT_SLTW || (r&0xFF) == PT_DSTW) && rand()%3)
                {
                    sim->kill_part(r>>8);
                    parts[i].tmp += 2;
                }
                else if ((r&0xFF)==PT_SEED)
                {
                    if (parts[r>>8].life==0) {
                        sim->create_part(i, x, y, PT_VINE);
                        sim->create_part(r>>8, x+rx, y+ry, PT_VINE);
                    }
                    else
                        if (parts[r>>8].life > 0)
                            parts[r>>8].life--;
                }
                else if ((r&0xFF)==PT_SOIL)
                {
                    if(parts[i].tmp <2)
                        spd = 0.125;
                    else if(parts[i].tmp <6)
                        spd = 0.25;
                    else if(parts[i].tmp <8)
                        spd = 0.5;
                    else
                        spd = 1;
                    parts[i].vx += 0.05*(rx*spd);
                    parts[i].vy += 0.05*(ry*spd);
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

    if (parts[i].tmp >= 10)
        sim->part_change_type(i,x,y, PT_MUD);
    return 0;
}


//#TPT-Directive ElementHeader Element_SOIL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_SOIL::graphics(GRAPHICS_FUNC_ARGS)

{
    int z = cpart->tmp / 2.0f;
    *colr += -17.2 * z;
    *colg += -12.4 * z;
    *colb += -3.6 * z;
    return 0;
}


Element_SOIL::~Element_SOIL() {}
