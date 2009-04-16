/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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
FunctionComponentPanel::ComponentPanelMoveListener::ComponentPanelMoveListener(FunctionComponentPanelPtr TheFunctionComponentPanel) :
_FunctionComponentPanel(TheFunctionComponentPanel)
{
}

inline
FunctionComponentPanel::ComponentMoveListener::ComponentMoveListener(FunctionComponentPanelPtr TheFunctionComponentPanel) :
_FunctionComponentPanel(TheFunctionComponentPanel)
{
}

inline
void FunctionComponentPanel::ComponentMoveListener::setInitialPosition(Pnt2f InitialPosition)
{
	_InitialPosition = InitialPosition;
}

inline
FunctionComponentPanel::ComponentResizeListener::ComponentResizeListener(FunctionComponentPanelPtr TheFunctionComponentPanel) :
_FunctionComponentPanel(TheFunctionComponentPanel)
{
}

inline
void FunctionComponentPanel::ComponentResizeListener::setInitialPosition(Pnt2f InitialPosition)
{
	_InitialPosition = InitialPosition;
}
OSG_END_NAMESPACE

#define OSGFUNCTIONCOMPONENTPANEL_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

