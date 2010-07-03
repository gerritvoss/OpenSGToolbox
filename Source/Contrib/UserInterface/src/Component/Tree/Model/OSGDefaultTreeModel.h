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

#ifndef _OSGDEFAULTTREEMODEL_H_
#define _OSGDEFAULTTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultTreeModelBase.h"
#include "OSGDefaultMutableTreeNodeFields.h"
#include "OSGMutableTreeNodeFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeModel class. See \ref
           PageContribUserInterfaceDefaultTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTreeModel : public DefaultTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTreeModelBase Inherited;
    typedef DefaultTreeModel     Self;

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
	virtual boost::any getChild(const boost::any& parent, const UInt32& index) const;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(const boost::any& parent) const;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(const boost::any& parent, const boost::any& child) const;

	//Returns the root of the tree.
	virtual boost::any getRoot(void) const;

	//Returns true if node is a leaf.
	virtual bool isLeaf(const boost::any& node) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, const boost::any& newValue);

    //Builds the parents of node up to and including the root node, where the original node is the last element in the returned array.
    std::vector<MutableTreeNodeRefPtr> getPathToRoot(ModelTreeNode* const aNode);

    //Invoked this to insert newChild at location index in parents children.
    void insertNodeInto(MutableTreeNode* const newChild, MutableTreeNode* const parent, const UInt32& index);

    //Invoke this method after you've changed how node is to be represented in the tree.
    void nodeChanged(ModelTreeNode* const node);

    //Invoke this method after you've changed how the children identified by childIndicies are to be represented in the tree.
    void nodesChanged(ModelTreeNode* const node, std::vector<UInt32> childIndices);

    //Invoke this method if you've totally changed the children of node and its childrens children...
    void nodeStructureChanged(ModelTreeNode* const node);

    //Invoke this method after you've inserted some TreeNodes into node.
    void nodesWereInserted(ModelTreeNode* const node, std::vector<UInt32> childIndices);

    //Invoke this method after you've removed some TreeNodes from node.
    void nodesWereRemoved(ModelTreeNode* const node, std::vector<UInt32> childIndices, std::vector<boost::any> removedChildren);

    //Invoke this method if you've modified the TreeNodes upon which this model depends.
    void reload(void);

    //Invoke this method if you've modified the TreeNodes upon which this model depends.
    void reload(ModelTreeNode* const node);

    //Message this to remove node from its parent.
    void removeNodeFromParent(MutableTreeNode* const node);

    //Sets the root to root.
    void setRoot(ModelTreeNode* const root);

    //Get the ModelTreeNode* const to the Root Node
    ModelTreeNode* getRootNode(void) const;
    
    //Get the Node for the given path
    ModelTreeNode* getNodeForPath(const TreePath& ThePath) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTreeModel(void);
    DefaultTreeModel(const DefaultTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    TreePath createPath(ModelTreeNode* const node) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTreeModel &source);
};

typedef DefaultTreeModel *DefaultTreeModelP;

OSG_END_NAMESPACE

#include "OSGModelTreeNode.h"
#include "OSGDefaultTreeModelBase.inl"
#include "OSGDefaultTreeModel.inl"

#endif /* _OSGDEFAULTTREEMODEL_H_ */
