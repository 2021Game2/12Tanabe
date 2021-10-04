#include "CBreakableWall.h"
#include"CTexture.h"

extern CTexture Texture;

CBreakableWall::CBreakableWall()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EBREAKABLEWALL;
	w = 50;
	h = 50;

}

void CBreakableWall::Updata()
{
}

void CBreakableWall::Render()
{
}
