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
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#ifndef _OPENSG_GEOPROPERTYUTILS_H_
#define _OPENSG_GEOPROPERTYUTILS_H_

#include "OSGConfig.h"
#include "OSGTBAnimationDef.h"

#include "OSGGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/*!
 * \brief Sets all of the values of a GeoVectorProperty to the "zero" of the
 * data type contained by the property.
 *
 * \param[out] GeoProp The Geometry property to zero.
 */
void OSG_TBANIMATION_DLLMAPPING zeroGeoProperty(GeoVectorProperty* GeoProp);

/*!
 * \brief Helper function used by the non-templated
 * zeroGeoProperty(GeoVectorProperty* GeoProp) 
 *
 * \param[out] GeoProp The Geometry property to zero.
 */
template<class TypeT>
void OSG_TBANIMATION_DLLMAPPING zeroGeoPropertyTmpl(GeoVectorProperty* GeoProp);

/*!
 * \brief Helper function used by the non-templated
 * zeroGeoProperty(GeoVectorProperty* GeoProp) 
 *
 * \param[out] GeoProp The Geometry property to zero.
 */
template<class TypeT>
void zeroNormGeoPropertyTmpl(GeoVectorProperty* GeoProp);

/*!
 * \brief Morphs the values of a GeoVectorProperty by a given weight between a
 * BaseGeomProp and a TargetGeoProp
 *
 * \param[in] TargetGeoProp The Target GeoProperty
 * \param[out] ResultGeoProp The GeoProperty to apply the morph to
 * \param[in] Weight The weight of morph between the base and target properties.
 */
void morphGeoProperty(GeoVectorProperty* TargetGeoProp,
                      GeoVectorProperty* ResultGeoProp,
                      Real32 Weight);

/*!
 * \brief Helper function used by the non-templated
 * morphGeoProperty() 
 *
 * \param[in] TargetGeoProp The Target GeoProperty
 * \param[out] ResultGeoProp The GeoProperty to apply the morph to
 * \param[in] Weight The weight of morph between the base and target properties.
 */
template<class TypeT>
void morphGeoPropertyTmpl(GeoVectorProperty* TargetGeoProp,
                          GeoVectorProperty* ResultGeoProp,
                          Real32 Weight);

/*!
 * \brief Helper function used by the non-templated
 * morphGeoProperty() for GeoProperties that represent normalized vectors.
 *
 * \param[in] TargetGeoProp The Target GeoProperty
 * \param[out] ResultGeoProp The GeoProperty to apply the morph to
 * \param[in] Weight The weight of morph between the base and target properties.
 */
template<class TypeT>
void morphNormGeoPropertyTmpl(GeoVectorProperty* TargetGeoProp,
                              GeoVectorProperty* ResultGeoProp,
                              Real32 Weight);

OSG_END_NAMESPACE

#include "OSGGeoPropertyUtils.inl"

#endif


