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

#include "OSGLuaIntrospectionTreeModel.h"
#include "OSGLuaManager.h"
#include "OSGLuaManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaIntrospectionTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaIntrospectionTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaIntrospectionTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

boost::any LuaIntrospectionTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
	    const lua_details::FieldStack& ThePath(boost::any_cast<lua_details::FieldStack >(parent));

        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        if(lua_details::pushFieldOntoStack(LuaState, ThePath))
        {
            //Check if the the value is a table
            if(lua_istable(LuaState, -1))
            {
                lua_details::TableInfo TableData;
                //Fill 
                lua_details::list_table(LuaState, -1, TableData);

                lua_pop(LuaState, 1);

                if(index >= TableData.size())
                {
                    SWARNING << "Index out of bounds" << std::endl;
                    return boost::any();
                }

                lua_details::FieldStack ChildPath(ThePath);
                //Get the ith index
                ChildPath.push_back(TableData[index]);

                return boost::any(ChildPath);
            }
            else
            {
                //Pop off the stack
                lua_pop(LuaState, 1);
            }
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
    }
    return boost::any();
}

UInt32 LuaIntrospectionTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
	    const lua_details::FieldStack& ThePath(boost::any_cast<lua_details::FieldStack >(parent));

        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        if(lua_details::pushFieldOntoStack(LuaState, ThePath))
        {

            //Check if the the value is a table
            if(lua_istable(LuaState, -1))
            {
                UInt32 count(lua_details::get_num_fields(LuaState, -1));

                //Pop the table off the stack
                lua_pop(LuaState, 1);
                return count;
            }
            else
            {
                //Pop off the stack
                lua_pop(LuaState, 1);
            }
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
    }
    return 0;
}

UInt32 LuaIntrospectionTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
   try
    {
        const lua_details::FieldStack& ChildPath(boost::any_cast< lua_details::FieldStack >(child));
	    const lua_details::FieldStack& ParentPath(boost::any_cast< lua_details::FieldStack >(parent));

        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        if(lua_details::pushFieldOntoStack(LuaState, ParentPath))
        {
            //Check if the the value is a table
            if(lua_istable(LuaState, -1))
            {
                lua_details::TableInfo TableData;
                //Fill 
                lua_details::list_table(LuaState, -1, TableData);

                lua_pop(LuaState, 1);

                UInt32 i(0);
                while(i < TableData.size())
                {
                    if(TableData[i].key.value == ChildPath.back().key.value)
                    {
                        return i;
                    }
                    ++i;
                }
            }
            else
            {
                //Pop off the stack
                lua_pop(LuaState, 1);
            }
        }
    }
    catch(const boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
    }
    return 0;
}

boost::any LuaIntrospectionTreeModel::getRoot(void) const
{
    //Get the Lua state
    lua_State *LuaState(LuaManager::the()->getLuaState());

    /*for(UInt32 i(0) ; i<getMFInternalRoot().size() ; ++i)
    {
    }*/
    lua_details::FieldStack v;

    return boost::any(v);
}

bool LuaIntrospectionTreeModel::isLeaf(const boost::any& node) const
{
    return getChildCount(node) == 0;
}

void LuaIntrospectionTreeModel::valueForPathChanged(TreePath path, const boost::any& newValueStack)
{
    //TODO
}

void LuaIntrospectionTreeModel::setRoot(const std::string& root)
{
    editMFInternalRoot()->clear();
    //TODO: split the root by '.'
    editMFInternalRoot()->push_back(root);
}


bool LuaIntrospectionTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        const lua_details::FieldStack& RightPath(boost::any_cast< lua_details::FieldStack >(left));
	    const lua_details::FieldStack& LeftPath(boost::any_cast< lua_details::FieldStack >(right));

        return RightPath == LeftPath;
    }
    catch(boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast" << ex.what() << "." << std::endl;
        return false;
    }
}

const std::string& LuaIntrospectionTreeModel::getRootLuaPath(void) const
{
    std::string Path("");
    for(UInt32 i(0) ; i<getMFInternalRoot()->size() ; ++i)
    {
        if(i != 0)
        {
            Path += ".";
        }
        Path += getInternalRoot(i);
    }
    return Path;
}

void LuaIntrospectionTreeModel::produceModelChanged(void)
{
    produceTreeStructureChanged(getRootPath(),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, getRoot()));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


/*----------------------- constructors & destructors ----------------------*/

LuaIntrospectionTreeModel::LuaIntrospectionTreeModel(void) :
    Inherited()
{
}

LuaIntrospectionTreeModel::LuaIntrospectionTreeModel(const LuaIntrospectionTreeModel &source) :
    Inherited(source)
{
}

LuaIntrospectionTreeModel::~LuaIntrospectionTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaIntrospectionTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & (InternalRootFieldMask |
                     ShowTableFieldMask |
                     ShowFunctionFieldMask |
                     ShowNilFieldMask |
                     ShowBooleanFieldMask |
                     ShowNumberFieldMask |
                     ShowStringFieldMask |
                     ShowThreadFieldMask |
                     ShowUserDataFieldMask)
        )
    {
        produceTreeStructureChanged(getRootPath(),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, getRoot()));
    }
}

void LuaIntrospectionTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaIntrospectionTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
