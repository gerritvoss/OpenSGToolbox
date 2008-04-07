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

#ifndef _OSGLABELMENUITEM_H_
#define _OSGLABELMENUITEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGLabelMenuItemBase.h"
#include "Event/OSGKeyAcceleratorListener.h"
#include "Component/Menu/OSGMenuFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief LabelMenuItem class. See \ref 
           PageUserInterfaceLabelMenuItem for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING LabelMenuItem : public LabelMenuItemBase
{
  private:

    typedef LabelMenuItemBase Inherited;

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

	Vec2f getContentRequestedSize(void) const;

    virtual void mouseReleased(const MouseEvent& e);
    
    void setDrawAsThoughSelected(bool Selected);
    bool getDrawAsThoughSelected(void) const;
    
    virtual void activate(void);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in LabelMenuItemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LabelMenuItem(void);
    LabelMenuItem(const LabelMenuItem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LabelMenuItem(void); 

	virtual void drawInternal(const GraphicsPtr Graphics) const;
	virtual Color4f getDrawnTextColor(void) const;
    virtual BorderPtr getDrawnBorder(void) const;
    virtual UIBackgroundPtr getDrawnBackground(void) const;
    
	class LabelMenuItemKeyAcceleratorListener : public KeyAcceleratorListener
	{
	public:
		LabelMenuItemKeyAcceleratorListener(LabelMenuItemPtr TheLabelMenuItem);
        virtual void acceleratorTyped(const KeyAcceleratorEvent& e);
	private:
		LabelMenuItemPtr _LabelMenuItem;
	};

	friend class LabelMenuItemKeyAcceleratorListener;

	LabelMenuItemKeyAcceleratorListener _LabelMenuItemKeyAcceleratorListener;
    
	class KeyAcceleratorMenuFlashUpdateListener : public UpdateListener
	{
	public:
		KeyAcceleratorMenuFlashUpdateListener(LabelMenuItemPtr TheLabelMenuItem);
        virtual void update(const UpdateEvent& e);
        void reset(void);
	private:
		LabelMenuItemPtr _LabelMenuItem;
	    Time _FlashElps;
	};

	friend class KeyAcceleratorMenuFlashUpdateListener;

	KeyAcceleratorMenuFlashUpdateListener _KeyAcceleratorMenuFlashUpdateListener;

    MenuPtr getTopLevelMenu(void) const;
    bool _DrawAsThoughSelected;
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LabelMenuItemBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LabelMenuItem &source);
    
    
};

typedef LabelMenuItem *LabelMenuItemP;

OSG_END_NAMESPACE

#include "OSGLabelMenuItemBase.inl"
#include "OSGLabelMenuItem.inl"

#define OSGLABELMENUITEM_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLABELMENUITEM_H_ */
