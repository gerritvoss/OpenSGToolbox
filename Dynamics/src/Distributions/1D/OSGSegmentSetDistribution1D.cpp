/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>

#include "OSGSegmentSetDistribution1D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SegmentSetDistribution1D
An SegmentSetDistribution1D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SegmentSetDistribution1D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

SegmentSetDistribution1D::FunctionIOTypeVector SegmentSetDistribution1D::getOutputTypes(FunctionIOParameterVector& InputParameters) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_SEGMENTSET_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

SegmentSetDistribution1D::FunctionIOTypeVector SegmentSetDistribution1D::getInputTypes(FunctionIOParameterVector& InputParameters) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

SegmentSetDistribution1D::FunctionIOParameterVector SegmentSetDistribution1D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_SEGMENTSET_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_SEGMENTSET_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_SEGMENTSET_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Real32 SegmentSetDistribution1D::generate(void)
{
    Real32 PickSegment(RandomPoolManager::getRandomReal32(0.0,1.0));
    Real32 CumLength(0.0);

    for(UInt32 i(0) ; i< getSegment().size() ; ++i)
    {
        CumLength += osgabs(getSegment()[i][1] - getSegment()[i][0]);
        if(PickSegment < CumLength/getTotalLength())
        {
            return RandomPoolManager::getRandomReal32(getSegment()[i][0],getSegment()[i][1]);
        }
    }

    return 0.0f;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SegmentSetDistribution1D::SegmentSetDistribution1D(void) :
    Inherited()
{
}

SegmentSetDistribution1D::SegmentSetDistribution1D(const SegmentSetDistribution1D &source) :
    Inherited(source)
{
}

SegmentSetDistribution1D::~SegmentSetDistribution1D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SegmentSetDistribution1D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & SegmentFieldMask)
    {
        Real32 TotalLength(0.0);
        for(UInt32 i(0) ; i< getSegment().size() ; ++i)
        {
            TotalLength += osgabs(getSegment()[i][1] - getSegment()[i][0]);
        }
        beginEditCP(SegmentSetDistribution1DPtr(this), TotalLengthFieldMask);
            setTotalLength(TotalLength);
        endEditCP(SegmentSetDistribution1DPtr(this), TotalLengthFieldMask);
    }
}

void SegmentSetDistribution1D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SegmentSetDistribution1D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSEGMENTSETDISTRIBUTION1DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSEGMENTSETDISTRIBUTION1DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSEGMENTSETDISTRIBUTION1DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

