/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGKEYACCELERATOREVENT_H_
#define _OSGKEYACCELERATOREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGKeyAcceleratorEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyAcceleratorEvent class. See \ref 
           PageUserInterfaceKeyAcceleratorEvent for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING KeyAcceleratorEvent : public KeyAcceleratorEventBase
{
  private:

    typedef KeyAcceleratorEventBase Inherited;

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

    static  KeyAcceleratorEventPtr      create( FieldContainerPtr Source,
                                                Time TimeStamp,
                                                UInt32 TheKey,
                                                UInt32 Modifiers); 

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in KeyAcceleratorEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyAcceleratorEvent(void);
    KeyAcceleratorEvent(const KeyAcceleratorEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyAcceleratorEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class KeyAcceleratorEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyAcceleratorEvent &source);
};

typedef KeyAcceleratorEvent *KeyAcceleratorEventP;

OSG_END_NAMESPACE

#include "OSGKeyAcceleratorEventBase.inl"
#include "OSGKeyAcceleratorEvent.inl"

#endif /* _OSGKEYACCELERATOREVENT_H_ */
