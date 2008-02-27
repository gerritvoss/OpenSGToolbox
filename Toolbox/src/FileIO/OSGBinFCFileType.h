/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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

#ifndef _OSGBINFCFILETYPE_H_
#define _OSGBINFCFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include "OSGFCFileType.h"
#include "OSGFCFileHandler.h"

//This is needed so that the Shared Ptr included in the OSG library is not used
//because it is already defined in the boost library
#define BOOST_SMART_PTR_HPP
#include <OpenSG/OSGXmlpp.h>

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING BinFCFileType : public FCFileType
{
     /*==========================  PUBLIC  =================================*/
   public:
	   /*---------------------------------------------------------------------*/
    static BinFCFileType *the(void);

     /*---------------------------------------------------------------------*/
	 virtual std::string getName(void) const;
     
     /*---------------------------------------------------------------------*/
     virtual ~BinFCFileType(void);
 
     /*---------------------------------------------------------------------*/
     virtual FCPtrStore read(std::istream &is,
		                     const std::string& FileNameOrExtension) const;
 
     /*---------------------------------------------------------------------*/
     virtual bool write(const FCPtrStore &Containers, std::ostream &os,
                        const std::string& FileNameOrExtension, const FCTypeVector& IgnoreTypes) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
	 struct FCIdMapper;
	 friend struct FCIdMapper;

	 struct FCInfoStruct
	 {
		UInt32            _NewId;
		FieldContainerPtr _Ptr;
		bool              _Read;
		FCInfoStruct();
	 };

	 typedef std::map<UInt32, FCInfoStruct> IDLookupMap;

	 struct FCIdMapper : public FieldContainerMapper
	 {
	 public:
		const IDLookupMap *_PtrMap;
		FCIdMapper(IDLookupMap *m);

		virtual UInt32 map(UInt32 uiId);
	 };

	 typedef FCFileType Inherited;
	 static       BinFCFileType*  _the;

     FCPtrStore getAllDependantFCs(FCPtrStore Containers, FCPtrStore IgnoreContainers, const FCTypeVector& IgnoreTypes) const;
     bool isFieldAFieldContainerPtr(const Field* TheField) const;
 
     /*---------------------------------------------------------------------*/
     BinFCFileType(void);
 
     BinFCFileType(const BinFCFileType &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
     void operator =(const BinFCFileType &source);
};

typedef BinFCFileType* BinFCFileTypeP;

OSG_END_NAMESPACE

#include "OSGBinFCFileType.inl"

#endif /* _OSGBINFCFILETYPE_H_ */
