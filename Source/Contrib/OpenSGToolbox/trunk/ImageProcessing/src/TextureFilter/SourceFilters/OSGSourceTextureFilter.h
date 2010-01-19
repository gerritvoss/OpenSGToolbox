/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
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

#ifndef _OSGSOURCETEXTUREFILTER_H_
#define _OSGSOURCETEXTUREFILTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGSourceTextureFilterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SourceTextureFilter class. See \ref 
           PageImageProcessingSourceTextureFilter for a description.
*/

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING SourceTextureFilter : public SourceTextureFilterBase
{
  private:

    typedef SourceTextureFilterBase Inherited;

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

    virtual Real32 getDepPixelRadius(void) const;
    
    virtual Int32 getNumInputSlots(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SourceTextureFilterBase.
    virtual TextureFilterInputSlot* editInputSlot(UInt32 InputSlot = 0); 

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SourceTextureFilter(void);
    SourceTextureFilter(const SourceTextureFilter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SourceTextureFilter(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SourceTextureFilterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SourceTextureFilter &source);
};

typedef SourceTextureFilter *SourceTextureFilterP;

OSG_END_NAMESPACE

#include "OSGSourceTextureFilterBase.inl"
#include "OSGSourceTextureFilter.inl"

#endif /* _OSGSOURCETEXTUREFILTER_H_ */
