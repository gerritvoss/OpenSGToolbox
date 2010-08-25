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

#ifndef _OSGTREEMODELEVENTDETAILS_H_
#define _OSGTREEMODELEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeModelEventDetailsBase.h"
#include "OSGTreePath.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelEventDetails class. See \ref
           PageContribUserInterfaceTreeModelEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeModelEventDetails : public TreeModelEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeModelEventDetailsBase Inherited;
    typedef TreeModelEventDetails     Self;

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

    static  TreeModelEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                   Time TimeStamp,
                                                   const TreePath&,
                                                   const std::vector<UInt32>& childIndices,
                                                   const std::vector<boost::any>& children); 

    static  TreeModelEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                   Time TimeStamp,
                                                   const TreePath&); 

    const std::vector<boost::any>& getChildren(void) const;
    
	const TreePath& getPath(void) const;

	TreePath getChildPath(UInt32 index) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeModelEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModelEventDetails(void);
    TreeModelEventDetails(const TreeModelEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModelEventDetails(void);

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
    friend class TreeModelEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeModelEventDetails &source);
};

typedef TreeModelEventDetails *TreeModelEventDetailsP;

OSG_END_NAMESPACE

#include "OSGTreeModelEventDetailsBase.inl"
#include "OSGTreeModelEventDetails.inl"

#endif /* _OSGTREEMODELEVENTDETAILS_H_ */
