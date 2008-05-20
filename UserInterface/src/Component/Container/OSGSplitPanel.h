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

#ifndef _OSGSPLITPANEL_H_
#define _OSGSPLITPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSplitPanelBase.h"
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief SplitPanel class. See \ref 
           PageUserInterfaceSplitPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SplitPanel : public SplitPanelBase	
{
  private:

    typedef SplitPanelBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum Orientation{VERTICAL_ORIENTATION=0, HORIZONTAL_ORIENTATION};

	virtual void setDividerDrawObject( const UIDrawObjectCanvasPtr &value );
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

	virtual void drawInternal(const GraphicsPtr Graphics) const;

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SplitPanelBase.

    virtual void updateLayout(void);

	class DividerListener : public MouseListener
	{
	public :
		DividerListener(SplitPanelPtr ptr);
		virtual void mouseClicked(const MouseEvent& e);
		virtual void mouseEntered(const MouseEvent& e);
		virtual void mouseExited(const MouseEvent& e);
		virtual void mousePressed(const MouseEvent& e);
		virtual void mouseReleased(const MouseEvent& e);
	protected :
		SplitPanelPtr _SplitPanel;
	};

	friend class DividerListener;

	DividerListener _DividerListener;
	class DividerDraggedListener : public MouseMotionListener, public MouseListener
	{
	public :
		DividerDraggedListener(SplitPanelPtr ptr);
		virtual void mouseMoved(const MouseEvent& e);
		virtual void mouseDragged(const MouseEvent& e);
		
		virtual void mouseClicked(const MouseEvent& e);
		virtual void mouseEntered(const MouseEvent& e);
		virtual void mouseExited(const MouseEvent& e);
		virtual void mousePressed(const MouseEvent& e);
		virtual void mouseReleased(const MouseEvent& e);
	protected :
		SplitPanelPtr _SplitPanel;
	};

	friend class DividerDraggedListener;

	DividerDraggedListener _DividerDraggedListener;

    void updateChildren(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SplitPanel(void);
    SplitPanel(const SplitPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SplitPanel(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SplitPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SplitPanel &source);
};

typedef SplitPanel *SplitPanelP;

OSG_END_NAMESPACE

#include "OSGSplitPanelBase.inl"
#include "OSGSplitPanel.inl"

#define OSGSPLITPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPLITPANEL_H_ */
