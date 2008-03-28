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

Pnt2f OSG_USERINTERFACELIB_DLLMAPPING calculateAlignment(const Pnt2f& Position1, const Vec2f& Size1, const Vec2f& Size2, const Real32& VAlign, const Real32& HAlign);

void OSG_USERINTERFACELIB_DLLMAPPING quadIntersection(const Pnt2f& Quad1TopLeft, const Pnt2f& Quad1BottomRight,
                                                      const Pnt2f& Quad2TopLeft, const Pnt2f& Quad2BottomRight,
                                                      Pnt2f& ResultQuadTopLeft, Pnt2f& ResultQuadBottomRight);

void OSG_USERINTERFACELIB_DLLMAPPING componentQuadIntersection(const ComponentPtr c1,
                                                      const ComponentPtr c2,
                                                      Pnt2f& ResultQuadTopLeft, Pnt2f& ResultQuadBottomRight);

bool OSG_USERINTERFACELIB_DLLMAPPING isContainedBounds(const Pnt2f& Point, const ComponentPtr Comp);

//Point: a point in Window space
//Comp: A component
bool OSG_USERINTERFACELIB_DLLMAPPING isContainedClipBounds(const Pnt2f& Point, const ComponentPtr Comp);

bool OSG_USERINTERFACELIB_DLLMAPPING isContainedBounds(const Pnt2f& Point, const Pnt2f& TopLeft, const Pnt2f& BottomRight);

Pnt2f OSG_USERINTERFACELIB_DLLMAPPING DrawingSurfaceToComponent(const Pnt2f& DrawingSurfacePoint, const ComponentPtr Comp);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ViewportToWindow(const Pnt2f& ViewportPoint, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ViewportToComponent(const Pnt2f& ViewportPoint, const ComponentPtr Comp, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ComponentToViewport(const Pnt2f& ComponentPoint, const ComponentPtr Comp, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ComponentToWindow(const Pnt2f& ComponentPoint, const ComponentPtr Comp, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ViewportToDrawingSurface(const Pnt2f& ViewportPoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING DrawingSurfaceToViewport(const Pnt2f& DrawingSurfacePoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ComponentToDrawingSurface(const Pnt2f& ComponentPoint, const ComponentPtr Comp);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING ComponentToFrame(const Pnt2f& ComponentPoint, const ComponentPtr Comp);
Pnt2f OSG_USERINTERFACELIB_DLLMAPPING Rotate(const Pnt2f& Point, const Real32& Angle);

void OSG_USERINTERFACELIB_DLLMAPPING getDrawObjectBounds(MFUIDrawObjectPtr DrawObjects, Pnt2f& TopLeft, Pnt2f& BottomRight);

OSG_END_NAMESPACE

#include "OSGUIDefines.inl"
#endif /* _OSG_UI_DRAW_UTILS_H_ */
