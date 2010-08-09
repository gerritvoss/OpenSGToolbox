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

#ifndef _OSGLUAERROREVENTDETAILS_H_
#define _OSGLUAERROREVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLuaErrorEventDetailsBase.h"
#include "lua.hpp"
#include <list>

OSG_BEGIN_NAMESPACE

/*! \brief LuaErrorEventDetails class. See \ref
           PageContribLuaLuaErrorEventDetails for a description.
*/

class OSG_CONTRIBLUA_DLLMAPPING LuaErrorEventDetails : public LuaErrorEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaErrorEventDetailsBase Inherited;
    typedef LuaErrorEventDetails     Self;

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

    const lua_State* getLuaState(void) const;

    std::string      getErrorString(void) const;

    static  LuaErrorEventDetailsTransitPtr      create( FieldContainer* const Source,
                                                 Time TimeStamp,
                                                 lua_State* State,
                                                 int LuaStatus,
                                                 const std::list<std::string>& StackTrace,
                                                 bool EnableStackTrace); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LuaErrorEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaErrorEventDetails(void);
    LuaErrorEventDetails(const LuaErrorEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaErrorEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaErrorEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaErrorEventDetails &source);
};

typedef LuaErrorEventDetails *LuaErrorEventDetailsP;

OSG_END_NAMESPACE

#include "OSGLuaErrorEventDetailsBase.inl"
#include "OSGLuaErrorEventDetails.inl"

#endif /* _OSGLUAERROREVENTDETAILS_H_ */
