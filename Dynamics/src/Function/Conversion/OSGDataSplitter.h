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

#ifndef _OSGDATASPLITTER_H_
#define _OSGDATASPLITTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"

#include "OSGDataSplitterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DataSplitter class. See \ref 
           PageDynamicsDataSplitter for a description.
*/

class OSG_DYNAMICSLIB_DLLMAPPING DataSplitter : public DataSplitterBase
{
  private:

    typedef DataSplitterBase Inherited;

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
    virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DataSplitterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DataSplitter(void);
    DataSplitter(const DataSplitter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DataSplitter(void); 

	static void addSplitOutputTypes(FunctionIOTypeVector& OutputTypes, const FunctionIOType& InputType);
	static void addSplitOutputData(FunctionIOParameterVector& OutputData, const FunctionIOParameter& InputParameter);
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DataSplitterBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DataSplitter &source);
};

typedef DataSplitter *DataSplitterP;

OSG_END_NAMESPACE

#include "OSGDataSplitterBase.inl"
#include "OSGDataSplitter.inl"

#define OSGDATASPLITTER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDATASPLITTER_H_ */
