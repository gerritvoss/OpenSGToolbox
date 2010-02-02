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

#ifndef _OSGLUAERROREVENT_H_
#define _OSGLUAERROREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLuaErrorEventBase.h"
#include "lua.hpp"
#include <list>

OSG_BEGIN_NAMESPACE

/*! \brief LuaErrorEvent class. See \ref
           PageContribLuaLuaErrorEvent for a description.
*/

class OSG_CONTRIBLUA_DLLMAPPING LuaErrorEvent : public LuaErrorEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaErrorEventBase Inherited;
    typedef LuaErrorEvent     Self;

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

    static  LuaErrorEventTransitPtr      create( FieldContainerRefPtr Source,
                                                 Time TimeStamp,
                                                 lua_State* State,
                                                 int LuaStatus,
                                                 const std::list<std::string>& StackTrace,
                                                 bool EnableStackTrace); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LuaErrorEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaErrorEvent(void);
    LuaErrorEvent(const LuaErrorEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaErrorEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaErrorEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaErrorEvent &source);
};

typedef LuaErrorEvent *LuaErrorEventP;

OSG_END_NAMESPACE

#include "OSGLuaErrorEventBase.inl"
#include "OSGLuaErrorEvent.inl"

#endif /* _OSGLUAERROREVENT_H_ */
