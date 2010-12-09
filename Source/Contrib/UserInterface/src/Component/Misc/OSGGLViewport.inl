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

inline
void GLViewport::setMode(Navigator::Mode TheMode)
{
    _Navigator.setMode(TheMode);
}

inline
void GLViewport::setCamera(Camera* TheCamera)
{
    _NavCamera = TheCamera;
    if(_DrawingViewport != NULL)
    {
        _DrawingViewport->setCamera(_NavCamera);
    }
}

inline
Camera* GLViewport::getCamera(void) const
{
    return _NavCamera;
}

inline
RenderAction* GLViewport::getRenderAction(void) const
{
    return _RenderAction.get();
}

inline
void GLViewport::showAll(void)
{
    if(getPort() != NULL)
    {
        show(getPort()->getRoot());
    }
}

inline
void GLViewport::setMotionFactor(Real32 Factor)
{
    _Navigator.setMotionFactor(Factor);
}

inline
Viewport* GLViewport::getDrawingViewport(void) const
{
    return _DrawingViewport;
}

OSG_END_NAMESPACE
