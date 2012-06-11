#include <stdio.h>
#include <SDL/SDL.h>
#include "_start.hpp"
#include "osx/osx_common.h"

sSystem_ *sSystem=NULL;
sBroker_ *sBroker=NULL;

static void initAttributes ()
{
	// Setup attributes we want for the OpenGL context

	int value;

	// Don't set color bit sizes (SDL_GL_RED_SIZE, etc)
	//    Mac OS X will always use 8-8-8-8 ARGB for 32-bit screens and
	//    5-5-5 RGB for 16-bit screens

	// Request a 16-bit depth buffer (without this, there is no depth buffer)
	// is there any speed benefit to using a lower precision depth buffer?
	value = 32;
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, value);


	// Request double-buffered OpenGL
	//     The fact that windows are double-buffered on Mac OS X has no effect
	//     on OpenGL double buffering.
	value = 1;
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, value);
}

static void createSurface (int fullscreen)
{
	int flags = 0;

	flags = SDL_OPENGL;
	if (fullscreen)
		flags |= SDL_FULLSCREEN;

	// Create window
	SDL_Surface *surface = SDL_SetVideoMode (640, 480, 0, flags);
	if (surface == NULL) {

		fprintf (stderr, "Couldn't set 640x480 OpenGL video mode: %s\n",
			SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Blobs",NULL);
}

static void printAttributes ()
{
	// Print out attributes of the context we created
	int nAttr;
	int i;

	SDL_GLattr  attr[] = { SDL_GL_RED_SIZE, SDL_GL_BLUE_SIZE, SDL_GL_GREEN_SIZE,
		SDL_GL_ALPHA_SIZE, SDL_GL_BUFFER_SIZE, SDL_GL_DEPTH_SIZE };

	const char *desc[] = { "Red size: %d bits\n", "Blue size: %d bits\n", "Green size: %d bits\n",
		"Alpha size: %d bits\n", "Color buffer size: %d bits\n", 
		"Depth bufer size: %d bits\n" };

	nAttr = sizeof(attr) / sizeof(int);

	for (i = 0; i < nAttr; i++) {

		int value;
		SDL_GL_GetAttribute (attr[i], &value);
		printf (desc[i], value);
	} 
}

int main(int argc, char *argv[])
{
	// Init SDL video subsystem
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 )
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
			SDL_GetError());
		exit(1);
	}

	// Set GL context attributes
	initAttributes ();

	// Create GL context
	createSurface (0);

	// Get GL context attributes
	printAttributes ();

	sSystem=new sSystem_;

  // config
  if(sAppHandler(sAPPCODE_CONFIG,0))
    sSystem->InitX();

	delete sSystem;

	SDL_Quit();

	// PC version prints memory leaks here

	return 0;
}

static void MakeCpuMask()
{
	sSystem->CpuMask=0;
}

sU32 sSystem_::PerfTime()
{
	MACTODO;
	return 0;	// TODO return some sort of precise timer value
}

void sSystem_::PerfKalib()
{
	MACTODO;
	// TODO - feedback loop to calibrate PerfTime
}

void sSystem_::InitScreens()
{
	// init SDL + GL

	// create dummy texture
	sU16 bmp[4*4*4];
	sSetMem(bmp,0,sizeof(bmp));
	AddTexture(4,4,sTF_A8R8G8B8,bmp,1);

	// TODO initialize gpumask
	// if(caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED) GpuMask |= sGPU_TWOSIDESTENCIL;

#ifdef _DOPE
	BufferMemAlloc = 0;
#endif

	ReCreateZBuffer();
	SyncQuery = 0;
	MACTODO;
	// /*DXERROR*/(DXDev->CreateQuery(D3DQUERYTYPE_EVENT,&SyncQuery));  // allow this to fail

	CreateGeoBuffer(0,1,0,MAX_DYNVBSIZE);
	CreateGeoBuffer(1,1,1,MAX_DYNIBSIZE);
	CreateGeoBuffer(2,1,2,MAX_DYNIBSIZE*2);
	CreateGeoBuffer(3,0,1,2*0x8000/4*6);
	MACTODO;
	/*
		DXERROR(GeoBuffer[3].IB->Lock(0,2*0x8000/4*6,(void **) &iblock,0));
		for(i=0;i<0x8000/6;i++)
		sQuad(iblock,i*4+0,i*4+1,i*4+2,i*4+3);
		DXERROR(GeoBuffer[3].IB->Unlock());

		HardwareShaderLevel = sPS_00;
		if((caps.PixelShaderVersion&0xffff)!=0x0000)
		{
		MakeCubeNormalizer();
		MakeAttenuationVolume();
		HardwareShaderLevel = sPS_11;
		if((caps.PixelShaderVersion&0xffff)>=0x0104)
		{
		HardwareShaderLevel = sPS_14;
		if((caps.PixelShaderVersion&0xffff)>=0x0200)
		{
		HardwareShaderLevel = sPS_20;
		}
		}
		}
	// set some defaults
	DXDev->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	DXDev->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	DXDev->SetRenderState(D3DRS_LIGHTING,0);

	for(i=0;i<MAX_TEXTURE;i++)
	{
	if(Textures[i].Flags & sTIF_RENDERTARGET)
	{
	tex = &Textures[i];
	DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&tex->Tex,0));

	if(Textures[i].Flags & sTIF_NEEDEXTRAZ)
	DXERROR(DXDev->CreateDepthStencilSurface(tex->XSize,tex->YSize,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&tex->Shadow,0));
	}
	}

	DiscardCount[0] = DiscardCount[1] = DiscardCount[2] = 1;

	LastDecl = -1;
	LastVB = -1;
	LastVSize = 0;
	LastIB = -1;
	MtrlReset = sTRUE;
	MtrlClearCaches();

	CurrentTarget = -1;
	NeedFinishBlit = sFALSE;
	*/
}

void sSystem_::ReCreateZBuffer()
{
	MACTODO;
}

void sSystem_::InitX()
{
  sInt i;

	MakeCpuMask();
	sInitTypes();
#if sLINK_RYGDXT
  sInitDXT();
#endif
  sBroker = new sBroker_;
#if sLINK_UTIL
  sPerfMon = new sPerfMon_;
  sBroker->AddRoot(sPerfMon);
#endif

// init

  WDeviceLost = 0;
  WActiveCount = 0;
  WActiveMsg = 1;
  WContinuous = 1;
  WSinglestep = 0;
  WFullscreen = 0;
  WWindowedStyle = 0;
  WMinimized = 0;
  WMaximized = 0;
  WAborting = sFALSE;
  WResponse = 0;
  WConstantUpdate = sTRUE;
  WAbortKeyFlag = 0;
  WFocus = 1;

  CmdLowQuality = 0;
  CmdLowRes = 0;
  CmdShaderLevel = sPS_20;
  CmdNoRt = sFALSE;

  CmdWindowed = 0;
  CmdFullscreen = 0;

	// TODO parse cmd line opts here
	

  sSetMem(GeoBuffer,0,sizeof(GeoBuffer));
  sSetMem(GeoHandle,0,sizeof(GeoHandle));

  sSetMem(&PerfThis,0,sizeof(PerfThis));
  sSetMem(&PerfLast,0,sizeof(PerfLast));
  PerfThis.Time = sSystem->PerfTime();

#ifdef _DOPE
  TexMemAlloc = 0;
#endif

	ZBufXSize = ZBufYSize = 0;
	ZBufFormat = 0;
	ZBuffer = 0;
  RTBuffer = 0;
  CurrentRT = 0;
  SyncQuery = 0;
  
  for(i=0;i<MAX_TEXTURE;i++)
    Textures[i].Flags = 0;

  sSetMem(Setups,0,sizeof(Setups));
  sSetMem(Shaders,0,sizeof(Shaders));

  MtrlClearCaches();
  InitScreens();

  if(CmdShaderLevel>GetShaderLevel())
    CmdShaderLevel = GetShaderLevel();

  sAppHandler(sAPPCODE_INIT,0);

	// TODO poll events
	//
	SDL_Event event;
	bool			done=false;
	while ( !done && SDL_PollEvent (&event) )
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				if ((event.key.keysym.mod&KMOD_META) && event.key.keysym.sym=='q')
				{
					//done=true;
				}
				MACTODO;
				//sAppHandler(sAPPCODE_KEY,KeyBuffer[i]);
				break;
			case SDL_QUIT:
				done=true;
				break;
			default:
				break;
		}
		Render();
		PerfLast.TimeFiltered = (PerfLast.TimeFiltered*7+PerfLast.Time)/8;
		PerfLast.Line     = PerfThis.Line;
		PerfLast.Triangle = PerfThis.Triangle;
		PerfLast.Vertex   = PerfThis.Vertex;
		PerfLast.Material = PerfThis.Material;
		PerfThis.Line     = 0;
		PerfThis.Triangle = 0;
		PerfThis.Vertex   = 0;
		PerfThis.Material = 0;
#if sLINK_UTIL
		sPerfMon->Flip();
#elif !sINTRO
		sSystem->PerfKalib();
#endif
		// TODO framelock
		SDL_Delay(0);
	}

  sAppHandler(sAPPCODE_EXIT,0);
// cleanup

#if sLINK_UTIL
  sBroker->RemRoot(sPerfMon);
#endif
  sBroker->Free();      // some objects may still hold resources, like Geometries
  sBroker->Dump();
  ExitScreens();

  for(i=0;i<MAX_TEXTURE;i++)
    Textures[i].Flags=0;
  sExitTypes();

  sBroker->Free();			// MT : PC code called this twice - is this intended?
  sBroker->Dump();
  delete sBroker;
  sBroker = 0;
}

void sSystem_::MtrlClearCaches()
{
  CurrentSetupId = sINVALID;
  CurrentVS = 0;
  CurrentPS = 0;

  for(sInt i=0;i<MAX_TEXSTAGE;i++)
    CurrentTextures[i] = sINVALID;

  for(sInt i=0;i<0x310;i++)
    CurrentStates[i] = 0xfefefefe; // let's hope we never actually want this value
}
