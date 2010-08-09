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

#ifndef _OSGCOLORSELECTIONMODEL_H_
#define _OSGCOLORSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGColorSelectionModelBase.h"
#include "OSGColor.h"

OSG_BEGIN_NAMESPACE

/*! \brief ColorSelectionModel class. See \ref
           PageContribUserInterfaceColorSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ColorSelectionModel : public ColorSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorSelectionModelBase Inherited;
    typedef ColorSelectionModel     Self;

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

	virtual Color4f getSelectedColor(void) const = 0;

	virtual void setSelectedColor(const Color4f& Value, bool isValueAdjusting) = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorSelectionModel(void);
    ColorSelectionModel(const ColorSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void produceStateChanged(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorSelectionModel &source);
};

typedef ColorSelectionModel *ColorSelectionModelP;

OSG_END_NAMESPACE

#include "OSGColorSelectionModelBase.inl"
#include "OSGColorSelectionModel.inl"

#endif /* _OSGCOLORSELECTIONMODEL_H_ */
