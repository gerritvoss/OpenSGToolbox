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

#ifndef _OSGSCROLLPANEL_H_
#define _OSGSCROLLPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "Event/OSGChangeListener.h"
#include "Event/OSGAdjustmentListener.h"
#include "OSGScrollPanelBase.h"
#include "OSGDefaultBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScrollPanel class. See \ref 
           PageUserInterfaceScrollPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ScrollPanel : public ScrollPanelBase
{
  private:

    typedef ScrollPanelBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum ScrollBarDisplayPolicy{SCROLLBAR_AS_NEEDED=0,SCROLLBAR_AS_ALWAYS,SCROLLBAR_AS_NEVER};
      enum ResizePolicy{NO_RESIZE=0,RESIZE_TO_VIEW};
      enum HorizontalAlign{SCROLLBAR_ALIGN_TOP=0,SCROLLBAR_ALIGN_BOTTOM};
      enum VerticalAlign{SCROLLBAR_ALIGN_LEFT=0,SCROLLBAR_ALIGN_RIGHT};

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    
    virtual void updateLayout(void);

    void setViewComponent(ComponentPtr TheComponent);
    
	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEvent& e);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ScrollPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScrollPanel(void);
    ScrollPanel(const ScrollPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScrollPanel(void); 

    /*! \}                                                                 */
    
    //Range Model for the UIViewport
    DefaultBoundedRangeModel _ViewportVerticalRangeModel;
    DefaultBoundedRangeModel _ViewportHorizontalRangeModel;
    
    //Listener for getting change updates of the UIViewport
	class ViewportChangeListener : public ChangeListener
	{
	public:
		ViewportChangeListener(ScrollPanelPtr TheScrollPanel);
        virtual void stateChanged(const ChangeEvent& e);
	private:
		ScrollPanelPtr _ScrollPanel;
	};

	friend class ViewportChangeListener;

	ViewportChangeListener _ViewportChangeListener;
    
    //Listener for getting change updates of the UIViewport Range Model
	class ViewportRangeModelChangeListener : public ChangeListener
	{
	public:
		ViewportRangeModelChangeListener(ScrollPanelPtr TheScrollPanel);
        virtual void stateChanged(const ChangeEvent& e);
	private:
		ScrollPanelPtr _ScrollPanel;
	};

	friend class ViewportRangeModelChangeListener;

	ViewportRangeModelChangeListener _ViewportRangeModelChangeListener;

    void updateRangeModels(void);

    ScrollBarPtr getVerticalScrollBar(void);

    ScrollBarPtr getHorizontalScrollBar(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ScrollPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ScrollPanel &source);
};

typedef ScrollPanel *ScrollPanelP;

OSG_END_NAMESPACE

#include "OSGScrollPanelBase.inl"
#include "OSGScrollPanel.inl"

#define OSGSCROLLPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSCROLLPANEL_H_ */
