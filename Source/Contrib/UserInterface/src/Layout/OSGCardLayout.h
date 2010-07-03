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

#ifndef _OSGCARDLAYOUT_H_
#define _OSGCARDLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCardLayoutBase.h"
#include "OSGCardLayoutConstraints.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

/*! \brief CardLayout class. See \ref
           PageContribUserInterfaceCardLayout for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CardLayout : public CardLayoutBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CardLayoutBase Inherited;
    typedef CardLayout     Self;

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

    virtual void updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
    
	void first(ComponentContainer* const TheContainer);
	void last(ComponentContainer* const TheContainer);
	void next(ComponentContainer* const TheContainer);
	void previous(ComponentContainer* const TheContainer);
    virtual Vec2f minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CardLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CardLayout(void);
    CardLayout(const CardLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CardLayout(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual Vec2f layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CardLayoutBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CardLayout &source);
};

typedef CardLayout *CardLayoutP;

OSG_END_NAMESPACE

#include "OSGCardLayoutBase.inl"
#include "OSGCardLayout.inl"

#endif /* _OSGCARDLAYOUT_H_ */
