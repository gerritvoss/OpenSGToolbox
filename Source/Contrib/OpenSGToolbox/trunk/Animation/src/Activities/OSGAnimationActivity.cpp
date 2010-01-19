/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEANIMATIONLIB

#include <OpenSG/OSGConfig.h>

#include "OSGAnimationActivity.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AnimationActivity

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimationActivity::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AnimationActivity::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    if (getAnimation() == NullFC) return;
    switch (getActivityType()){
        case ANIMATION_START:
            //animation->pause(); 
            break;
        case ANIMATION_PAUSE:
            //animation->pause(); 
            break;
        case ANIMATION_PAUSETOGGLE: 
            //animation->pauseToggle(); 
            break;
        case ANIMATION_UNPAUSE:
            //animation->unpause();
            break;
        case ANIMATION_STOP:
            //animation->stop();
            break;
        default:
            SWARNING << "AnimationActivity::eventProduced(): Unknown Activity Type: " << getActivityType() << std::endl;
            break;
    };
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimationActivity::AnimationActivity(void) :
    Inherited()
{
}

AnimationActivity::AnimationActivity(const AnimationActivity &source) :
    Inherited(source)
{
}

AnimationActivity::~AnimationActivity(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimationActivity::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AnimationActivity::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AnimationActivity NI" << std::endl;
}


OSG_END_NAMESPACE

