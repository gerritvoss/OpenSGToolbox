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

#ifndef _OSGIMAGEPROCESSEDFOREGROUND_H_
#define _OSGIMAGEPROCESSEDFOREGROUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGImageProcessedForegroundBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ImageProcessedForeground class. See \ref 
           PageImageProcessingImageProcessedForeground for a description.
*/

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING ImageProcessedForeground : public ImageProcessedForegroundBase
{
  private:

    typedef ImageProcessedForegroundBase Inherited;

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
	virtual void draw( DrawActionBase * action, Viewport * port );
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ImageProcessedForegroundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ImageProcessedForeground(void);
    ImageProcessedForeground(const ImageProcessedForeground &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ImageProcessedForeground(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ImageProcessedForegroundBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ImageProcessedForeground &source);
};

typedef ImageProcessedForeground *ImageProcessedForegroundP;

OSG_END_NAMESPACE

#include "OSGImageProcessedForegroundBase.inl"
#include "OSGImageProcessedForeground.inl"

#endif /* _OSGIMAGEPROCESSEDFOREGROUND_H_ */
