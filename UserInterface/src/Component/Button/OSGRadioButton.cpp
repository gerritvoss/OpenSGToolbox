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

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGRadioButton.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RadioButton
A UI Radio Button. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RadioButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RadioButton::drawInternal(const GraphicsPtr TheGraphics) const
{
	Pnt2f TopLeft, BottomRight;
	Vec2f drawObjectSize;
	Pnt2f TempPos;

    Pnt2f InnerComponentsPosition(0,0);
    Vec2f InnerComponentsSize(0,0);

    UInt32 DrawnComponentToTextGap(2);

	getInsideBorderBounds(TopLeft, BottomRight);

    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    Vec2f TextBounds( TextBottomRight - TextTopLeft);
	if(TextBounds.x()>0)
    {
	    InnerComponentsSize[0] += TextBounds.x();
	}
   
    UIDrawObjectCanvasPtr DrawnDrawObject = getDrawnDrawObject();
    if(DrawnDrawObject != NullFC)
    {
	    Pnt2f drawObjectTopLeft;
	    Pnt2f drawObjectBottomRight;
        DrawnDrawObject->getDrawObjectBounds(drawObjectTopLeft, drawObjectBottomRight);
        drawObjectSize = drawObjectBottomRight-drawObjectTopLeft;
		
        InnerComponentsSize[0] += drawObjectSize.x() + DrawnComponentToTextGap;
	    
	}
    else
    {
        drawObjectSize.setValues(0,0);
    }
    InnerComponentsSize[1] = osgMax(drawObjectSize.y(), TextBounds.y());
    InnerComponentsPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, InnerComponentsSize, getVerticalAlignment(), getHorizontalAlignment());
    
    if(DrawnDrawObject != NullFC)
    {
        beginEditCP(DrawnDrawObject, PositionFieldMask);
            DrawnDrawObject->setPosition( calculateAlignment(InnerComponentsPosition, InnerComponentsSize,drawObjectSize,0.5,0.0 ) );
	    endEditCP(DrawnDrawObject, PositionFieldMask);
        DrawnDrawObject->draw(TheGraphics);
    }

    TheGraphics->drawText(calculateAlignment(InnerComponentsPosition + Vec2f(drawObjectSize.x()+ DrawnComponentToTextGap,0), InnerComponentsSize-Vec2f(drawObjectSize.x()+ DrawnComponentToTextGap,0),TextBounds,0.5,0.0 )
        ,   getText(), getFont(), getDrawnTextColor(), getOpacity());

}

UIDrawObjectCanvasPtr RadioButton::getDrawnDrawObject(void) const
{
    if(getEnabled())
    {
        if(getActive())
        {
            if(getSelected())
            {
                return getActiveRadioDrawObject();
            }
            else
            {
                return getActiveSelectedRadioDrawObject();
            }
        }
        else if(_MouseInComponentLastMouse)
        {
            if(getSelected())
            {
                return getRolloverSelectedRadioDrawObject();
            }
            else
            {
                return getRolloverRadioDrawObject();
            }
        }
        else
        {
            if(getSelected())
            {
                return getSelectedRadioDrawObject();
            }
            else
            {
                return getRadioDrawObject();
            }
        }
    }
    else
    {
        if(getSelected())
        {
            return getDisabledSelectedRadioDrawObject();
        }
        else
        {
            return getDisabledRadioDrawObject();
        }
    }
}

void RadioButton::actionPreformed(const ActionEvent& e)
{
    beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
	    setSelected(true);
    endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RadioButton::RadioButton(void) :
    Inherited()
{
}

RadioButton::RadioButton(const RadioButton &source) :
    Inherited(source)
{
}

RadioButton::~RadioButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RadioButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
}

void RadioButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RadioButton NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGRADIOBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRADIOBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRADIOBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

