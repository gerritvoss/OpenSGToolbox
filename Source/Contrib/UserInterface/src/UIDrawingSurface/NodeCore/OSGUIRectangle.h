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

#ifndef _OSGUIRECTANGLE_H_
#define _OSGUIRECTANGLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIRectangleBase.h"
#include "OSGRenderAction.h"
#include "OSGUIDrawingSurface.h"
#include "OSGPolygonChunk.h"
#include "OSGColorMaskChunk.h"
#include "OSGChunkMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIRectangle class. See \ref
           PageContribUserInterfaceUIRectangle for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIRectangle : public UIRectangleBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIRectangleBase Inherited;
    typedef UIRectangle     Self;

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

    Action::ResultE renderActionEnterHandler(Action  *action);

    Action::ResultE renderActionLeaveHandler(Action  *action);

    virtual void drawPrimitives          (DrawEnv *pEnv  );

    virtual void fill(DrawableStatsAttachment *pStat);

    ActionBase::ResultE     intersect(Action    *action);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIRectangleBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIRectangle(void);
    UIRectangle(const UIRectangle &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIRectangle(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const UIRectangle *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    void    adjustVolume(Volume & volume);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIRectangleBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIRectangle &source);

	ChunkMaterialRefPtr _Mat;


};

typedef UIRectangle *UIRectangleP;

OSG_END_NAMESPACE

#include "OSGUIRectangleMouseTransformFunctor.h"
#include "OSGInternalWindow.h"

#include "OSGUIRectangleBase.inl"
#include "OSGUIRectangle.inl"

#endif /* _OSGUIRECTANGLE_H_ */
