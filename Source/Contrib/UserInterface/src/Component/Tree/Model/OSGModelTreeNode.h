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

#ifndef _OSGMODELTREENODE_H_
#define _OSGMODELTREENODE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGModelTreeNodeBase.h"
#include "OSGTreePath.h"
#include <boost/any.hpp>
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief ModelTreeNode class. See \ref
           PageContribUserInterfaceModelTreeNode for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ModelTreeNode : public ModelTreeNodeBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ModelTreeNodeBase Inherited;
    typedef ModelTreeNode     Self;

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
	
	//Returns the children of the receiver as a Vector.
    virtual std::vector<ModelTreeNodeRefPtr> getChildren(void) const;

	//Returns true if the receiver allows children.
	virtual bool getAllowsChildren(void) const = 0;

	//Returns the child ModelTreeNode at index childIndex.
	virtual ModelTreeNode* getChildAt(const UInt32& childIndex) const = 0;

	//Returns the number of children ModelTreeNodes the receiver contains.
	virtual UInt32 getChildCount(void) const = 0;

	//Returns the index of node in the receivers children.
	virtual Int32 getIndex(ModelTreeNode* const node) const = 0;

	//Returns the parent ModelTreeNode of the receiver.
	virtual ModelTreeNode* getParent(void) const = 0;

	//Returns true if the receiver is a leaf.
	virtual bool isLeaf(void) const = 0;

	//Resets the user object of the receiver to object.
	virtual void setUserObject(const boost::any& object) = 0;
    
	//Returns this node's user object.
	virtual boost::any getUserObject(void) const = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ModelTreeNodeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ModelTreeNode(void);
    ModelTreeNode(const ModelTreeNode &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ModelTreeNode(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ModelTreeNodeBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ModelTreeNode &source);
};

typedef ModelTreeNode *ModelTreeNodeP;

OSG_END_NAMESPACE

#include "OSGModelTreeNodeBase.inl"
#include "OSGModelTreeNode.inl"

#endif /* _OSGMODELTREENODE_H_ */
