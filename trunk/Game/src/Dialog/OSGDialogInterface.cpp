/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDialogInterface.h"

#include "OSGDialog.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DialogInterface
A Dialog. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogInterface::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void DialogInterface::DialogInterfaceListener::newDialogStarted(const DialogHierarchyEvent& e)
{
    if(DialogHierarchyPtr::dcast(e.getSource())->getDualNodeStyle())
    {
        if(DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialog()->getInteractive())
        {
            LabelPtr Response = LabelPtr::dcast(_DialogInterface->getComponentGenerator()->getQuestionComponent(_DialogInterface, DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialog()->getResponse()));

            beginEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);
                _DialogInterface->getParentContainer()->getChildren().push_back(Response);
            endEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);
        }
    }
}
void DialogInterface::DialogInterfaceListener::dialogEnded(const DialogHierarchyEvent& e)
{
}
void DialogInterface::DialogInterfaceListener::dialogResponseSelected(const DialogHierarchyEvent& e)
{
        beginEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);
            _DialogInterface->getParentContainer()->getChildren().clear();
        endEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);
}
void DialogInterface::DialogInterfaceListener::dialogResponsesReady(const DialogHierarchyEvent& e)
{
    if(DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialog()->getInteractive())
    {
        for(UInt32 c = 0; DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialogResponses().getSize() > c; c++)
        {
            ButtonPtr Response = ButtonPtr::dcast(_DialogInterface->getComponentGenerator()->getResponseComponent(_DialogInterface,DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialogResponses(c)->getResponse()));

            beginEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);
                _DialogInterface->getParentContainer()->getChildren().push_back(Response);
            endEditCP(_DialogInterface->getParentContainer(), InternalWindow::ChildrenFieldMask);

            Response->addActionListener(&_DialogInterface->_DialogInterfaceListener);
            _DialogInterface->_ButtonToResponseMap[Response] = DialogHierarchyPtr::dcast(e.getSource())->getCurrentDialogResponses(c);
        }
    }
}
void DialogInterface::DialogInterfaceListener::terminated(const DialogHierarchyEvent& e)
{
}
void DialogInterface::DialogInterfaceListener::actionPerformed(const ActionEvent& e)
{
    _DialogInterface->_ButtonToResponseMap[ButtonPtr::dcast(e.getSource())]->selectResponse();
}
void DialogInterface::setHierarchy()
{
    getSourceDialogHierarchy()->addDialogHierarchyListener(&_DialogInterfaceListener);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogInterface::DialogInterface(void) :
    Inherited(),
    _DialogInterfaceListener(DialogInterfacePtr(this))
{
}

DialogInterface::DialogInterface(const DialogInterface &source) :
    Inherited(source),
    _DialogInterfaceListener(DialogInterfacePtr(this))
{
}

DialogInterface::~DialogInterface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogInterface::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & SourceDialogHierarchyFieldMask && getSourceDialogHierarchy() != NullFC)
    {
        setHierarchy();
    }
}

void DialogInterface::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DialogInterface NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDIALOGINTERFACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIALOGINTERFACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIALOGINTERFACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

