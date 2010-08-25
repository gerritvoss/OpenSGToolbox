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

#ifndef _OSGLUAACTIVITY_H_
#define _OSGLUAACTIVITY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLuaActivityBase.h"
#include "OSGPathType.h"

OSG_BEGIN_NAMESPACE

/*! \brief LuaActivity class. See \ref
           PageContribLuaLuaActivity for a description.
*/

class OSG_CONTRIBLUA_DLLMAPPING LuaActivity : public LuaActivityBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaActivityBase Inherited;
    typedef LuaActivity     Self;

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

    virtual void eventProduced(EventDetails* const details,
                               UInt32 producedEventId);

    static FieldContainerTransitPtr createLuaActivity( const BoostPath& FilePath );

    static boost::signals2::connection addLuaCallback(FieldContainerRefPtr producerObject,
                                            std::string funcName,
                                            UInt32 producedMethodId);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LuaActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaActivity(void);
    LuaActivity(const LuaActivity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaActivity(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    std::vector< std::string > _EntryFunctionPath;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaActivityBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaActivity &source);
};

typedef LuaActivity *LuaActivityP;

OSG_END_NAMESPACE

#include "OSGLuaActivityBase.inl"
#include "OSGLuaActivity.inl"

#endif /* _OSGLUAACTIVITY_H_ */
