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

// Source file for new Field type

// This define is only set in this source file. It switches the
// Windows-specific declarations in the header for compiling the Field, 
// not for using it.
#define OSG_COMPILESTRINGTOUINT32MAPTYPEINST

// You need this in every OpenSG file
#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

// Some basic system headers
#include <OpenSG/OSGBaseTypes.h>

// The new field type include
#include "OSGStringToUInt32MapType.h"

// Needed to instantiate some template functions on Windows
#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldDataTraits<StringToUInt32Map>::_type("StringToUInt32Map", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_DLLEXPORT_SFIELD_DEF1(StringToUInt32Map, OSG_TOOLBOXLIB_DLLTMPLMAPPING );

OSG_DLLEXPORT_MFIELD_DEF1(StringToUInt32Map, OSG_TOOLBOXLIB_DLLTMPLMAPPING );

OSG_END_NAMESPACE

