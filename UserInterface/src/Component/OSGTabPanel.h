/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

OSG_BEGIN_NAMESPACE

/*! \brief TabPanel class. See \ref 
           PageUserInterfaceTabPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TabPanel : public TabPanelBase
{
  private:

    typedef TabPanelBase Inherited;

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
	virtual void drawInternal(const GraphicsPtr Graphics) const;

	virtual void addTab(const ComponentPtr Tab, const ComponentPtr TabContent);
	virtual void removeTab(const ComponentPtr Tab);
	virtual void removeTab(const UInt32 TabIndex);
	virtual void insertTab(const ComponentPtr TabInsert, const ComponentPtr Tab, const ComponentPtr TabContent);
	virtual void insertTab(const UInt32 TabIndex, const ComponentPtr Tab, const ComponentPtr TabContent);
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
    void updateTabLayout(void);
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
