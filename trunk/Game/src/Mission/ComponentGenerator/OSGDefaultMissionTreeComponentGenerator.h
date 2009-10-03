/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#ifndef _OSGDEFAULTMISSIONTREECOMPONENTGENERATOR_H_
#define _OSGDEFAULTMISSIONTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultMissionTreeComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultMissionTreeComponentGenerator class. See \ref 
           PageGameDefaultMissionTreeComponentGenerator for a description.
*/

class OSG_GAMELIB_DLLMAPPING DefaultMissionTreeComponentGenerator : public DefaultMissionTreeComponentGeneratorBase
{
  private:

    typedef DefaultMissionTreeComponentGeneratorBase Inherited;

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

	ComponentPtr getTreeComponent(TreePtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus);
    
    ComponentPtr getTreeExpandedComponent(TreePtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultMissionTreeComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultMissionTreeComponentGenerator(void);
    DefaultMissionTreeComponentGenerator(const DefaultMissionTreeComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultMissionTreeComponentGenerator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultMissionTreeComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultMissionTreeComponentGenerator &source);
};

typedef DefaultMissionTreeComponentGenerator *DefaultMissionTreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultMissionTreeComponentGeneratorBase.inl"
#include "OSGDefaultMissionTreeComponentGenerator.inl"

#endif /* _OSGDEFAULTMISSIONTREECOMPONENTGENERATOR_H_ */
