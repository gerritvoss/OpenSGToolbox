/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGINTERPOLATIONFACTORY_H_
#define _OSGINTERPOLATIONFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationDef.h"
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGGeoPositionsFields.h> // BaseValues type

#include <OpenSG/Toolbox/OSGInterpolations.h>
#include "KeyframeSequence/OSGKeyframeSequence.h"

#include <map>

OSG_BEGIN_NAMESPACE

class TypeBase;

/*! \ingroup GrpBaseBaseTypeSystem
 */

class OSG_ANIMATIONLIB_DLLMAPPING InterpolationFactory
{
  public:
    typedef bool (*InterpFunc)(const osg::KeyframeSequencePtr& KeyValues,
                               const osg::MFReal32& Keys,
                               const osg::UInt32& Cycling,
                               const osg::Real32& Time,
                               const osg::Real32& PrevTime,
                               const osg::ValueReplacementPolicy& ReplacementPolicy,
                               osg::Field& Result);
    
    typedef void (*MFieldInterpFunc)(const osg::Field& FromMField,
                                    const osg::Field& ToMField,
                                    osg::Field& ResultMField,
                                    const osg::UInt32 FromIndex,
                                    const osg::UInt32 ToIndex,
                                    const osg::UInt32 ResultIndex,
                                    const osg::Real32 t);
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

                               
    //Keyframe Interpolation Functions
    typedef std::map<osg::UInt32, InterpFunc> InterpFuncMap;
    typedef InterpFuncMap::iterator              InterpFuncMapIt;
    typedef InterpFuncMap::const_iterator        InterpFuncMapConstIt;
    
    typedef std::map<osg::InterpolationType, InterpFuncMap> InterpMap;
    typedef InterpMap::iterator              InterpMapIt;
    typedef InterpMap::const_iterator        InterpMapConstIt;

    //MField Interpolation Functions
    typedef std::map<osg::UInt32, MFieldInterpFunc> MFieldInterpFuncMap;
    typedef MFieldInterpFuncMap::iterator              MFieldInterpFuncMapIt;
    typedef MFieldInterpFuncMap::const_iterator        MFieldInterpFuncMapConstIt;
    
    typedef std::map<osg::InterpolationType, MFieldInterpFuncMap> MFieldInterpMap;
    typedef MFieldInterpMap::iterator              MFieldInterpMapIt;
    typedef MFieldInterpMap::const_iterator        MFieldInterpMapConstIt;
                               

    /*! \{                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Static Variables                             */
    /*! \{                                                                 */

    static InterpolationFactory   *_the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Members                                 */
    /*! \{                                                                 */

    
          InterpMap _InterpMap;
          MFieldInterpMap _MFieldInterpMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    InterpolationFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~InterpolationFactory(void);
    
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static InterpolationFactory *the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Info                                   */
    /*! \{                                                                 */

    bool registerFieldInterpFunc(const osg::InterpolationType& InterpType,const osg::FieldType& F, const InterpFunc& Func);

    UInt32    getNumFuncs   (const osg::InterpolationType& InterpType);
    InterpFunc    getFunc   (const osg::InterpolationType& InterpType, const osg::FieldType& F);
    InterpFunc    getFunc   (const osg::InterpolationType& InterpType, const UInt32& Id);
    
    bool registerMFieldInterpFunc(const osg::InterpolationType& InterpType,const osg::FieldType& F, const MFieldInterpFunc& Func);

    UInt32    getNumMFieldFuncs   (const osg::InterpolationType& InterpType);
    MFieldInterpFunc    getMFieldFunc   (const osg::InterpolationType& InterpType, const osg::FieldType& F);
    MFieldInterpFunc    getMFieldFunc   (const osg::InterpolationType& InterpType, const UInt32& Id);


    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    InterpolationFactory(const InterpolationFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const InterpolationFactory &source);
};

OSG_END_NAMESPACE

#define OSGINTERPOLATIONFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGINTERPOLATIONFACTORY_H_ */
