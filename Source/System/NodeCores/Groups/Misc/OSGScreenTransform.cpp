/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGScreenTransform.h"
#include "OSGVolume.h"
#include "OSGPlane.h"

#ifndef OSG_EMBEDDED
#include "OSGIntersectAction.h"
#endif

#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScreenTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGScreenTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifndef OSG_EMBEDDED
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::intersectLeave));
#endif
       
        RenderAction::registerEnterDefault(
            ScreenTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::renderEnter));

        RenderAction::registerLeaveDefault(
            ScreenTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ScreenTransform::renderLeave));

    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ScreenTransform::calcMatrix(const Matrixr &toWorld, Viewport* const theViewport)
{
    //Get the local to world transformation
    Matrix BeaconToWorld;
    if(getBeacon() != NULL)
    {
        BeaconToWorld = getBeacon()->getToWorld();
    }
    
    //Get the Viewport Camera
    CameraUnrecPtr ViewportCamera = theViewport->getCamera();

    //Get the World to View transformation
    Matrix WorldToView;
    ViewportCamera->getViewing(WorldToView, theViewport->getPixelWidth(), theViewport->getPixelHeight());

    //Store the previous value
    Matrixr prevValue(_Transform);
    
    //Invert the current Model Transformation
    if(getInvertWorldTransform())
    {
        _Transform.invertFrom(toWorld);
    }
    else
    {
        _Transform.setIdentity();
    }

    //Invert the current View Transformation
    if(getInvertViewTransform())
    {
        Matrix ViewToWorld;
        ViewToWorld.invertFrom(WorldToView);
        _Transform.mult(ViewToWorld);
        

        //Setup a new view transformation
        _Transform.mult(getView());
    }

    //Setup a new Model Transformation, transform such that the screen position of the origin of the beacon
    //node and the screen position of the origin of child nodes are the same.
    if(getApplyBeaconScreenTranslation())
    {
        //The Screen Pos should now be projected to the near plane
        Matrix proj, projtrans;

        ViewportCamera->getProjection(proj,
                           theViewport->getPixelWidth(),
                           theViewport->getPixelHeight());

        ViewportCamera->getProjectionTranslation(projtrans,
                                      theViewport->getPixelWidth(),
                                      theViewport->getPixelHeight());

        Matrix wctocc = proj;

        wctocc.mult(projtrans);

        Matrix cctowc;

        cctowc.invertFrom(wctocc);

        Pnt3f from, at;

        Pnt3f BeaconScreenPos = BeaconToWorld * Pnt3f(0.0f,0.0f,0.0f);


        //Get the World to Screen transformation
        Matrix WorldToScreen;
        ViewportCamera->getWorldToScreen(WorldToScreen, *theViewport);
        WorldToScreen.multFull(BeaconScreenPos, BeaconScreenPos);

        cctowc.multFull(Pnt3f(BeaconScreenPos.x(), BeaconScreenPos.y(), -1), from);
        cctowc.multFull(Pnt3f(BeaconScreenPos.x(), BeaconScreenPos.y(),  1), at  );

	    Vec3f dir = at - from;

        Line line;
        line.setValue(from, dir);

        Vec3f PlaneNormal(0.0f,0.0f,1.0f);
        Pnt3f PlanePoint(0.0f,0.0f,0.0f);
        getView().mult(PlaneNormal,PlaneNormal);
        getView().mult(PlanePoint,PlanePoint);
        Plane p(PlaneNormal, PlanePoint);
        Real32 t;
        p.intersect(line,t);

        Pnt3f TransformedPoint = line.getPosition() + line.getDirection() * t;
        
        Matrix TranslateMat;
        TranslateMat.setIdentity();

        TranslateMat.setTranslate(Vec3f(TransformedPoint.x(),TransformedPoint.y(),0.0f));

        _Transform.mult(TranslateMat);
    }
    
    //The new model transformation should be rotated by the Beacons rotation
    if(getApplyBeaconRotation())
    {
        Matrix BeaconToView(BeaconToWorld);
        if(getInvertViewTransform())
        {
            BeaconToView.multLeft(WorldToView);
        }
        Vec3f      translation;       // for matrix decomposition
        Quaternion BeaconRot;
        Vec3f      scaleFactor;
        Quaternion scaleOrientation;
        BeaconToView.getTransform(translation, BeaconRot, scaleFactor, scaleOrientation);

        Matrix RotMat;
        RotMat.setRotate(BeaconRot);
        _Transform.mult(RotMat);
    }

    if(_Transform != prevValue)
    {
        invalidateVolume();
    }
}

void ScreenTransform::accumulateMatrix(Matrixr &result)
{
    result.mult(_Transform);
}

void ScreenTransform::adjustVolume(Volume &volume)
{
    volume.transform(_Transform);
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE ScreenTransform::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    calcMatrix(pAction->topMatrix(), pAction->getViewport());

    pAction->pushVisibility();

    pAction->pushMatrix(_Transform);

    return Action::Continue;
}

ActionBase::ResultE ScreenTransform::renderLeave(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

#ifndef OSG_EMBEDDED
ActionBase::ResultE ScreenTransform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_Transform);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

ActionBase::ResultE ScreenTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_Transform);

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}
#endif
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenTransform::ScreenTransform(void) :
    Inherited(),
    _Transform ()
{
}

ScreenTransform::ScreenTransform(const ScreenTransform &source) :
    Inherited(source),
    _Transform (source._Transform)
{
}

ScreenTransform::~ScreenTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenTransform::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & BeaconFieldMask)
    {
        invalidateVolume();
    }
}

void ScreenTransform::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScreenTransform NI" << std::endl;
}

OSG_END_NAMESPACE
