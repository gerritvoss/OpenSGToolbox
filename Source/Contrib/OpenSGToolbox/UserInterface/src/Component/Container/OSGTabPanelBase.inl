/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class TabPanel!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TabPanelBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 TabPanelBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
TabPanelPtr TabPanelBase::create(void) 
{
    TabPanelPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = TabPanelPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
TabPanelPtr TabPanelBase::createEmpty(void) 
{ 
    TabPanelPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the TabPanel::_mfTabs field.
inline
const MFComponentPtr *TabPanelBase::getMFTabs(void) const
{
    return &_mfTabs;
}

//! Get the TabPanel::_mfTabs field.
inline
MFComponentPtr *TabPanelBase::editMFTabs(void)
{
    return &_mfTabs;
}

//! Get the TabPanel::_mfTabContents field.
inline
const MFComponentPtr *TabPanelBase::getMFTabContents(void) const
{
    return &_mfTabContents;
}

//! Get the TabPanel::_mfTabContents field.
inline
MFComponentPtr *TabPanelBase::editMFTabContents(void)
{
    return &_mfTabContents;
}

//! Get the TabPanel::_sfTabPlacement field.
inline
const SFUInt32 *TabPanelBase::getSFTabPlacement(void) const
{
    return &_sfTabPlacement;
}

//! Get the TabPanel::_sfTabPlacement field.
inline
SFUInt32 *TabPanelBase::editSFTabPlacement(void)
{
    return &_sfTabPlacement;
}

//! Get the TabPanel::_sfTabAlignment field.
inline
const SFReal32 *TabPanelBase::getSFTabAlignment(void) const
{
    return &_sfTabAlignment;
}

//! Get the TabPanel::_sfTabAlignment field.
inline
SFReal32 *TabPanelBase::editSFTabAlignment(void)
{
    return &_sfTabAlignment;
}

//! Get the TabPanel::_sfTabRotation field.
inline
const SFUInt32 *TabPanelBase::getSFTabRotation(void) const
{
    return &_sfTabRotation;
}

//! Get the TabPanel::_sfTabRotation field.
inline
SFUInt32 *TabPanelBase::editSFTabRotation(void)
{
    return &_sfTabRotation;
}

//! Get the TabPanel::_sfTabBorderInsets field.
inline
const SFVec2f *TabPanelBase::getSFTabBorderInsets(void) const
{
    return &_sfTabBorderInsets;
}

//! Get the TabPanel::_sfTabBorderInsets field.
inline
SFVec2f *TabPanelBase::editSFTabBorderInsets(void)
{
    return &_sfTabBorderInsets;
}

//! Get the TabPanel::_sfTabBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFTabBorder(void) const
{
    return &_sfTabBorder;
}

//! Get the TabPanel::_sfTabBorder field.
inline
SFBorderPtr *TabPanelBase::editSFTabBorder(void)
{
    return &_sfTabBorder;
}

//! Get the TabPanel::_sfTabBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFTabBackground(void) const
{
    return &_sfTabBackground;
}

//! Get the TabPanel::_sfTabBackground field.
inline
SFLayerPtr *TabPanelBase::editSFTabBackground(void)
{
    return &_sfTabBackground;
}

//! Get the TabPanel::_sfTabDisabledBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFTabDisabledBorder(void) const
{
    return &_sfTabDisabledBorder;
}

//! Get the TabPanel::_sfTabDisabledBorder field.
inline
SFBorderPtr *TabPanelBase::editSFTabDisabledBorder(void)
{
    return &_sfTabDisabledBorder;
}

//! Get the TabPanel::_sfTabDisabledBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFTabDisabledBackground(void) const
{
    return &_sfTabDisabledBackground;
}

//! Get the TabPanel::_sfTabDisabledBackground field.
inline
SFLayerPtr *TabPanelBase::editSFTabDisabledBackground(void)
{
    return &_sfTabDisabledBackground;
}

//! Get the TabPanel::_sfTabFocusedBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFTabFocusedBorder(void) const
{
    return &_sfTabFocusedBorder;
}

//! Get the TabPanel::_sfTabFocusedBorder field.
inline
SFBorderPtr *TabPanelBase::editSFTabFocusedBorder(void)
{
    return &_sfTabFocusedBorder;
}

//! Get the TabPanel::_sfTabFocusedBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFTabFocusedBackground(void) const
{
    return &_sfTabFocusedBackground;
}

//! Get the TabPanel::_sfTabFocusedBackground field.
inline
SFLayerPtr *TabPanelBase::editSFTabFocusedBackground(void)
{
    return &_sfTabFocusedBackground;
}

//! Get the TabPanel::_sfTabRolloverBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFTabRolloverBorder(void) const
{
    return &_sfTabRolloverBorder;
}

//! Get the TabPanel::_sfTabRolloverBorder field.
inline
SFBorderPtr *TabPanelBase::editSFTabRolloverBorder(void)
{
    return &_sfTabRolloverBorder;
}

//! Get the TabPanel::_sfTabRolloverBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFTabRolloverBackground(void) const
{
    return &_sfTabRolloverBackground;
}

//! Get the TabPanel::_sfTabRolloverBackground field.
inline
SFLayerPtr *TabPanelBase::editSFTabRolloverBackground(void)
{
    return &_sfTabRolloverBackground;
}

//! Get the TabPanel::_sfTabActiveBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFTabActiveBorder(void) const
{
    return &_sfTabActiveBorder;
}

//! Get the TabPanel::_sfTabActiveBorder field.
inline
SFBorderPtr *TabPanelBase::editSFTabActiveBorder(void)
{
    return &_sfTabActiveBorder;
}

//! Get the TabPanel::_sfTabActiveBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFTabActiveBackground(void) const
{
    return &_sfTabActiveBackground;
}

//! Get the TabPanel::_sfTabActiveBackground field.
inline
SFLayerPtr *TabPanelBase::editSFTabActiveBackground(void)
{
    return &_sfTabActiveBackground;
}

//! Get the TabPanel::_sfContentBorderInsets field.
inline
const SFVec2f *TabPanelBase::getSFContentBorderInsets(void) const
{
    return &_sfContentBorderInsets;
}

//! Get the TabPanel::_sfContentBorderInsets field.
inline
SFVec2f *TabPanelBase::editSFContentBorderInsets(void)
{
    return &_sfContentBorderInsets;
}

//! Get the TabPanel::_sfContentBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFContentBorder(void) const
{
    return &_sfContentBorder;
}

//! Get the TabPanel::_sfContentBorder field.
inline
SFBorderPtr *TabPanelBase::editSFContentBorder(void)
{
    return &_sfContentBorder;
}

//! Get the TabPanel::_sfContentBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFContentBackground(void) const
{
    return &_sfContentBackground;
}

//! Get the TabPanel::_sfContentBackground field.
inline
SFLayerPtr *TabPanelBase::editSFContentBackground(void)
{
    return &_sfContentBackground;
}

//! Get the TabPanel::_sfContentDisabledBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFContentDisabledBorder(void) const
{
    return &_sfContentDisabledBorder;
}

//! Get the TabPanel::_sfContentDisabledBorder field.
inline
SFBorderPtr *TabPanelBase::editSFContentDisabledBorder(void)
{
    return &_sfContentDisabledBorder;
}

//! Get the TabPanel::_sfContentDisabledBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFContentDisabledBackground(void) const
{
    return &_sfContentDisabledBackground;
}

//! Get the TabPanel::_sfContentDisabledBackground field.
inline
SFLayerPtr *TabPanelBase::editSFContentDisabledBackground(void)
{
    return &_sfContentDisabledBackground;
}

//! Get the TabPanel::_sfContentRolloverBorder field.
inline
const SFBorderPtr *TabPanelBase::getSFContentRolloverBorder(void) const
{
    return &_sfContentRolloverBorder;
}

//! Get the TabPanel::_sfContentRolloverBorder field.
inline
SFBorderPtr *TabPanelBase::editSFContentRolloverBorder(void)
{
    return &_sfContentRolloverBorder;
}

//! Get the TabPanel::_sfContentRolloverBackground field.
inline
const SFLayerPtr *TabPanelBase::getSFContentRolloverBackground(void) const
{
    return &_sfContentRolloverBackground;
}

//! Get the TabPanel::_sfContentRolloverBackground field.
inline
SFLayerPtr *TabPanelBase::editSFContentRolloverBackground(void)
{
    return &_sfContentRolloverBackground;
}

//! Get the TabPanel::_sfSelectionModel field.
inline
const SFSingleSelectionModelPtr *TabPanelBase::getSFSelectionModel(void) const
{
    return &_sfSelectionModel;
}

//! Get the TabPanel::_sfSelectionModel field.
inline
SFSingleSelectionModelPtr *TabPanelBase::editSFSelectionModel(void)
{
    return &_sfSelectionModel;
}


//! Get the value of the TabPanel::_sfTabPlacement field.
inline
UInt32 &TabPanelBase::editTabPlacement(void)
{
    return _sfTabPlacement.getValue();
}

//! Get the value of the TabPanel::_sfTabPlacement field.
inline
const UInt32 &TabPanelBase::getTabPlacement(void) const
{
    return _sfTabPlacement.getValue();
}

//! Set the value of the TabPanel::_sfTabPlacement field.
inline
void TabPanelBase::setTabPlacement(const UInt32 &value)
{
    _sfTabPlacement.setValue(value);
}

//! Get the value of the TabPanel::_sfTabAlignment field.
inline
Real32 &TabPanelBase::editTabAlignment(void)
{
    return _sfTabAlignment.getValue();
}

//! Get the value of the TabPanel::_sfTabAlignment field.
inline
const Real32 &TabPanelBase::getTabAlignment(void) const
{
    return _sfTabAlignment.getValue();
}

//! Set the value of the TabPanel::_sfTabAlignment field.
inline
void TabPanelBase::setTabAlignment(const Real32 &value)
{
    _sfTabAlignment.setValue(value);
}

//! Get the value of the TabPanel::_sfTabRotation field.
inline
UInt32 &TabPanelBase::editTabRotation(void)
{
    return _sfTabRotation.getValue();
}

//! Get the value of the TabPanel::_sfTabRotation field.
inline
const UInt32 &TabPanelBase::getTabRotation(void) const
{
    return _sfTabRotation.getValue();
}

//! Set the value of the TabPanel::_sfTabRotation field.
inline
void TabPanelBase::setTabRotation(const UInt32 &value)
{
    _sfTabRotation.setValue(value);
}

//! Get the value of the TabPanel::_sfTabBorderInsets field.
inline
Vec2f &TabPanelBase::editTabBorderInsets(void)
{
    return _sfTabBorderInsets.getValue();
}

//! Get the value of the TabPanel::_sfTabBorderInsets field.
inline
const Vec2f &TabPanelBase::getTabBorderInsets(void) const
{
    return _sfTabBorderInsets.getValue();
}

//! Set the value of the TabPanel::_sfTabBorderInsets field.
inline
void TabPanelBase::setTabBorderInsets(const Vec2f &value)
{
    _sfTabBorderInsets.setValue(value);
}

//! Get the value of the TabPanel::_sfTabBorder field.
inline
BorderPtr &TabPanelBase::editTabBorder(void)
{
    return _sfTabBorder.getValue();
}

//! Get the value of the TabPanel::_sfTabBorder field.
inline
const BorderPtr &TabPanelBase::getTabBorder(void) const
{
    return _sfTabBorder.getValue();
}

//! Set the value of the TabPanel::_sfTabBorder field.
inline
void TabPanelBase::setTabBorder(const BorderPtr &value)
{
    _sfTabBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfTabBackground field.
inline
LayerPtr &TabPanelBase::editTabBackground(void)
{
    return _sfTabBackground.getValue();
}

//! Get the value of the TabPanel::_sfTabBackground field.
inline
const LayerPtr &TabPanelBase::getTabBackground(void) const
{
    return _sfTabBackground.getValue();
}

//! Set the value of the TabPanel::_sfTabBackground field.
inline
void TabPanelBase::setTabBackground(const LayerPtr &value)
{
    _sfTabBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfTabDisabledBorder field.
inline
BorderPtr &TabPanelBase::editTabDisabledBorder(void)
{
    return _sfTabDisabledBorder.getValue();
}

//! Get the value of the TabPanel::_sfTabDisabledBorder field.
inline
const BorderPtr &TabPanelBase::getTabDisabledBorder(void) const
{
    return _sfTabDisabledBorder.getValue();
}

//! Set the value of the TabPanel::_sfTabDisabledBorder field.
inline
void TabPanelBase::setTabDisabledBorder(const BorderPtr &value)
{
    _sfTabDisabledBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfTabDisabledBackground field.
inline
LayerPtr &TabPanelBase::editTabDisabledBackground(void)
{
    return _sfTabDisabledBackground.getValue();
}

//! Get the value of the TabPanel::_sfTabDisabledBackground field.
inline
const LayerPtr &TabPanelBase::getTabDisabledBackground(void) const
{
    return _sfTabDisabledBackground.getValue();
}

//! Set the value of the TabPanel::_sfTabDisabledBackground field.
inline
void TabPanelBase::setTabDisabledBackground(const LayerPtr &value)
{
    _sfTabDisabledBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfTabFocusedBorder field.
inline
BorderPtr &TabPanelBase::editTabFocusedBorder(void)
{
    return _sfTabFocusedBorder.getValue();
}

//! Get the value of the TabPanel::_sfTabFocusedBorder field.
inline
const BorderPtr &TabPanelBase::getTabFocusedBorder(void) const
{
    return _sfTabFocusedBorder.getValue();
}

//! Set the value of the TabPanel::_sfTabFocusedBorder field.
inline
void TabPanelBase::setTabFocusedBorder(const BorderPtr &value)
{
    _sfTabFocusedBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfTabFocusedBackground field.
inline
LayerPtr &TabPanelBase::editTabFocusedBackground(void)
{
    return _sfTabFocusedBackground.getValue();
}

//! Get the value of the TabPanel::_sfTabFocusedBackground field.
inline
const LayerPtr &TabPanelBase::getTabFocusedBackground(void) const
{
    return _sfTabFocusedBackground.getValue();
}

//! Set the value of the TabPanel::_sfTabFocusedBackground field.
inline
void TabPanelBase::setTabFocusedBackground(const LayerPtr &value)
{
    _sfTabFocusedBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfTabRolloverBorder field.
inline
BorderPtr &TabPanelBase::editTabRolloverBorder(void)
{
    return _sfTabRolloverBorder.getValue();
}

//! Get the value of the TabPanel::_sfTabRolloverBorder field.
inline
const BorderPtr &TabPanelBase::getTabRolloverBorder(void) const
{
    return _sfTabRolloverBorder.getValue();
}

//! Set the value of the TabPanel::_sfTabRolloverBorder field.
inline
void TabPanelBase::setTabRolloverBorder(const BorderPtr &value)
{
    _sfTabRolloverBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfTabRolloverBackground field.
inline
LayerPtr &TabPanelBase::editTabRolloverBackground(void)
{
    return _sfTabRolloverBackground.getValue();
}

//! Get the value of the TabPanel::_sfTabRolloverBackground field.
inline
const LayerPtr &TabPanelBase::getTabRolloverBackground(void) const
{
    return _sfTabRolloverBackground.getValue();
}

//! Set the value of the TabPanel::_sfTabRolloverBackground field.
inline
void TabPanelBase::setTabRolloverBackground(const LayerPtr &value)
{
    _sfTabRolloverBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfTabActiveBorder field.
inline
BorderPtr &TabPanelBase::editTabActiveBorder(void)
{
    return _sfTabActiveBorder.getValue();
}

//! Get the value of the TabPanel::_sfTabActiveBorder field.
inline
const BorderPtr &TabPanelBase::getTabActiveBorder(void) const
{
    return _sfTabActiveBorder.getValue();
}

//! Set the value of the TabPanel::_sfTabActiveBorder field.
inline
void TabPanelBase::setTabActiveBorder(const BorderPtr &value)
{
    _sfTabActiveBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfTabActiveBackground field.
inline
LayerPtr &TabPanelBase::editTabActiveBackground(void)
{
    return _sfTabActiveBackground.getValue();
}

//! Get the value of the TabPanel::_sfTabActiveBackground field.
inline
const LayerPtr &TabPanelBase::getTabActiveBackground(void) const
{
    return _sfTabActiveBackground.getValue();
}

//! Set the value of the TabPanel::_sfTabActiveBackground field.
inline
void TabPanelBase::setTabActiveBackground(const LayerPtr &value)
{
    _sfTabActiveBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfContentBorderInsets field.
inline
Vec2f &TabPanelBase::editContentBorderInsets(void)
{
    return _sfContentBorderInsets.getValue();
}

//! Get the value of the TabPanel::_sfContentBorderInsets field.
inline
const Vec2f &TabPanelBase::getContentBorderInsets(void) const
{
    return _sfContentBorderInsets.getValue();
}

//! Set the value of the TabPanel::_sfContentBorderInsets field.
inline
void TabPanelBase::setContentBorderInsets(const Vec2f &value)
{
    _sfContentBorderInsets.setValue(value);
}

//! Get the value of the TabPanel::_sfContentBorder field.
inline
BorderPtr &TabPanelBase::editContentBorder(void)
{
    return _sfContentBorder.getValue();
}

//! Get the value of the TabPanel::_sfContentBorder field.
inline
const BorderPtr &TabPanelBase::getContentBorder(void) const
{
    return _sfContentBorder.getValue();
}

//! Set the value of the TabPanel::_sfContentBorder field.
inline
void TabPanelBase::setContentBorder(const BorderPtr &value)
{
    _sfContentBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfContentBackground field.
inline
LayerPtr &TabPanelBase::editContentBackground(void)
{
    return _sfContentBackground.getValue();
}

//! Get the value of the TabPanel::_sfContentBackground field.
inline
const LayerPtr &TabPanelBase::getContentBackground(void) const
{
    return _sfContentBackground.getValue();
}

//! Set the value of the TabPanel::_sfContentBackground field.
inline
void TabPanelBase::setContentBackground(const LayerPtr &value)
{
    _sfContentBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfContentDisabledBorder field.
inline
BorderPtr &TabPanelBase::editContentDisabledBorder(void)
{
    return _sfContentDisabledBorder.getValue();
}

//! Get the value of the TabPanel::_sfContentDisabledBorder field.
inline
const BorderPtr &TabPanelBase::getContentDisabledBorder(void) const
{
    return _sfContentDisabledBorder.getValue();
}

//! Set the value of the TabPanel::_sfContentDisabledBorder field.
inline
void TabPanelBase::setContentDisabledBorder(const BorderPtr &value)
{
    _sfContentDisabledBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfContentDisabledBackground field.
inline
LayerPtr &TabPanelBase::editContentDisabledBackground(void)
{
    return _sfContentDisabledBackground.getValue();
}

//! Get the value of the TabPanel::_sfContentDisabledBackground field.
inline
const LayerPtr &TabPanelBase::getContentDisabledBackground(void) const
{
    return _sfContentDisabledBackground.getValue();
}

//! Set the value of the TabPanel::_sfContentDisabledBackground field.
inline
void TabPanelBase::setContentDisabledBackground(const LayerPtr &value)
{
    _sfContentDisabledBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfContentRolloverBorder field.
inline
BorderPtr &TabPanelBase::editContentRolloverBorder(void)
{
    return _sfContentRolloverBorder.getValue();
}

//! Get the value of the TabPanel::_sfContentRolloverBorder field.
inline
const BorderPtr &TabPanelBase::getContentRolloverBorder(void) const
{
    return _sfContentRolloverBorder.getValue();
}

//! Set the value of the TabPanel::_sfContentRolloverBorder field.
inline
void TabPanelBase::setContentRolloverBorder(const BorderPtr &value)
{
    _sfContentRolloverBorder.setValue(value);
}

//! Get the value of the TabPanel::_sfContentRolloverBackground field.
inline
LayerPtr &TabPanelBase::editContentRolloverBackground(void)
{
    return _sfContentRolloverBackground.getValue();
}

//! Get the value of the TabPanel::_sfContentRolloverBackground field.
inline
const LayerPtr &TabPanelBase::getContentRolloverBackground(void) const
{
    return _sfContentRolloverBackground.getValue();
}

//! Set the value of the TabPanel::_sfContentRolloverBackground field.
inline
void TabPanelBase::setContentRolloverBackground(const LayerPtr &value)
{
    _sfContentRolloverBackground.setValue(value);
}

//! Get the value of the TabPanel::_sfSelectionModel field.
inline
SingleSelectionModelPtr &TabPanelBase::editSelectionModel(void)
{
    return _sfSelectionModel.getValue();
}

//! Get the value of the TabPanel::_sfSelectionModel field.
inline
const SingleSelectionModelPtr &TabPanelBase::getSelectionModel(void) const
{
    return _sfSelectionModel.getValue();
}

//! Set the value of the TabPanel::_sfSelectionModel field.
inline
void TabPanelBase::setSelectionModel(const SingleSelectionModelPtr &value)
{
    _sfSelectionModel.setValue(value);
}


//! Get the value of the \a index element the TabPanel::_mfTabs field.
inline
ComponentPtr &TabPanelBase::editTabs(const UInt32 index)
{
    return _mfTabs[index];
}

//! Get the value of the \a index element the TabPanel::_mfTabs field.
inline
const ComponentPtr &TabPanelBase::getTabs(const UInt32 index) const
{
    return _mfTabs[index];
}

#ifndef OSG_2_PREP
//! Get the TabPanel::_mfTabs field.
inline
MFComponentPtr &TabPanelBase::getTabs(void)
{
    return _mfTabs;
}

//! Get the TabPanel::_mfTabs field.
inline
const MFComponentPtr &TabPanelBase::getTabs(void) const
{
    return _mfTabs;
}

#endif
//! Get the value of the \a index element the TabPanel::_mfTabContents field.
inline
ComponentPtr &TabPanelBase::editTabContents(const UInt32 index)
{
    return _mfTabContents[index];
}

//! Get the value of the \a index element the TabPanel::_mfTabContents field.
inline
const ComponentPtr &TabPanelBase::getTabContents(const UInt32 index) const
{
    return _mfTabContents[index];
}

#ifndef OSG_2_PREP
//! Get the TabPanel::_mfTabContents field.
inline
MFComponentPtr &TabPanelBase::getTabContents(void)
{
    return _mfTabContents;
}

//! Get the TabPanel::_mfTabContents field.
inline
const MFComponentPtr &TabPanelBase::getTabContents(void) const
{
    return _mfTabContents;
}

#endif
OSG_END_NAMESPACE