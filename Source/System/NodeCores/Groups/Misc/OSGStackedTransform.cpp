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

#include "OSGStackedTransform.h"
#include "OSGTransformationElement.h"

#ifndef OSG_EMBEDDED
#include "OSGIntersectAction.h"
#endif

#include "OSGRenderAction.h"
#include "OSGNameAttachment.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGIntersectActor.h"
#endif

#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStackedTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGStackedTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
std::string StackedTransform::TranslateName = std::string("translate");
std::string StackedTransform::RotateXName   = std::string("rotateX");
std::string StackedTransform::RotateYName   = std::string("rotateY");
std::string StackedTransform::RotateZName   = std::string("rotateZ");
std::string StackedTransform::ScaleName     = std::string("scale");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StackedTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            StackedTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &StackedTransform::renderEnter));
        
        RenderAction::registerLeaveDefault(
            StackedTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &StackedTransform::renderLeave));
        
        
#ifndef OSG_EMBEDDED
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &StackedTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &StackedTransform::intersectLeave));
#endif
        
#ifdef OSG_HAVE_ACTION //CHECK
        IntersectActor::regClassEnter(
            osgTypedMethodFunctor2BaseCPtr<
                NewActionTypes::ResultE,
                StackedTransformPtr  ,
                NodeCorePtr            ,
                ActorBase::FunctorArgumentType &>(
                    &StackedTransform::intersectActorEnter),
            getClassType());
        
        IntersectActor::regClassLeave(
            osgTypedMethodFunctor2BaseCPtr<
                NewActionTypes::ResultE,
                StackedTransformPtr  ,
                NodeCorePtr            ,
                ActorBase::FunctorArgumentType &>(
                    &StackedTransform::intersectActorLeave),
            getClassType());
#endif
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void StackedTransform::updateTransform(void)
{
    _Transformation.setIdentity();

    for(UInt32 i(0) ; i<getMFTransformElements()->size(); ++i)
    {
        getTransformElements(i)->accumulateMatrix(_Transformation);
    }
        
    invalidateVolume();
}

void StackedTransform::accumulateMatrix(Matrixr &result)
{
    result.mult(_Transformation);
}

void StackedTransform::adjustVolume(Volume &volume)
{
    volume.transform(_Transformation);
}

TransformationElement* StackedTransform::getElement(const std::string& Name) const
{
    const Char8* ElemName;
    for(UInt32 i(0) ; i<getMFTransformElements()->size(); ++i)
    {
        ElemName = getName(getTransformElements(i));
        if(ElemName != NULL &&
           Name.compare(ElemName) == 0)
        {
            return getTransformElements(i);
        }
    }

    return NULL;
}

void StackedTransform::pushToNamedTransformElements(TransformationElement * const value,
                                    const std::string& Name)
{
    setName(value, Name.c_str());
    Inherited::pushToTransformElements(value);
}

void StackedTransform::insertIntoNamedTransformElements(UInt32               uiIndex,
                                    TransformationElement * const value,
                                    const std::string& Name)
{
    setName(value, Name.c_str());
    Inherited::insertIntoTransformElements(uiIndex, value);
}

void StackedTransform::replaceInNamedTransformElements(UInt32         uiIndex,
                                    TransformationElement * const value,
                                    const std::string& Name)
{
    setName(value, Name.c_str());
    Inherited::replaceInTransformElements(uiIndex, value);
}

void StackedTransform::replaceObjInNamedTransformElements (TransformationElement * const pOldElem,
                                    TransformationElement * const pNewElem,
                                    const std::string& Name)
{
    setName(pNewElem, Name.c_str());
    Inherited::replaceObjInTransformElements(pOldElem, pNewElem);
}

void StackedTransform::removeFromNamedTransformElements   (const std::string& Name)
{
    const Char8* ElemName;
    for(UInt32 i(0) ; i<getMFTransformElements()->size(); ++i)
    {
        ElemName = getName(getTransformElements(i));
        if(ElemName != NULL &&
           Name.compare(ElemName) == 0)
        {
            Inherited::removeFromTransformElements(i);
            return;
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE StackedTransform::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->pushMatrix(this->_Transformation);

    return ActionBase::Continue;
}

ActionBase::ResultE StackedTransform::renderLeave(Action *action)
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
ActionBase::ResultE StackedTransform::intersectEnter(Action *action)
{
    // Use parent class for trivial reject
    if(Inherited::intersect(action) == Action::Skip)
        return Action::Skip;
    
    // Need to check children
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->_Transformation;

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);
    
    Real32 length = dir.length();

    if(length < TypeTraits<Real32>::getDefaultEps())
        SWARNING << "StackedTransform::intersectEnter: Near-zero scale!" << std::endl;

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale  (length                          );
    
    return ActionBase::Continue; 
}

ActionBase::ResultE StackedTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->_Transformation;
    
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
NewActionTypes::ResultE StackedTransform::intersectActorEnter(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA        = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    Matrix          matrix     = this->_Transformation;
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

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

NewActionTypes::ResultE StackedTransform::intersectActorLeave(
    ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(
                                                           funcArg.getActor());
    const Matrix   &matrix = this->_Transformation;
          Pnt3f     pos;
          Vec3f     dir;

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

/*----------------------- constructors & destructors ----------------------*/

StackedTransform::StackedTransform(void) :
    Inherited()
{
}

StackedTransform::StackedTransform(const StackedTransform &source) :
    Inherited(source)
{
}

StackedTransform::~StackedTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StackedTransform::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & TransformElementsFieldMask))
    {
        updateTransform();
    }
}

void StackedTransform::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StackedTransform NI" << std::endl;
}

OSG_END_NAMESPACE
