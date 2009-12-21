/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
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
 * This library is free software you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library if not, write to the Free Software       *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, bool   value       )
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, Int32  value       )
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, Real32 value       )
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const Vec2f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const Vec3f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const Vec4f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const Matrix &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}


inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFInt32  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFReal32 &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFVec2f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFVec3f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFVec4f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::setUniformParameter(const char *name, const MFMatrix &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}


inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, bool   &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Int32  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Real32 &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Vec2f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Vec3f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Vec4f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, Matrix &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFInt32  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFReal32 &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFVec2f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFVec3f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFVec4f  &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}

inline
bool    ShaderTextureFilter::getUniformParameter(const char *name, MFMatrix &value)
{
    getInternalParameters()->setUniformParameter(name,value);
}


OSG_END_NAMESPACE

