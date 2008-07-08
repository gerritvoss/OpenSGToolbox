/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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

#ifndef _OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATOR_H_
#define _OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDefaultFunctionComponentIOTabComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultFunctionComponentIOTabComponentGenerator class. See \ref 
           PageUserInterfaceDefaultFunctionComponentIOTabComponentGenerator for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultFunctionComponentIOTabComponentGenerator : public DefaultFunctionComponentIOTabComponentGeneratorBase
{
  private:

    typedef DefaultFunctionComponentIOTabComponentGeneratorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum TextSource {TEXT_SOURCE_TYPE_NAME};

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
    virtual ComponentPtr getIOTabComponent(FunctionComponentPtr Parent, const FunctionIOType& Value, UInt32 Index, bool IsSelected, bool HasFocus, bool isDragFrom, bool isDragTo);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultFunctionComponentIOTabComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultFunctionComponentIOTabComponentGenerator(void);
    DefaultFunctionComponentIOTabComponentGenerator(const DefaultFunctionComponentIOTabComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultFunctionComponentIOTabComponentGenerator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultFunctionComponentIOTabComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultFunctionComponentIOTabComponentGenerator &source);
};

typedef DefaultFunctionComponentIOTabComponentGenerator *DefaultFunctionComponentIOTabComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultFunctionComponentIOTabComponentGeneratorBase.inl"
#include "OSGDefaultFunctionComponentIOTabComponentGenerator.inl"

#define OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATOR_H_ */
