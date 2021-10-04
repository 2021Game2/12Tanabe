#include"CInvisibleBlock.h"
#include"CTexture.h"

extern CTexture Texture;

CInvisibleBlock::CInvisibleBlock()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EINVISIBLEBLOCK;
	w = 50;
	h = 50;
}

void CInvisibleBlock::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture, 130 - 1, 150 + 1, 90 + 1, 95 - 1);
	}
}