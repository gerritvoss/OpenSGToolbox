/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#include "OSGGeometryUtils.h"
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGGeoFunctions.h>

OSG_BEGIN_NAMESPACE

void addColorToGeometry(GeometryPtr TheGeometry, const Color4f& TheColor)
{
    //Only supported for non-indexed geometries
    if(TheGeometry->getIndices() != NullFC)
    {
        SWARNING << "addColorToGeometry(): Indexed geometries not supported." << std::endl;
        return;
    }

    GeoColors4fPtr colors = GeoColors4f::create();
    beginEditCP(colors, GeoColors4f::GeoPropDataFieldMask);
        for(UInt32 i(0) ; TheGeometry->getPositions()->size(); ++i)
        {
            colors->getField().push_back(TheColor);
        }
    endEditCP(colors, GeoColors4f::GeoPropDataFieldMask);

    beginEditCP(TheGeometry, Geometry::ColorsFieldMask);
        TheGeometry->setColors(colors);
    endEditCP(TheGeometry, Geometry::ColorsFieldMask);

}

GeometryPrimitivesCounter::GeometryPrimitivesCounter(void) :
    _TriCount(0),
    _LineCount(0),
    _PointCount(0)
{
}

void GeometryPrimitivesCounter::operator() (NodePtr root)
{
    _TriCount = 0;
    _LineCount = 0;
    _PointCount = 0;

    traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef(
        this, 
        &GeometryPrimitivesCounter::check));

}

UInt32 GeometryPrimitivesCounter::getTriCount(void) const
{
    return _TriCount;
}

UInt32 GeometryPrimitivesCounter::getPrimitiveCount(void) const
{
    return _TriCount + _PointCount + _LineCount;
}

UInt32 GeometryPrimitivesCounter::getPointCount(void) const
{
    return _PointCount;
}

UInt32 GeometryPrimitivesCounter::getLineCount(void) const
{
    return _LineCount;
}

Action::ResultE GeometryPrimitivesCounter::check(NodePtr& node)
{
    if(node->getCore() != NullFC &&
       node->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
    {
        UInt32 triangle, point, line;
        calcPrimitiveCount(GeometryPtr::dcast(node->getCore()), triangle, line, point);
        _TriCount += triangle;
        _LineCount += line;
        _PointCount += point;
    }
    //TODO: Add primitives for Particle Systems
	return Action::Continue;
}

OSG_END_NAMESPACE

