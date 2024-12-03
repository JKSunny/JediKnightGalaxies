// Just corrected to shaders that NOT are BaseJKA shaders. >_>

models/map_objects/ships/swoop
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_black
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_black
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_black_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_blue
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_blue
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_gold
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_gold
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_green
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_green
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_purple
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_purple
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop_silver
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop_silver
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop_glow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen identity
    }
    {
        map models/players/swoop/swoop_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/swoop2
{
    {
        map $lightmap
    }
    {
        map models/players/swoop/swoop2
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/players/swoop/swoop2_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        glow
        detail
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/lm_z95_wing
{
    {
        map models/map_objects/ships/z95_wing
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/map_objects/ships/z95_wing_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
    {
        map textures/common/detail4
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        detail
        tcMod scale 4 4
    }
}

models/map_objects/ships/lm_z95_cockpit
{
    {
        map envmap
        tcGen environment
        tcMod scale 2 2
    }
    {
        map models/map_objects/ships/z95_cockpit_mask
        blendFunc GL_ZERO GL_ONE_MINUS_SRC_COLOR
    }
    {
        map models/map_objects/ships/z95_cockpit
        blendFunc GL_ONE GL_ONE
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/map_objects/ships/z_95_canopy_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        alphaGen lightingSpecular
    }
}

models/map_objects/ships/lm_z95_body
{
    {
        map models/map_objects/ships/z95_body
    }
    {
        map $lightmap
        blendFunc GL_DST_COLOR GL_ZERO
    }
    {
        map models/map_objects/ships/z_95_body_spec
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
    {
        map textures/common/detail4
        blendFunc GL_DST_COLOR GL_SRC_COLOR
        detail
        tcMod scale 4 4
    }
}
