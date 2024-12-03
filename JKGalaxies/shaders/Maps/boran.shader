
textures/boran/river
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material water
	deformvertexes normal 0.1 0.1
	deformvertexes wave 100 sin 1 2 2 0.6
	cull	twosided
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ONE
    }
    {
        map envmaps/dantooine
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen identity
        alphaGen const 0.4
        tcGen environment
    }
    {
        map envmaps/dantooine_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        glow
        rgbGen const ( 0.821805 0.665614 1 )
        alphaGen lightingSpecular
        tcGen environment
    }
    {
        map gfx/water/surface_50
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        rgbGen identity
        tcMod scroll 0.02 -0.05
        tcMod turb 1 0.001 0 0.3
    }
    {
        map gfx/water/surface2_50
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        rgbGen identity
        tcMod scroll -0.02 -0.03
        tcMod stretch sin 1 0.002 0 0.7
    }
}



textures/boran/dantooine_sky
{
	qer_editorimage	textures/skies/sky
	surfaceparm	sky
	surfaceparm	noimpact
	surfaceparm	nomarks
	notc
	q3map_nolightmap
	skyParms	textures/boran/dant 1024 -
}

textures/asjc_geonosis/sjc_geo
{
	qer_editorimage	textures/skies/sky
	surfaceparm	sky
	surfaceparm	noimpact
	surfaceparm	nomarks
	notc
	q3map_nolightmap
	skyParms	textures/asjc_geonosis/sjcgeo 1024 -
}

textures/boran/cobble
{
    {
        map $lightmap
    }
    {
        map textures/boran/cobble
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/cobble_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
}

textures/boran/pave1
{
    {
        map $lightmap
    }
    {
        map textures/boran/pave1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/pave_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
}

textures/boran/pave2
{
    {
        map $lightmap
    }
    {
        map textures/boran/pave2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/pave_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
}

textures/boran/pave3
{
    {
        map $lightmap
    }
    {
        map textures/boran/pave3
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/pave_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
}

textures/boran/2crystal_rock
{
	q3map_lightimage	textures/boran/2crystal_rock_glw
	qer_editorimage		textures/Asjc_snow/mushroom_blue
	q3map_surfacelight	800
	q3map_lightsubdivide	60
    {
        map $lightmap
    }
    {
        map textures/boran/2crystal_rock
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/2crystal_rock_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 1 1 0 111
    }
    {
	map textures/boran/2crystal_rock2_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0 1 0 88
    }
    {   
map textures/boran/crystall_env
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen const 0.25
        tcGen environment
    }

}

textures/boran/crystal_rock
{
	q3map_lightimage	textures/boran/crystal_rock_glw
	qer_editorimage		textures/Asjc_snow/mushroom_blue
	q3map_surfacelight	800
	q3map_lightsubdivide	60
    {
        map $lightmap
    }
    {
        map textures/boran/crystal_rock
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/crystal_rock_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 1 1 0 111
    }
    {
	map textures/boran/crystal_rock2_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0 1 0 88
    }
    {   
map textures/boran/crystall_env
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen const 0.25
        tcGen environment
    }

}


textures/boran/river_old
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material water
	deformvertexes normal 0.1 0.1
      deformvertexes	wave	100 sin 1 2 2 0.6
    	{
        animMap 8 textures/boran/1 textures/boran/2 textures/boran/3 textures/boran/4 textures/boran/5 textures/boran/6 textures/boran/7 textures/boran/8 textures/boran/9 textures/boran/10 textures/boran/9 textures/boran/8 textures/boran/7 textures/boran/6 textures/boran/5 textures/boran/4 textures/boran/3 textures/boran/2
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.8
    	}
    	{
        map textures/boran/water_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
	glow
    	}
      {
	  map textures/boran/dantooine_envmap_sun.tga
	  rgbGen const ( 0.821805 0.665614 1 ) 
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.3
	tcGen environment
	glow
	}
}


textures/boran/grass_1
{
	qer_editorimage	textures/boran/grass_1
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material	Glass
	deformvertexes	autoSprite
    {
        map textures/boran/grass_1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaGen const 1
    }
}

textures/boran/grass_2
{
	qer_editorimage	textures/boran/grass_2
	q3map_shadeangle 90
	q3map_material	ShortGrass
	cull	twosided
    {
        map $lightmap
    }
    {
        map textures/boran/grass_2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/med1
            surfaceSprites vertical 32 24 42 500
            ssFademax 1500
            ssFadescale 1
            ssVariance 1 2
            ssWind 0.5
        alphaFunc GE192
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen vertex
    }
}

textures/boran/grass
{
	qer_editorimage	textures/boran/grass
	q3map_shadeangle 90
	q3map_material	ShortGrass
	cull	twosided
    {
        map $lightmap
    }
    {
        map textures/boran/grass
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/med2
            surfaceSprites vertical 32 24 42 500
            ssFademax 1500
            ssFadescale 1
            ssVariance 1 2
            ssWind 0.5
        alphaFunc GE192
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen vertex
    }
}

textures/boran/grass_bullrush
{
	qer_editorimage	textures/boran/grass_2
	q3map_shadeangle 90
	q3map_material	ShortGrass
	cull	twosided
    {
        map $lightmap
    }
    {
        map textures/boran/grass_2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/riverrush
            surfaceSprites vertical 32 24 42 500
            ssFademax 1500
            ssFadescale 1
            ssVariance 1 2
            ssWind 0.5
        alphaFunc GE192
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen vertex
    }
}

textures/boran/stone1a
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/stone1a
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/stone1a
 		blendFunc filter
	}
}

textures/boran/wall
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/wall
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/wall
 		blendFunc filter
	}
}

textures/boran/wall2
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/wall2
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/wall2
 		blendFunc filter
	}
}


textures/boran/wallgreen
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/wallgreen
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/wallgreen
 		blendFunc filter
	}
}

textures/boran/wallgrass
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/wallgrass
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/wallgrass
 		blendFunc filter
	}
}


textures/boran/grassfade1
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/grassfade1
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/grassfade1
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/grassfade2
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/grassfade2
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/grassfade2
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/grassfade3
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/grassfade3
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/grassfade3
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/sith_jp10
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/sith_jp10
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/sith_jp10
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/river_wall1
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/river_wall1
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/river_wall1
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}


textures/boran/grassfade4
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/grassfade4
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/grassfade4
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}


textures/boran/grass
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/grass
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/grass
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}



textures/boran/sith_jp10
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/sith_jp10
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/sith_jp10
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/dome
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/dome
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/dome
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/rim
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/rim
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/rim
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/templ1
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/templ1
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/templ1
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/tree
{
	q3map_shadeangle	98
	qer_editorimage	textures/boran/tree
	q3map_nonplanar
	q3map_splotchfix
	q3map_forcemeta
    {
        map textures/boran/tree
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        rgbGen identity
    }
}

textures/boran/vine
{
	qer_editorimage	textures/boran/vine
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
	deformvertexes	wave	300 sin 0 3 4 0.55
    {
        map textures/boran/vine
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/treesjc
{
	qer_editorimage	textures/boran/treesjc
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
	deformvertexes	wave	300 sin 0 3 4 0.55
    {
        map textures/boran/treesjc
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}


textures/boran/bridge_end
{
    {
        map $lightmap
    }
    {
        map textures/boran/bridge_end
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/bridge_end_glw
        blendFunc GL_ONE GL_ONE
	glow
    }
}

textures/boran/bridge1
{
    {
        map $lightmap
    }
    {
        map textures/boran/bridge1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/bridge1_glw
        blendFunc GL_ONE GL_ONE
	glow
    }
}

textures/boran/antenna1
{
    {
        map $lightmap
    }
    {
        map textures/boran/antenna1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/antenna_glw
        blendFunc GL_ONE GL_ONE
	glow
    }
}

textures/boran/antenna2
{
    {
        map $lightmap
    }
    {
        map textures/boran/antenna2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/antenna_glw
        blendFunc GL_ONE GL_ONE
	glow
    }
}

textures/boran/antenna2a
{
    {
        map $lightmap
    }
    {
        map textures/boran/antenna2a
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/antenna_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_light_1
{
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_light_1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_light_1_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_plate_lights
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_plate_lights
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_plate_lights_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_plate_light_1a
{
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_plate_light_1a
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_plate_light_1a_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_plate_lightsa
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_plate_lightsa
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_plate_lightsa_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_plate_lights2
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_plate_lights2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_plate_lights2_glw
        blendFunc GL_ONE GL_ONE
    }
}


textures/wookiesjc/seat_back
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/seat_back
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/seat_back_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_controls
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_controls
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_controls_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_controls2
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_controls2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_controls2_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/chess_side
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/chess_side
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/chess_side_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_plate_light_1
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_plate_light_1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_plate_light_1_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/door_side
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/door_side
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/door_side_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/han_hole1
{
qer_editorimage textures/wookiesjc/han_hole1
surfaceparm nonopaque
surfaceparm trans
surfaceparm alphashadow
cull twosided
qer_trans 1.0
{
map textures/wookiesjc/han_hole1
alphaFunc GE128
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/wookiesjc/falcon_window_hull
{
qer_editorimage textures/wookiesjc/falcon_window_hull
surfaceparm nonopaque
surfaceparm trans
surfaceparm alphashadow
cull twosided
qer_trans	0.4
{
map textures/wookiesjc/falcon_window_hull
alphaFunc GE128
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/wookiesjc/falcon_window_hull2
{
qer_editorimage textures/wookiesjc/falcon_window_hull2
surfaceparm nonopaque
surfaceparm trans
surfaceparm alphashadow
cull twosided
qer_trans 0.4
{
map textures/wookiesjc/falcon_window_hull2
alphaFunc GE128
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}

textures/wookiesjc/bulk_head_light
{
qer_editorimage textures/wookiesjc/bulk_head_light
surfaceparm nonopaque
surfaceparm trans
surfaceparm alphashadow
cull twosided
qer_trans 1.0
{
map textures/wookiesjc/bulk_head_light
alphaFunc GE128
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
depthWrite
}
{
map $lightmap
rgbGen identity
blendFunc GL_DST_COLOR GL_ZERO
depthFunc equal
}
}


textures/wookiesjc/floor5
{
	q3map_material	SolidMetal
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/floor5
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/falcon_sjc/env_basic2
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen const 0.10
        tcGen environment
    }
}

textures/wookiesjc/chair_panel
{
	qer_editorimage	textures/wookiesjc/chair_panel
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/chair_panel
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/chair_panel_glw
        blendFunc GL_ONE GL_ONE
    }
    {
        map textures/wookiesjc/chair_panel2_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0 1 0 1
    }
}

textures/wookiesjc/cockpit_1
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/cockpit_1
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/cockpit_1_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/cockpit_2
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/cockpit_2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/cockpit_2_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/cockpit_3
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/cockpit_3
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/cockpit_3_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/1
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material	Glass
    {
        animMap 3 textures/wookiesjc/1 textures/wookiesjc/2 textures/wookiesjc/3
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.8
        rgbGen wave sin 0.75 0.05 0 5
    }
}

textures/wookiesjc/gears2
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material	Glass
	cull	twosided
    {
        animMap 2 textures/wookiesjc/gears2 textures/wookiesjc/1 textures/wookiesjc/2 textures/wookiesjc/3
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.8
        rgbGen wave sin 0.75 0.05 0 5
    }
}

textures/wookiesjc/a
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material	Glass
    {
        animMap 1.5 textures/wookiesjc/a textures/wookiesjc/b textures/wookiesjc/c textures/wookiesjc/d
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.8
        rgbGen wave sin 0.75 0.05 0 5
    }
}

textures/wookiesjc/font1
{
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	q3map_material	Glass
	cull	twosided
    {
        animMap 1 textures/wookiesjc/font1 textures/wookiesjc/font2 textures/wookiesjc/font3 textures/wookiesjc/font4
blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen const 0.8
        rgbGen wave sin 0.75 0.05 0 5
    }
}

textures/wookiesjc/falcon_floor_panels
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_floor_panels
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_floor_panels_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_floor_panels_l

{
// final

	qer_editorimage	textures/wookiesjc/falcon_floor_panels_l

	q3map_surfacelight	300
	q3map_lightsubdivide	60
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_floor_panels_l

        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_floor_panels_l_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0.75 0.005 0 10
    }
}

textures/wookiesjc/falcon_hull_dockring
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/falcon_hull_dockring
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/falcon_hull_dockring_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/falcon_window_frost
{
	qer_editorimage	textures/wookiesjc/falcon_window_frost
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	cull	twosided
        {
        map textures/wookiesjc/falcon_window_frost
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaGen const 10
        }
}

textures/wookiesjc/falcon_window_frost2
{
	qer_editorimage	textures/wookiesjc/falcon_window_frost2
	qer_trans	0.4
	surfaceparm	nonopaque
	surfaceparm	nonsolid
	surfaceparm	trans
	cull	twosided
        {
        map textures/wookiesjc/falcon_window_frost2
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaGen const 10
        }
}



textures/wookiesjc/cockpit_4
{
	qer_editorimage	textures/wookiesjc/cockpit_4
    {
        map $lightmap
    }
    {
        map textures/wookiesjc/cockpit_4
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/cockpit_4_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 1.3 0.5 1 0.3
    }
    {
        map textures/wookiesjc/cockpit_42_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0 1 0 1
    }
    {
        map textures/wookiesjc/cockpit_43_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 1 1 0 111
    }
}

textures/wookiesjc/panel_large_alpha
{
	qer_editorimage	textures/wookiesjc/panel_large_alpha
	surfaceparm     nonsolid
	surfaceparm	nomarks
	q3map_alphashadow
    {
        map textures/wookiesjc/panel_large_alpha
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/wookiesjc/chair_panel_3
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/chair_panel_3
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/chair_panel_3_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/wookiesjc/cockpit_door
{   
	{
        map $lightmap
    }
    {
        map textures/wookiesjc/cockpit_door
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/wookiesjc/cockpit_door_glw
        blendFunc GL_ONE GL_ONE
    }
}


textures/boran/taris_3
{   
	{
        map $lightmap
    }
    {
        map textures/boran/taris_3
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/taris_3_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/boran/taris_4
{   
	{
        map $lightmap
    }
    {
        map textures/boran/taris_4
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/taris_4_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/boran/taris_5
{   
	{
        map $lightmap
    }
    {
        map textures/boran/taris_5
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/taris_5_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/boran/taris_6
{   
	{
        map $lightmap
    }
    {
        map textures/boran/taris_6
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/taris_6_glw
        blendFunc GL_ONE GL_ONE
    }
}

textures/boran/gungan
{   
	{
        map $lightmap
    }
    {
        map textures/boran/gungan
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/gungan_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0.75 0.005 0 10
    }
}

textures/boran/jump_pad
{   
	{
        map $lightmap
    }
    {
        map textures/boran/jump_pad
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/jump_pad_glw
        blendFunc GL_ONE GL_ONE
        rgbGen wave sin 0.75 0.005 0 10
    }
}


textures/boran/dirt
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/dirt
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/dirt
 		blendFunc filter
	}
}

textures/boran/mid
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/mid
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/mid
 		blendFunc filter
	}
}


textures/boran/dirt2
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/dirt2
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/dirt2
 		blendFunc filter
	}
}

textures/boran/dirt4
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/dirt4
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/dirt4
 		blendFunc filter
	}
}


textures/boran/dirt_crack
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/dirt_crack
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/dirt_crack
 		blendFunc filter
	}
}

textures/boran/cave
{
	q3map_nonplanar
 	q3map_shadeangle 45
	q3map_material	dirt
 	qer_editorimage textures/boran/cave
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave
 		blendFunc filter
	}
}

textures/boran/gungan
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	sand
 	qer_editorimage textures/boran/gungan
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/gungan
 		blendFunc filter
	}
}

textures/boran/broken_rock
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/broken_rock
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/broken_rock
 		blendFunc filter
	}
}


textures/boran/cave1
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave1
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave1
 		blendFunc filter
	}
}

textures/boran/cave_new2
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave_new2
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave_new2
 		blendFunc filter
	}
}

textures/boran/cave_new
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave_new
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave_new
 		blendFunc filter
	}
}

textures/boran/cave_fade_vine_r
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave_fade_vine_r
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave_fade_vine_r
 		blendFunc filter
	}
}

textures/boran/cave_fade_vine_c
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave_fade_vine_c
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave_fade_vine_c
 		blendFunc filter
	}
}

textures/boran/cave_fade_vine_l
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/boran/cave_fade_vine_l
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/cave_fade_vine_l
 		blendFunc filter
	}
}


textures/sockter/ter_rock2
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	dirt
 	qer_editorimage textures/sockter/ter_rock2
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/sockter/ter_rock2
 		blendFunc filter
	}
}

textures/boran/secret_door
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	ShortGrass
 	qer_editorimage textures/boran/secret_door
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/secret_door
 		blendFunc filter
	}
}

textures/boran/grass_4
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	ShortGrass
 	qer_editorimage textures/boran/grass_4
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/grass_4
 		blendFunc filter
	}
}


textures/boran/vine2
{
	qer_editorimage	textures/boran/vine2
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
    {
        map textures/boran/vine2
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/ring
{
	qer_editorimage	textures/boran/ring
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
    {
        map textures/boran/ring.tga
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/bell
{
	q3map_material	SolidMetal
    {
        map $lightmap
    }
    {
        map textures/boran/bell
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map textures/boran/bell_env
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen const 0.25
        tcGen environment
    }
}


textures/boran/sun
{
	surfaceparm nonsolid	
	surfaceparm nomarks	
	surfaceparm nolightmap 
	{
		clampmap textures/boran/sun.tga
		// Sadly any speed lower than 5 stutters
		tcmod rotate 5
		blendFunc add
		rgbGen identity
	}
}


textures/boran/crack_dirt_over
{
	qer_editorimage	textures/boran/crack_dirt_over
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_material	Gravel
	q3map_alphashadow
	cull	twosided
    {
        map textures/boran/crack_dirt_over
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/crack_dirt_over2
{
	qer_editorimage	textures/boran/crack_dirt_over2
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
    {
        map textures/boran/crack_dirt_over2
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/crack_dirt_over3
{
	qer_editorimage	textures/boran/crack_dirt_over3
	surfaceparm	nomarks
	surfaceparm	nonsolid
	q3map_alphashadow
	cull	twosided
    {
        map textures/boran/crack_dirt_over3
        alphaFunc GE128
        depthWrite
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/boran/ground
{
	q3map_nonplanar
 	q3map_shadeangle 90
	q3map_material	ShortGrass
 	qer_editorimage textures/boran/ground
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/ground
 		blendFunc filter
	}
}

textures/boran/rock_cover
{
	q3map_nonplanar
 	q3map_shadeangle 120
	q3map_material	grass
 	qer_editorimage textures/boran/rock_cover
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/rock_cover
 		blendFunc filter
	}
}

textures/boran/river_floor
{
	q3map_nonplanar
 	q3map_shadeangle 120
	q3map_material	mud
 	qer_editorimage textures/boran/river_floor
 	{
 		map $lightmap
		rgbGen identity
	}
      {
		map textures/boran/river_floor
 		blendFunc filter
	}
}

textures/boran/sky
{
	qer_editorimage	textures/skies/sky

	q3map_noFog
	q3map_globalTexture
	surfaceparm sky
	surfaceparm noimpact
	surfaceparm nolightmap
	skyParms	textures/skies/gungan 512 -
	nopicmip
	{
		map textures/boran/clouds.tga
		tcMod scroll 0.0055 -0.005
		blendFunc blend
		rgbGen identityLighting
	}	
	{
		map textures/boran/mask.tga
		blendFunc GL_ONE_MINUS_SRC_ALPHA GL_SRC_ALPHA
		tcMod transform 0.25 0 0 0.25 0.1075 0.1075
		rgbGen identityLighting
	}
}


textures/sockter/ter_dirtmud
{
        qer_editorimage textures/sockter/ter_dirtmud.tga
	
	q3map_nonplanar
	q3map_shadeangle 120
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	{
		map textures/sockter/ter_dirt1.tga	// Primary
		rgbGen identity
	}
	{
		map textures/sockter/ter_mud1.tga	// Secondary
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GE128
		rgbGen identity
		alphaGen vertex
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
}

textures/sockter/mush_top01
{
	qer_editorimage textures/sockter/mush_top01.tga
//	** Remove the following line if creating the ASE **
	q3map_backShader textures/sockter/mush_backface01
	q3map_vertexScale 2
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	qer_trans 0.99

	q3map_nonplanar
	q3map_shadeAngle 179		// Smooth surface

	{
		map textures/sockter/mush_top01.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/mush_backface01
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/mush_back01.tga
		rgbGen const ( 0.3 0.3 0.3 )
		alphaFunc GE128		
	}	
}

textures/sockter/mush_stem01
{
	qer_editorimage textures/sockter/mush_stem01.tga
//	q3map_clipModel	** causes problems with AAS

	{
		map textures/sockter/mush_stem01.tga
		rgbGen const ( 0.3 0.3 0.3 )
	}	
}

// ======================================================================
// Leaves
// ======================================================================
textures/sockter/aseleaf		// Used for ASE file generation only
{
	qer_editorimage textures/sockter/leave02d.tga	// Good solid leaf design
	qer_alphafunc greater 0.5
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02d.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave01a		// fern 1
{
	qer_editorimage textures/sockter/leave01a.tga
	q3map_backShader textures/sockter/leave01a_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01a.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave01a_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01a.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave01b		// fern 2
{
	qer_editorimage textures/sockter/leave01b.tga
	q3map_backShader textures/sockter/leave01b_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01b.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave01b_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01b.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave01d		// fern (dead)
{
	qer_editorimage textures/sockter/leave01d.tga
	q3map_backShader textures/sockter/leave01d_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01d.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave01d_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave01d.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave02a		// Dock leave
{
	qer_editorimage textures/sockter/leave02a.tga
	q3map_backShader textures/sockter/leave02a_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02a.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave02a_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02a.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave02b		// Solid flat leave
{
	qer_editorimage textures/sockter/leave02b.tga
	q3map_backShader textures/sockter/leave02b_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02b.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave02b_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02b.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave02c		// Like a lilly with lots of vains
{
	qer_editorimage textures/sockter/leave02c.tga
	q3map_backShader textures/sockter/leave02c_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02c.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave02c_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02c.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave02d		// Curvy pointy leave
{
	qer_editorimage textures/sockter/leave02d.tga
	q3map_backShader textures/sockter/leave02d_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02d.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave02d_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave02d.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave03a		// Two tone green
{
	qer_editorimage textures/sockter/leave03a.tga
	q3map_backShader textures/sockter/leave03a_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03a.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave03a_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03a.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave03b		// Green with yellow edges
{
	qer_editorimage textures/sockter/leave03b.tga
	q3map_backShader textures/sockter/leave03b_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03b.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave03b_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03b.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave03c		// Green with whitish edges
{
	qer_editorimage textures/sockter/leave03c.tga
	q3map_backShader textures/sockter/leave03c_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03c.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave03c_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave03c.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave04c		// Shiney leave
{
	qer_editorimage textures/sockter/leave04c.tga
	q3map_backShader textures/sockter/leave04c_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave04c.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave04c_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave04c.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

// ----------------------------------------------------------------------
textures/sockter/leave04d		// Dead shiney leave
{
	qer_editorimage textures/sockter/leave04d.tga
	q3map_backShader textures/sockter/leave04d_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave04d.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/leave04d_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/leave04d.tga
		rgbGen const ( 0.2 0.2 0.2 )
		alphaFunc GE128		
	}	
}

textures/sockter/tree01_leaves
{
	qer_editorimage textures/sockter/tree01_leaves.tga
//	** Remove the following line if creating the ASE **
	q3map_backShader textures/sockter/tree01_leaves_back
	q3map_vertexScale 1.5
	qer_alphafunc greater 0.5
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm nomarks
	{
		map textures/sockter/tree01_leaves.tga
		rgbGen vertex
		depthWrite
		alphaFunc GE128		
	}	
}

textures/sockter/tree01_leaves_back
{
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm nomarks
	{
		map textures/sockter/tree01_leaves.tga
		rgbGen const ( 0.225 0.225 0.225 )
		alphaFunc GE128		
	}	
}
