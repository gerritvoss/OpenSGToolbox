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

#ifndef _OSGCGFXMATERIAL_H_
#define _OSGCGFXMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCgfxMaterialBase.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

OSG_BEGIN_NAMESPACE

/*! \brief CgfxMaterial class. See \ref
           PageStateCgfxMaterial for a description.
*/

class OSG_STATE_DLLMAPPING CgfxMaterial : public CgfxMaterialBase
{
  protected:
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
									 CGFX_VIEWINVERSETRANSPOSE_PARAMETER = 11 	};

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CgfxMaterialBase Inherited;
    typedef CgfxMaterial     Self;

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
    virtual PrimeMaterial *finalize(MaterialMapKey oKey);                                                        

    virtual void    rebuildState(void            ) ;
    virtual State  *getState    (UInt32 index = 0);
    virtual UInt32  getNPasses  (void            );
    virtual bool           isTransparent(void               ) const;

	/*! Initialize from a CGFX file */
	bool initFromFile(const char* filename, const char** args = NULL);

	/*! Get number of parameters being used for this material */
	Int32 getNumParameters();

	/*! Get names of available parameters */
	std::vector<std::string> getParameterNames();

	/*! Functions to retrieve parameters from the material */
	Int32 getParami(std::string paramName);
	Real32 getParamf(std::string paramName);
	Real64 getParamd(std::string paramName);
	OSG::Vec2f getParam2f(std::string paramName);
	OSG::Vec3f getParam3f(std::string paramName);
	OSG::Vec4f getParam4f(std::string paramName);
	OSG::Vec2d getParam2d(std::string paramName);
	OSG::Vec3d getParam3d(std::string paramName);
	OSG::Vec4d getParam4d(std::string paramName);
	
	template<UInt8 Rows, UInt8 Cols>
	OSG::Matrix4f getParamMatrixf(std::string paramName);

	template<UInt8 Rows, UInt8 Cols>
	OSG::Matrix4d getParamMatrixd(std::string paramName);

	/*! Functions to set parameter values */
	void setParam(std::string paramName, Int32 val);
	void setParam(std::string paramName, Real32 val);
	void setParam(std::string paramName, Real64 val);
	void setParam(std::string paramName, Vec2f val);
	void setParam(std::string paramName, Vec3f val);
	void setParam(std::string paramName, Vec4f val);
	void setParam(std::string paramName, Vec2d val);
	void setParam(std::string paramName, Vec3d val);
	void setParam(std::string paramName, Vec4d val);

	template<UInt8 Rows, UInt8 Cols>
	void setParamMatrixf(std::string paramName, Matrix4f val);

	template<UInt8 Rows, UInt8 Cols>
	void setParamMatrixd(std::string paramName, Matrix4d val);
	

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CgfxMaterialBase.
	// flag for initializing effect from string
	bool _mRebuildFromString;
	// string for holding the contents of the file
	std::string _mEffectFile;
	// for holding on to the args from a failed init
	const char ** _mArgHolder;
	// Each CgfxMaterial = one CGFX effect
    CGeffect _mCGeffect;
	// context shared by materials
	static CGcontext _mCGcontext;


	void extractTextureAndSamplerData(CGpass pass);
    static bool checkForCgError(const char *situation);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CgfxMaterial(void);
    CgfxMaterial(const CgfxMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CgfxMaterial(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

	// Initializes and adds states.  Assumes that _mCGeffect is properly initialized.
	void initializeStates(void);

	UInt32 getEffectMatrixDependencies(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CgfxMaterialBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CgfxMaterial &source);
};

typedef CgfxMaterial *CgfxMaterialP;

//exception class for handling errors 
#include <exception>

class UndefinedParameterException: public std::exception
{
public:
  const char* what() const throw()
  {
    return "An undefined CGparameter was attempted to be accessed.";
  }
};

OSG_END_NAMESPACE


#include "OSGCgfxMaterialBase.inl"
#include "OSGCgfxMaterial.inl"

#endif /* _OSGCGFXMATERIAL_H_ */
