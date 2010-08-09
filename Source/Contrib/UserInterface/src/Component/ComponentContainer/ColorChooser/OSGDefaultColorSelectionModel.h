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

#ifndef _OSGDEFAULTCOLORSELECTIONMODEL_H_
#define _OSGDEFAULTCOLORSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultColorSelectionModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultColorSelectionModel class. See \ref
           PageContribUserInterfaceDefaultColorSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultColorSelectionModel : public DefaultColorSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultColorSelectionModelBase Inherited;
    typedef DefaultColorSelectionModel     Self;

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

	virtual Color4f getSelectedColor(void) const;

	virtual void setSelectedColor(const Color4f& Value, bool isValueAdjusting);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultColorSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultColorSelectionModel(void);
    DefaultColorSelectionModel(const DefaultColorSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultColorSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultColorSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultColorSelectionModel &source);
};

typedef DefaultColorSelectionModel *DefaultColorSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultColorSelectionModelBase.inl"
#include "OSGDefaultColorSelectionModel.inl"

#endif /* _OSGDEFAULTCOLORSELECTIONMODEL_H_ */
