// ///////////////////////////////////

// //// World ////////////////////////

// ///////////////////////////////////

textures/jkg_tatooine/sky
{
	qer_editorimage	textures/skies/sky
	surfaceparm	sky
	surfaceparm	noimpact
	surfaceparm	nomarks
	surfaceparm	nodlight
	q3map_SunExt 1 .7 .55 220 80 54 1 10
	q3map_SunExt 1 .9 .9 250 65 62 1 10
	q3map_nofog
	notc
	q3map_nolightmap
	skyParms	textures/skies/desert 1024 -
}

textures/jkg_tatooine/sky_night
{
	qer_editorimage	textures/skies/sky
	surfaceparm	sky
	surfaceparm	noimpact
	surfaceparm	nomarks
	surfaceparm	nodlight
	q3map_SunExt .24 .3 .70 100 80 54 1 10
	q3map_nofog
	notc
	q3map_nolightmap
	skyParms	textures/skies/sky_night 1024 -
{
map textures/skies/cloudlayer4
blendFunc GL_DST_COLOR GL_SRC_ALPHA
rgbGen const ( .36 .4 .62 )
tcMod scroll 0 0.03
tcMod scale .5 .5
}
}



textures/jkg_tatooine/fog
{
	qer_editorimage	textures/fogs/fog.tga
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	surfaceparm	fog
	surfaceparm	trans
	q3map_nolightmap
	fogparms	( 0.75 0.65 0.5 ) 9000.0
}

textures/jkg_tatooine/night_fog
{
	qer_editorimage	textures/fogs/fog.tga
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	surfaceparm	fog
	surfaceparm	trans
	q3map_nolightmap
	fogparms	( 0.06 0.109 0.207 ) 12000.0
}

textures/jkg_tatooine/jundland_fog
{
	qer_editorimage	textures/fogs/fog.tga
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	surfaceparm	fog
	surfaceparm	trans
	q3map_nolightmap
	fogparms	( 0.75 0.65 0.5 ) 55300.0
}

textures/jkg_tatooine/camera

{
	qer_editorimage textures/colors/black
	surfaceparm playerclip
	surfaceparm nolightmap
	portal
    {
	map textures/colors/black
 	blendFunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
	depthWrite
	alphaGen portal 2048
    }
}

/////////////////////////////////////

////// Decals ///////////////////////

/////////////////////////////////////

textures/jkg_tatooine/dmg1
{
	qer_editorimage	textures/jkg_tatooine/dmg1
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg1
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg2
{
	qer_editorimage	textures/jkg_tatooine/dmg2
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg2
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg3
{
	qer_editorimage	textures/jkg_tatooine/dmg3
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg3
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg4
{
	qer_editorimage	textures/jkg_tatooine/dmg4
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg4
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg5
{
	qer_editorimage	textures/jkg_tatooine/dmg5
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg5
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg6
{
	qer_editorimage	textures/jkg_tatooine/dmg6
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg6
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg7
{
	qer_editorimage	textures/jkg_tatooine/dmg7
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg7
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg8
{
	qer_editorimage	textures/jkg_tatooine/dmg8
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg8
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg9
{
	qer_editorimage	textures/jkg_tatooine/dmg9
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg9
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg10
{
	qer_editorimage	textures/jkg_tatooine/dmg10
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg10
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/dmg_wide
{
	qer_editorimage	textures/jkg_tatooine/dmg_wide
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/dmg_wide
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/imp_decal
{
	qer_editorimage	textures/jkg_tatooine/imp_decal
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/imp_decal
        blendfunc blend
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/hide1
{
	qer_editorimage	textures/jkg_tatooine/hide1
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/hide1
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/hide2
{
	qer_editorimage	textures/jkg_tatooine/hide2
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/hide2
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/hide3
{
	qer_editorimage	textures/jkg_tatooine/hide3
	qer_trans	0.8
	surfaceparm	nomarks
	surfaceparm	trans
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/hide3
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/window
{
	qer_editorimage	textures/jkg_tatooine/window
	qer_trans	0.8
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	nonopaque
	polygonOffset
	sort	6
    {
        map textures/jkg_tatooine/window
        alphaFunc GE128
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
    }
}

textures/jkg_tatooine/grate
{
	qer_editorimage	textures/jkg_tatooine/grate
	qer_trans	0.8
	q3map_alphashadow
    {
        map textures/jkg_tatooine/grate
        alphaFunc GE128
        blendFunc GL_ONE GL_ZERO
        depthWrite
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthFunc equal
        rgbGen identity
    }
}

// ///////////////////////////////////

// //// Lights ///////////////////////

// ///////////////////////////////////

textures/jkg_tatooine/under_grate
{
	qer_editorimage	textures/jkg_tatooine/under_grate
	q3map_surfacelight	400
	q3map_lightRGB .96 .92 .55
	q3map_nolightmap
    {
        map textures/jkg_tatooine/under_grate
    }
}

/////////////////////////////////////

////// Walls ////////////////////////

/////////////////////////////////////


textures/jkg_tatooine/ship_junk_shiny
{
qer_editorimage textures/jkg_tatooine/ship_junk
{
map textures/skies/Desert_up
tcgen Environment
}
{
map textures/jkg_tatooine/ship_junk
blendfunc blend
}
{
map $lightmap
blendfunc filter
}
}

textures/jkg_tatooine/ship_junk
{
qer_editorimage textures/jkg_tatooine/ship_junk
{
map textures/jkg_tatooine/ship_junk
alphaFunc GE128
blendFunc GL_ONE GL_ZERO
rgbGen identity
depthWrite
}
{
map $lightmap
blendfunc filter
}
}

textures/jkg_tatooine/chrome
{
	qer_editorimage	textures/jkg_tatooine/metal1
	surfaceparm	nomarks
	surfaceparm	trans
    {
        map textures/colors/white
        rgbGen const ( 0.400000 0.400000 0.400000 )
    }
    {
        map textures/common/env_chrome
        blendFunc GL_ONE GL_ONE
        tcGen environment
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1
{
	q3map_shadeangle 45
	qer_editorimage	textures/jkg_tatooine/mudwall1
	
    {
        map $lightmap
    }
    {
        map textures/jkg_tatooine/mudwall1
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_glow
{
	q3map_shadeangle 45
	qer_editorimage	textures/jkg_tatooine/mudwall1_glow
	
    {
        map textures/jkg_tatooine/mudwall1
    }
{
        map textures/jkg_tatooine/mudwall1
rgbGen const ( .2 .2 .2)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_glow_night
{
	q3map_shadeangle 45
	qer_editorimage	textures/jkg_tatooine/mudwall1_glow
	
    {
        map textures/jkg_tatooine/mudwall1
    }
{
        map textures/jkg_tatooine/mudwall1
rgbGen const ( .03 .05 .1)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_outside
{
	q3map_shadeangle	45
	qer_editorimage	textures/jkg_tatooine/mudwall1
	q3map_lightmapsamplesize	8
    {
        map textures/jkg_tatooine/mudwall1
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_high_angle
{
	q3map_shadeangle	150
	qer_editorimage	textures/jkg_tatooine/mudwall1
	q3map_lightmapsamplesize	8
    {
        map textures/jkg_tatooine/mudwall1
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_base
{
	q3map_shadeangle	45
	qer_editorimage	textures/jkg_tatooine/mudwall1_base
    {
        map textures/jkg_tatooine/mudwall1_base
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_base_glow
{
	q3map_shadeangle	45
	qer_editorimage	textures/jkg_tatooine/mudwall1_base_glow
    {
        map textures/jkg_tatooine/mudwall1_base
    }

{
        map textures/jkg_tatooine/mudwall1_base
rgbGen const ( .2 .2 .2)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/mudwall1_base_glow_night
{
	q3map_shadeangle	45
	qer_editorimage	textures/jkg_tatooine/mudwall1_base_glow
    {
        map textures/jkg_tatooine/mudwall1_base
    }

{
        map textures/jkg_tatooine/mudwall1_base
rgbGen const ( .03 .05 .1)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/plaster_new_glow
{
	qer_editorimage	textures/jkg_tatooine/plaster_new_glow
    {
        map textures/jkg_tatooine/plaster_new
    }
{
        map textures/jkg_tatooine/plaster_new
rgbGen const ( .2 .2 .2)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/plaster_new_glow_night
{
	qer_editorimage	textures/jkg_tatooine/plaster_new_glow
    {
        map textures/jkg_tatooine/plaster_new
    }
{
        map textures/jkg_tatooine/plaster_new
rgbGen const ( .03 .05 .1)
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
glow
detail
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/metal1
{
	q3map_shadeangle	45
	qer_editorimage	textures/jkg_tatooine/metal1
	q3map_material	HollowMetal
    {
        map textures/jkg_tatooine/metal1
    }
    {
        map textures/jkg_tatooine/metal1_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}


textures/jkg_tatooine/vent_pipe
{
	qer_editorimage	textures/jkg_tatooine/vent_pipe
	q3map_material	HollowMetal
    {
        map textures/jkg_tatooine/vent_pipe
    }
    {
        map textures/jkg_tatooine/vent_pipe_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
}
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/vent_s
{
	q3map_Offset 0.25
    {
        map textures/jkg_tatooine/vent_s
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/vent_l
{
	q3map_Offset 0.25
    {
        map textures/jkg_tatooine/vent_s
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/sand1
{
	q3map_shadeangle	120
	qer_editorimage	textures/jkg_tatooine/sand1
	q3map_material	Sand
q3map_nonplanar
q3map_notjunc
    {
        map textures/jkg_tatooine/sand1
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/sand_to_steps
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/sand1
	q3map_material	Sand
    {
        map textures/jkg_tatooine/sand_trodden
        rgbGen identity
    }
    {
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/dirty_to_sand
{
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/dirty_to_sand
	q3map_material	Sand
q3map_nonplanar
q3map_notjunc
    {
        map textures/jkg_tatooine/dirty_sand
tcMod scale .75 .75
        rgbGen identity
    }
    {
// rgbGen identity
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
// rgbGen identity
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/concrete_to_sand
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/concrete_to_sand
    {
        map textures/jkg_tatooine/concrete
tcMod scale .5 .5
        rgbGen identity
    }
    {
// rgbGen identity
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
// rgbGen identity
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/concrete_to_tiles
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/concrete_to_tiles
    {
        map textures/jkg_tatooine/concrete
        rgbGen identity
    }
    {
// rgbGen identity
        map textures/jkg_tatooine/tiles
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
// rgbGen identity
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}


textures/jkg_tatooine/sand_to_floor
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/sand_to_floor
    {
        map textures/desert/s_floor_lrg
tcMod scale 2 2
    }
    {
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
// rgbGen identity
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/sand_to_macefloor
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/sand_to_macefloor
	q3map_material	Sand
    {
        map textures/jkg_tatooine/floor
        rgbGen identity
    }
    {
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

textures/jkg_tatooine/tiles_to_sand
{
q3map_nonplanar
q3map_notjunc
	q3map_shadeangle	80
	qer_editorimage	textures/jkg_tatooine/tiles_to_sand
    {
        map textures/jkg_tatooine/floorbricks
tcMod scale 2 2
        rgbGen identity
    }
    {
        map textures/jkg_tatooine/sand1
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        alphaGen vertex
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
}

models/spaceport/spaceport_objects
{
	q3map_shadeangle	45
    {
        map models/spaceport/spaceport_objects
        blendFunc GL_ONE GL_ZERO
        rgbGen identity
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/spaceport/main_building
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
        tcMod scale 10 10
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/spaceport/house_building
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
        tcMod scale 10 10
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/spaceport/arch_building
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
        tcMod scale 10 10
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/spaceport/stair_building
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
        tcMod scale 10 10
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/jkg_tatooine/cantina_building
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
        tcMod scale 10 10
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/jkg_tatooine/tat_strut1
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}


models/jkg_tatooine/rubble
{
	q3map_shadeangle	45
	
    {
        map textures/jkg_tatooine/mudwall1
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
        depthWrite
    }
}

models/map_objects/desert/vent_grime
{
	surfaceparm	nomarks
	surfaceparm	trans
	q3map_nolightmap
	q3map_alphashadow
    {
        map models/map_objects/desert/vent_grime
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        rgbGen vertex
    }
}




models/players/veh_Landspeeder/Landspeeder_WShield
{
cull twosided
    {
        map models/players/veh_Landspeeder/Landspeeder_WShield
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen lightingDiffuse
    }
}

models/players/veh_Landspeeder/Landspeeder_screen
{
q3map_nolightmap
    {
        map models/players/veh_Landspeeder/Landspeeder_screen
        blendFunc GL_ONE GL_ZERO
        depthWrite
        rgbGen lightingDiffuse
glow
    }
}

models/players/veh_Landspeeder/Landspeeder
{
    {
        map models/players/veh_Landspeeder/Landspeeder
        blendFunc GL_ONE GL_ZERO
        rgbGen lightingDiffuse
    }
    {
        map models/players/veh_Landspeeder/Landspeeder_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
{
map models/players/veh_Landspeeder/Landspeeder_paint_main
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen lightingDiffuse
}
{
map models/players/veh_Landspeeder/Landspeeder_paint_decal
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        depthWrite
        rgbGen lightingDiffuse
}
}

