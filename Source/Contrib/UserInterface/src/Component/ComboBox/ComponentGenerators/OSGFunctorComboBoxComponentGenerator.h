/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#ifndef _OSGFUNCTORCOMBOBOXCOMPONENTGENERATOR_H_
#define _OSGFUNCTORCOMBOBOXCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFunctorComboBoxComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FunctorComboBoxComponentGenerator class. See \ref
           PageContribUserInterfaceFunctorComboBoxComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FunctorComboBoxComponentGenerator : public FunctorComboBoxComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FunctorComboBoxComponentGeneratorBase Inherited;
    typedef FunctorComboBoxComponentGenerator     Self;

    typedef boost::function<
        ComponentTransitPtr (ComboBox* const Parent,
                             const boost::any& Value,
                             UInt32 Index,
                             bool IsSelected,
                             bool HasFocus)>     GenerateFunctorType;

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

	virtual ComponentTransitPtr getComboBoxComponent(ComboBox* const Parent,
                                                     const boost::any& Value,
                                                     UInt32 Index,
                                                     bool IsSelected,
                                                     bool HasFocus);

    void setGenerateFunction(GenerateFunctorType Functor);

    GenerateFunctorType getGenerateFunction(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FunctorComboBoxComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FunctorComboBoxComponentGenerator(void);
    FunctorComboBoxComponentGenerator(const FunctorComboBoxComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FunctorComboBoxComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    GenerateFunctorType _GenerateFunctor;

    friend class FieldContainer;
    friend class FunctorComboBoxComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FunctorComboBoxComponentGenerator &source);
};

typedef FunctorComboBoxComponentGenerator *FunctorComboBoxComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGFunctorComboBoxComponentGeneratorBase.inl"
#include "OSGFunctorComboBoxComponentGenerator.inl"

#endif /* _OSGFUNCTORCOMBOBOXCOMPONENTGENERATOR_H_ */
