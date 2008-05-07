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

#ifndef _OSGTOOLBAR_H_
#define _OSGTOOLBAR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGToolbarBase.h"
#include "Layout/OSGBoxLayout.h"
#include "Component/Misc/OSGSeparatorFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Toolbar class. See \ref 
           PageUserInterfaceToolbar for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING Toolbar : public ToolbarBase
{
  private:

    typedef ToolbarBase Inherited;

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

	void setOrientation(BoxLayout::Orientation TheOrientation);
	BoxLayout::Orientation getOrientation(void) const;

    void addTool(ComponentPtr TheTool);
    void removeTool(ComponentPtr TheTool);
    void removeTool(const UInt32&  Index);
    void removeAllTools(void);
    UInt32 getNumTools(void) const;

    void addSeparator(void);
    void addSeparator(SeparatorPtr TheSeparator);
    void removeSeparator(const UInt32&  Index);
    void removeSeparator(SeparatorPtr TheSeparator);
    void removeAllSeparators(void);
    UInt32 getNumSeparators(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ToolbarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Toolbar(void);
    Toolbar(const Toolbar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Toolbar(void); 

    /*! \}                                                                 */
	BoxLayoutPtr createDefaultLayout(void) const;

    void updateSeparatorSizes(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ToolbarBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Toolbar &source);
};

typedef Toolbar *ToolbarP;

OSG_END_NAMESPACE

#include "OSGToolbarBase.inl"
#include "OSGToolbar.inl"

#define OSGTOOLBAR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTOOLBAR_H_ */
