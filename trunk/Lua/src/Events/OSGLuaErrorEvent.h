/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef _OSGLUAERROREVENT_H_
#define _OSGLUAERROREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGLuaErrorEventBase.h"
#include "lua.hpp"
#include <list>

OSG_BEGIN_NAMESPACE

/*! \brief LuaErrorEvent class. See \ref 
           PageLuaLuaErrorEvent for a description.
*/

class OSG_LUALIB_DLLMAPPING LuaErrorEvent : public LuaErrorEventBase
{
  private:

    typedef LuaErrorEventBase Inherited;

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

    const lua_State* getLuaState(void) const;
    std::string      getErrorString(void) const;

    static  LuaErrorEventPtr      create( FieldContainerPtr Source,
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LuaErrorEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LuaErrorEvent &source);
};

typedef LuaErrorEvent *LuaErrorEventP;

OSG_END_NAMESPACE

#include "OSGLuaErrorEventBase.inl"
#include "OSGLuaErrorEvent.inl"

#endif /* _OSGLUAERROREVENT_H_ */
