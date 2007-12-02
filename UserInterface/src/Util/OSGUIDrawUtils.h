#ifndef _OSG_UI_DRAW_UTILS_H_
#define _OSG_UI_DRAW_UTILS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/OSGVector.h>
#include "Component/OSGComponent.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Graphics/UIDrawObjects/OSGUIDrawObjectFields.h"

OSG_BEGIN_NAMESPACE

void OSG_USERINTERFACELIB_DLLMAPPING convertTopLeftToCenteredLine(const Pnt2s& Point1, const Pnt2s& Point2, const UInt16 Width,Pnt2s& ResultPoint1, Pnt2s& ResultPoint2);
void OSG_USERINTERFACELIB_DLLMAPPING convertTopRightToCenteredLine(const Pnt2s& Point1, const Pnt2s& Point2, const UInt16 Width,Pnt2s& ResultPoint1, Pnt2s& ResultPoint2);

Pnt2s OSG_USERINTERFACELIB_DLLMAPPING calculateAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const Real32& VAlign, const Real32& HAlign);
//Pnt2s OSG_USERINTERFACELIB_DLLMAPPING calculateAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const UInt32& VAlign, const UInt32& HAlign);

void OSG_USERINTERFACELIB_DLLMAPPING quadIntersection(const Pnt2s& Quad1TopLeft, const Pnt2s& Quad1BottomRight,
                                                      const Pnt2s& Quad2TopLeft, const Pnt2s& Quad2BottomRight,
                                                      Pnt2s& ResultQuadTopLeft, Pnt2s& ResultQuadBottomRight);

void OSG_USERINTERFACELIB_DLLMAPPING componentQuadIntersection(const ComponentPtr c1,
                                                      const ComponentPtr c2,
                                                      Pnt2s& ResultQuadTopLeft, Pnt2s& ResultQuadBottomRight);

bool OSG_USERINTERFACELIB_DLLMAPPING isContainedBounds(const Pnt2s& Point, const ComponentPtr Comp);

//Point: a point in Window space
//Comp: A component
bool OSG_USERINTERFACELIB_DLLMAPPING isContainedClipBounds(const Pnt2s& Point, const ComponentPtr Comp);

bool OSG_USERINTERFACELIB_DLLMAPPING isContainedBounds(const Pnt2s& Point, const Pnt2s& TopLeft, const Pnt2s& BottomRight);
//Pnt2s OSG_USERINTERFACELIB_DLLMAPPING WindowToComponent(const Pnt2s& WindowPoint, const ComponentPtr Comp);
//Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ComponentToWindow(const Pnt2s& ComponentPoint, const ComponentPtr Comp);

Pnt2s OSG_USERINTERFACELIB_DLLMAPPING DrawingSurfaceToComponent(const Pnt2s& DrawingSurfacePoint, const ComponentPtr Comp);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ViewportToComponent(const Pnt2s& ViewportPoint, const ComponentPtr Comp, const ViewportPtr TheViewport);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ComponentToViewport(const Pnt2s& ComponentPoint, const ComponentPtr Comp, const ViewportPtr TheViewport);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ViewportToDrawingSurface(const Pnt2s& ViewportPoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING DrawingSurfaceToViewport(const Pnt2s& DrawingSurfacePoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ComponentToDrawingSurface(const Pnt2s& ComponentPoint, const ComponentPtr Comp);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING ComponentToFrame(const Pnt2s& ComponentPoint, const ComponentPtr Comp);
Pnt2s OSG_USERINTERFACELIB_DLLMAPPING Rotate(const Pnt2s& Point, const Real32& Angle);

void OSG_USERINTERFACELIB_DLLMAPPING getDrawObjectBounds(MFUIDrawObjectPtr DrawObjects, Pnt2s& TopLeft, Pnt2s& BottomRight);

OSG_END_NAMESPACE

#include "OSGUIDefines.inl"
#endif /* _OSG_UI_DRAW_UTILS_H_ */
