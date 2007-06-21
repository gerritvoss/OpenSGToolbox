#ifndef _OPENSG_USERINTERFACE_GRAPHICS2D_H_
#define _OPENSG_USERINTERFACE_GRAPHICS2D_H_

#include "OSGUserInterfaceConfig.h"

#include "OSGGraphicsInterface.h"

#include <OpenSG/OSGGL.h>

OSG_BEGIN_NAMESPACE

class OSG_USER_INTERFACE_CLASS_API Graphics2D : public GraphicsInterface
{
protected:
	GLboolean _light;
	GLint _fill[2];
	GLboolean _depth;
	GLboolean _colmat;

public:
	virtual void preDraw();
	virtual void postDraw();

	virtual void drawSolidRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color) const;
	virtual void drawTransleucentRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color) const;
};

OSG_END_NAMESPACE

#endif