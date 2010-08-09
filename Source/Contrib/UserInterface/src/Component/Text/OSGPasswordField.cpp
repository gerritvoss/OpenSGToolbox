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

#include "OSGPasswordField.h"
#include "OSGUIDrawUtils.h"

#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGStringUtils.h"

#include "OSGLookAndFeelManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPasswordFieldBase.cpp file.
// To modify it, please change the .fcd file (OSGPasswordField.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PasswordField::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string PasswordField::getDrawnText(void) const
{
	return getEcho();
}

void PasswordField::mouseClicked(MouseEventDetails* const e)
{	
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{

		if(e->getClickCount() == 2)
		{
			selectAll();
			setCaretPosition(getText().size());
		}
	}
	TextComponent::mouseClicked(e);

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PasswordField::PasswordField(void) :
    Inherited()
{
}

PasswordField::PasswordField(const PasswordField &source) :
    Inherited(source)
{
}

PasswordField::~PasswordField(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PasswordField::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(whichField & TextFieldMask)
    {
        std::string EchoString("");
        for(UInt32 i(0) ; i<getText().size(); ++i)
        {
            EchoString = EchoString + getEchoChar();
        }
        setEcho(EchoString);
    }
}

void PasswordField::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PasswordField NI" << std::endl;
}

OSG_END_NAMESPACE
