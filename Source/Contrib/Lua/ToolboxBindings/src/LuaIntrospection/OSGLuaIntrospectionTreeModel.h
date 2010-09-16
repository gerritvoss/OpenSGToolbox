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

#ifndef _OSGLUAINTROSPECTIONTREEMODEL_H_
#define _OSGLUAINTROSPECTIONTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLuaIntrospectionTreeModelBase.h"
#include "OSGLuaUtils.h"

OSG_BEGIN_NAMESPACE

/*! \brief LuaIntrospectionTreeModel class. See \ref
           PageContribLuaToolboxLuaIntrospectionTreeModel for a description.
*/

class OSG_CONTRIBLUATOOLBOX_DLLMAPPING LuaIntrospectionTreeModel : public LuaIntrospectionTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaIntrospectionTreeModelBase Inherited;
    typedef LuaIntrospectionTreeModel     Self;

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

    //Sets the root to root.
    void setRoot(const std::string& root);

    //Get the NodeUnrecPtr to the Root Node
    const std::string& getRootLuaPath(void) const;

    //Returns true if these objects represent the same node in the tree
    virtual bool isEqual(const boost::any& left, const boost::any& right) const;

    //Produces a TreeModelEvent that indicates the entire model has changed
    //and any objects listening to the event need to update accordingly
    void produceModelChanged(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LuaIntrospectionTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaIntrospectionTreeModel(void);
    LuaIntrospectionTreeModel(const LuaIntrospectionTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaIntrospectionTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    TreePath createPath(const std::string& luaPath) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaIntrospectionTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaIntrospectionTreeModel &source);
};

typedef LuaIntrospectionTreeModel *LuaIntrospectionTreeModelP;

OSG_END_NAMESPACE

#include "OSGLuaIntrospectionTreeModelBase.inl"
#include "OSGLuaIntrospectionTreeModel.inl"

#endif /* _OSGLUAINTROSPECTIONTREEMODEL_H_ */
