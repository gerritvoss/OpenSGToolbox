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

#ifndef _OSGScrollBar_H_
#define _OSGScrollBar_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGScrollBarBase.h"
#include "OSGBoundedRangeModel.h"
#include "Event/OSGAdjustmentListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScrollBar class. See \ref 
           PageUserInterfaceScrollBar for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ScrollBar : public ScrollBarBase
{
  private:

    typedef ScrollBarBase Inherited;

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

    void setModel(BoundedRangeModel* Model);
    BoundedRangeModel* getModel(void) const;
    
    void addAdjustmentListener(AdjustmentListenerPtr Listener);
    void removeAdjustmentListener(AdjustmentListenerPtr Listener);

    UInt32 getExtent(void) const;
    
    UInt32 getMaximum(void) const;
    
    UInt32 getMinimum(void) const;
    
    UInt32 getValue(void) const;
    
    bool getValueIsAdjusting(void) const;
    
    void setExtent(UInt32 newExtent);
    
    void setMaximum(UInt32 newMaximum);
    
    void setMinimum(UInt32 newMinimum);
    
    void setRangeProperties(UInt32 value, UInt32 extent, UInt32 min, UInt32 max, bool adjusting);
    
    void setValue(UInt32 newValue);
    
    void setValueIsAdjusting(bool Value);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ScrollBarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScrollBar(void);
    ScrollBar(const ScrollBar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScrollBar(void); 

    /*! \}                                                                 */
    
	virtual void drawInternal(const GraphicsPtr Graphics) const;

	typedef std::set<AdjustmentListenerPtr> AdjustmentListenerSet;
    typedef AdjustmentListenerSet::iterator AdjustmentListenerSetItor;
    typedef AdjustmentListenerSet::const_iterator AdjustmentListenerSetConstItor;
	
    AdjustmentListenerSet       _AdjustmentListeners;
    void produceAdjustmentValueChanged(const AdjustmentEvent& e);

    BoundedRangeModel* _Model;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ScrollBarBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ScrollBar &source);
};

typedef ScrollBar *ScrollBarP;

OSG_END_NAMESPACE

#include "OSGScrollBarBase.inl"
#include "OSGScrollBar.inl"

#define OSGScrollBar_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGScrollBar_H_ */
