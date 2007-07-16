/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGKEYFRAMESEQUENCEUINT16_H_
#define _OSGKEYFRAMESEQUENCEUINT16_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"
#include <OpenSG/OSGMFSysTypes.h>

#include "OSGKeyframeSequenceUInt16Base.h"

#include "Interpolation/OSGInterpolationFactory.h"
OSG_BEGIN_NAMESPACE

/*! \brief KeyframeSequenceUInt16 class. See \ref 
           PageSystemKeyframeSequenceUInt16 for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING KeyframeSequenceUInt16 : public KeyframeSequenceUInt16Base
{
  private:

    typedef KeyframeSequenceUInt16Base Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    static bool linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                  const osg::MFReal32& Keys,
                                  const osg::UInt32& Cycling,
                                  const osg::Real32& Time,
                                  const osg::Real32& PrevTime,
                                  const osg::ValueReplacementPolicy& ReplacementPolicy,
                                  osg::Field& Result);
    
    static bool cubicFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                  const osg::MFReal32& Keys,
                                  const osg::UInt32& Cycling,
                                  const osg::Real32& Time,
                                  const osg::Real32& PrevTime,
                                  const osg::ValueReplacementPolicy& ReplacementPolicy,
                                  osg::Field& Result);
    
    static bool stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                  const osg::MFReal32& Keys,
                                  const osg::UInt32& Cycling,
                                  const osg::Real32& Time,
                                  const osg::Real32& PrevTime,
                                  const osg::ValueReplacementPolicy& ReplacementPolicy,
                                  osg::Field& Result);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in KeyframeSequenceUInt16Base.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeSequenceUInt16(void);
    KeyframeSequenceUInt16(const KeyframeSequenceUInt16 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeSequenceUInt16(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class KeyframeSequenceUInt16Base;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyframeSequenceUInt16 &source);
};

typedef KeyframeSequenceUInt16 *KeyframeSequenceUInt16P;

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceUInt16Base.inl"
#include "OSGKeyframeSequenceUInt16.inl"

#define OSGKEYFRAMESEQUENCEUINT16_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGKEYFRAMESEQUENCEUINT16_H_ */
