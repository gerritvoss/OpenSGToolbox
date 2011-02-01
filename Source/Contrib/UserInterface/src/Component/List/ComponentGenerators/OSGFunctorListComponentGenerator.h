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

#ifndef _OSGFUNCTORLISTCOMPONENTGENERATOR_H_
#define _OSGFUNCTORLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFunctorListComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FunctorListComponentGenerator class. See \ref
           PageContribUserInterfaceFunctorListComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FunctorListComponentGenerator : public FunctorListComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FunctorListComponentGeneratorBase Inherited;
    typedef FunctorListComponentGenerator     Self;

    typedef boost::function<
        ComponentTransitPtr (List* const Parent,
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

	virtual ComponentTransitPtr getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);

    void setGenerateFunction(GenerateFunctorType Functor);

    GenerateFunctorType getGenerateFunction(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FunctorListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FunctorListComponentGenerator(void);
    FunctorListComponentGenerator(const FunctorListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FunctorListComponentGenerator(void);

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
    friend class FunctorListComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FunctorListComponentGenerator &source);
};

typedef FunctorListComponentGenerator *FunctorListComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGFunctorListComponentGeneratorBase.inl"
#include "OSGFunctorListComponentGenerator.inl"

#endif /* _OSGFUNCTORLISTCOMPONENTGENERATOR_H_ */
