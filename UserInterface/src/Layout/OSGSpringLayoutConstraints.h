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

#ifndef _OSGSPRINGLAYOUTCONSTRAINTS_H_
#define _OSGSPRINGLAYOUTCONSTRAINTS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGSpringLayoutConstraintsBase.h"
#include "Layout/Spring/OSGLayoutSpringFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpringLayoutConstraints class. See \ref 
           PageUserInterfaceSpringLayoutConstraints for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SpringLayoutConstraints : public SpringLayoutConstraintsBase
{
  private:

    typedef SpringLayoutConstraintsBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum Edge {NO_EDGE, NORTH_EDGE, SOUTH_EDGE, EAST_EDGE, WEST_EDGE, HORIZONTAL_CENTER_EDGE, VERTICAL_CENTER_EDGE, BASELINE_EDGE, WIDTH_EDGE, HEIGHT_EDGE};

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
    LayoutSpringPtr getConstraint(const UInt32 TheEdge);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SpringLayoutConstraintsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpringLayoutConstraints(void);
    SpringLayoutConstraints(const SpringLayoutConstraints &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpringLayoutConstraints(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SpringLayoutConstraintsBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpringLayoutConstraints &source);
};

typedef SpringLayoutConstraints *SpringLayoutConstraintsP;

OSG_END_NAMESPACE

#include "OSGSpringLayoutConstraintsBase.inl"
#include "OSGSpringLayoutConstraints.inl"

#define OSGSPRINGLAYOUTCONSTRAINTS_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPRINGLAYOUTCONSTRAINTS_H_ */
