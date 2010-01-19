/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#ifndef _OSGRUBBERBANDCAMERA_H_
#define _OSGRUBBERBANDCAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGRubberBandCameraBase.h"

OSG_BEGIN_NAMESPACE

class OSG_GAMELIB_DLLMAPPING RubberBandCamera : public RubberBandCameraBase
{
  private:

    typedef RubberBandCameraBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    virtual void getViewing              (Matrix        &result, 
                                           UInt32 width, UInt32 height);
    void update              (const Real32& Elps);
    void setToBeacon(void);

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in RubberBandCameraBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RubberBandCamera(void);
    RubberBandCamera(const RubberBandCamera &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RubberBandCamera(void); 

    /*! \}                                                                 */
    
    osg::Matrix _Matrix;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RubberBandCameraBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RubberBandCamera &source);
};

typedef RubberBandCamera *RubberBandCameraP;

OSG_END_NAMESPACE

#include "OSGRubberBandCameraBase.inl"
#include "OSGRubberBandCamera.inl"

#define OSGRUBBERBANDCAMERA_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGRUBBERBANDCAMERA_H_ */
