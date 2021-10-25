#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;

class CMap : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 48, 95, 191, 144);
		}
		else{
			CRectangle::Render(Texture, 48, 95, 47, 1);
		}
	}
};

#endif
