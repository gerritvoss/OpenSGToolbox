/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGKEYFRAMESEQUENCE_H_
#define _OSGKEYFRAMESEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceBase.h"
#include "Interpolation/OSGKeyframeInterpolations.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyframeSequence class. See \ref 
           PageAnimationKeyframeSequence for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING KeyframeSequence : public KeyframeSequenceBase
{
  private:

    typedef KeyframeSequenceBase Inherited;

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

    Real32 getKey(UInt32 index);

    Real32 getKey(UInt32 index) const;

    void getKey( Real32 &val, UInt32 index);

    void getKey( Real32 &val, UInt32 index) const;

    const MFReal32 &getKeys(void) const;

    virtual UInt32  getSize      (void) const = 0;
    virtual UInt32  size         (void) const = 0;
    
    virtual void        clear    (      void               )       = 0;
    virtual void        resize   (      size_t      newsize)       = 0;
    virtual void        shrink   (void                     )       = 0;
    virtual bool        isBlendable(void) const = 0;

    bool interpolate(const InterpolationType& Type, const Real32& time, const Real32& prevTime, const osg::ValueReplacementPolicy& ReplacePolicy, bool isCyclic, osg::Field& Result, UInt32 Index, Real32 Blend);
    virtual void zeroField(osg::Field& Result, UInt32 Index) const = 0;
    
    virtual const osg::Field& getKeyValues(void) const = 0;
    
    virtual const DataType &getDataType(void) const = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    virtual RawInterpFuncion getStepInterpFuncion(void) = 0;
    virtual RawInterpFuncion getLinearInterpFuncion(void) = 0;
    virtual RawInterpFuncion getCubicInterpFuncion(void) = 0;
    virtual RawInterpFuncion getLinearNormalInterpFuncion(void) = 0;
    virtual ReplacementFuncion getReplacementFuncion(void) = 0;

    RawInterpFuncion getRawInterpFuncion(const InterpolationType& Type);

    // Variables should all be in KeyframeSequenceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeSequence(void);
    KeyframeSequence(const KeyframeSequence &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeSequence(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class KeyframeSequenceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyframeSequence &source);
};

typedef KeyframeSequence *KeyframeSequenceP;

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceBase.inl"
#include "OSGKeyframeSequence.inl"

#define OSGKEYFRAMESEQUENCE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGKEYFRAMESEQUENCE_H_ */


