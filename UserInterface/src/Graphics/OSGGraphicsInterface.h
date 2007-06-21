#ifndef _OPENSG_USERINTERFACE_GRAPHICSINTERFACE_H_
#define _OPENSG_USERINTERFACE_GRAPHICSINTERFACE_H_

#include "OSGUserInterfaceConfig.h"
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGColor.h>

OSG_BEGIN_NAMESPACE

class OSG_USER_INTERFACE_CLASS_API GraphicsInterface
{
    /*==========================  PUBLIC  =================================*/
public:
	
    /*---------------------------------------------------------------------*/
    /*! \name                      drawSolidRect                           */
    /*! \{                                                                 */
	virtual void drawSolidRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color) const = 0;

    /*---------------------------------------------------------------------*/
    /*! \name                      drawTransleucentRect                           */
    /*! \{                                                                 */
	virtual void drawTransleucentRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color) const = 0;
	
	virtual void drawSolidLine(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color) const = 0;

	virtual void drawTransleucentLine(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color) const = 0;
	
	virtual void drawSolidDisc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Int16& StartAngle, const Int16& EndAngle, const Color3f& Color) const = 0;

	virtual void drawTransleucentDisc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Int16& StartAngle, const Int16& EndAngle, const Color4f& Color) const = 0;
	
	virtual void drawSolidArc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Int16& StartAngle, const Int16& EndAngle, const Color3f& Color) const = 0;

	virtual void drawTransleucentArc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Int16& StartAngle, const Int16& EndAngle, const Color4f& Color) const = 0;

	virtual void drawLoweredBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color, const Int16& Width) const = 0;

	virtual void drawRaisedBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color, const Int16& Width) const = 0;
	
	virtual void drawString(const Pnt2s& Position, const std::string& Text) const = 0;

	virtual void preDraw() = 0;


};

OSG_END_NAMESPACE

#endif