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

#ifndef _OSGSPRINGLAYOUT_H_
#define _OSGSPRINGLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSpringLayoutBase.h"
#include "Layout/Spring/OSGLayoutSpringFields.h"
#include "Component/OSGComponentFields.h"
#include "Component/Container/OSGContainerFields.h"
#include "Layout/Spring/OSGLayoutSpringFields.h"
#include "Layout/OSGSpringLayoutConstraintsFields.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief SpringLayout class. See \ref 
           PageUserInterfaceSpringLayout for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SpringLayout : public SpringLayoutBase
{
  private:

    typedef SpringLayoutBase Inherited;

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
    virtual void updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const;

    bool isCyclic(LayoutSpringPtr TheSpring) const;

    //Returns the constraints for the specified component.
    SpringLayoutConstraintsPtr getConstraints(ComponentPtr TheComponent);

    //Returns the spring controlling the distance between the specified edge of the component and the top or left edge of its parent.
    LayoutSpringPtr getConstraint(const UInt32 Edge, ComponentPtr TheComponent) const;

    //Links edge e1 of component c1 to edge e2 of component c2, with a fixed distance between the edges.
    void putConstraint(const UInt32 e1, ComponentPtr c1, const UInt32& pad, const UInt32 e2, ComponentPtr c2);

    //Links edge e1 of component c1 to edge e2 of component c2.
    void putConstraint(const UInt32 e1, ComponentPtr c1, LayoutSpringPtr s, const UInt32 e2, ComponentPtr c2);

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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SpringLayoutBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpringLayout &source);

    LayoutSpringPtr getDecycledSpring(LayoutSpringPtr s);

    void resetCyclicStatuses(void);

    void setParent(ContainerPtr p);

    SpringLayoutConstraintsPtr applyDefaults(ComponentPtr c, SpringLayoutConstraintsPtr& constraints);

    //void applyDefaults(SpringLayoutConstraintsPtr constraints, const UInt32 name1,
    //                       LayoutSpringPtr spring1, const UInt32 name2, LayoutSpringPtr spring2,
    //                       List<String> history);
    void putConstraint(const UInt32 e, ComponentPtr c, LayoutSpringPtr s);

    typedef std::set<LayoutSpringPtr> LayoutSpringSet;

    mutable LayoutSpringSet _CyclicSprings;
    mutable LayoutSpringSet _AcyclicSprings;

    LayoutSpringPtr _CyclicDummySpring;
};

typedef SpringLayout *SpringLayoutP;

OSG_END_NAMESPACE

#include "OSGSpringLayoutBase.inl"
#include "OSGSpringLayout.inl"

#define OSGSPRINGLAYOUT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPRINGLAYOUT_H_ */
