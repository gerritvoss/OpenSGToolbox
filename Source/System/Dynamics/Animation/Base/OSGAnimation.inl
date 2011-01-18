/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

/*!\fn bool Animation::isPlaying(void) const
 *
 * \brief Queries the playing state of the animation.
 *
 * @return true if the animation is playing, false otherwise.
 */
inline
bool Animation::isPlaying(void) const
{
    return _IsPlaying;
}

/*!\fn bool Animation::isPaused(void) const
 *
 * \brief Queries the pause state of the animation.
 *
 * @return true if the animation is paused, false otherwise.
 */
inline
bool Animation::isPaused(void) const
{
    return _IsPaused;
}

/*!\fn void Animation::detachUpdateProducer(void)
 *
 * \brief Detach the event update producer from this animation if there is one
 * attached.
 */
inline
void Animation::detachUpdateProducer(void)
{
    _UpdateEventConnection.disconnect();
}

OSG_END_NAMESPACE
