// Replaces the BaseJKA crosshairs with JKG ones
// cg_drawCrosshair [number] doesn't correspond directly to letters - see comments

gfx/2d/crosshaira	// 9
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/e-11_rifle/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairb	// 1 - default
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/bryar_rifle/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairc	// 2
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/a200_acp_battlerifle/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshaird	// 3
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/dlt-19_heavyblaster/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshaire	// 4
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/dc-15a_rifle/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairf	// 5
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/lt-60_slugcarbine/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairg	// 6
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/bowcaster_heavy/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairh	// 7
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/drsln_slugrifle/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}

gfx/2d/crosshairi	// 8
{
	nomipmaps
	cull	twosided
    {
        ClampMap models/weapons/de-10_pistol/crosshair
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}
