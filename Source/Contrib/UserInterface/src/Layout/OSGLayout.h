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

#ifndef _OSGLAYOUT_H_
#define _OSGLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLayoutBase.h"
#include "OSGGraphics.h"
#include "OSGComponent.h"
#include "OSGComponentContainerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Layout class. See \ref
           PageContribUserInterfaceLayout for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Layout : public LayoutBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LayoutBase Inherited;
    typedef Layout     Self;

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
    virtual void updateLayout(const MFUnrecChildComponentPtr* Components,
                              const Component* ParentComponent) const = 0;

    virtual Vec2f minimumLayoutSize(const MFUnrecChildComponentPtr* Components,
                                    const Component* ParentComponent) const;
    virtual Vec2f requestedLayoutSize(const MFUnrecChildComponentPtr* Components,
                                      const Component* ParentComponent) const;
    virtual Vec2f preferredLayoutSize(const MFUnrecChildComponentPtr* Components,
                                      const Component* ParentComponent) const;
    virtual Vec2f maximumLayoutSize(const MFUnrecChildComponentPtr* Components,
                                    const Component* ParentComponent) const;

    virtual Vec2f minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                            const Component* ParentComponent) const = 0;
    virtual Vec2f requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                              const Component* ParentComponent) const = 0;
    virtual Vec2f preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                              const Component* ParentComponent) const = 0;
    virtual Vec2f maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                            const Component* ParentComponent) const = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum SizeType
    {
        MIN_SIZE       = 0,
        MAX_SIZE       = 1,
        REQUESTED_SIZE = 2,
        PREFERRED_SIZE = 3
    };

    // Variables should all be in LayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Layout(void);
    Layout(const Layout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Layout(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    static Vec2f getComponentSize(const Component* TheComponent, SizeType TheSizeType);

    ComponentContainer* getParentContainer(UInt32 index) const;

    UInt32 getNumParentContainers(void) const;

    void updateParentContainers(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LayoutBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Layout &source);
};

typedef Layout *LayoutP;

OSG_END_NAMESPACE

#include "OSGComponentContainer.h"

#include "OSGLayoutBase.inl"
#include "OSGLayout.inl"

#endif /* _OSGLAYOUT_H_ */
