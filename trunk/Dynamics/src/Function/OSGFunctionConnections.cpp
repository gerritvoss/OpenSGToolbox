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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFunctionConnections.h"
#include <set>
#include <algorithm>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FunctionConnections
A Function Connection Hierarchy. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FunctionConnections::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


bool FunctionConnections::addConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex)
{
	if(Output != NullFC && Input != NullFC)
	{
		beginEditCP(FunctionConnectionsPtr(this), FunctionOutputsFieldMask |FunctionInputsFieldMask |FunctionOutputIndexFieldMask |FunctionInputIndexFieldMask);
			getFunctionOutputs().push_back(Output);
			getFunctionInputs().push_back(Input);
			getFunctionOutputIndex().push_back(OutputIndex);
			getFunctionInputIndex().push_back(InputIndex);
		endEditCP(FunctionConnectionsPtr(this), FunctionOutputsFieldMask |FunctionInputsFieldMask |FunctionOutputIndexFieldMask |FunctionInputIndexFieldMask);
		return true;
	}
	else
	{
		return false;
	}
}

bool FunctionConnections::addConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName)
{
	if(Output != NullFC && Input != NullFC)
	{
		//TODO: Implement
		assert(false && "Not Implemented" );
		return true;
	}
	else
	{
		return false;
	}
}

Int32 FunctionConnections::findConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex) const
{
	if(Output != NullFC && Input != NullFC)
	{
		for(UInt32 i(0) ; i<numConnections() ; ++i)
		{
			if(getFunctionOutputs()[i] == Output &&
				getFunctionInputs()[i] == Input &&
				getFunctionOutputIndex()[i] == OutputIndex &&
				getFunctionInputIndex()[i] == InputIndex
				)
			{
				return i;
			}
		}
	}
	return -1;
}

Int32 FunctionConnections::findConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName) const
{
	//TODO: Implement
		assert(false && "Not Implemented" );
	return -1;
}

bool FunctionConnections::removeConnection(Int32 Index)
{
	if(Index >= 0 && Index < numConnections())
	{
		MFFunctionPtr::iterator FunctionIter;
		MFUInt32::iterator UInt32Iter;

		beginEditCP(FunctionConnectionsPtr(this), FunctionOutputsFieldMask |FunctionInputsFieldMask |FunctionOutputIndexFieldMask |FunctionInputIndexFieldMask);
			FunctionIter = getFunctionOutputs().begin();
			FunctionIter += Index;
			getFunctionOutputs().erase(FunctionIter);
			FunctionIter = getFunctionInputs().begin();
			FunctionIter += Index;
			getFunctionInputs().erase(FunctionIter);
			UInt32Iter = getFunctionOutputIndex().begin();
			UInt32Iter += Index;
			getFunctionOutputIndex().erase(UInt32Iter);
			UInt32Iter = getFunctionInputIndex().begin();
			UInt32Iter += Index;
			getFunctionInputIndex().erase(UInt32Iter);
		endEditCP(FunctionConnectionsPtr(this), FunctionOutputsFieldMask |FunctionInputsFieldMask |FunctionOutputIndexFieldMask |FunctionInputIndexFieldMask);

		return true;
	}
	else
	{
		return false;
	}
}

bool FunctionConnections::removeConnection(FunctionPtr Output, FunctionPtr Input, UInt32 OutputIndex, UInt32 InputIndex)
{
	Int32 Index(findConnection(Output, Input, OutputIndex, InputIndex));
	if(Index >= 0 && Index < numConnections())
	{
		return removeConnection(Index);
	}
	else
	{
		return false;
	}
}

bool FunctionConnections::removeConnection(FunctionPtr Output, FunctionPtr Input, std::string OutputName, std::string InputName)
{
	Int32 Index(findConnection(Output, Input, OutputName, InputName));
	if(Index >= 0 && Index < numConnections())
	{
		return removeConnection(Index);
	}
	else
	{
		return false;
	}
}

std::vector<FunctionConnections::EvaluationResult> FunctionConnections::evaluate(void)
{
	//TODO: Implement
	assert(false && "Not Implemented" );

	std::vector<EvaluationResult> Result;

    //Get all of the Root Functions
    std::vector<FunctionPtr> CurFunctions;
    std::vector<FunctionPtr> NextFunctions(getRootFunctions());
    std::vector<FunctionIOParameterVector> FunctionEvaluations;

    //Evaluate the hierarchy
     while(NextFunctions.size() > 0)
    {
        CurFunctions = NextFunctions;

        FunctionEvaluations.clear();
        for(UInt32 i(0) ; i<CurFunctions.size() ; ++i)
        {
            FunctionIOParameterVector Params;
            FunctionEvaluations.push_back(CurFunctions[i]->evaluate(Params));
        }
        
        NextFunctions.clear();
	    for(UInt32 i(0) ; i<numConnections() ; ++i)
	    {
            if(std::find(CurFunctions.begin(), CurFunctions.end(), getFunctionOutputs()[i]) != CurFunctions.end())
            {
                NextFunctions.push_back(getFunctionInputs()[i]);
            }
        }

    }

    //Place the evaluations of the leaf nodes in the result
    for(UInt32 i(0) ; CurFunctions.size(); ++i)
    {
        Result.push_back(EvaluationResult(CurFunctions[i],FunctionEvaluations[i] ));
    }


	return Result;
}

UInt32 FunctionConnections::numConnections(void) const
{
	return getFunctionOutputs().size();
}

std::vector<FunctionPtr> FunctionConnections::getRootFunctions(void) const
{	
    std::vector<FunctionPtr> Result;
    
    std::set<FunctionPtr> FunctionOutputConnected;
    std::set<FunctionPtr> FunctionInputConnected;
	for(UInt32 i(0) ; i<numConnections() ; ++i)
	{
        FunctionOutputConnected.insert(getFunctionOutputs()[i]);
        FunctionInputConnected.insert(getFunctionInputs()[i]);
    }

    std::set_difference(FunctionInputConnected.begin(), FunctionInputConnected.end(), FunctionOutputConnected.begin(), FunctionOutputConnected.end(),std::inserter(Result, Result.end()));

	return Result;
}

std::vector<FunctionPtr> FunctionConnections::getLeafFunctions(void) const
{
    std::vector<FunctionPtr> Result;
    
    std::set<FunctionPtr> FunctionOutputConnected;
    std::set<FunctionPtr> FunctionInputConnected;
	for(UInt32 i(0) ; i<numConnections() ; ++i)
	{
        FunctionOutputConnected.insert(getFunctionOutputs()[i]);
        FunctionInputConnected.insert(getFunctionInputs()[i]);
    }

    std::set_difference(FunctionOutputConnected.begin(), FunctionOutputConnected.end(), FunctionInputConnected.begin(), FunctionInputConnected.end(),std::inserter(Result, Result.end()));

	return Result;
}

void FunctionConnections::validate(void)
{
	//TODO: Implement
	assert(false && "Not Implemented" );
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FunctionConnections::FunctionConnections(void) :
    Inherited()
{
}

FunctionConnections::FunctionConnections(const FunctionConnections &source) :
    Inherited(source)
{
}

FunctionConnections::~FunctionConnections(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FunctionConnections::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FunctionConnections::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FunctionConnections NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFUNCTIONCONNECTIONSBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFUNCTIONCONNECTIONSBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFUNCTIONCONNECTIONSFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

