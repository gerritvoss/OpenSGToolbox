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

#ifndef _OSGSPRINGLAYOUT_H_
#define _OSGSPRINGLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSpringLayoutBase.h"
#include "OSGLayoutSpringFields.h"
#include "OSGComponentFields.h"
#include "OSGComponentContainerFields.h"
#include "OSGLayoutSpringFields.h"
#include "OSGSpringLayoutConstraintsFields.h"
#include <set>

#include "rapidxml.h"
#include "rapidxml_iterators.h"
#include "OSGXMLFCFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpringLayout class. See \ref
           PageContribUserInterfaceSpringLayout for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SpringLayout : public SpringLayoutBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SpringLayoutBase Inherited;
    typedef SpringLayout     Self;

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

    bool isCyclic(const LayoutSpring* TheSpring) const;

    //Returns the constraints for the specified component.
    SpringLayoutConstraintsRefPtr getConstraint(Component* const TheComponent) const;

    //Returns the spring controlling the distance between the specified edge of the component and the top or left edge of its parent.
    LayoutSpringRefPtr getConstraint(const UInt32 Edge, Component* const TheComponent) const;

    //Links edge e1 of component c1 to edge e2 of component c2, with a fixed distance between the edges.
    void putConstraint(const UInt32 e1, Component* const c1, const Real32& pad, const UInt32 e2, Component* const c2);

    //Links edge e1 of component c1 to edge e2 of component c2.
    void putConstraint(const UInt32 e1, Component* const c1, LayoutSpringRefPtr s, const UInt32 e2, Component* const c2);

    void putConstraint(const UInt32 e, Component* const c, LayoutSpringRefPtr s);

    void clearConstraints(void);

    virtual Vec2f minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;
	virtual Vec2f maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const;

	static bool xmlReadHandler (rapidxml::xml_node<char>&, const XMLFCFileType::IDLookupMap&,const FieldContainerRefPtr&);
	static bool xmlWriteHandler (const FieldContainerRefPtr&);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SpringLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpringLayout(void);
    SpringLayout(const SpringLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpringLayout(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SpringLayoutBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SpringLayout &source);

    LayoutSpringRefPtr getDecycledSpring(LayoutSpringRefPtr s) const;
	
    void resetCyclicStatuses(void);

    void setParent(ComponentContainerRefPtr p);

    static SpringLayoutConstraintsRefPtr applyDefaults(Component* const c, SpringLayoutConstraintsRefPtr constraints);

    //void applyDefaults(SpringLayoutConstraintsRefPtr constraints, const UInt32 name1,
    //                       LayoutSpringRefPtr spring1, const UInt32 name2, LayoutSpringRefPtr spring2,
    //                       List<String> history);

    typedef std::set<const LayoutSpring*> LayoutSpringSet;

    mutable LayoutSpringSet _CyclicSprings;
    mutable LayoutSpringSet _AcyclicSprings;

    LayoutSpringRefPtr _CyclicDummySpring;
};

typedef SpringLayout *SpringLayoutP;

OSG_END_NAMESPACE

#include "OSGSpringLayoutBase.inl"
#include "OSGSpringLayout.inl"

#endif /* _OSGSPRINGLAYOUT_H_ */
