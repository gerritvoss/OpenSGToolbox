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

#ifndef _OSGTREEMODELEVENT_H_
#define _OSGTREEMODELEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeModelEventBase.h"
#include "OSGTreePath.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelEvent class. See \ref
           PageContribUserInterfaceTreeModelEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeModelEvent : public TreeModelEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeModelEventBase Inherited;
    typedef TreeModelEvent     Self;

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

    static  TreeModelEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                   Time TimeStamp,
                                                   const TreePath&,
                                                   const std::vector<UInt32>& childIndices,
                                                   const std::vector<boost::any>& children); 

    static  TreeModelEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                   Time TimeStamp,
                                                   const TreePath&); 

    const std::vector<boost::any>& getChildren(void) const;
    
	const TreePath& getPath(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeModelEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModelEvent(void);
    TreeModelEvent(const TreeModelEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModelEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    TreePath _Path;
    std::vector<boost::any> _Children;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeModelEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeModelEvent &source);
};

typedef TreeModelEvent *TreeModelEventP;

OSG_END_NAMESPACE

#include "OSGTreeModelEventBase.inl"
#include "OSGTreeModelEvent.inl"

#endif /* _OSGTREEMODELEVENT_H_ */
