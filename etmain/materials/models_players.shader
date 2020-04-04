// models_players.shader

models/players/temperate/allied/strap
{
	cull disable
	
	implicitMap models/players/temperate/allied/inside.tga
	
	//diffusemap models/players/temperate/allied/inside
	//bumpmap models/players/temperate/allied/inside_n
	//specularmap models/players/temperate/allied/inside_s
}

// why is this shader here ?
models/players/multi/acc/backpack/backpack_lieu
{
	cull disable //Rich - Why does this shader has cull disable??
	
	{
		map models/players/multi/acc/backpack/backpack_lieu.tga
		alphafunc ge128
		rgbGen lightingDiffuse
	}
}

// FIXME: inspect all ranks
models/players/temperate/axis/ranks/major
{
	polygonoffset
	{
		map gfx/hud/ranks/major.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/feldwebel
{
	polygonoffset
	{
		map gfx/hud/ranks/sergeant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/leutnant
{
	polygonoffset
	{
		map gfx/hud/ranks/lieutenant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}
models/players/temperate/axis/ranks/gefreiter
{
	polygonoffset	
	{
		map gfx/hud/ranks/corporal.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/oberst
{
	polygonoffset
	{
		map gfx/hud/ranks/colonel.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/axis/ranks/hauptmann
{
	polygonoffset		
	{
		map gfx/hud/ranks/captain.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

// FIXME: 1stclass.tga?
models/players/temperate/axis/ranks/oberschutze
{
	polygonoffset		
	{
		map gfx/hud/ranks/1stclass.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/major
{
	polygonoffset
	
	{
		map gfx/hud/ranks/major.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/sergeant
{
	qer_models/players/temperate/allied/ranks/sergeant.tga
	polygonoffset	
	{
		map gfx/hud/ranks.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/lieutenant
{
	polygonoffset
	{
		map gfx/hud/ranks/lieutenant.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/corporal
{
	polygonoffset
	{
		map gfx/hud/ranks/corporal.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/colonel
{
	polygonoffset	
	{
		map gfx/hud/ranks/colonel.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/captain
{
	polygonoffset		
	{
		map gfx/hud/ranks/captain.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}

models/players/temperate/allied/ranks/1stclass
{
	polygonoffset		
	{
		map gfx/hud/ranks/1stclass.tga
		alphaFunc GE128
		rgbGen lightingDiffuse
	}
}


models/players/temperate/axis/engineer/engineer_body
{
	cull none
	implicitMap -
}

models/players/temperate/axis/cvops/body_cvops
{
	cull none
	implicitMap -
}

models/players/temperate/axis/fieldops/body_fieldops
{
	cull none
	implicitMap -
}

models/players/temperate/axis/medic/axis_medic
{
	cull none
	implicitMap -
}

models/players/temperate/axis/soldier/body_soldier
{
	cull none
	implicitMap -
}

models/players/temperate/allied/soldier/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/medic/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/engineer/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/fieldops/body
{
	cull none
	implicitMap -
}

models/players/temperate/allied/cvops/body
{
	cull none
	implicitMap -
}
