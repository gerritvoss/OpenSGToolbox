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

#ifndef _OSGFUNCTION_H_
#define _OSGFUNCTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"

#include "OSGFunctionBase.h"

#include <exception>

#include <boost/shared_ptr.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define OSG_FUNC_IOPARAMETERARRAY_SIZE(parameterArray) BOOST_PP_ARRAY_SIZE(parameterArray)

#define OSG_FUNC_IOPARAMETER_NAME(index, parameterArray) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_ARRAY_ELEM(index, parameterArray))

#define OSG_FUNC_IOPARAMETER_TYPE(index, parameterArray) FieldDataTraits<BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_ARRAY_ELEM(index, parameterArray))>::getType()

#define OSG_FUNC_IOPARAMETER_DATA(index, parameterArray) osg::Function::FunctionIOData<BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_ARRAY_ELEM(index, parameterArray))>

#define OSG_FUNC_INST_FUNCTIONIOTYPE(index, parameterArray) osg::Function::FunctionIOType(OSG_FUNC_IOPARAMETER_NAME(index,parameterArray), &OSG_FUNC_IOPARAMETER_TYPE(index,parameterArray))

#define OSG_FUNC_INST_FUNCTIONIOPARAMETER(index, parameterArray, value) osg::Function::FunctionIOParameter(OSG_FUNC_IOPARAMETER_NAME(index, parameterArray), new OSG_FUNC_IOPARAMETER_DATA(index, parameterArray)(value))

#define OSG_FUNC_IOPARAMETER_GET_DATA(index, parameterArray, parameterVector) FunctionIOData<BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_ARRAY_ELEM(index, parameterArray))>::dcast(parameterVector[index].getDataPtr())->getData()

OSG_BEGIN_NAMESPACE

class OSG_DYNAMICSLIB_DLLMAPPING FunctionException : public std::exception
{
};

class OSG_DYNAMICSLIB_DLLMAPPING FunctionInputException : public FunctionException
{
    virtual const char* what() const throw();
};

class OSG_DYNAMICSLIB_DLLMAPPING FunctionBadTypeException : public FunctionException
{
    virtual const char* what() const throw();
};

class OSG_DYNAMICSLIB_DLLMAPPING Function : public FunctionBase
{
  private:
    typedef FunctionBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    class FunctionIOType{
	private:
        std::string _IOParameterName;
        const DataType* _Type;
	public:
        FunctionIOType(const std::string& name, const DataType* type) :
           _IOParameterName(name),
           _Type(type)
        {
        }

	    const DataType* getType(void) const;
		std::string getParameterName(void) const;
    };

    class FunctionIODataBase
    {
      public:
        virtual const DataType* getType(void) const = 0;
    };

    template<class RawTypeT>
    class FunctionIOData : public FunctionIODataBase
    {
      public:
        typedef RawTypeT RawType;

      protected:
        typedef FunctionIODataBase Inherited;
        RawType _Data;

      public:

        FunctionIOData(RawTypeT data) : _Data(data)
        {
        }

        virtual const DataType* getType(void) const
        {
            return &FieldDataTraits<RawTypeT>::getType();
        }

        static FunctionIOData<RawTypeT>* dcast(FunctionIODataBase* Value)
        {
            return dynamic_cast< FunctionIOData<RawTypeT>* >(Value);
        }

        static const FunctionIOData<RawTypeT>* dcast(const FunctionIODataBase* Value)
        {
            return dynamic_cast< const FunctionIOData<RawTypeT>* >(Value);
        }

        const RawType& getData(void) const
        {
            return _Data;
        }
    };
	
    template<class RawFieldTypeT>
    class FunctionIOFieldData : public FunctionIODataBase
    {
      public:
        typedef RawFieldTypeT RawType;

      protected:
        typedef FunctionIODataBase Inherited;
        RawFieldTypeT _Data;

      public:

        FunctionIOFieldData(RawFieldTypeT data) : _Data(data)
        {
        }

        virtual const DataType* getType(void) const
        {
            return &RawFieldTypeT::getClassType();
        }

        static FunctionIOFieldData<RawFieldTypeT>* dcast(FunctionIODataBase* Value)
        {
            return dynamic_cast< FunctionIOData<RawFieldTypeT>* >(Value);
        }

        static const FunctionIOFieldData<RawFieldTypeT>* dcast(const FunctionIODataBase* Value)
        {
            return dynamic_cast< const FunctionIOData<RawFieldTypeT>* >(Value);
        }

        const RawFieldTypeT& getData(void) const
        {
            return _Data;
        }
    };

    class FunctionIOParameter
    {
      protected:
        std::string _IOParameterName;
        boost::shared_ptr<FunctionIODataBase> _DataPtr;
      public:
        FunctionIOParameter(const std::string& name, FunctionIODataBase* data) :
           _IOParameterName(name),
           _DataPtr(data)
        {
        }

        FunctionIOParameter(const std::string& name, boost::shared_ptr<FunctionIODataBase> ptr) :
           _IOParameterName(name),
           _DataPtr(ptr)
        {
        }

        const FunctionIODataBase* getDataPtr(void) const
        {
            return _DataPtr.get();
        }

        const boost::shared_ptr<FunctionIODataBase> getPtr(void) const
        {
            return _DataPtr;
        }

    };
    typedef std::vector<FunctionIOType> FunctionIOTypeVector;
    typedef std::vector<FunctionIOParameter> FunctionIOParameterVector;

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
    /*=========================  PROTECTED  ===============================*/

    virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const = 0;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const = 0;

    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters) = 0;
  protected:

    // Variables should all be in FunctionBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Function(void);
    Function(const Function &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Function(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FunctionBase;
    friend class FunctionFactory;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Function &source);
};

typedef Function *FunctionP;

OSG_END_NAMESPACE

#include "OSGFunctionBase.inl"
#include "OSGFunction.inl"

#define OSGFUNCTION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGFUNCTION_H_ */
