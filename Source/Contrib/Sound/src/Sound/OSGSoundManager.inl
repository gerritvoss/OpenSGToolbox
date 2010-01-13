/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

inline
void SoundManager::attachUpdateProducer(WindowEventProducerUnrecPtr TheProducer)
{
    TheProducer->addUpdateListener(this);
}

inline
void SoundManager::detachUpdateProducer(WindowEventProducerUnrecPtr TheProducer)
{
    TheProducer->removeUpdateListener(this);
}

inline
void SoundManager::setCamera(CameraUnrecPtr TheCamera)
{
    //if(_Camera != NULL)
    //{
        //subRefCP(_Camera);
    //}
    _Camera = TheCamera;
    //if(_Camera != NULL)
    //{
        //addRefCP(_Camera);
    //}
}

inline
CameraUnrecPtr SoundManager::getCamera(void) const
{
    return _Camera;
}

OSG_END_NAMESPACE

