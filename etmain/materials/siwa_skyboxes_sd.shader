// siwa_skyboxes_sd.shader

textures/siwa_skyboxes_sd/sd_siwa
{
	qer_editorimage textures/siwa_terrain_sd/siwa_skyenv1.tga
	q3map_globaltexture
	q3map_lightimage textures/siwa_terrain_sd/siwa_skyenv2.tga
	q3map_lightsubdivide 256
	q3map_sun 1.0 0.85 0.6 180 220 70
	q3map_surfacelight 25
	fogvars ( 0.77 0.64 0.46 ) .0001
	skyfogvars ( 0.77 0.64 0.46 ) .01
	skyparms - 200 -
	surfaceparm nodlight
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	{
		map textures/skies/newclouds.tga
		tcMod scroll -0.001 -0.003
		tcMod scale 6 6
	}
}
