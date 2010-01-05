/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGCGFXRENDERPASSCHUNK_H_
#define _OSGCGFXRENDERPASSCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCgfxRenderPassChunkBase.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

OSG_BEGIN_NAMESPACE

/*! \brief CgfxRenderPassChunk class. See \ref
           PageStateCgfxRenderPassChunk for a description.
*/

class OSG_STATE_DLLMAPPING CgfxRenderPassChunk : public CgfxRenderPassChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CgfxRenderPassChunkBase Inherited;
    typedef CgfxRenderPassChunk     Self;


    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static       UInt32            getStaticClassId(void);
    static const StateChunkClass * getStaticClass  (void);

    /*! \}                                                                 */
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
    virtual void activate     (DrawEnv    *pEnv, 
                               UInt32      index = 0);

    virtual void changeFrom   (DrawEnv    *pEnv, 
                               StateChunk *pOld,
                               UInt32      index = 0);

    virtual void deactivate   (DrawEnv    *pEnv, 
                               UInt32      index = 0);


	void setCGTechnique(CGtechnique tech);
	const CGtechnique getCGTechnique(void);
	void setCGPass(CGpass renderPass);
	void setCGEffect(CGeffect *effect);
	const CGpass getCGPass(void);
	std::string getPassName(void);
	void setPassName(std::string name);
	void setSemanticBitVector(OSG::BitVector bitVec);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CgfxRenderPassChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CgfxRenderPassChunk(void);
    CgfxRenderPassChunk(const CgfxRenderPassChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CgfxRenderPassChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

	CGtechnique _mTechnique;
	CGpass	_mPass;
	CGeffect *_mEffect;

	// only one pass per chunk.  To ensure that the proper pass is being grabbed from the 
	// technique, each pass must have a unique name (naming is taken care of in CgfxMaterial)
	std::string _mName;
	// bit vector used to determine which matricies to update (modelview, etc...)
	OSG::BitVector _mSemanticBV;

	void updateGLMatricies(DrawEnv *pEnv);


	// These must be the same as the semantic effect params in cgfxmaterial!
	enum SemanticEffectParameters{ CGFX_MODELVIEWPROJECTION_PARAMETER = 1,
									 CGFX_MODELVIEW_PARAMETER = 2,
									 CGFX_MODELINVERSETRANSPOSE_PARAMETER = 3,
									 CGFX_MODELTRANSPOSE_PARAMETER = 4,
									 CGFX_WORLDVIEWPROJECTION_PARAMETER = 5,
									 CGFX_WORLD_PARAMETER = 6,
									 CGFX_WORLDINVERSETRANSPOSE_PARAMETER = 7,
									 CGFX_VIEWINVERSE_PARAMETER = 8,
									 CGFX_VIEW_PARAMETER = 9,
									 CGFX_VIEWTRANSPOSE_PARAMETER = 10,
									 CGFX_VIEWINVERSETRANSPOSE_PARAMETER = 11 };


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CgfxRenderPassChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CgfxRenderPassChunk &source);

    // class. Used for indexing in State
    static StateChunkClass _class;
};



typedef CgfxRenderPassChunk *CgfxRenderPassChunkP;

OSG_END_NAMESPACE

#include "OSGCgfxRenderPassChunkBase.inl"
#include "OSGCgfxRenderPassChunk.inl"

#endif /* _OSGCGFXRENDERPASSCHUNK_H_ */
