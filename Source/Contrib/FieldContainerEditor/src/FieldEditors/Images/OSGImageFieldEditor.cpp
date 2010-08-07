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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGImageFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGImage.h"
#include "OSGFieldEditorFactory.h"
#include "OSGImageFileHandler.h"
#include "OSGWindowEventProducer.h"
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGFilePathAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGImageFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGImageFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        FieldEditorFactory::the()->setSingleDefaultEditor(&FieldTraits<Image*>::getType(), &getClassType());
        FieldEditorFactory::the()->setEditorType(&FieldTraits<Image*>::getType(), &getClassType(),
                                                 "ImageLoader");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ImageFieldEditor::openCreateHandler(void)
{
    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;

    std::list< const Char8 * > ReadableImageSuff;
    ImageFileHandler::the()->getSuffixList(ReadableImageSuff, ImageFileType::OSG_READ_SUPPORTED);
    //Determine all of the readable image filetypes
    Filters.push_back(WindowEventProducer::FileDialogFilter("All Image filetypes",""));
    std::string AllImageSuffixes;
    std::string AllImageSuffixesDesc("All Image filetypes (");
    for(std::list<const Char8*>::const_iterator SuffixItor(ReadableImageSuff.begin()) ; SuffixItor != ReadableImageSuff.end() ; ++SuffixItor)
    {
        if(ImageFileHandler::the()->getFileType(*SuffixItor))
        {
            if(!AllImageSuffixes.empty())
            {
                AllImageSuffixes += ",";
                AllImageSuffixesDesc += ", ";
            }
            AllImageSuffixes += *SuffixItor;
            AllImageSuffixesDesc = AllImageSuffixesDesc + "*." + *SuffixItor;
            Filters.push_back(WindowEventProducer::FileDialogFilter(std::string(ImageFileHandler::the()->getFileType(*SuffixItor)->getMimeType()) +  " (*." + *SuffixItor + ")",*SuffixItor));
        }
    }
    AllImageSuffixesDesc += ")";
    Filters[0] = WindowEventProducer::FileDialogFilter(AllImageSuffixesDesc,AllImageSuffixes);
    Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

	std::vector<BoostPath> FilesToOpen;
    FilesToOpen = getParentWindow()->getParentDrawingSurface()->getEventProducer()->openFileDialog("Import a image file.",
                                                                          Filters,
                                                                          BoostPath("."),
                                                                          false);

	ImageRefPtr NewImage = NULL;

    if(FilesToOpen.size() > 0)
    {
        //Try loading the file using the ImageFileHandler
        NewImage = ImageFileHandler::the()->read(FilesToOpen[0].string().c_str());

        if(NewImage)
        {
            FilePathAttachment::setFilePath(NewImage, FilesToOpen[0]);

            //Set the value of the field
            SetFieldValueCommandPtr SetCommand =
                SetFieldValueCommand::create(getEditingFC(),
                                             getEditingFieldId(),
                                             boost::lexical_cast<std::string>(NewImage->getId()),
                                             getEditingFieldIndex());

            getCommandManager()->executeCommand(SetCommand);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ImageFieldEditor::ImageFieldEditor(void) :
    Inherited()
{
}

ImageFieldEditor::ImageFieldEditor(const ImageFieldEditor &source) :
    Inherited(source)
{
}

ImageFieldEditor::~ImageFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ImageFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ImageFieldEditor NI" << std::endl;
}

OSG_END_NAMESPACE
