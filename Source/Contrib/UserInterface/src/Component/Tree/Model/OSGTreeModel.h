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

#ifndef _OSGTREEMODEL_H_
#define _OSGTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeModelBase.h"
#include <boost/any.hpp>
#include "OSGBaseTypes.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeModel class. See \ref
           PageContribUserInterfaceTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeModel : public TreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeModelBase Inherited;
    typedef TreeModel     Self;

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

	//Returns the child of parent at index index in the parent's child array.
	virtual boost::any getChild(const boost::any& parent, const UInt32& index) const = 0;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(const boost::any& parent) const = 0;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(const boost::any& parent, const boost::any& child) const = 0;

	//Returns the root of the tree.
	virtual boost::any getRoot(void) const = 0;

	//Returns true if node is a leaf.
	virtual bool isLeaf(const boost::any& node) const = 0;

    //Returns the Tree Path to root
    TreePath getRootPath(void) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, const boost::any& newValue) = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModel(void);
    TreeModel(const TreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeModel &source);
};

typedef TreeModel *TreeModelP;

OSG_END_NAMESPACE

#include "OSGTreeModelBase.inl"
#include "OSGTreeModel.inl"

#endif /* _OSGTREEMODEL_H_ */
