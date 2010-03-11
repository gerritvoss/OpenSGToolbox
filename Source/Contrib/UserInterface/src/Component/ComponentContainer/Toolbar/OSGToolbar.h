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

#ifndef _OSGTOOLBAR_H_
#define _OSGTOOLBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGToolbarBase.h"
#include "OSGBoxLayout.h"
#include "OSGSeparatorFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Toolbar class. See \ref
           PageContribUserInterfaceToolbar for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Toolbar : public ToolbarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ToolbarBase Inherited;
    typedef Toolbar     Self;

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

	void setOrientation(BoxLayout::Orientation TheOrientation);
	BoxLayout::Orientation getOrientation(void) const;

    void addTool(ComponentRefPtr TheTool);
    void removeTool(ComponentRefPtr TheTool);
    void removeTool(const UInt32&  Index);
    void removeAllTools(void);
    UInt32 getNumTools(void) const;

    void addSeparator(void);
    void addSeparator(SeparatorRefPtr TheSeparator);
    void removeSeparator(const UInt32&  Index);
    void removeSeparator(SeparatorRefPtr TheSeparator);
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Toolbar *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
	BoxLayoutRefPtr createDefaultLayout(void) const;

    void updateSeparatorSizes(void);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ToolbarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Toolbar &source);
};

typedef Toolbar *ToolbarP;

OSG_END_NAMESPACE

#include "OSGToolbarBase.inl"
#include "OSGToolbar.inl"

#endif /* _OSGTOOLBAR_H_ */
