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

#include "OSGAbstractFieldContainerEditor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AbstractFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the Generic Field Container Editor
    _GenericEditor->attachFieldContainer(fc); 

    return true;
}

bool AbstractFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the Generic Field Container Editor
    _GenericEditor->dettachFieldContainer(); 

    return Inherited::dettachFieldContainer();
}

Vec2f AbstractFieldContainerEditor::getPreferredScrollableViewportSize(void)
{
    return getRequestedSize();
}

Int32 AbstractFieldContainerEditor::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    return direction * (VisibleRectBottomRight[1] - VisibleRectTopLeft[1]);
}

bool AbstractFieldContainerEditor::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool AbstractFieldContainerEditor::getScrollableTracksViewportWidth(void)
{
    return true;
}


bool AbstractFieldContainerEditor::getScrollableHeightMinTracksViewport(void)
{
    return false;
}

bool AbstractFieldContainerEditor::getScrollableWidthMinTracksViewport(void)
{
    return false;
}

Int32 AbstractFieldContainerEditor::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    return 20;
}

void AbstractFieldContainerEditor::setCommandManager(CommandManagerPtr manager)
{
    Inherited::setCommandManager(manager);
    _GenericEditor->setCommandManager(manager);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void AbstractFieldContainerEditor::onCreate(const AbstractFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        //Create the Generic FieldContainerEditor
        _GenericEditor = GenericFieldContainerEditor::create();
    }
}

void AbstractFieldContainerEditor::onDestroy()
{
}

void AbstractFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _GenericEditor = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

AbstractFieldContainerEditor::AbstractFieldContainerEditor(void) :
    Inherited()
{
}

AbstractFieldContainerEditor::AbstractFieldContainerEditor(const AbstractFieldContainerEditor &source) :
    Inherited(source)
{
}

AbstractFieldContainerEditor::~AbstractFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
