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

#ifndef _OSGMFIELDLISTMODEL_H_
#define _OSGMFIELDLISTMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMFieldListModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MFieldListModel class. See \ref
           PageContribUserInterfaceMFieldListModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MFieldListModel : public MFieldListModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    typedef std::pair<GetFieldHandlePtr, UInt32>         MFieldIndexed;

    typedef MFieldListModelBase Inherited;
    typedef MFieldListModel     Self;

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

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MFieldListModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MFieldListModel(void);
    MFieldListModel(const MFieldListModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MFieldListModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    void containerChanged(FieldContainer * container, ConstFieldMaskArg whichField);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MFieldListModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MFieldListModel &source);
};

typedef MFieldListModel *MFieldListModelP;

OSG_END_NAMESPACE

#include "OSGMFieldListModelBase.inl"
#include "OSGMFieldListModel.inl"

#endif /* _OSGMFIELDLISTMODEL_H_ */
