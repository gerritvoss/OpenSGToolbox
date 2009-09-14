/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>

#include "OSGTreeModelBase.h"
#include <boost/any.hpp>
#include <OpenSG/OSGBaseTypes.h>


#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE
class TreeModelListener;
class TreePath;
typedef TreeModelListener* TreeModelListenerPtr;

/*! \brief TreeModel class. See \ref 
           PageUserInterfaceTreeModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TreeModel : public TreeModelBase
{
  private:

    typedef TreeModelBase Inherited;

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

	//Adds a listener for the TreeModelEvent posted after the tree changes.
	virtual EventConnection addTreeModelListener(TreeModelListenerPtr l) = 0;
	virtual bool isTreeModelListenerAttached(TreeModelListenerPtr l) const = 0;

	//Removes a listener previously added with addTreeModelListener.
	virtual void removeTreeModelListener(TreeModelListenerPtr l) = 0;

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
    
    //Returns the Parent of this node
    virtual boost::any getParent(const boost::any& node) const = 0;
    
    //Returns the Tree Path to this node
    TreePath getPath(const boost::any& node) const;

    //Returns true if these objects represent the same node in the tree
    bool isEqual(const boost::any& left, const boost::any& right) const;

    //A Depth First Traversal comparator
    //Returns true if left would be visited before right in a DFT
    bool depthFirstLessThan(const boost::any& left, const boost::any& right) const;
    
    //A Breadth First Traversal comparator
    //Returns true if left would be visited before right in a BFT
    bool breadthFirstLessThan(const boost::any& left, const boost::any& right) const;


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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TreeModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TreeModel &source);
};

typedef TreeModel *TreeModelP;

OSG_END_NAMESPACE

#include "OSGTreeModelBase.inl"
#include "OSGTreeModel.inl"

#endif /* _OSGTREEMODEL_H_ */
