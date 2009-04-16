/*---------------------------------------------------------------------------*\
 *                         OpenSG Toolbox Toolbox                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
#ifndef _OSGTOOLBOXDEF_H_
#define _OSGTOOLBOXDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILETOOLBOXLIB
#       define OSG_TOOLBOXLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_TOOLBOXLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_TOOLBOXLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_TOOLBOXLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_TOOLBOXLIB_DLLMAPPING
#define OSG_TOOLBOXLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGTOOLBOXDEF_H_ */
