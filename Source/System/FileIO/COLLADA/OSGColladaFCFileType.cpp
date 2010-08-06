/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGColladaFCFileType.h"

#include "OSGColladaGlobal.h"

#include "OSGImageFileHandler.h"


OSG_BEGIN_NAMESPACE

/*----------------------- constructors & destructors ----------------------*/

ColladaFCFileType::ColladaFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("dae")),
        false,
        50,
        FCFileType::OSG_READ_SUPPORTED)
{
}



ColladaFCFileType::ColladaFCFileType(const ColladaFCFileType &obj) : Inherited(obj)

{
}

ColladaFCFileType::~ColladaFCFileType(void)
{
}

/***************************************************************************\
* Description *
\***************************************************************************/

/*! \class osg::XMLFCFileType
A XMLFCFileType.
*/

/***************************************************************************\
* Class variables *
\***************************************************************************/

ColladaFCFileType* ColladaFCFileType::_the(new ColladaFCFileType());


/***************************************************************************\
* Instance methods *
\***************************************************************************/

 
 /*---------------------------------------------------------------------*/
ColladaFCFileType::FCPtrStore ColladaFCFileType::read(std::istream &is,
                                                      const std::string& fileNameOrExtension) const
{
    ColladaGlobal::ObjTransitPtr colladaReader = ColladaGlobal::create();

    ColladaOptionsRefPtr colOpts = ColladaOptions::create();
    colOpts->setInvertTransparency(false);
    colOpts->setCreateNameAttachments(true);
    colOpts->setFlattenNodeXForms(true);
    colOpts->setReadAnimations(true);
    colladaReader->setOptions(colOpts);

    //NodeTransitPtr colRoot = colladaReader->read(is,fileNameOrExtension);
    //FCPtrStore store;
    //store.insert(colRoot);
    //return store;

    return colladaReader->readAll(is,fileNameOrExtension);

}

 /*---------------------------------------------------------------------*/

bool ColladaFCFileType::write(const FCPtrStore &Containers, std::ostream &os,
                              const std::string& fileNameOrExtension, const FCTypeVector& IgnoreTypes) const
{
    SWARNING << "In ColladaFCFileType: Write support for COLLADA files NIY." << std::endl;
    return false;
}


std::string ColladaFCFileType::getName(void) const
{
    return std::string("ColladaFCFileType");
}

OSG_END_NAMESPACE


