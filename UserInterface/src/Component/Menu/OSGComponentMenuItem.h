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

#ifndef _OSGCOMPONENTMENUITEM_H_
#define _OSGCOMPONENTMENUITEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComponentMenuItemBase.h"
#include "Event/OSGKeyAcceleratorListener.h"
#include "Component/Menu/OSGMenuFields.h"


OSG_BEGIN_NAMESPACE

/*! \brief ComponentMenuItem class. See \ref 
           PageUserInterfaceComponentMenuItem for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComponentMenuItem : public ComponentMenuItemBase
{
  private:

    typedef ComponentMenuItemBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

	Vec2f getContentRequestedSize(void) const;

    virtual void mouseReleased(const MouseEvent& e);
    
    void setDrawAsThoughSelected(bool Selected);
    bool getDrawAsThoughSelected(void) const;
    
    virtual void activate(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComponentMenuItemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentMenuItem(void);
    ComponentMenuItem(const ComponentMenuItem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentMenuItem(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;
    virtual BorderPtr getDrawnBorder(void) const;
    virtual UIBackgroundPtr getDrawnBackground(void) const;
    
    virtual void actionPreformed(const ActionEvent& e);
    
	class ComponentMenuItemKeyAcceleratorListener : public KeyAcceleratorListener
	{
	public:
		ComponentMenuItemKeyAcceleratorListener(ComponentMenuItemPtr TheComponentMenuItem);
        virtual void acceleratorTyped(const KeyAcceleratorEvent& e);
	private:
		ComponentMenuItemPtr _ComponentMenuItem;
	};

	friend class ComponentMenuItemKeyAcceleratorListener;

	ComponentMenuItemKeyAcceleratorListener _ComponentMenuItemKeyAcceleratorListener;
    
	class KeyAcceleratorMenuFlashUpdateListener : public UpdateListener
	{
	public:
		KeyAcceleratorMenuFlashUpdateListener(ComponentMenuItemPtr TheComponentMenuItem);
        virtual void update(const UpdateEvent& e);
        void reset(void);
	private:
		ComponentMenuItemPtr _ComponentMenuItem;
	    Time _FlashElps;
	};

	friend class KeyAcceleratorMenuFlashUpdateListener;

	KeyAcceleratorMenuFlashUpdateListener _KeyAcceleratorMenuFlashUpdateListener;

    MenuPtr getTopLevelMenu(void) const;
    bool _DrawAsThoughSelected;

	void updateComponentBounds(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComponentMenuItemBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComponentMenuItem &source);
};

typedef ComponentMenuItem *ComponentMenuItemP;

OSG_END_NAMESPACE

#include "OSGComponentMenuItemBase.inl"
#include "OSGComponentMenuItem.inl"

#define OSGCOMPONENTMENUITEM_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMPONENTMENUITEM_H_ */
