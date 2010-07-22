/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),                            *
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

#ifndef _OSGMORPHGEOMETRY_H_
#define _OSGMORPHGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMorphGeometryBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MorphGeometry class. See \ref
           PageTBAnimationMorphGeometry for a description.
*/

class OSG_TBANIMATION_DLLMAPPING MorphGeometry : public MorphGeometryBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MorphGeometryBase Inherited;
    typedef MorphGeometry     Self;

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
    void addMorphTarget(Geometry * const Target, Real32 Weight);
    //void removeMorphTarget(Geometry * const Target);
    //void removeMorphTarget(UInt32 Index);
    void clearMorphTargets(void);

    void setMorphTarget(UInt32 Index, Geometry * const Target);
    void setMorphTargetWeight(UInt32 Index, Real32 Weight);

    UInt32 getNumMorphTargets(void) const;
    Geometry* getMorphTarget(UInt32 Index) const;
    Int32 getMorphTargetIndex(Geometry * const Target) const;
    Real32 getMorphTargetWeight(UInt32 Index) const;
    Real32 getMorphTargetWeight(Geometry * const Target) const;

    template<class TypeT>
    static void morphProperty(GeoVectorProperty* BaseGeoProp,
                              GeoVectorProperty* TargetGeoProp,
                              GeoVectorProperty* ResultGeoProp,
                              Real32 Weight);

    template<class TypeT>
    static void morphNormProperty(GeoVectorProperty* BaseGeoProp,
                                  GeoVectorProperty* TargetGeoProp,
                                  GeoVectorProperty* ResultGeoProp,
                                  Real32 Weight);

    GeoVectorProperty*   getWeights      (void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MorphGeometryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MorphGeometry(void);
    MorphGeometry(const MorphGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MorphGeometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MorphGeometry *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

	void updateMorph(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MorphGeometryBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MorphGeometry &source);
};

typedef MorphGeometry *MorphGeometryP;

OSG_END_NAMESPACE

#include "OSGMorphGeometryBase.inl"
#include "OSGMorphGeometry.inl"

#endif /* _OSGMORPHGEOMETRY_H_ */
