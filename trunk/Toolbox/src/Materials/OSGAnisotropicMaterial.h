/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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

#ifndef _OSGANISOTROPICMATERIAL_H_
#define _OSGANISOTROPICMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAnisotropicMaterialBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnisotropicMaterial class. See \ref 
           PageToolboxAnisotropicMaterial for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING AnisotropicMaterial : public AnisotropicMaterialBase
{
  private:

    typedef AnisotropicMaterialBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AnisotropicMaterialBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnisotropicMaterial(void);
    AnisotropicMaterial(const AnisotropicMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnisotropicMaterial(void); 

    /*! \}                                                                 */
    virtual void internalCreateShaderParameters(void);
    virtual void internalUpdateShaderParameters(UInt8& NumTextures, UInt8& ParamIndex);
    virtual void internalAttachChunks(void);

    virtual bool shouldRecreateChunks(BitVector FieldMask) const;
    virtual bool shouldUpdateParameters(BitVector FieldMask) const;

    virtual std::string generateVertexCode(void);
    virtual std::string generateFragmentCode(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AnisotropicMaterialBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AnisotropicMaterial &source);
};

typedef AnisotropicMaterial *AnisotropicMaterialP;

OSG_END_NAMESPACE

#include "OSGAnisotropicMaterialBase.inl"
#include "OSGAnisotropicMaterial.inl"

#endif /* _OSGANISOTROPICMATERIAL_H_ */
