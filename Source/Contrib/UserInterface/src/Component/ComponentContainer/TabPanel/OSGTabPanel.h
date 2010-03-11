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

#ifndef _OSGTABPANEL_H_
#define _OSGTABPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTabPanelBase.h"
#include "OSGFocusListener.h"
#include "OSGSingleSelectionModel.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief TabPanel class. See \ref
           PageContribUserInterfaceTabPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TabPanel : public TabPanelBase, public FocusListener
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum TabRotation
    {
        CLOCKWISE_0   = 0,
        CLOCKWISE_90  = 1,
        CLOCKWISE_180 = 2,
        CLOCKWISE_270 = 3
    };

	enum TabPlacement
    {
        PLACEMENT_NORTH = 0,
        PLACEMENT_EAST  = 1,
        PLACEMENT_SOUTH = 2,
        PLACEMENT_WEST  = 3
    };

    typedef TabPanelBase Inherited;
    typedef TabPanel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual void focusGained(const FocusEventUnrecPtr e);
	virtual void focusLost(const FocusEventUnrecPtr e);
	virtual void drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity = 1.0f) const;

	virtual void addTab(const ComponentRefPtr Tab, const ComponentRefPtr TabContent);
	virtual void removeTab(const ComponentRefPtr Tab);
	virtual void removeTab(const UInt32 TabIndex);
	virtual void removeAllTabs(void);
	virtual void insertTab(const ComponentRefPtr TabInsert, const ComponentRefPtr Tab, const ComponentRefPtr TabContent);
	virtual void insertTab(const UInt32 TabIndex, const ComponentRefPtr Tab, const ComponentRefPtr TabContent);
    
    //Returns the currently selected component for this tabpanel.
    ComponentRefPtr getSelectedComponent(void) const;

    //Returns the currently selected index for this tabpanel.
    Int32 getSelectedIndex(void) const;
    //Returns the currently selected index for this tabpanel.
    void setSelectedIndex(const Int32& Index);

    //Adds listener as a listener to changes in the model.
    EventConnection addSelectionListener(SelectionListenerPtr listener);
	bool isSelectionListenerAttached(SelectionListenerPtr listener) const;
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const TabPanel *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    virtual void updateLayout(void);

	//Mouse Events
    virtual void mouseClicked(const MouseEventUnrecPtr e);
    virtual void mouseEntered(const MouseEventUnrecPtr e);
    virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mousePressed(const MouseEventUnrecPtr e);
    virtual void mouseReleased(const MouseEventUnrecPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventUnrecPtr e);
    virtual void mouseDragged(const MouseEventUnrecPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

	void calculateTabBorderLengths(BorderRefPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;
	void calculateMaxTabBorderLengths(Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;

	void calculateContentBorderLengths(BorderRefPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const;

    virtual BorderRefPtr getDrawnTabBorder(const UInt32& Index) const;
    virtual LayerRefPtr getDrawnTabBackground(const UInt32& Index) const;
    virtual BorderRefPtr getDrawnContentBorder(void) const;
    virtual LayerRefPtr getDrawnContentBackground(void) const;

	Int32 _MouseInTabLastMouse;
    
	class TabSelectionListener : public SelectionListener
	{
	public:
		TabSelectionListener(TabPanelRefPtr TheTabPanel);
        virtual void selectionChanged(const SelectionEventUnrecPtr e);
	private:
		TabPanelRefPtr _TabPanel;
	};

	friend class TabSelectionListener;

	TabSelectionListener _TabSelectionListener;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TabPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TabPanel &source);
};

typedef TabPanel *TabPanelP;

OSG_END_NAMESPACE

#include "OSGTabPanelBase.inl"
#include "OSGTabPanel.inl"

#endif /* _OSGTABPANEL_H_ */
