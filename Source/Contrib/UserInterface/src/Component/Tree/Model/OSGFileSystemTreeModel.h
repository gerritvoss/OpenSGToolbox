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

#ifndef _OSGFILESYSTEMTREEMODEL_H_
#define _OSGFILESYSTEMTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFileSystemTreeModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FileSystemTreeModel class. See \ref
           PageContribUserInterfaceFileSystemTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FileSystemTreeModel : public FileSystemTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FileSystemTreeModelBase Inherited;
    typedef FileSystemTreeModel     Self;

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
    void setRoot(const BoostPath& root);

    //Get the NodeRefPtr to the Root Node
    const BoostPath& getRootPath(void) const;

    //Returns true if these objects represent the same node in the tree
    virtual bool isEqual(const boost::any& left, const boost::any& right) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FileSystemTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FileSystemTreeModel(void);
    FileSystemTreeModel(const FileSystemTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FileSystemTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FileSystemTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FileSystemTreeModel &source);
};

typedef FileSystemTreeModel *FileSystemTreeModelP;

OSG_END_NAMESPACE

#include "OSGFileSystemTreeModelBase.inl"
#include "OSGFileSystemTreeModel.inl"

#endif /* _OSGFILESYSTEMTREEMODEL_H_ */
