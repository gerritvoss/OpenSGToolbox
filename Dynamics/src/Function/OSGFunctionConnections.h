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

#ifndef _OSGFUNCTIONCONNECTIONS_H_
#define _OSGFUNCTIONCONNECTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGFunctionConnectionsBase.h"
#include "OSGFunction.h"

OSG_BEGIN_NAMESPACE

/*! \brief FunctionConnections class. See \ref 
           PageDynamicsFunctionConnections for a description.
*/

class OSG_DYNAMICSLIB_DLLMAPPING FunctionConnections : public FunctionConnectionsBase
{
  private:

    typedef FunctionConnectionsBase Inherited;

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

	class EvaluationResult
	{
	public:
		EvaluationResult(FunctionPtr Func, FunctionIOParameterVector Output);

		FunctionPtr getFunction(void) const;
		const FunctionIOParameterVector &getOutput(void) const;
	protected:
		FunctionPtr _Function;
		FunctionIOParameterVector _Output;


	};

	bool addConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex);
	bool addConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName);
	
	Int32 findConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex) const;
	Int32 findConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName) const;

	bool removeConnection(Int32 Index);
	bool removeConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex);
	bool removeConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName);

	std::vector<EvaluationResult> evaluate(void);
	UInt32 numConnections(void) const;

	std::vector<FunctionPtr> getRootFunctions(void) const;
	std::vector<FunctionPtr> getLeafFunctions(void) const;

	void validate(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FunctionConnectionsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FunctionConnections(void);
    FunctionConnections(const FunctionConnections &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FunctionConnections(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FunctionConnectionsBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FunctionConnections &source);
};

typedef FunctionConnections *FunctionConnectionsP;

OSG_END_NAMESPACE

#include "OSGFunctionConnectionsBase.inl"
#include "OSGFunctionConnections.inl"

#define OSGFUNCTIONCONNECTIONS_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGFUNCTIONCONNECTIONS_H_ */
