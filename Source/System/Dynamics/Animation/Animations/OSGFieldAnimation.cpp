/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGAnimator.h"
#include "OSGFieldAnimation.h"
//#include "OSGKeyframeAnimator.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldAnimationBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldAnimation.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldAnimation::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 FieldAnimation::getUnclippedCycleLength(void) const
{
    if(getAnimator())
    {
        return getAnimator()->getLength();
    }
    else
    {
        return -1.0f;
    }
}

void FieldAnimation::setAnimatedField(FieldContainerUnrecPtr TheContainer, const std::string& FieldName)
{
    setFieldName( FieldName );
    setContainer( TheContainer );
    commitChanges();
}

void FieldAnimation::setAnimatedField(FieldContainerUnrecPtr TheContainer, UInt32 FieldID)
{
    setFieldId( FieldID );
    setContainer( TheContainer );
    commitChanges();
}

void FieldAnimation::setAnimatedMultiField(FieldContainerUnrecPtr TheContainer, const std::string& FieldName, UInt32 Index)
{
    setFieldName( FieldName );
    setContainer( TheContainer );
    setIndex( Index );
    commitChanges();
}

void FieldAnimation::setAnimatedMultiField(FieldContainerUnrecPtr TheContainer, UInt32 FieldID, UInt32 Index)
{
    setFieldId( FieldID );
    setContainer( TheContainer );
    setIndex( Index );
    commitChanges();
}

void FieldAnimation::internalUpdate(Real32 t, const Real32 prev_t)
{
    if(getContainer() == NULL || getFieldId() == 0)
    {
        SWARNING << "There is no Field Container defined to Animate"  << std::endl;
        return;
    }
    EditFieldHandlePtr TheField = getContainer()->editField( getFieldId() );

    //Check if it's the right type
    if(getAnimator() == NULL)
    {
        SWARNING << "No Animator attached."  << std::endl;
        return;
    }

    //Check if it's the right type
    if(getAnimator()->getDataType() == NULL)
    {
        SWARNING << "Cannot update animation, because the animator attached to this animation does not work on any data types."  << std::endl;
        return;
    }

    if(getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType()
       != *getAnimator()->getDataType())
    {
        SWARNING << "The data type of the field: "
            << getContainer()->getFieldDescription(getFieldId())->getName()
            << " with type: "
            << getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType().getCName()
            << " connected to this animation is not the same data type: "
            << getAnimator()->getDataType()->getCName()
            << ", that the animator works on."  << std::endl;
        return;
    }

    //Update the Field Container
    if( getAnimator()->animate(
                               static_cast<Animator::InterpolationType>(getInterpolationType()), 
                               static_cast<Animator::ValueReplacementPolicy>(getReplacementPolicy()),
                               (getCycling() < 0) || (getCycling() > getCycles()), 
                               t,
                               prev_t,
                               TheField,
                               getIndex()) )
    {
        //commitChanges();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldAnimation::FieldAnimation(void) :
    Inherited()
{
}

FieldAnimation::FieldAnimation(const FieldAnimation &source) :
    Inherited(source)
{
}

FieldAnimation::~FieldAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldAnimation::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & FieldNameFieldMask)
    {
        if(getContainer() != NULL)
        {

            FieldDescriptionBase * f = getContainer()->getFieldDescription(getFieldName().c_str());
            if( f == NULL )
            {
                SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
                return;
            }
            else
            {
                setFieldId(f->getFieldId());
                //commitChanges();
            }
        }
        else
        {
            SWARNING << "There is no Field Container defined to Animate"  << std::endl;
            return;
        }
    }
    else if((whichField & FieldIdFieldMask) ||
            (whichField & ContainerFieldMask))
    {
        if(getContainer() != NULL)
        {
            FieldDescriptionBase * f = getContainer()->getFieldDescription(getFieldId());
            if( f == NULL )
            {
                SWARNING << "Could not find Field ID"<< getFieldId() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
                return;
            }
            else
            {
                if(getAnimator()->getDataType() == NULL)
                {
                    SWARNING << "Cannot update animation, because the animator attached to this animation does not work on any data types."  << std::endl;
                    return;
                }
                //Check if it's the right type
                if(getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType()
                   != *getAnimator()->getDataType())
                {
                    SWARNING << "The data type of the field: "
                             << getContainer()->getFieldDescription(getFieldId())->getName()
                             << " with type: "
                             << getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType().getCName()
                             << " connected to this animation is not the same data type: "
                             << getAnimator()->getDataType()->getCName()
                             << ", that the animator works on."  << std::endl;
                    return;
                }
            }
        }
        else
        {
            SWARNING << "There is no Field Container defined to Animate"  << std::endl;
            return;
        }
    }
    if(whichField & IndexFieldMask)
    {
        if(getContainer() != NULL)
        {
            FieldDescriptionBase * f = getContainer()->getFieldDescription(getFieldId());
            if( f == NULL )
            {
                SWARNING << "Could not find Field ID"<< getFieldId() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
            }
            else
            {

                //Check if animator supports any types
                if(getAnimator()->getDataType() == NULL)
                {
                    SWARNING << "Cannot update animation, because the animator attached to this animation does not work on any data types."  << std::endl;
                }
                //Check if it's the right type
                if(getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType()
                   != *getAnimator()->getDataType())
                {
                    SWARNING << "The data type of the field: "
                             << getContainer()->getFieldDescription(getFieldId())->getName()
                             << " with type: "
                             << getContainer()->getFieldDescription(getFieldId())->getFieldType().getContentType().getCName()
                             << " connected to this animation is not the same data type: "
                             << getAnimator()->getDataType()->getCName()
                             << ", that the animator works on."  << std::endl;
                }
                GetFieldHandlePtr TheFieldHandle = getContainer()->getField( getFieldId() );

                if( getIndex() > 0 )
                {
                    if(TheFieldHandle->getCardinality() != FieldType::MultiField)
                    {
                        SWARNING << "Cannot attach to index: " << getIndex() 
                                 << " of field " << getContainer()->getFieldDescription(getFieldId())->getName() 
                                 << " because it has cardinality 1." << std::endl;
                    }
                    else if(getIndex() < TheFieldHandle->size())
                    {
                        SWARNING << "Cannot attach to index: " << getIndex() 
                                 << " of field " << getContainer()->getFieldDescription(getFieldId())->getName() 
                                 << " because that index is out of bounds on a field of size " << TheFieldHandle->size() << "." << std::endl;
                    }
                }
            }
        }
        else
        {
            SWARNING << "There is no Field Container defined to Animate"  << std::endl;
        }
    }
}

void FieldAnimation::dump(      UInt32    ,
                                const BitVector ) const
{
    SLOG << "Dump FieldAnimation NI" << std::endl;
}

OSG_END_NAMESPACE
