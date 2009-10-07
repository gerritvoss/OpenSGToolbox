/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGSpinnerNumberEditor.h"
#include <boost/lexical_cast.hpp>
#include "Component/Spinner/OSGSpinner.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SpinnerNumberEditor
A UI SpinnerNumberEditor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpinnerNumberEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpinnerNumberEditor::commitEdit(void)
{
	try
	{
        Real64 result = boost::lexical_cast<Real64>(getTextField()->getText());

		getSpinner()->getModel()->setValue(getTextField()->getText());
	}
    catch(std::exception &)
	{
		//Reset to the old value
		beginEditCP(getTextField(), TextField::TextFieldMask);
			std::string NewValue;
            try
            {
                getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
            }
            catch(boost::bad_any_cast &)
            {
				getTextField()->setText("0.0");
            }
		endEditCP(getTextField(), TextField::TextFieldMask);
	}
}

void SpinnerNumberEditor::stateChanged(const ChangeEventPtr e)
{
	if(getSpinner()->getModel()->getValue().type() == typeid(Real32))
	{
		//Update the Value of the TextField
		beginEditCP(getTextField(), TextField::TextFieldMask);
            try
            {
                getTextField()->setText(boost::lexical_cast<std::string>(boost::any_cast<Real32>(getSpinner()->getModel()->getValue())));
            }
            catch(std::exception &)
            {
				getTextField()->setText("0.0");
            }
		endEditCP(getTextField(), TextField::TextFieldMask);
	}
	else
	{
		Inherited::stateChanged(e);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SpinnerNumberEditor::SpinnerNumberEditor(void) :
    Inherited()
{
}

SpinnerNumberEditor::SpinnerNumberEditor(const SpinnerNumberEditor &source) :
    Inherited(source)
{
}

SpinnerNumberEditor::~SpinnerNumberEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpinnerNumberEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SpinnerNumberEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SpinnerNumberEditor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSPINNERNUMBEREDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPINNERNUMBEREDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPINNERNUMBEREDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

