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

#ifndef _OSGDEFAULTCOMBOBOXCOMPONENTGENERATOR_H_
#define _OSGDEFAULTCOMBOBOXCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultComboBoxComponentGeneratorBase.h"
#include "OSGComponent.h"
#include "OSGLayer.h"
#include "OSGBorder.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultComboBoxComponentGenerator class. See \ref
           PageContribUserInterfaceDefaultComboBoxComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultComboBoxComponentGenerator : public DefaultComboBoxComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultComboBoxComponentGeneratorBase Inherited;
    typedef DefaultComboBoxComponentGenerator     Self;

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

	virtual ComponentTransitPtr getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultComboBoxComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultComboBoxComponentGenerator(void);
    DefaultComboBoxComponentGenerator(const DefaultComboBoxComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultComboBoxComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultComboBoxComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultComboBoxComponentGenerator &source);
};

typedef DefaultComboBoxComponentGenerator *DefaultComboBoxComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultComboBoxComponentGeneratorBase.inl"
#include "OSGDefaultComboBoxComponentGenerator.inl"

#endif /* _OSGDEFAULTCOMBOBOXCOMPONENTGENERATOR_H_ */
