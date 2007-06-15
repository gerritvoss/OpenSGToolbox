#include "Util/OSGGeoPropertyOperations.h"

//Colors
osg::GeoColorsPtr osg::createEmptyFromBase(osg::GeoColorsPtr Base)
{
   if( strcmp( Base->getTypeName(), osg::GeoColors3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors3f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoColors4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors4f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoColors3ubPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors3ub::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoColors4ubPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors4ub::create();
   }
   else
   {
      return osg::NullFC;
   }
}

void osg::addValueAsBaseType(osg::GeoColorsPtr Dst, const osg::GeoColorsPtr Src,
                        const osg::UInt32 SrcIndex)
{
   if(strcmp( Dst->getTypeName(), Src->getTypeName()) == 0)
   {
      if( strcmp( Dst->getTypeName(), osg::GeoColors3fPropertyDesc::getTypeName()) == 0 )
      {
         GeoColors3fPtr::dcast(Dst)->getField().addValue( GeoColors3fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoColors4fPropertyDesc::getTypeName()) == 0 )
      {
         GeoColors4fPtr::dcast(Dst)->getField().addValue( GeoColors4fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoColors3ubPropertyDesc::getTypeName()) == 0 )
      {
         GeoColors3ubPtr::dcast(Dst)->getField().addValue( GeoColors3ubPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoColors4ubPropertyDesc::getTypeName()) == 0 )
      {
         GeoColors4ubPtr::dcast(Dst)->getField().addValue( GeoColors4ubPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
   }
}

osg::Field* osg::getField(osg::GeoColorsPtr Colors)
{
   if( strcmp( Colors->getTypeName(), osg::GeoColors3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors3fPtr::dcast(Colors)->getFieldPtr();
   }
   else if( strcmp( Colors->getTypeName(), osg::GeoColors4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors4fPtr::dcast(Colors)->getFieldPtr();
   }
   else if( strcmp( Colors->getTypeName(), osg::GeoColors3ubPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors3ubPtr::dcast(Colors)->getFieldPtr();
   }
   else if( strcmp( Colors->getTypeName(), osg::GeoColors4ubPropertyDesc::getTypeName()) == 0 )
   {
      return GeoColors4ubPtr::dcast(Colors)->getFieldPtr();
   }
   else
   {
      return NULL;
   }
}

//Normals
osg::GeoNormalsPtr osg::createEmptyFromBase(osg::GeoNormalsPtr Base)
{
   if( strcmp( Base->getTypeName(), osg::GeoNormals3bPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3b::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoNormals3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoNormals3sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3s::create();
   }
   else
   {
      return osg::NullFC;
   }
}

void osg::addValueAsBaseType(osg::GeoNormalsPtr Dst, const osg::GeoNormalsPtr Src,
                        const osg::UInt32 SrcIndex)
{
   if(strcmp( Dst->getTypeName(), Src->getTypeName()) == 0)
   {
      if( strcmp( Dst->getTypeName(), osg::GeoNormals3bPropertyDesc::getTypeName()) == 0 )
      {
         GeoNormals3bPtr::dcast(Dst)->getField().addValue( GeoNormals3bPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoNormals3fPropertyDesc::getTypeName()) == 0 )
      {
         GeoNormals3fPtr::dcast(Dst)->getField().addValue( GeoNormals3fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoNormals3sPropertyDesc::getTypeName()) == 0 )
      {
         GeoNormals3sPtr::dcast(Dst)->getField().addValue( GeoNormals3sPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
   }
}

osg::Field* osg::getField(osg::GeoNormalsPtr Norms)
{
   if( strcmp( Norms->getTypeName(), osg::GeoNormals3bPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3bPtr::dcast(Norms)->getFieldPtr();
   }
   else if( strcmp( Norms->getTypeName(), osg::GeoNormals3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3fPtr::dcast(Norms)->getFieldPtr();
   }
   else if( strcmp( Norms->getTypeName(), osg::GeoNormals3sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoNormals3sPtr::dcast(Norms)->getFieldPtr();
   }
   else
   {
      return NULL;
   }
}

//Positions
osg::GeoPositionsPtr osg::createEmptyFromBase(osg::GeoPositionsPtr Base)
{
   if( strcmp( Base->getTypeName(), osg::GeoPositions2sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2s::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions2fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions2dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2d::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions3sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3s::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions3dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3d::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions4sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4s::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoPositions4dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4d::create();
   }
   else
   {
      return osg::NullFC;
   }
}

void osg::addValueAsBaseType(osg::GeoPositionsPtr Dst, const osg::GeoPositionsPtr Src,
                        const osg::UInt32 SrcIndex)
{
   if(strcmp( Dst->getTypeName(), Src->getTypeName()) == 0)
   {
      if( strcmp( Dst->getTypeName(), osg::GeoPositions2sPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions2sPtr::dcast(Dst)->getField().addValue( GeoPositions2sPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions2fPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions2fPtr::dcast(Dst)->getField().addValue( GeoPositions2fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions2dPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions2dPtr::dcast(Dst)->getField().addValue( GeoPositions2dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions3sPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions3sPtr::dcast(Dst)->getField().addValue( GeoPositions3sPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions3fPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions3fPtr::dcast(Dst)->getField().addValue( GeoPositions3fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions3dPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions3dPtr::dcast(Dst)->getField().addValue( GeoPositions3dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions4sPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions4sPtr::dcast(Dst)->getField().addValue( GeoPositions4sPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions4fPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions4fPtr::dcast(Dst)->getField().addValue( GeoPositions4fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoPositions4dPropertyDesc::getTypeName()) == 0 )
      {
         GeoPositions4dPtr::dcast(Dst)->getField().addValue( GeoPositions4dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
   }
}

osg::Field* osg::getField(osg::GeoPositionsPtr Pos)
{
   if( strcmp( Pos->getTypeName(), osg::GeoPositions2sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2sPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions2fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2fPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions2dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions2dPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions3sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3sPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3fPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions3dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions3dPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions4sPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4sPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4fPtr::dcast(Pos)->getFieldPtr();
   }
   else if( strcmp( Pos->getTypeName(), osg::GeoPositions4dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoPositions4dPtr::dcast(Pos)->getFieldPtr();
   }
   else
   {
      return NULL;
   }
}
//TexCoords
osg::GeoTexCoordsPtr osg::createEmptyFromBase(osg::GeoTexCoordsPtr Base)
{
   if( strcmp( Base->getTypeName(), osg::GeoTexCoords1fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords1f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords1dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords1d::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords2fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords2f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords2dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords2d::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords3f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords3dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords3d::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords4f::create();
   }
   else if( strcmp( Base->getTypeName(), osg::GeoTexCoords4dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords4d::create();
   }
   else
   {
      return osg::NullFC;
   }
}

void osg::addValueAsBaseType(osg::GeoTexCoordsPtr Dst, const osg::GeoTexCoordsPtr Src,
                        const osg::UInt32 SrcIndex)
{
   if(strcmp( Dst->getTypeName(), Src->getTypeName()) == 0)
   {
      if( strcmp( Dst->getTypeName(), osg::GeoTexCoords1fPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords1fPtr::dcast(Dst)->getField().addValue( GeoTexCoords1fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords1dPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords1dPtr::dcast(Dst)->getField().addValue( GeoTexCoords1dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords2fPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords2fPtr::dcast(Dst)->getField().addValue( GeoTexCoords2fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords2dPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords2dPtr::dcast(Dst)->getField().addValue( GeoTexCoords2dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords3fPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords3fPtr::dcast(Dst)->getField().addValue( GeoTexCoords3fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords3dPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords3dPtr::dcast(Dst)->getField().addValue( GeoTexCoords3dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords4fPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords4fPtr::dcast(Dst)->getField().addValue( GeoTexCoords4fPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
      else if( strcmp( Dst->getTypeName(), osg::GeoTexCoords4dPropertyDesc::getTypeName()) == 0 )
      {
         GeoTexCoords4dPtr::dcast(Dst)->getField().addValue( GeoTexCoords4dPtr::dcast(Src)->getField().getValue(SrcIndex) );
      }
   }
}

osg::Field* osg::getField(osg::GeoTexCoordsPtr Coords)
{
   if( strcmp( Coords->getTypeName(), osg::GeoTexCoords1fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords1fPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords1dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords1dPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords2fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords2fPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords2dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords2dPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords3fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords3fPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords3dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords3dPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords4fPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords4fPtr::dcast(Coords)->getFieldPtr();
   }
   else if( strcmp( Coords->getTypeName(), osg::GeoTexCoords4dPropertyDesc::getTypeName()) == 0 )
   {
      return GeoTexCoords4dPtr::dcast(Coords)->getFieldPtr();
   }
   else
   {
      return NULL;
   }
}
