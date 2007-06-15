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

#ifndef _OSGKEYFRAMESEQUENCESTATECHUNKPTR_H_
#define _OSGKEYFRAMESEQUENCESTATECHUNKPTR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationConfig.h"
#include <OpenSG/OSGConfig.h>

#include "OSGKeyframeSequenceStateChunkPtrBase.h"

#include "Interpolation/OSGInterpolationFactory.h"
OSG_BEGIN_NAMESPACE

class OSG_ANIMATION_CLASS_API KeyframeSequenceStateChunkPtr : public KeyframeSequenceStateChunkPtrBase
{
  private:

    typedef KeyframeSequenceStateChunkPtrBase Inherited;

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
    static bool stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                       const osg::MFReal32& Keys,
                                       const osg::UInt32& Cycling,
                                       const osg::Real32& Time,
                                       const osg::Real32& PrevTime,
                                       const osg::ValueReplacementPolicy& ReplacementPolicy,
                                       osg::Field& Result);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in KeyframeSequenceStateChunkPtrBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeSequenceStateChunkPtr(void);
    KeyframeSequenceStateChunkPtr(const KeyframeSequenceStateChunkPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeSequenceStateChunkPtr(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class KeyframeSequenceStateChunkPtrBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyframeSequenceStateChunkPtr &source);
};

typedef KeyframeSequenceStateChunkPtr *KeyframeSequenceStateChunkPtrP;

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceStateChunkPtrBase.inl"
#include "OSGKeyframeSequenceStateChunkPtr.inl"

#define OSGKEYFRAMESEQUENCESTATECHUNKPTR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGKEYFRAMESEQUENCESTATECHUNKPTR_H_ */
