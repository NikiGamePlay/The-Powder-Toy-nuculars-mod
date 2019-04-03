#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_LOGT PT_LOGT 199
Element_LOGT::Element_LOGT()
{
    Identifier = "DEFAULT_PT_LOGT";
    Name = "LOGT";
    Colour = PIXPACK(0x1E90FF);
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
    HotAir = 0.000f * CFDS;
    Falldown = 0;
    
    Flammable = 0;
    Explosive = 0;
    Meltable = 0;
    Hardness = 2;
    
    Weight = 100;
    
    Temperature = R_TEMP+0.0f   +273.15f;
    HeatConduct = 0;
    Description = "Universal Logic Gate, PSCN for input, NSCN for output, TMP 1: AND, 2: OR, 3: NOT, 4: NAND, 5: NOR, 6: XOR, 7: XNOR";
    
    Properties = TYPE_SOLID;
    
    LowPressure = IPL;
    LowPressureTransition = NT;
    HighPressure = 200.0f;
    HighPressureTransition = PT_BRMT;
    LowTemperature = ITL;
    LowTemperatureTransition = NT;
    HighTemperature = ITH;
    HighTemperatureTransition = NT;
    
    Update = &Element_LOGT::update;
    
}

//#TPT-Directive ElementHeader Element_LOGT static int update(UPDATE_FUNC_ARGS)
int Element_LOGT::update(UPDATE_FUNC_ARGS)
 {
    int r, rx, ry, rt;
    int inputs = 0, low = 0, high = 0;

    for (rx = -1; rx < 2; rx++)
    {
        for (ry = -1; ry < 2; ry++)
        {
            if (BOUNDS_CHECK && (rx || ry))
            {
                r = pmap[y + ry][x + rx];
                if (!r)
                    continue;
                rt = (r&0xFF);
                if (rt == PT_PSCN)
                {
                    inputs++;
                    if (parts[r>>8].life == 0)
                        low++;
                    else
                        high++;
                }
                else if (rt == PT_SPRK) {
                    if (parts[r>>8].ctype == PT_PSCN)
                    {
                        inputs++;
                        high++;
                    }
                }
            }
        }
    }

    bool output = false;
    switch (parts[i].tmp)
    {
        case 1: // AND
            output = low == 0; break;
        case 2: // OR
            output = high > 0; break;
        case 3: // NOT
            output = high == 0; break;
        case 4: // NAND
            output = high < inputs; break;
        case 5: // NOR (same as NOT?)
            output = high == 0; break;
        case 6: // XOR
            output = high % 2; break;
        case 7: // XNOR
            output = !(high % 2); break;
    }

    if (output)
    {
        for (rx = -1; rx < 2; rx++)
        {
            for (ry =- 1; ry < 2; ry++)
            {
                if (BOUNDS_CHECK && (rx || ry))
                {
                    r = pmap[y + ry][x + rx];
                    if (!r)
                        continue;
                    if ((r&0xFF) == PT_NSCN && parts[r>>8].life == 0)
                    {
                        parts[r>>8].life = 4;
                        parts[r>>8].ctype = PT_NSCN;
                        sim->part_change_type(r>>8, x+rx, y+ry, PT_SPRK);
                    }
                }
            }
        }
    }
    return 0;
}


Element_LOGT::~Element_LOGT() {}
