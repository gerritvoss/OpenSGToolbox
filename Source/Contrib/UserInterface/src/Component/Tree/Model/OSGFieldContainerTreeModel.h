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

#ifndef _OSGFIELDCONTAINERTREEMODEL_H_
#define _OSGFIELDCONTAINERTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerTreeModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FieldContainerTreeModel class. See \ref
           PageContribUserInterfaceFieldContainerTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FieldContainerTreeModel : public FieldContainerTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldContainerTreeModelBase Inherited;
    typedef FieldContainerTreeModel     Self;

    enum PseudoId 
    {
        //ATTACHMENT_MAP_ID = -1,
        FIELD_CONTAINER_ID = 0,

    };

    struct ContainerFieldIdPair
    {
      public:
        ContainerFieldIdPair(FieldContainer* container, UInt32 fieldId);
        ContainerFieldIdPair(void);

        FieldContainer* _Container;
        Int32                _FieldID;

        bool operator==(const ContainerFieldIdPair& right) const;
    };

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
    void setRoot(FieldContainer* const root);

    //Get the Node* to the Root Node
    FieldContainer* getRootFieldContainer(void) const;

    //Returns true if these objects represent the same node in the tree
    virtual bool isEqual(const boost::any& left, const boost::any& right) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FieldContainerTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldContainerTreeModel(void);
    FieldContainerTreeModel(const FieldContainerTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldContainerTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    bool isFieldAllowed(const FieldDescriptionBase* fieldDesc) const;
    UInt32 getIndexFromFieldId(const FieldContainer* container, UInt32 index) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldContainerTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FieldContainerTreeModel &source);
};

typedef FieldContainerTreeModel *FieldContainerTreeModelP;

OSG_END_NAMESPACE

#include "OSGFieldContainerTreeModelBase.inl"
#include "OSGFieldContainerTreeModel.inl"

#endif /* _OSGFIELDCONTAINERTREEMODEL_H_ */
