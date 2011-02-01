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

#ifndef _OSGFUNCTORTREECOMPONENTGENERATOR_H_
#define _OSGFUNCTORTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFunctorTreeComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FunctorTreeComponentGenerator class. See \ref
           PageContribUserInterfaceFunctorTreeComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING FunctorTreeComponentGenerator : public FunctorTreeComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FunctorTreeComponentGeneratorBase Inherited;
    typedef FunctorTreeComponentGenerator     Self;

    typedef boost::function<
        ComponentTransitPtr (Tree* const Parent,
                             const boost::any& Value,
                             bool IsSelected,
                             bool Expanded,
                             bool Leaf,
                             UInt32 Row,
                             bool HasFocus)>     GenerateFunctorType;

    typedef boost::function<
        ComponentTransitPtr (Tree* const Parent,
                             const boost::any& Value,
                             bool IsSelected,
                             bool Expanded,
                             bool Leaf,
                             UInt32 Row,
                             bool HasFocus)>     ExpandGenerateFunctorType;

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

    virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                                 const boost::any& Value,
                                                 bool IsSelected,
                                                 bool Expanded,
                                                 bool Leaf,
                                                 UInt32 Row,
                                                 bool HasFocus);

    virtual ComponentTransitPtr getTreeExpandedComponent(Tree* const Parent,
                                                         const boost::any& Value,
                                                         bool IsSelected,
                                                         bool Expanded,
                                                         bool Leaf,
                                                         UInt32 Row,
                                                         bool HasFocus);

    void setGenerateFunction(GenerateFunctorType Functor);
    void setExpandGenerateFunction(ExpandGenerateFunctorType Functor);

    GenerateFunctorType getGenerateFunction(void) const;
    ExpandGenerateFunctorType getExpandGenerateFunction(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FunctorTreeComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FunctorTreeComponentGenerator(void);
    FunctorTreeComponentGenerator(const FunctorTreeComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FunctorTreeComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    GenerateFunctorType _GenerateFunctor;
    ExpandGenerateFunctorType _ExpandGenerateFunctor;

    friend class FieldContainer;
    friend class FunctorTreeComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FunctorTreeComponentGenerator &source);
};

typedef FunctorTreeComponentGenerator *FunctorTreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGFunctorTreeComponentGeneratorBase.inl"
#include "OSGFunctorTreeComponentGenerator.inl"

#endif /* _OSGFUNCTORTREECOMPONENTGENERATOR_H_ */
