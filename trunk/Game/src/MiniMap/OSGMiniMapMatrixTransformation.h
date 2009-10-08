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

#ifndef _OSGMINIMAPMATRIXTRANSFORMATION_H_
#define _OSGMINIMAPMATRIXTRANSFORMATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGMiniMapMatrixTransformationBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MiniMapMatrixTransformation class. See \ref 
           PageGameMiniMapMatrixTransformation for a description.
*/

class OSG_GAMELIB_DLLMAPPING MiniMapMatrixTransformation : public MiniMapMatrixTransformationBase
{
  private:

    typedef MiniMapMatrixTransformationBase Inherited;

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
	virtual void transform(Pnt3f& p);
	virtual void transform(Vec3f& v);
	virtual void transform(Quaternion& r);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MiniMapMatrixTransformationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MiniMapMatrixTransformation(void);
    MiniMapMatrixTransformation(const MiniMapMatrixTransformation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MiniMapMatrixTransformation(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MiniMapMatrixTransformationBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MiniMapMatrixTransformation &source);
};

typedef MiniMapMatrixTransformation *MiniMapMatrixTransformationP;

OSG_END_NAMESPACE

#include "OSGMiniMapMatrixTransformationBase.inl"
#include "OSGMiniMapMatrixTransformation.inl"

#endif /* _OSGMINIMAPMATRIXTRANSFORMATION_H_ */
