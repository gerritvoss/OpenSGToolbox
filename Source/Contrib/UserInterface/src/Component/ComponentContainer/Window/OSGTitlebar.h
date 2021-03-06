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

#ifndef _OSGTITLEBAR_H_
#define _OSGTITLEBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTitlebarBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Titlebar class. See \ref
           PageContribUserInterfaceTitlebar for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Titlebar : public TitlebarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TitlebarBase Inherited;
    typedef Titlebar     Self;

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
    virtual void updateLayout(void);
	virtual void updateClipBounds(void);

	void setTitle(const std::string& Title);
	std::string getTitle(void) const;

    void setParentWindow(InternalWindow* const parent);

    virtual ComponentContainer* getParentContainer(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TitlebarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Titlebar(void);
    Titlebar(const Titlebar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Titlebar(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Titlebar *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TitlebarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Titlebar &source);
};

typedef Titlebar *TitlebarP;

OSG_END_NAMESPACE

#include "OSGButton.h"
#include "OSGLabel.h"

#include "OSGTitlebarBase.inl"
#include "OSGTitlebar.inl"

#endif /* _OSGTITLEBAR_H_ */
