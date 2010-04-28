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

#ifndef _OSGSCENEGRAPHTREEMODEL_H_
#define _OSGSCENEGRAPHTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSceneGraphTreeModelBase.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneGraphTreeModel class. See \ref
           PageContribUserInterfaceSceneGraphTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SceneGraphTreeModel : public SceneGraphTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneGraphTreeModelBase Inherited;
    typedef SceneGraphTreeModel     Self;

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
    
    //Returns the Parent of this node
    virtual boost::any getParent(const boost::any& node) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, const boost::any& newValue);

    //Sets the root to root.
    void setRoot(NodeUnrecPtr root);

    //Get the NodeUnrecPtr to the Root Node
    NodeUnrecPtr getRootNode(void) const;

    //Get the the path in the model to the given node
    TreePath getPathForNode(NodeUnrecPtr theNode) const;

    //Returns true if these objects represent the same node in the tree
    virtual bool isEqual(const boost::any& left, const boost::any& right) const;

    void removeNode(const boost::any& nodeToBeRemoved);

    void addNode(const boost::any& parent,const boost::any& nodeToBeAdded);

    void insertNode(const boost::any& parent,
                    const boost::any& nodeToBeAdded,
                    UInt32 Index);


    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneGraphTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneGraphTreeModel(void);
    SceneGraphTreeModel(const SceneGraphTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneGraphTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneGraphTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneGraphTreeModel &source);
};

typedef SceneGraphTreeModel *SceneGraphTreeModelP;

OSG_END_NAMESPACE

#include "OSGSceneGraphTreeModelBase.inl"
#include "OSGSceneGraphTreeModel.inl"

#endif /* _OSGSCENEGRAPHTREEMODEL_H_ */
