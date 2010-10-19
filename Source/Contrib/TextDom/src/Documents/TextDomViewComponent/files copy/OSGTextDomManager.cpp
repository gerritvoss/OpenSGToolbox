/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala*
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

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGTextDomManager.h"

OSG_BEGIN_NAMESPACE

#define LINEHEIGHT 20

// Documentation for this class is emitted in the
// OSGTextDomManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGTextDomManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextDomManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextDomManager::initialVisibleViews(void)
{
	std::cout<<"calculating the initial visible views";

	_theViews.clear();

	if(getTextDomArea()->getDocumentModel())
	{
		if(getTextDomArea()->getDocumentModel()->isA("PlainDocument"))
		{
			ElementRefPtr defaultRoot=getTextDomArea()->getDocumentModel()->getDefaultRootElement();
			PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);

			Pnt2f init = getTextDomArea()->getPosition();
			Pnt2f topLeft,bottomRight;

			getTextDomArea()->getBounds(topLeft,bottomRight);

			for(UInt32 i=0;i<rootElement->getElementCount();i++)
			{

				//if(init.y() + i*LINEHEIGHT <= bottomRight.y())
				//{
					GlyphViewRefPtr view = GlyphView::create();
					PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
					view->setElement(ElementRefPtr(temp));
					
					init.setValues(init.x(),init.y() + LINEHEIGHT);
					view->setInitialPosition(init); // + i*_textDomArea->getLineSpacing()
					_theViews.push_back(view);
				//}
				//else 
				//{
					//if(init.y() < 0)	// for elements above the visible area
					//{
					//	continue;	
					//}
					//else return;		// for elements that are below the visible area
				//	return;
				//}
				
			}
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextDomManager::TextDomManager(void) :
	_theViews(NULL),
    Inherited()
{
}

TextDomManager::TextDomManager(const TextDomManager &source) :
    Inherited(source)
{
	_theViews = source._theViews;
}

TextDomManager::~TextDomManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextDomManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextDomManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextDomManager NI" << std::endl;
}

OSG_END_NAMESPACE
