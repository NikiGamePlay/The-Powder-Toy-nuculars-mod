#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SOIL PT_SOIL 184
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
    Description = "Soil. SEED can gow to PLNT on this. Mix with WATR to produce MUD.";
    
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
    int r, rx, ry;
    float cxy = 0;
    for (rx=-2; rx<3; rx++)
        for (ry=-2; ry<3; ry++)
            if (BOUNDS_CHECK && (rx || ry))
            {
                r = pmap[y+ry][x+rx];
                if (!r)
                    continue;
                if ((r&0xFF)==PT_WATR)
                {
                    if (!(rand()%1500))
                    {
                        sim->part_change_type(i,x,y,PT_MUD);
                        sim->kill_part(r>>8);
                    }
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
                    if(parts[i].temp <195)
                        cxy = 0.05;
                    else if(parts[i].temp <295)
                        cxy = 0.015;
                    else if(parts[i].temp <350)
                        cxy = 0.01;
                    else
                        cxy = 0.005;
                    parts[i].vx += cxy*rx;
                    parts[i].vy += cxy*ry;//These two can be set not to calculate over 350 later. They do virtually nothing over 0.005.
                }
            }
    return 0;
}


//#TPT-Directive ElementHeader Element_SOIL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_SOIL::graphics(GRAPHICS_FUNC_ARGS)

{
    int z = cpart->tmp - 5;//speckles!
    *colr += z * 16;
    *colg += z * 16;
    *colb += z * 16;
    return 0;
}


Element_SOIL::~Element_SOIL() {}
