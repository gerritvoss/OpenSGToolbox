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

#ifndef _OSGVIDEOEVENTDETAILS_H_
#define _OSGVIDEOEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVideoEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VideoEventDetails class. See \ref
           PageContribVideoVideoEventDetails for a description.
*/

class OSG_CONTRIBVIDEO_DLLMAPPING VideoEventDetails : public VideoEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VideoEventDetailsBase Inherited;
    typedef VideoEventDetails     Self;

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
    static  VideoEventDetailsTransitPtr      create(FieldContainer* const Source,
                                                    Time TimeStamp); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VideoEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VideoEventDetails(void);
    VideoEventDetails(const VideoEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VideoEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VideoEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VideoEventDetails &source);
};

typedef VideoEventDetails *VideoEventDetailsP;

OSG_END_NAMESPACE

#include "OSGVideoEventDetailsBase.inl"
#include "OSGVideoEventDetails.inl"

#endif /* _OSGVIDEOEVENTDETAILS_H_ */
