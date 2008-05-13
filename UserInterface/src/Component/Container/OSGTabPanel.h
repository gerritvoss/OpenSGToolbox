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

#ifndef _OSGTABPANEL_H_
#define _OSGTABPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGTabPanelBase.h"
#include "Event/OSGFocusListener.h"
#include "Models/SelectionModels/OSGSingleSelectionModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief TabPanel class. See \ref 
           PageUserInterfaceTabPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TabPanel : public TabPanelBase, public FocusListener
{
  private:

    typedef TabPanelBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	enum TabRotation {CLOCKWISE_0=0, CLOCKWISE_90=1, CLOCKWISE_180=2, CLOCKWISE_270=3};
	enum TabPlacement {PLACEMENT_NORTH=0, PLACEMENT_EAST, PLACEMENT_SOUTH, PLACEMENT_WEST};

	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);
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
	virtual void drawInternal(const GraphicsPtr Graphics) const;

	virtual void addTab(const ComponentPtr Tab, const ComponentPtr TabContent);
	virtual void removeTab(const ComponentPtr Tab);
	virtual void removeTab(const UInt32 TabIndex);
	virtual void removeAllTabs(void);
	virtual void insertTab(const ComponentPtr TabInsert, const ComponentPtr Tab, const ComponentPtr TabContent);
	virtual void insertTab(const UInt32 TabIndex, const ComponentPtr Tab, const ComponentPtr TabContent);
    
    //Returns the currently selected component for this tabpanel.
    ComponentPtr getSelectedComponent(void) const;

    //Returns the currently selected index for this tabpanel.
    Int32 getSelectedIndex(void) const;
    //Returns the currently selected index for this tabpanel.
    void setSelectedIndex(const Int32& Index);

    //Adds listener as a listener to changes in the model.
    void addSelectionListener(SelectionListenerPtr listener);
    //Removes listener as a listener to changes in the model.
    void removeSelectionListener(SelectionListenerPtr listener);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TabPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TabPanel(void);
    TabPanel(const TabPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TabPanel(void); 

    /*! \}                                                                 */
    virtual void updateLayout(void);

	//Mouse Events
    virtual void mouseClicked(const MouseEvent& e);
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEvent& e);

	void calculateTabBorderLengths(BorderPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;
	void calculateMaxTabBorderLengths(Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;

	void calculateContentBorderLengths(BorderPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;

    virtual BorderPtr getDrawnTabBorder(const UInt32& Index) const;
    virtual UIBackgroundPtr getDrawnTabBackground(const UInt32& Index) const;
    virtual BorderPtr getDrawnContentBorder(void) const;
    virtual UIBackgroundPtr getDrawnContentBackground(void) const;

	Int32 _MouseInTabLastMouse;
    
	class TabSelectionListener : public SelectionListener
	{
	public:
		TabSelectionListener(TabPanelPtr TheTabPanel);
        virtual void selectionChanged(const SelectionEvent& e);
	private:
		TabPanelPtr _TabPanel;
	};

	friend class TabSelectionListener;

	TabSelectionListener _TabSelectionListener;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TabPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TabPanel &source);
};

typedef TabPanel *TabPanelP;

OSG_END_NAMESPACE

#include "OSGTabPanelBase.inl"
#include "OSGTabPanel.inl"

#define OSGTABPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTABPANEL_H_ */
