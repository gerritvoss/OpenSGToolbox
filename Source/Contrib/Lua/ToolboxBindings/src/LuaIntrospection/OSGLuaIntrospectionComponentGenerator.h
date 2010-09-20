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

#ifndef _OSGLUAINTROSPECTIONCOMPONENTGENERATOR_H_
#define _OSGLUAINTROSPECTIONCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLuaIntrospectionComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LuaIntrospectionComponentGenerator class. See \ref
           PageContribLuaToolboxLuaIntrospectionComponentGenerator for a description.
*/

class OSG_CONTRIBLUATOOLBOX_DLLMAPPING LuaIntrospectionComponentGenerator : public LuaIntrospectionComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LuaIntrospectionComponentGeneratorBase Inherited;
    typedef LuaIntrospectionComponentGenerator     Self;

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

	virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                             const boost::any& Value,
                                             bool IsSelected,
                                             bool Expanded,
                                             bool Leaf,
                                             UInt32 Row,
                                             bool HasFocus);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LuaIntrospectionComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaIntrospectionComponentGenerator(void);
    LuaIntrospectionComponentGenerator(const LuaIntrospectionComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaIntrospectionComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LuaIntrospectionComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LuaIntrospectionComponentGenerator &source);
};

typedef LuaIntrospectionComponentGenerator *LuaIntrospectionComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGLuaIntrospectionComponentGeneratorBase.inl"
#include "OSGLuaIntrospectionComponentGenerator.inl"

#endif /* _OSGLUAINTROSPECTIONCOMPONENTGENERATOR_H_ */
