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

#ifndef _OSGDEFAULTLISTMODEL_H_
#define _OSGDEFAULTLISTMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultListModelBase.h"
#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListModel class. See \ref
           PageContribUserInterfaceDefaultListModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultListModel : public DefaultListModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultListModelBase Inherited;
    typedef DefaultListModel     Self;

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
	virtual UInt32 getSize(void) const;
    virtual boost::any getElementAt(UInt32 index) const;

	

    typedef std::deque<boost::any> FieldList;
	void pushBack(const boost::any& f);
	void popBack(void);

	void pushFront(const boost::any& f);
	void popFront(void);

	void insert(UInt32 Index, const boost::any& f);
	
	void erase(UInt32 Index);
	void set(UInt32 Index, const boost::any& v);
	void clear(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultListModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultListModel(void);
    DefaultListModel(const DefaultListModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultListModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	FieldList _FieldList;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultListModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultListModel &source);
};

typedef DefaultListModel *DefaultListModelP;

OSG_END_NAMESPACE

#include "OSGDefaultListModelBase.inl"
#include "OSGDefaultListModel.inl"

#endif /* _OSGDEFAULTLISTMODEL_H_ */
