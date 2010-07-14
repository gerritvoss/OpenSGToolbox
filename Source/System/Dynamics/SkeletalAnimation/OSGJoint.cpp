/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#include "OSGJoint.h"
#ifndef OSG_EMBEDDED
#include "OSGIntersectAction.h"
#endif

#include "OSGRenderAction.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGIntersectActor.h"
#endif

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGJointBase.cpp file.
// To modify it, please change the .fcd file (OSGJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Joint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifndef OSG_EMBEDDED
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Joint::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Joint::intersectLeave));
#endif
       
        RenderAction::registerEnterDefault(
            Joint::getClassType(), 
            reinterpret_cast<Action::Callback>(&Joint::renderEnter));

        RenderAction::registerLeaveDefault(
            Joint::getClassType(), 
            reinterpret_cast<Action::Callback>(&Joint::renderLeave));

#ifdef OSG_HAVE_ACTION //CHECK
    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          JointPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Joint::intersectActorEnter),
        getClassType());

    IntersectActor::regClassLeave(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          JointPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Joint::intersectActorLeave),
        getClassType());
#endif
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Joint::accumulateMatrix(Matrixr &result)
{
    Inherited::accumulateMatrix(result);

    result.mult(getJointTransformation());
}
/*-------------------------------------------------------------------------*/
/*                            Render                                       */

ActionBase::ResultE Joint::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    Matrix Transform(this->getMatrix());
    Transform.mult(this->getJointTransformation());
    pAction->pushMatrix(Transform);

    return ActionBase::Continue;
}

ActionBase::ResultE Joint::renderLeave(Action *action)
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
ActionBase::ResultE Joint::intersectEnter(Action *action)
{
    // Use parent class for trivial reject
    if(Inherited::intersect(action) == Action::Skip)
        return Action::Skip;
    
    // Need to check children
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.mult(this->getJointTransformation());
    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    Real32 length = dir.length();

    if(length < TypeTraits<Real32>::getDefaultEps())
        SWARNING << "Joint::intersectEnter: Near-zero scale!" << std::endl;

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale  (length                          );
    
    return ActionBase::Continue; 
}

ActionBase::ResultE Joint::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();
    m.mult(this->getJointTransformation());
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return ActionBase::Continue;
}
#endif

#ifdef OSG_HAVE_ACTION //CHECK
NewActionTypes::ResultE Joint::intersectActorEnter(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA        = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    Matrix          matrix     = this->getMatrix();
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

    matrix.mult(this->getJointTransformation());
    matrix.invert();

    matrix.multFull(pIA->getRay().getPosition (), pos);
    matrix.mult    (pIA->getRay().getDirection(), dir);

    transLine.setValue(pos, dir);

    pIA->beginEditState();
    {
        pIA->setRay        (transLine                           );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE Joint::intersectActorLeave(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    const Matrix   &matrix = this->getMatrix();
          Pnt3f     pos;
          Vec3f     dir;

    matrix.mult(this->getJointTransformation());
    matrix.multFull(pIA->getRay().getPosition (), pos);
    matrix.mult    (pIA->getRay().getDirection(), dir);

    pIA->beginEditState();
    {
        pIA->setRay        (Line(pos, dir)                      );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    return NewActionTypes::Continue;
}
#endif

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void Joint::adjustVolume(Volume &volume)
{
    Inherited::adjustVolume(volume);

    volume.transform(getJointTransformation());
}

/*----------------------- constructors & destructors ----------------------*/

Joint::Joint(void) :
    Inherited()
{
}

Joint::Joint(const Joint &source) :
    Inherited(source)
{
}

Joint::~Joint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Joint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & JointTransformationFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

void Joint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Joint NI" << std::endl;
}

OSG_END_NAMESPACE
