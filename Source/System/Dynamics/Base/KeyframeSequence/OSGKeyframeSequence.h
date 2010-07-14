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

#ifndef _OSGKEYFRAMESEQUENCE_H_
#define _OSGKEYFRAMESEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeInterpolations.h"
#include "OSGKeyframeSequenceBase.h"


OSG_BEGIN_NAMESPACE

/*! \brief KeyframeSequence class. See \ref
           PageDynamicsKeyframeSequence for a description.
*/

class OSG_TBANIMATION_DLLMAPPING KeyframeSequence : public KeyframeSequenceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef KeyframeSequenceBase Inherited;
    typedef KeyframeSequence     Self;

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
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    Real32 getKey(UInt32 index);

    Real32 getKey(UInt32 index) const;

    void getKey( Real32 &val, UInt32 index);

    void getKey( Real32 &val, UInt32 index) const;

    const MFReal32 &getKeys(void) const;

          MFReal32 *editKeys(void);

    virtual UInt32  size         (void) const = 0;
    virtual bool        isBlendable(void) const = 0;

    virtual const Field& getKeyValues(void) const = 0;
    
    virtual const DataType &getDataType(void) const = 0;

    /*! \}                                                                 */
    
    /*! \name                 Keyframe Modifiers                           */
    /*! \{                                                                 */

    virtual void        clear    (      void               )       = 0;
    virtual void        resize   (      size_t      newsize)       = 0;
    virtual void        shrink   (void                     )       = 0;

    /*! \}                                                                 */

    /*! \name                  Interpolation                               */
    /*! \{                                                                 */

    bool interpolate(const UInt32& Type,
                     const Real32& time,
                     const Real32& prevTime,
                     const UInt32& ReplacePolicy,
                     bool isCyclic,
                     EditFieldHandlePtr Result,
                     UInt32 Index,
                     Real32 Blend);

    virtual void zeroField(EditFieldHandlePtr Result,
                           UInt32 Index) const = 0;
    
    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*! \name         Internal Interpolation Handling                      */
    /*! \{                                                                 */

    virtual RawInterpFuncion bindInterpFunction(UInt32 InterpolationFunctionId) const = 0;
    virtual ReplacementFuncion getReplacementFuncion(void) const = 0;

    /*! \}                                                                 */
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class KeyframeSequenceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const KeyframeSequence &source);
};

typedef KeyframeSequence *KeyframeSequenceP;

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceBase.inl"
#include "OSGKeyframeSequence.inl"

#endif /* _OSGKEYFRAMESEQUENCE_H_ */
