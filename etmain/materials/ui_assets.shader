// ui_assets.shader

ui/assets/button
{
	nocompress
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/button.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/button_click
{
	nocompress
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/button_click.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/et_clouds/old
{
	nomipmaps
	nopicmip
	{
		map ui/assets/et_mainbg.tga
		tcmod scroll .005 0
	}
	{
		map ui/assets/et_mainclouds.tga
		blendfunc add
		tcmod scroll .01 0
	}
}

// similar to console background shader
ui/assets/et_clouds
{
	nopicmip
	{
		map textures/skies_sd/wurzburg_clouds.tga
		rgbGen identityLighting
		tcMod scale 0.65 0.75
		tcMod scroll 0.0025 -0.002
	}
	{
		map textures/skies_sd/wurzburg_clouds.tga
		blendFunc GL_DST_COLOR GL_ONE
		rgbGen identityLighting
		tcMod scale 1.35 0.96
		tcMod scroll 0.055 -0.04
	}
	{
		map textures/skies_sd/ydnar_lightning.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		rgbGen wave triangle -8 9 0.63 0.137
		alphaGen wave noise -3 4 0 2.37
		tcMod scale 1.275 -1.2
		tcMod scroll 0.0025 -0.002
	}
	{
		map textures/skies_sd/ydnar_lightning.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		rgbGen wave triangle -8 9 0.91 0.15
		alphaGen wave noise -3 4 0 2.57
		tcMod scale 1 0.85
		tcMod scroll 0.0025 0.002
	}
	{
		clampmap ui/assets/background_mask.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
		tcMod stretch sin 1.1 0.1 0 0.0125
	}
}

ui/assets/et_logo_huge_dark
{
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/et_logo_huge.tga
		blendfunc blend
		alphaGen const 0.25
	}
}

ui/assets/logo_id_dark
{
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/logo_id.tga
		blendfunc blend
		alphaGen const 0.25
	}
}

ui/assets/logo_sd_dark
{
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/logo_sd.tga
		blendfunc blend
		alphaGen const 0.25
	}
}

ui/assets/logo_atvi_dark
{
	nomipmaps
	nopicmip
	{
		clampmap ui/assets/logo_atvi.tga
		blendfunc blend
		alphaGen const 0.25
	}
}


ui/assets/et_logo
{
	nomipmaps
	nopicmip
	{
		map ui/assets/et_logo.tga
		blendfunc blend
	}
}

ui/assets/et_logo_ingame
{
	nomipmaps
	nopicmip
	{
		map ui/assets/et_logo_ingame.tga
		blendfunc blend
	}
}

ui/assets/et_soldier
{
	nomipmaps
	nopicmip
	{
		map ui/assets/et_mainbg.tga
		tcmod scroll .005 0
	}
	{
		map ui/assets/et_mainclouds.tga
		blendfunc add
		tcmod scroll .01 0
	}
	{
		map ui/assets/et_soldier.tga
		blendfunc blend
	}
}

ui/assets/et_squad
{
	nomipmaps
	nopicmip
	{
		map ui/assets/et_mainbg.tga
		tcmod scroll .005 0
	}
	{
		map ui/assets/et_mainclouds.tga
		blendfunc add
		tcmod scroll .01 0
	}
	{
		map ui/assets/et_squad.tga
		blendfunc blend
	}
}

ui/assets/medal1
{
	nocompress
	nopicmip
	{
		map ui/assets/medal1.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/medal2
{
	nocompress
	nopicmip
	{
		map ui/assets/medal2.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/medal3
{
	nocompress
	nopicmip
	{
		map ui/assets/medal3.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/medal4
{
	nocompress
	nopicmip
	{
		map ui/assets/medal4.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/medal5
{
	nocompress
	nopicmip
	{
		map ui/assets/medal5.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/nerve_logo
{
	nocompress
	nopicmip
	{
		map ui/assets/nerve_logo_fx.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 .75 .05
	}
	{
		map ui/assets/nerve_logo.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 0 .05
	}
}

ui/assets/pblogo
{
	nomipmaps
	nopicmip
	{
		map ui/assets/pblogo.tga
		blendfunc blend
	}
}

ui/assets/portraits/allies_win
{
	nomipmaps
	nopicmip
	{
		map ui/assets/portraits/allies_sky.tga
		tcmod scroll .06 0
	}
	{
		map ui/assets/portraits/allies_win.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/portraits/allies_win_flag
{
	nomipmaps
	nopicmip
	{
		map ui/assets/portraits/allies_win_flag.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaGen wave sin 0.5 0.2 0 0.2
	}
}

ui/assets/portraits/axis_win
{
	nomipmaps
	nopicmip
	{
		map ui/assets/portraits/axis_sky.tga
		tcmod scroll .06 0
	}
	{
		map ui/assets/portraits/axis_win.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

ui/assets/portraits/axis_win_flag
{
	nomipmaps
	nopicmip
	{
		map ui/assets/portraits/axis_win_flag.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaGen wave sin 0.5 0.2 0 0.2
	}
}

ui/assets/quickmessage_background
{
	nocompress
	nomipmaps
	nopicmip
	{
		map ui/assets/quickmessage_background.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

// ydnar: radio tower shader
ui/assets/radio_tower
{
	nopicmip
	
	// clouds
	{
		map ui/assets/clouds.tga
		tcMod turb 0 0.009 0 0.01
		tcMod scroll 0.025 0
		rgbGen wave noise 0.95 0.05 0 45
	}
	{
		map ui/assets/clouds.tga
		blendFunc GL_DST_COLOR GL_ONE
		tcMod scale 0.75 1
		tcMod turb 0 0.009 0 0.01
		tcMod scroll 0.15 0
		rgbGen wave noise 0.95 0.05 0 45
	}
	
	// tower
	{
		map ui/assets/radio_tower.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		tcMod turb 0 0.009 0 0.01
		rgbGen wave noise 0.95 0.05 0 45
	}
	{
		map ui/assets/radio_tower.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		tcMod turb 0 0.009 0 0.01
		rgbGen wave noise 0.95 0.05 0 45
	}
	
	// transmission rings
	{
		clampmap ui/assets/ring.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		tcMod transform 1 0 0 1 0 0.25
		tcMod turb 0 0.009 0 0.01
		tcMod stretch sawtooth			0.1 1 0 0.4
		alphaGen wave inversesawtooth	0 1 0 0.4
		rgbGen wave noise 0.95 0.05 0 45
	}
	{
		clampmap ui/assets/ring.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		tcMod transform 1 0 0 1 0 0.25
		tcMod turb 0 0.009 0 0.01
		tcMod stretch sawtooth			0.1 1 0.33 0.4
		alphaGen wave inversesawtooth	0 1 0.33 0.4
		rgbGen wave noise 0.95 0.05 0 45
	}
	{
		clampmap ui/assets/ring.tga
		blendFunc GL_SRC_ALPHA GL_ONE
		tcMod transform 1 0 0 1 0 0.25
		tcMod turb 0 0.009 0 0.01
		tcMod stretch sawtooth			0.1 1 0.66 0.4
		alphaGen wave inversesawtooth	0 1 0.66 0.4
		rgbGen wave noise 0.95 0.05 0 45
	}
}
