/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
void WindowEventProducer::blockInputConnections(bool Block)
{
    _BlockInput = Block;
}

inline
bool WindowEventProducer::isBlockInputConnections(void) const
{
    return _BlockInput;
}

inline
WindowEventProducer::FileDialogFilter::FileDialogFilter(const std::string& Name, const std::string& Filter) : 
_Name(Name),
_Filter(Filter)
{
}

inline
const std::string& WindowEventProducer::FileDialogFilter::getName(void) const
{
    return _Name;
}

inline
const std::string& WindowEventProducer::FileDialogFilter::getFilter(void) const
{
    return _Filter;
}

inline
RenderAction * WindowEventProducer::getRenderAction(void)
{
	return _RenderAction;
}

inline
void WindowEventProducer::setRenderAction(RenderAction *action)
{
	_RenderAction = action;
}

inline
void WindowEventProducer::internalDraw(void)
{
	if(_DisplayCallbackFunc)
	{
		_DisplayCallbackFunc();
	}
	else
	{
		render(_RenderAction);
	}
}

inline
void WindowEventProducer::internalReshape(Vec2f size)
{
	if(_ReshapeCallbackFunc)
	{
		_ReshapeCallbackFunc(size);
	}
	else
	{
		resize(size.x(), size.y());
	}
}

inline
void WindowEventProducer::draw(void)
{
}

inline
UInt32 WindowEventProducer::getCursorType(void) const
{
	return _CursorType;
}

inline
WindowEventProducer::Click::Click(Time TimeStamp, Pnt2f Location) :
_TimeStamp(TimeStamp),
_Location(Location)
{
}

OSG_END_NAMESPACE
