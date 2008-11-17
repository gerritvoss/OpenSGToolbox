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

#ifndef _OSGKEYFRAMESEQUENCEGLENUM_H_
#define _OSGKEYFRAMESEQUENCEGLENUM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"
#include <OpenSG/OSGMFSysTypes.h>

#include "OSGKeyframeSequenceGLenumBase.h"

#include "Interpolation/OSGInterpolationFactory.h"
OSG_BEGIN_NAMESPACE

/*! \brief KeyframeSequenceGLenum class. See \ref 
           PageSystemKeyframeSequenceGLenum for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING KeyframeSequenceGLenum : public KeyframeSequenceGLenumBase
{
  private:

    typedef KeyframeSequenceGLenumBase Inherited;

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

    // Variables should all be in KeyframeSequenceGLenumBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeSequenceGLenum(void);
    KeyframeSequenceGLenum(const KeyframeSequenceGLenum &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeSequenceGLenum(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class KeyframeSequenceGLenumBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyframeSequenceGLenum &source);
};

typedef KeyframeSequenceGLenum *KeyframeSequenceGLenumP;

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceGLenumBase.inl"
#include "OSGKeyframeSequenceGLenum.inl"

#define OSGKEYFRAMESEQUENCEGLENUM_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGKEYFRAMESEQUENCEGLENUM_H_ */
