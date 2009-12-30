/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
bool Animation::isAnimationListenerAttached(AnimationListenerPtr Listener) const
{
    return _AnimationListeners.find(Listener) != _AnimationListeners.end();
}


inline
bool Animation::isPlaying(void) const
{
    return _IsPlaying;
}

inline
bool Animation::isPaused(void) const
{
    return _IsPaused;
}

inline
void Animation::attachUpdateProducer(EventProducerPtr TheProducer)
{
    if(_UpdateEventConnection.isConnected())
    {
        _UpdateEventConnection.disconnect();
    }
    _UpdateEventConnection = TheProducer->attachEventListener(&_UpdateHandler, "Update");
}

inline
void Animation::detachUpdateProducer(void)
{
    _UpdateEventConnection.disconnect();
}

inline
Animation::UpdateHandler::UpdateHandler(AnimationPtr TheAnimation) : _AttachedAnimation(TheAnimation)
{
}

OSG_END_NAMESPACE

