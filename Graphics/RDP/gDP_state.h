#ifndef _GDP_STATE_H
#define _GDP_STATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gDPCombine
{
	union
	{
		struct
		{
			// muxs1
			unsigned	aA1		: 3;
			unsigned	sbA1	: 3;
			unsigned	aRGB1	: 3;
			unsigned	aA0		: 3;
			unsigned	sbA0	: 3;
			unsigned	aRGB0	: 3;
			unsigned	mA1		: 3;
			unsigned	saA1	: 3;
			unsigned	sbRGB1	: 4;
			unsigned	sbRGB0	: 4;

			// muxs0
			unsigned	mRGB1	: 5;
			unsigned	saRGB1	: 4;
			unsigned	mA0		: 3;
			unsigned	saA0	: 3;
			unsigned	mRGB0	: 5;
			unsigned	saRGB0	: 4;
		};

		struct
		{
			uint32_t			muxs1, muxs0;
		};

		uint64_t				mux;
	};
};

struct FrameBuffer;
struct gDPTile
{
	uint32_t format, size, line, tmem, palette;

	union
	{
		struct
		{
			unsigned	mirrort	: 1;
			unsigned	clampt	: 1;
			unsigned	pad0	: 30;

			unsigned	mirrors	: 1;
			unsigned	clamps	: 1;
			unsigned	pad1	: 30;
		};

		struct
		{
			uint32_t cmt, cms;
		};
	};

	uint32_t maskt, masks;
	uint32_t shiftt, shifts;
	float fuls, fult, flrs, flrt;
	uint32_t uls, ult, lrs, lrt;

	uint32_t textureMode;
	uint32_t loadType;
	uint32_t imageAddress;
	struct FrameBuffer *frameBuffer;
};

struct gDPLoadTileInfo
{
   uint8_t size;
   uint8_t loadType;
   uint16_t uls;
   uint16_t ult;
   uint16_t width;
   uint16_t height;
   uint16_t texWidth;
   uint32_t texAddress;
   uint32_t dxt;
};

struct gDPInfo
{
	struct
	{
		union
		{
			struct
			{
				unsigned int alphaCompare : 2;
				unsigned int depthSource : 1;

//				struct
//				{
					unsigned int AAEnable : 1;
					unsigned int depthCompare : 1;
					unsigned int depthUpdate : 1;
					unsigned int imageRead : 1;
					unsigned int clearOnCvg : 1;

					unsigned int cvgDest : 2;
					unsigned int depthMode : 2;

					unsigned int cvgXAlpha : 1;
					unsigned int alphaCvgSel : 1;
					unsigned int forceBlender : 1;
					unsigned int textureEdge : 1;
//				} renderMode;

//				struct
//				{
					unsigned int c2_m2b : 2;
					unsigned int c1_m2b : 2;
					unsigned int c2_m2a : 2;
					unsigned int c1_m2a : 2;
					unsigned int c2_m1b : 2;
					unsigned int c1_m1b : 2;
					unsigned int c2_m1a : 2;
					unsigned int c1_m1a : 2;
//				} blender;

				unsigned int blendMask : 4;
				unsigned int alphaDither : 2;
				unsigned int colorDither : 2;

				unsigned int combineKey : 1;
				unsigned int textureConvert : 3;
				unsigned int textureFilter : 2;
				unsigned int textureLUT : 2;

				unsigned int textureLOD : 1;
				unsigned int textureDetail : 2;
				unsigned int texturePersp : 1;
				unsigned int cycleType : 2;
				unsigned int unusedColorDither : 1; // unsupported
				unsigned int pipelineMode : 1;

				unsigned int pad : 8;

			};

			uint64_t			_u64;

			struct
			{
				uint32_t			l, h;
			};
		};
	} otherMode;

	struct gDPCombine combine;
	struct gDPTile tiles[8], *loadTile;

	struct Color
	{
		float r, g, b, a;
	} fogColor,  blendColor, envColor;

	struct
	{
		float z, dz;
		uint32_t color;
	} fillColor;

	struct PrimColor
	{
      float r, g, b, a;
		float l, m;
	} primColor;

	struct
	{
		float z, deltaZ;
	} primDepth;

	struct
	{
		uint32_t format, size, width, bpl;
		uint32_t address;
	} textureImage;

	struct
	{
		uint32_t format, size, width, height, bpl;
		uint32_t address, changed;
		uint32_t depthImage;
	} colorImage;

	uint32_t	depthImageAddress;

	struct
	{
		uint32_t mode;
		float ulx, uly, lrx, lry;
	} scissor;

	struct
	{
		int32_t k0, k1, k2, k3, k4, k5;
	} convert;

	struct
	{
		struct Color center, scale, width;
	} key;

   struct
   {
      uint32_t width, height;
   }  texRect;

	uint32_t changed;

	uint16_t TexFilterPalette[512];
	uint32_t paletteCRC16[16];
	uint32_t paletteCRC256;
	uint32_t half_1, half_2;

   struct gDPLoadTileInfo loadInfo[512];
};

extern struct gDPInfo gDP;

#ifdef __cplusplus
}
#endif

#endif
