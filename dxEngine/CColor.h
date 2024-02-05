#ifndef _CColor
#define _CColor

#include "standard.h"

class CColor
{
public:

	FLOAT RGBA[4];

	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;

	CColor();

	CColor(BYTE br, BYTE bg, BYTE bb, BYTE ba)
	{
		memset(this, 0x00, sizeof(CColor));

		r = br;
		g = bg;
		b = bb;
		a = ba;

		SetRGBA();
	}

	~CColor();

	VOID SetRGBA()
	{
		RGBA[0] = r / 255.0F;
		RGBA[1] = g / 255.0F;
		RGBA[2] = b / 255.0F;
		RGBA[3] = a / 255.0F;
	}

	FLOAT* GetFloatArray()
	{
		return (FLOAT*)& RGBA;
	}
};

//static CColor AlgaeGreen(100, 233, 134, 255);
//static CColor AliceBlue(240, 248, 255, 255);
//static CColor AlienGreen(108, 196, 23, 255);
//static CColor AntiqueWhite(250, 235, 215, 255);
//static CColor Aqua(0, 255, 255, 255);
//static CColor Aquamarine(127, 255, 212, 255);
//static CColor ArmyBrown(130, 123, 96, 255);
//static CColor AshGray(102, 99, 98, 255);
//static CColor AvocadoGreen(178, 194, 72, 255);
//static CColor AztechPurple(137, 59, 255, 255);
//static CColor Azure(240, 255, 255, 255);
//static CColor BabyBlue(149, 185, 199, 255);
//static CColor BashfulPink(194, 82, 131, 255);
//static CColor BasketBallOrange(248, 129, 88, 255);
//static CColor BattleshipGray(132, 132, 130, 255);
//static CColor BeanRed(247, 93, 89, 255);
static CColor Beer(251, 177, 23, 255);
//static CColor BeetleGreen(76, 120, 126, 255);
//static CColor BeeYellow(233, 171, 23, 255);
//static CColor Beige(245, 245, 220, 255);
//static CColor Bisque(255, 228, 196, 255);
//static CColor Black(0, 0, 0, 255);
//static CColor BlackCat(65, 56, 57, 255);
//static CColor BlackCow(76, 70, 70, 255);
//static CColor BlackEel(70, 62, 63, 255);
//static CColor BlanchedAlmond(255, 235, 205, 255);
//static CColor Blonde(251, 246, 217, 255);
//static CColor BloodRed(126, 53, 23, 255);
//static CColor BlossomPink(249, 183, 255, 255);
//static CColor Blue(0, 0, 255, 255);
//static CColor BlueAngel(183, 206, 236, 255);
//static CColor BlueberryBlue(0, 65, 194, 255);
//static CColor BlueDiamond(78, 226, 236, 255);
//static CColor BlueDress(21, 125, 236, 255);
//static CColor BlueEyes(21, 105, 199, 255);
//static CColor BlueGray(152, 175, 199, 255);
//static CColor Bluegreen(123, 204, 181, 255);
//static CColor BlueHosta(119, 191, 199, 255);
//static CColor BlueIvy(48, 144, 199, 255);
//static CColor BlueJay(43, 84, 126, 255);
//static CColor BlueKoi(101, 158, 199, 255);
//static CColor BlueLagoon(142, 235, 236, 255);
//static CColor BlueLotus(105, 96, 236, 255);
//static CColor BlueOrchid(31, 69, 252, 255);
//static CColor BlueRibbon(48, 110, 255, 255);
//static CColor BlueViolet(138, 43, 226, 255);
//static CColor BlueWhale(52, 45, 126, 255);
//static CColor BlueZircon(87, 254, 255, 255);
//static CColor BlushPink(230, 169, 236, 255);
//static CColor BlushRed(229, 110, 148, 255);
//static CColor Brass(181, 166, 66, 255);
//static CColor BrightGold(253, 208, 23, 255);
//static CColor BrightNeonPink(244, 51, 255, 255);
//static CColor Bronze(205, 127, 50, 255);
//static CColor Brown(165, 42, 42, 255);
//static CColor BrownBear(131, 92, 59, 255);
//static CColor BrownSugar(226, 167, 111, 255);
//static CColor BulletShell(175, 155, 96, 255);
//static CColor Burgundy(140, 0, 26, 255);
//static CColor BurlyWood(222, 184, 135, 255);
//static CColor BurntPink(193, 34, 103, 255);
//static CColor ButterflyBlue(56, 172, 236, 255);
//static CColor CadetBlue(95, 158, 160, 255);
//static CColor CadillacPink(227, 138, 174, 255);
//static CColor Camelbrown(193, 154, 107, 255);
//static CColor CamouflageGreen(120, 134, 107, 255);
//static CColor Cantaloupe(255, 166, 47, 255);
//static CColor Caramel(198, 142, 23, 255);
//static CColor CarbonGray(98, 93, 93, 255);
//static CColor CarnationPink(247, 120, 161, 255);
//static CColor Celeste(80, 235, 236, 255);
//static CColor Champagne(247, 231, 206, 255);
//static CColor Charcoal(52, 40, 44, 255);
//static CColor Chartreuse(127, 255, 0, 255);
//static CColor Chartreuse2(138, 251, 23, 255);
//static CColor CherryRed(194, 70, 65, 255);
//static CColor Chestnut(149, 69, 53, 255);
//static CColor ChestnutRed(195, 74, 44, 255);
//static CColor ChilliPepper(193, 27, 23, 255);
//static CColor Chocolate(200, 90, 23, 255);
//static CColor Chocolate2(210, 105, 30, 255);
//static CColor Cinnamon(197, 137, 23, 255);
//static CColor CloudyGray(109, 105, 104, 255);
//static CColor CloverGreen(62, 160, 85, 255);
//static CColor CobaltBlue(0, 32, 194, 255);
//static CColor Coffee(111, 78, 55, 255);
//static CColor ColumbiaBlue(135, 175, 199, 255);
//static CColor ConstructionConeOrange(248, 116, 49, 255);
//static CColor CookieBrown(199, 163, 23, 255);
//static CColor Copper(184, 115, 51, 255);
//static CColor Coral(255, 127, 80, 255);
//static CColor CoralBlue(175, 220, 236, 255);
static CColor CornflowerBlue(100, 149, 237, 255);
//static CColor Cornsilk(255, 248, 220, 255);
//static CColor CornYellow(255, 243, 128, 255);
//static CColor CottonCandy(252, 223, 255, 255);
//static CColor Cranberry(159, 0, 15, 255);
//static CColor Cream(255, 255, 204, 255);
//static CColor Crimson(220, 20, 60, 255);
//static CColor Crimson2(226, 56, 236, 255);
//static CColor CrocusPurple(145, 114, 236, 255);
//static CColor CrystalBlue(92, 179, 255, 255);
//static CColor Cyan(0, 255, 255, 255);
//static CColor CyanOpaque(146, 199, 199, 255);
//static CColor CyanorAqua(0, 255, 255, 255);
//static CColor DarkBlue(0, 0, 139, 255);
//static CColor DarkCarnationPink(193, 34, 131, 255);
//static CColor DarkCyan(0, 139, 139, 255);
//static CColor DarkForestGreen(37, 65, 23, 255);
//static CColor DarkGoldenrod(175, 120, 23, 255);
//static CColor DarkGoldenrod2(184, 134, 11, 255);
//static CColor DarkGray(169, 169, 169, 255);
//static CColor DarkGreen(0, 100, 0, 255);
//static CColor DarkKhaki(189, 183, 107, 255);
//static CColor DarkMagenta(139, 0, 139, 255);
//static CColor DarkOliveGreen(85, 107, 47, 255);
//static CColor DarkOrange(248, 128, 23, 255);
//static CColor DarkOrange2(255, 140, 0, 255);
//static CColor DarkOrchid(125, 27, 126, 255);
//static CColor DarkOrchid2(153, 50, 204, 255);
//static CColor DarkRed(139, 0, 0, 255);
//static CColor DarkSalmon(225, 139, 107, 255);
//static CColor DarkSalmon2(233, 150, 122, 255);
//static CColor DarkSeaGreen(139, 179, 129, 255);
//static CColor DarkSeaGreen2(143, 188, 143, 255);
//static CColor DarkSlateBlue(43, 56, 86, 255);
//static CColor DarkSlateBlue2(72, 61, 139, 255);
//static CColor DarkSlateGray(47, 79, 79, 255);
//static CColor DarkSlateGrey(37, 56, 60, 255);
//static CColor DarkTurquoise(0, 206, 209, 255);
//static CColor DarkTurquoise2(59, 156, 156, 255);
//static CColor DarkViolet(132, 45, 206, 255);
//static CColor DarkViolet2(148, 0, 211, 255);
//static CColor DaySkyBlue(130, 202, 255, 255);
//static CColor DeepPeach(255, 203, 164, 255);
//static CColor DeepPink(245, 40, 135, 255);
//static CColor DeepPink2(255, 20, 147, 255);
//static CColor DeepSkyBlue(0, 191, 255, 255);
//static CColor DeepSkyBlue2(59, 185, 255, 255);
//static CColor DenimBlue(121, 186, 236, 255);
//static CColor DenimDarkBlue(21, 27, 141, 255);
//static CColor DesertSand(237, 201, 175, 255);
//static CColor DimGray(105, 105, 105, 255);
//static CColor DimorphothecaMagenta(227, 49, 157, 255);
//static CColor DodgerBlue(21, 137, 255, 255);
//static CColor DodgerBlue2(30, 144, 255, 255);
//static CColor DollarBillGreen(133, 187, 101, 255);
//static CColor DragonGreen(106, 251, 146, 255);
//static CColor DullPurple(127, 82, 93, 255);
//static CColor EarthBlue(0, 0, 160, 255);
//static CColor Eggplant(97, 64, 81, 255);
//static CColor ElectricBlue(154, 254, 255, 255);
//static CColor EmeraldGreen(95, 251, 23, 255);
//static CColor FallLeafBrown(200, 181, 96, 255);
//static CColor FernGreen(102, 124, 38, 255);
//static CColor FerrariRed(247, 13, 26, 255);
//static CColor Firebrick(128, 5, 23, 255);
//static CColor Firebrick2(178, 34, 34, 255);
//static CColor FireEngineRed(246, 40, 23, 255);
//static CColor FlamingoPink(249, 167, 176, 255);
//static CColor FloralWhite(255, 250, 240, 255);
//static CColor ForestGreen(34, 139, 34, 255);
//static CColor ForestGreen2(78, 146, 88, 255);
//static CColor FrogGreen(153, 198, 142, 255);
//static CColor Fuchsia(255, 0, 255, 255);
//static CColor Gainsboro(220, 220, 220, 255);
//static CColor GhostWhite(248, 248, 255, 255);
//static CColor GingerBrown(201, 190, 98, 255);
//static CColor GlacialBlueIce(54, 139, 193, 255);
//static CColor Gold(255, 215, 0, 255);
//static CColor Goldenbrown(234, 193, 23, 255);
//static CColor Goldenrod(218, 165, 32, 255);
//static CColor Goldenrod2(237, 218, 116, 255);
//static CColor Granite(131, 126, 124, 255);
//static CColor Grape(94, 90, 128, 255);
//static CColor Grapefruit(220, 56, 31, 255);
//static CColor Gray(115, 111, 110, 255);
//static CColor Gray2(128, 128, 128, 255);
//static CColor GrayCloud(182, 182, 180, 255);
//static CColor GrayDolphin(92, 88, 88, 255);
//static CColor GrayGoose(209, 208, 206, 255);
//static CColor GrayishTurquoise(94, 125, 126, 255);
//static CColor GrayWolf(80, 74, 75, 255);
static CColor Green(0, 128, 0, 255);
//static CColor Green2(0, 255, 0, 255);
//static CColor GreenApple(76, 196, 23, 255);
//static CColor GreenishBlue(48, 125, 126, 255);
//static CColor GreenOnion(106, 161, 33, 255);
//static CColor GreenPeas(137, 195, 92, 255);
//static CColor GreenSnake(108, 187, 60, 255);
//static CColor GreenThumb(181, 234, 170, 255);
//static CColor GreenYellow(173, 255, 47, 255);
//static CColor GreenYellow2(177, 251, 23, 255);
//static CColor Gunmetal(44, 53, 57, 255);
//static CColor HalloweenOrange(230, 108, 44, 255);
//static CColor HarvestGold(237, 226, 117, 255);
//static CColor HazelGreen(97, 124, 88, 255);
//static CColor HeliotropePurple(212, 98, 255, 255);
//static CColor Honeydew(240, 255, 240, 255);
//static CColor HotPink(246, 96, 171, 255);
//static CColor HotPink2(255, 105, 180, 255);
//static CColor HummingbirdGreen(127, 232, 23, 255);
//static CColor Iceberg(86, 165, 236, 255);
//static CColor IguanaGreen(156, 176, 113, 255);
//static CColor IndianRed(205, 92, 92, 255);
//static CColor Indigo(75, 0, 130, 255);
//static CColor Iridium(61, 60, 58, 255);
//static CColor Ivory(255, 255, 240, 255);
//static CColor JadeGreen(94, 251, 110, 255);
//static CColor JasminePurple(162, 59, 236, 255);
//static CColor JeansBlue(160, 207, 236, 255);
//static CColor Jellyfish(70, 199, 199, 255);
//static CColor JetGray(97, 109, 126, 255);
//static CColor JungleGreen(52, 124, 44, 255);
//static CColor KellyGreen(76, 197, 82, 255);
//static CColor Khaki(173, 169, 110, 255);
//static CColor Khaki2(240, 230, 140, 255);
//static CColor KhakiRose(197, 144, 142, 255);
//static CColor LapisBlue(21, 49, 126, 255);
//static CColor LavaRed(228, 34, 23, 255);
//static CColor Lavender(230, 230, 250, 255);
//static CColor Lavenderblue(227, 228, 250, 255);
//static CColor LavenderBlush(255, 240, 245, 255);
//static CColor LavenderPinocchio(235, 221, 226, 255);
//static CColor LawnGreen(124, 252, 0, 255);
//static CColor LawnGreen2(135, 247, 23, 255);
//static CColor LemonChiffon(255, 248, 198, 255);
//static CColor LemonChiffon2(255, 250, 205, 255);
//static CColor LightAquamarine(147, 255, 232, 255);
//static CColor LightBlue(173, 216, 230, 255);
//static CColor LightBlue2(173, 223, 255, 255);
//static CColor LightCoral(231, 116, 113, 255);
//static CColor LightCoral2(240, 128, 128, 255);
//static CColor LightCyan(224, 255, 255, 255);
//static CColor LightGoldenrodYellow(250, 250, 210, 255);
static CColor LightGray(211, 211, 211, 255);
//static CColor LightGreen(144, 238, 144, 255);
//static CColor LightJade(195, 253, 184, 255);
//static CColor LightPink(250, 175, 186, 255);
//static CColor LightPink2(255, 182, 193, 255);
//static CColor LightSalmon(249, 150, 107, 255);
//static CColor LightSalmon2(255, 160, 122, 255);
//static CColor LightSeaGreen(32, 178, 170, 255);
//static CColor LightSeaGreen2(62, 169, 159, 255);
//static CColor LightSkyBlue(130, 202, 250, 255);
//static CColor LightSkyBlue2(135, 206, 250, 255);
//static CColor LightSlate(204, 255, 255, 255);
//static CColor LightSlateBlue(115, 106, 255, 255);
//static CColor LightSlateGray(109, 123, 141, 255);
//static CColor LightSlateGray2(119, 136, 153, 255);
//static CColor LightSteelBlue(114, 143, 206, 255);
//static CColor LightSteelBlue2(176, 196, 222, 255);
//static CColor LightYellow(255, 255, 224, 255);
//static CColor Lilac(200, 162, 200, 255);
//static CColor Lime(0, 255, 0, 255);
//static CColor LimeGreen(50, 205, 50, 255);
//static CColor LimeGreen2(65, 163, 23, 255);
//static CColor Linen(250, 240, 230, 255);
//static CColor LipstickPink(196, 135, 147, 255);
static CColor LovelyPurple(127, 56, 236, 255);
//static CColor LoveRed(228, 27, 23, 255);
//static CColor MacaroniandCheese(242, 187, 102, 255);
//static CColor MacawBlueGreen(67, 191, 199, 255);
//static CColor Magenta(255, 0, 255, 255);
//static CColor Mahogany(192, 64, 0, 255);
//static CColor MangoOrange(255, 128, 64, 255);
//static CColor MarbleBlue(86, 109, 126, 255);
//static CColor Maroon(128, 0, 0, 255);
//static CColor Maroon2(129, 5, 65, 255);
//static CColor Mauve(224, 176, 255, 255);
//static CColor MediumAquamarine(52, 135, 129, 255);
//static CColor MediumAquamarine2(102, 205, 170, 255);
//static CColor MediumBlue(0, 0, 205, 255);
//static CColor MediumForestGreen(52, 114, 53, 255);
//static CColor MediumOrchid(176, 72, 181, 255);
//static CColor MediumOrchid2(186, 85, 211, 255);
//static CColor MediumPurple(132, 103, 215, 255);
//static CColor MediumPurple2(147, 112, 219, 255);
//static CColor MediumSeaGreen(48, 103, 84, 255);
//static CColor MediumSeaGreen2(60, 179, 113, 255);
//static CColor MediumSlateBlue(123, 104, 238, 255);
//static CColor MediumSpringGreen(0, 250, 154, 255);
//static CColor MediumSpringGreen2(52, 128, 23, 255);
//static CColor MediumTurquoise(72, 204, 205, 255);
//static CColor MediumTurquoise2(72, 209, 204, 255);
//static CColor MediumVioletRed(199, 21, 133, 255);
//static CColor MediumVioletRed2(202, 34, 107, 255);
//static CColor MetallicSilver(188, 198, 204, 255);
//static CColor Midnight(43, 27, 23, 255);
//static CColor MidnightBlue(21, 27, 84, 255);
//static CColor MidnightBlue2(25, 25, 112, 255);
//static CColor MilkWhite(254, 252, 255, 255);
//static CColor MintCream(245, 255, 250, 255);
//static CColor Mintgreen(152, 255, 152, 255);
//static CColor MistBlue(100, 109, 126, 255);
//static CColor MistyRose(251, 187, 185, 255);
//static CColor MistyRose2(255, 228, 225, 255);
//static CColor Moccasin(130, 120, 57, 255);
//static CColor Moccasin2(255, 228, 181, 255);
//static CColor Mocha(73, 61, 38, 255);
//static CColor Mustard(255, 219, 88, 255);
//static CColor NavajoWhite(255, 222, 173, 255);
//static CColor Navy(0, 0, 128, 255);
//static CColor NavyBlue(0, 0, 128, 255);
//static CColor NebulaGreen(89, 232, 23, 255);
//static CColor NeonPink(245, 53, 170, 255);
//static CColor Night(12, 9, 10, 255);
//static CColor NorthernLightsBlue(120, 199, 199, 255);
//static CColor OakBrown(128, 101, 23, 255);
//static CColor OceanBlue(43, 101, 236, 255);
//static CColor Oil(59, 49, 49, 255);
//static CColor OldLace(253, 245, 230, 255);
//static CColor Olive(128, 128, 0, 255);
//static CColor OliveDrab(107, 142, 35, 255);
//static CColor Orange(255, 165, 0, 255);
//static CColor OrangeGold(212, 160, 23, 255);
//static CColor OrangeRed(255, 69, 0, 255);
//static CColor OrangeSalmon(196, 116, 81, 255);
//static CColor Orchid(218, 112, 214, 255);
//static CColor PaleBlueLily(207, 236, 236, 255);
//static CColor PaleGoldenrod(238, 232, 170, 255);
//static CColor PaleGreen(152, 251, 152, 255);
//static CColor PaleTurquoise(175, 238, 238, 255);
//static CColor PaleVioletRed(209, 101, 135, 255);
//static CColor PaleVioletRed2(219, 112, 147, 255);
//static CColor PapayaOrange(229, 103, 23, 255);
//static CColor PapayaWhip(255, 239, 213, 255);
//static CColor Parchment(255, 255, 194, 255);
//static CColor PastelBlue(180, 207, 236, 255);
//static CColor Peach(255, 229, 180, 255);
//static CColor PeachPuff(255, 218, 185, 255);
//static CColor Pearl(253, 238, 244, 255);
//static CColor Periwinkle(233, 207, 236, 255);
//static CColor Peru(205, 133, 63, 255);
//static CColor PigPink(253, 215, 228, 255);
//static CColor PineGreen(56, 124, 68, 255);
//static CColor Pink(250, 175, 190, 255);
//static CColor Pink2(255, 192, 203, 255);
//static CColor PinkBow(196, 129, 137, 255);
//static CColor PinkBubbleGum(255, 223, 221, 255);
//static CColor PinkCupcake(228, 94, 157, 255);
//static CColor PinkDaisy(231, 153, 163, 255);
//static CColor PinkLemonade(228, 40, 124, 255);
//static CColor PinkRose(231, 161, 176, 255);
//static CColor PistachioGreen(157, 194, 9, 255);
//static CColor Platinum(229, 228, 226, 255);
//static CColor Plum(185, 59, 143, 255);
//static CColor Plum2(221, 160, 221, 255);
//static CColor PlumPie(125, 5, 65, 255);
//static CColor PlumPurple(88, 55, 89, 255);
//static CColor PlumVelvet(125, 5, 82, 255);
//static CColor PowderBlue(176, 224, 230, 255);
//static CColor PowderBlue2(198, 222, 255, 255);
//static CColor Puce(127, 90, 88, 255);
//static CColor PumpkinOrange(248, 114, 23, 255);
//static CColor Purple(128, 0, 128, 255);
//static CColor Purple2(142, 53, 239, 255);
//static CColor PurpleAmethyst(108, 45, 199, 255);
//static CColor PurpleDaffodil(176, 65, 255, 255);
//static CColor PurpleDragon(195, 142, 199, 255);
//static CColor PurpleFlower(167, 74, 199, 255);
//static CColor PurpleHaze(78, 56, 126, 255);
//static CColor PurpleIris(87, 27, 126, 255);
//static CColor PurpleJam(106, 40, 126, 255);
//static CColor PurpleMimosa(158, 123, 255, 255);
//static CColor PurpleMonster(70, 27, 126, 255);
//static CColor PurpleSageBush(122, 93, 199, 255);
//static CColor Red(255, 0, 0, 255);
//static CColor RedDirt(127, 82, 23, 255);
//static CColor RedFox(195, 88, 23, 255);
//static CColor RedWine(153, 0, 18, 255);
//static CColor RobinEggBlue(189, 237, 255, 255);
//static CColor RoguePink(193, 40, 105, 255);
//static CColor Rose(232, 173, 170, 255);
//static CColor RoseGold(236, 197, 192, 255);
//static CColor RosyBrown(179, 132, 129, 255);
//static CColor RosyBrown2(188, 143, 143, 255);
//static CColor RosyFinch(127, 78, 82, 255);
//static CColor RoyalBlue(43, 96, 222, 255);
//static CColor RoyalBlue2(65, 105, 225, 255);
//static CColor RubberDuckyYellow(255, 216, 1, 255);
//static CColor RubyRed(246, 34, 23, 255);
//static CColor Rust(195, 98, 65, 255);
//static CColor SaddleBrown(139, 69, 19, 255);
//static CColor Saffron(251, 185, 23, 255);
//static CColor SageGreen(132, 139, 121, 255);
//static CColor SaladGreen(161, 201, 53, 255);
//static CColor Salmon(250, 128, 114, 255);
//static CColor Sand(194, 178, 128, 255);
//static CColor Sandstone(120, 109, 95, 255);
//static CColor SandyBrown(238, 154, 77, 255);
//static CColor SandyBrown2(244, 164, 96, 255);
//static CColor Sangria(126, 56, 23, 255);
//static CColor SapphireBlue(37, 84, 199, 255);
//static CColor Scarlet(255, 36, 0, 255);
//static CColor SchoolBusYellow(232, 163, 23, 255);
//static CColor SeaBlue(194, 223, 255, 255);
//static CColor SeaGreen(46, 139, 87, 255);
//static CColor SeaGreen2(78, 137, 117, 255);
//static CColor SeaShell(255, 245, 238, 255);
//static CColor SeaTurtleGreen(67, 141, 128, 255);
//static CColor SeaweedGreen(67, 124, 23, 255);
//static CColor Sedona(204, 102, 0, 255);
//static CColor Sepia(127, 70, 44, 255);
//static CColor ShamrockGreen(52, 124, 23, 255);
//static CColor ShockingOrange(229, 91, 60, 255);
//static CColor Sienna(138, 65, 23, 255);
//static CColor Sienna2(160, 82, 45, 255);
//static CColor SilkBlue(72, 138, 199, 255);
//static CColor Silver(192, 192, 192, 255);
//static CColor SkyBlue(102, 152, 255, 255);
//static CColor SkyBlue2(135, 206, 235, 255);
//static CColor SlateBlue(106, 90, 205, 255);
//static CColor SlateBlue2(115, 124, 161, 255);
//static CColor SlateGray(101, 115, 131, 255);
//static CColor SlateGray2(112, 128, 144, 255);
//static CColor SlimeGreen(188, 233, 84, 255);
//static CColor SmokeyGray(114, 110, 109, 255);
//static CColor Snow(255, 250, 250, 255);
//static CColor SpringGreen(0, 255, 127, 255);
//static CColor SpringGreen2(74, 160, 44, 255);
//static CColor SteelBlue(70, 130, 180, 255);
//static CColor SteelBlue2(72, 99, 160, 255);
//static CColor StoplightGoGreen(87, 233, 100, 255);
//static CColor SunriseOrange(230, 116, 81, 255);
//static CColor SunYellow(255, 232, 124, 255);
//static CColor Tan(210, 180, 140, 255);
//static CColor TanBrown(236, 229, 182, 255);
//static CColor Tangerine(231, 138, 97, 255);
//static CColor Taupe(72, 60, 50, 255);
//static CColor TeaGreen(204, 251, 93, 255);
//static CColor Teal(0, 128, 128, 255);
//static CColor Thistle(210, 185, 211, 255);
//static CColor Thistle2(216, 191, 216, 255);
//static CColor TiffanyBlue(129, 216, 208, 255);
//static CColor TigerOrange(200, 129, 65, 255);
//static CColor Tomato(255, 99, 71, 255);
//static CColor TronBlue(125, 253, 254, 255);
//static CColor TulipPink(194, 90, 124, 255);
//static CColor Turquoise(64, 224, 208, 255);
//static CColor Turquoise2(67, 198, 219, 255);
//static CColor TyrianPurple(196, 90, 236, 255);
//static CColor ValentineRed(229, 84, 81, 255);
//static CColor VampireGray(86, 80, 81, 255);
//static CColor Vanilla(243, 229, 171, 255);
//static CColor VelvetMaroon(126, 53, 77, 255);
//static CColor VenomGreen(114, 140, 0, 255);
//static CColor ViolaPurple(126, 88, 126, 255);
//static CColor Violet(141, 56, 201, 255);
//static CColor Violet2(238, 130, 238, 255);
//static CColor VioletRed(246, 53, 138, 255);
//static CColor Water(235, 244, 250, 255);
//static CColor WatermelonPink(252, 108, 133, 255);
//static CColor Wheat(245, 222, 179, 255);
static CColor White(255, 255, 255, 255);
//static CColor WhiteSmoke(245, 245, 245, 255);
//static CColor WindowsBlue(53, 126, 199, 255);
//static CColor WisteriaPurple(198, 174, 199, 255);
//static CColor Wood(150, 111, 51, 255);
//static CColor Yellow(255, 255, 0, 255);
//static CColor YellowGreen(82, 208, 23, 255);
//static CColor YellowGreen2(154, 205, 50, 255);
//static CColor ZombieGreen(84, 197, 113, 255);
#endif