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

#ifndef _OSGDEFAULTLOOKANDFEEL_H_
#define _OSGDEFAULTLOOKANDFEEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDefaultLookAndFeelBase.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING DefaultLookAndFeel : public DefaultLookAndFeelBase
{
  private:

    typedef DefaultLookAndFeelBase Inherited;

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
	
	virtual void init(void);
	virtual Time getTextCaretRate(void) const;
	virtual Time getToolTipPopupTime(void) const;
	virtual Time getSubMenuPopupTime(void) const;
    virtual Time getKeyAcceleratorMenuFlashTime(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultLookAndFeelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultLookAndFeel(void);
    DefaultLookAndFeel(const DefaultLookAndFeel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultLookAndFeel(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultLookAndFeelBase;

    static void initMethod(void);

	Real32 _TextCaretRate;
	Real32 _ToolTipPopupTime;
	Real32 _SubMenuPopupTime;
	Real32 _KeyAcceleratorMenuFlashTime;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultLookAndFeel &source);
};

typedef DefaultLookAndFeel *DefaultLookAndFeelP;

OSG_END_NAMESPACE

#include "OSGDefaultLookAndFeelBase.inl"
#include "OSGDefaultLookAndFeel.inl"

#define OSGDEFAULTLOOKANDFEEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTLOOKANDFEEL_H_ */
