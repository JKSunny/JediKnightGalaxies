gfx/ui/main_bg_smoke
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_bg_smoke
        rgbGen wave random 0.9 0.1 0 1
        tcMod scroll 0.06 0.02
        tcMod turb 0 0.02 0 0.1
    }
    {
        map gfx/ui/main_bg_dust
        blendFunc GL_ONE GL_ONE
        rgbGen wave random 0.9 0.1 0.1 1
        tcMod scroll 0.01 -0.07
        tcMod turb 0 0.02 0 0.1
    }
}

gfx/ui/main_video_roq
{
	nopicmip
	nomipmaps
    {
        videoMap video/ja09	//04, 05, 07, 08
        tcMod transform 1.35 -0.1 0.42 1.1 -0.38 0.02
    }
    {
        map gfx/ui/main_video
        blendFunc GL_ONE GL_ONE
        rgbGen wave random 0.8 0.1 0 1
    }
    {
        map gfx/ui/main_darkline
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        tcMod scroll 0 -0.2
        tcMod transform 1 -3.2 0 32 0 0
    }
}

gfx/ui/main_video_exit
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_video_bsod
    }
    {
        map gfx/ui/main_video
        blendFunc GL_ONE GL_ONE
        rgbGen wave random 0.8 0.1 0 1
    }
    {
        map gfx/ui/main_darkline
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        tcMod scroll 0 -0.2
        tcMod transform 1 -3.2 0 32 0 0
    }
}

gfx/ui/main_bg
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_bg2
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    }
    {
        map gfx/ui/main_bg
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen wave noise 0.5 0.1 0 3
    }
    {
        map gfx/ui/main_bg_glow
        blendFunc GL_ONE GL_ONE
        rgbGen wave random 0.5 0.07 0 1
    }
    {
        map gfx/ui/main_bg_holo
        blendFunc GL_ONE GL_ONE
        rgbGen wave noise 0.8 0.2 0 3
    }
}

gfx/ui/main_bg_logo
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_bg_logo
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    }
}

gfx/ui/main_bg_grain
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_bg_grain
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        tcMod scroll 2 4
        tcMod scale 11 8
    }
}

gfx/ui/mainsub_bg
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/mainsub_bg
    }
    {
        map gfx/ui/mainsub_bg_glow
        blendFunc GL_ONE GL_ONE
        rgbGen wave random 0.5 0.07 0 1
    }
    {
        map gfx/ui/mainsub_bg_holo
        blendFunc GL_ONE GL_ONE
        rgbGen wave noise 0.8 0.2 0 3
    }
}

gfx/ui/mainsub_datapad_lines
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/main_darkline
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        tcMod scroll 0 -0.1
        tcMod scale 0 64
    }
}

gfx/ui/inv_overlay
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/inv_overlay
        blendFunc GL_DST_COLOR GL_ONE
    }
}

gfx/ui/shop_overlay
{
	nopicmip
	nomipmaps
    {
        map gfx/ui/shop_overlay
        blendFunc GL_DST_COLOR GL_ONE
    }
}

gfx/jkghud/topright_overlay
{
	nopicmip
	nomipmaps
    {
        map gfx/jkghud/topright_overlay
        blendFunc GL_DST_COLOR GL_ONE
    }
}