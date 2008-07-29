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
#include "OSGCheckboxButton.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CheckboxButton
A UI Checkbox Button. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CheckboxButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CheckboxButton::drawInternal(const GraphicsPtr TheGraphics) const
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
    InnerComponentsPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, InnerComponentsSize,getAlignment().y(), getAlignment().x());
    
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

UIDrawObjectCanvasPtr CheckboxButton::getDrawnDrawObject(void) const
{
    if(getEnabled())
    {
        if(getActive())
        {
            if(getSelected())
            {
                return getActiveCheckboxDrawObject();
            }
            else
            {
                return getActiveSelectedCheckboxDrawObject();
            }
        }
        else if(_MouseInComponentLastMouse)
        {
            if(getSelected())
            {
                return getRolloverSelectedCheckboxDrawObject();
            }
            else
            {
                return getRolloverCheckboxDrawObject();
            }
        }
        else
        {
            if(getSelected())
            {
                return getSelectedCheckboxDrawObject();
            }
            else
            {
                return getCheckboxDrawObject();
            }
        }
    }
    else
    {
        if(getSelected())
        {
            return getDisabledSelectedCheckboxDrawObject();
        }
        else
        {
            return getDisabledCheckboxDrawObject();
        }
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CheckboxButton::CheckboxButton(void) :
    Inherited()
{
}

CheckboxButton::CheckboxButton(const CheckboxButton &source) :
    Inherited(source)
{
}

CheckboxButton::~CheckboxButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CheckboxButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
}

void CheckboxButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CheckboxButton NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCHECKBOXBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCHECKBOXBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCHECKBOXBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

