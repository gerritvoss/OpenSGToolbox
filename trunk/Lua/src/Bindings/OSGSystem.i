%include <OSGBase.i>
%native(getFieldValue) int getFieldValue(lua_State*L);  // registers native_function() with SWIG
%native(setFieldValue) int setFieldValue(lua_State*L);  // registers native_function() with SWIG
%native(pushFieldValue) int pushFieldValue(lua_State*L);  // registers native_function() with SWIG
%module OSG
%{
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainerPtr.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGSysFieldDataType.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGSFVecTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>
    int getFieldValue(lua_State*L) // my native code
    {
        int argc = lua_gettop(L);
        int SWIG_arg = 0;
        if (argc == 2) {
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",2,2)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"osg::FieldContainerPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"osg::Char8 const *");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
          }
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          const osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Check that this is not a MultiField
          if(TheField->getCardinality() == osg::FieldType::MULTI_FIELD)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a multi-field, you must also supply the index.",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const osg::DataType& FieldContentType(TheField->getContentType());
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              lua_pushboolean(L,dynamic_cast<const osg::SFBool*>(TheField)->getValue()); SWIG_arg++;
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              lua_pushstring(L,dynamic_cast<const osg::SFString*>(TheField)->getValue().c_str()); SWIG_arg++;
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt8*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt16*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt32*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt64*>(TheField)->getValue()); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFBitVector*>(TheField)->getValue()); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFGLenum*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt8*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt16*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt32*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt64*>(TheField)->getValue()); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFReal32*>(TheField)->getValue()); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFReal64*>(TheField)->getValue()); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f * resultptr = new osg::Color3f((const osg::Color3f &) dynamic_cast<const osg::SFColor3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color3T_float_t,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f * resultptr = new osg::Color4f((const osg::Color4f &) dynamic_cast<const osg::SFColor4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color4T_float_t,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f * resultptr = new osg::Vec2f((const osg::Vec2f &) dynamic_cast<const osg::SFVec2f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f * resultptr = new osg::Vec3f((const osg::Vec3f &) dynamic_cast<const osg::SFVec3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f * resultptr = new osg::Vec4f((const osg::Vec4f &) dynamic_cast<const osg::SFVec4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f * resultptr = new osg::Pnt2f((const osg::Pnt2f &) dynamic_cast<const osg::SFPnt2f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f * resultptr = new osg::Pnt3f((const osg::Pnt3f &) dynamic_cast<const osg::SFPnt3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f * resultptr = new osg::Pnt4f((const osg::Pnt4f &) dynamic_cast<const osg::SFPnt4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix * resultptr = new osg::Matrix((const osg::Matrix &) dynamic_cast<const osg::SFMatrix*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion * resultptr = new osg::Quaternion((const osg::Quaternion &) dynamic_cast<const osg::SFQuaternion*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerPtrs
          //Volumes
          //otherwize
          else
          {
              TheField->getValueByStr(result);
              lua_pushstring(L,result.c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }
        else if (argc == 3) {
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          osg::UInt32 arg3 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",3,3)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"osg::FieldContainerPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"osg::Char8 const *");
          if(!lua_isnumber(L,3)) SWIG_fail_arg("getFieldValue",3,"osg::UInt32");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
          }
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          arg3 = (osg::UInt32)lua_tonumber(L, 3);
          
          const osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a single-field, you do not need to supply an index..",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const osg::DataType& FieldContentType(TheField->getContentType());
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              lua_pushboolean(L,dynamic_cast<const osg::MFBool*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              lua_pushstring(L,dynamic_cast<const osg::MFString*>(TheField)->getValue(arg3).c_str()); SWIG_arg++;
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt8*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt16*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFBitVector*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFGLenum*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt8*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt16*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFReal32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFReal64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f * resultptr = new osg::Color3f((const osg::Color3f &) dynamic_cast<const osg::MFColor3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color3T_float_t,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f * resultptr = new osg::Color4f((const osg::Color4f &) dynamic_cast<const osg::MFColor4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color4T_float_t,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f * resultptr = new osg::Vec2f((const osg::Vec2f &) dynamic_cast<const osg::MFVec2f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f * resultptr = new osg::Vec3f((const osg::Vec3f &) dynamic_cast<const osg::MFVec3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f * resultptr = new osg::Vec4f((const osg::Vec4f &) dynamic_cast<const osg::MFVec4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f * resultptr = new osg::Pnt2f((const osg::Pnt2f &) dynamic_cast<const osg::MFPnt2f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f * resultptr = new osg::Pnt3f((const osg::Pnt3f &) dynamic_cast<const osg::MFPnt3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f * resultptr = new osg::Pnt4f((const osg::Pnt4f &) dynamic_cast<const osg::MFPnt4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix * resultptr = new osg::Matrix((const osg::Matrix &) dynamic_cast<const osg::MFMatrix*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion * resultptr = new osg::Quaternion((const osg::Quaternion &) dynamic_cast<const osg::MFQuaternion*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerPtrs
          //Volumes
          //otherwize
          else
          {
              TheField->getValueByStr(result, arg3);
              lua_pushstring(L,result.c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    bool LUA_BINDING_check_num_args(lua_State*L, char* func_name,unsigned int a,unsigned int b)
    {
        if (lua_gettop(L)<a || lua_gettop(L)>b)
        {
            lua_pushfstring(L,"Error in %s expected %d..%d args, got %d",func_name,a,b,lua_gettop(L));
            lua_error(L);
            return false;
        }
        return true;
    }

    void LUA_BINDING_fail_arg(lua_State*L, const char* func_name, unsigned int argnum,const char* type)
    {
      lua_pushfstring(L,"Error in %s (arg %d), expected '%s' got '%s'", func_name,argnum,type,SWIG_Lua_typename(L,argnum));
      lua_error(L);
    }

    void LUA_BINDING_fail_ptr(lua_State*L, const char* func_name, unsigned int argnum,swig_type_info* type)
    {
        LUA_BINDING_fail_arg(L, func_name, argnum,(type && type->str)?type->str:"void*");
    }

    int setFieldValue(lua_State*L) // my native code
    {
        int SWIG_arg = 0;
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"setFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"setFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in setFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFBool*>(TheField)->setValue(static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFString*>(TheField)->setValue(static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt8*>(TheField)->setValue(static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt16*>(TheField)->setValue(static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt32*>(TheField)->setValue(static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt64*>(TheField)->setValue(static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFBitVector*>(TheField)->setValue(static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFGLenum*>(TheField)->setValue(static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt8*>(TheField)->setValue(static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt16*>(TheField)->setValue(static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt32*>(TheField)->setValue(static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt64*>(TheField)->setValue(static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFReal32*>(TheField)->setValue(static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFReal64*>(TheField)->setValue(static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFColor3f*>(TheField)->setValue(static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFColor4f*>(TheField)->setValue(static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec2f*>(TheField)->setValue(static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec3f*>(TheField)->setValue(static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec4f*>(TheField)->setValue(static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt2f*>(TheField)->setValue(static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt3f*>(TheField)->setValue(static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt4f*>(TheField)->setValue(static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFMatrix*>(TheField)->setValue(static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFQuaternion*>(TheField)->setValue(static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          //Volumes
          //Otherwise
          else
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  TheField->pushValueByStr((osg::Char8 *)lua_tostring(L, 3));
              osg::endEditCP((*arg1), TheMask);
          }

          return SWIG_arg;
    }

    int pushFieldValue(lua_State*L) // my native code
    {
        int SWIG_arg = 0;
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"pushFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"pushFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in pushFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in pushFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in pushFieldValue field of name '%s' on type '%s' is a single-field.  Use setFieldValue instead.",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBool*>(TheField)->push_back(static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFString*>(TheField)->push_back(static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt8*>(TheField)->push_back(static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt16*>(TheField)->push_back(static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt32*>(TheField)->push_back(static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt64*>(TheField)->push_back(static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBitVector*>(TheField)->push_back(static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFGLenum*>(TheField)->push_back(static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt8*>(TheField)->push_back(static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt16*>(TheField)->push_back(static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt32*>(TheField)->push_back(static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt64*>(TheField)->push_back(static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal32*>(TheField)->push_back(static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal64*>(TheField)->push_back(static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor3f*>(TheField)->push_back(static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor4f*>(TheField)->push_back(static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec2f*>(TheField)->push_back(static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec3f*>(TheField)->push_back(static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec4f*>(TheField)->push_back(static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt2f*>(TheField)->push_back(static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt3f*>(TheField)->push_back(static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt4f*>(TheField)->push_back(static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFMatrix*>(TheField)->push_back(static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFQuaternion*>(TheField)->push_back(static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          //Volumes
          //Otherwise
          else
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  TheField->pushValueByStr((osg::Char8 *)lua_tostring(L, 3));
              osg::endEditCP((*arg1), TheMask);
          }

          return SWIG_arg;
    }
%}

namespace osg {

    class FieldDescription;
    class FieldContainerPtr;
    class FieldContainerType;
    class FieldContainer;
    class AttachmentContainer;
    class Attachment;
    class AttachmentPtr;
    class AttachmentContainerPtr;
    class NodePtr;
    class NodeCorePtr;
    class Node;
    class Matrix;
    class DynamicVolume;
    class BoxVolume;
    /******************************************************/
    /*              FieldDescription                    */
    /******************************************************/
    class FieldDescription
    {
      public :


        FieldDescription(const FieldDescription &source                     );

        virtual ~FieldDescription(void); 

        const Char8     *getCName       (void                ) const;

              UInt32     getTypeId      (void                ) const;  

              BitVector  getFieldMask   (void                ) const;
              void       setFieldMask   (BitVector vFieldMask);

              UInt32     getFieldId     (void                ) const;
              void       setFieldId     (UInt32 uiFieldId    );

        const Char8     *getDefaultValue(void                ) const;

        const TypeBase  &getFieldType   (void                ) const;

              bool       isInternal     (void                ) const;

              bool       isValid        (void                ) const;

    };

    /******************************************************/
    /*              FieldContainerPtr                    */
    /******************************************************/
    class FieldContainerPtr
    {
      public:

        typedef FieldContainer        StoredObjectType;
        typedef FieldContainerPtr     ObjectType;

        typedef FieldContainerPtrBase Inherited;

        FieldContainer *operator->(void);

        FieldContainerPtr(      void                         );
        /*FieldContainerPtr(const NullFieldContainerPtr &      );*/
        FieldContainerPtr(const FieldContainerPtr     &source);

        ~FieldContainerPtr(void); 

    };
    /******************************************************/
    /*              FieldContainerType                    */
    /******************************************************/
    class FieldContainerType : public DataType
    {
      public :

        FieldContainerType(const FieldContainerType &source);

        virtual ~FieldContainerType(void); 

        UInt16              getGroupId(void) const;
        FieldContainerType *getParent (void) const;

              FieldDescription *getFieldDescription (UInt32 uiFieldId);

              FieldDescription *findFieldDescription(const Char8 *szFieldName);

        const FieldDescription *findFieldDescription(
            const Char8 *szFieldName) const; 

        UInt32                 getNumFieldDescs(void) const;

        UInt32                 addDescription  (const FieldDescription &desc     );
        bool                   subDescription  (      UInt32            uiFieldId);

        FieldContainerPtr getPrototype(void                        ) const;
        bool              setPrototype(FieldContainerPtr pPrototype);

        bool isInitialized(void                           ) const;

        bool isAbstract   (void                           ) const;

        bool isDerivedFrom(const TypeBase           &other) const;
        bool isDerivedFrom(const FieldContainerType &other) const;    

        bool isNode       (void                           ) const;
        bool isNodeCore   (void                           ) const;
        bool isAttachment (void                           ) const;

        FieldContainerPtr createFieldContainer(void) const;
        NodePtr           createNode          (void) const;
        NodeCorePtr       createNodeCore      (void) const;
        AttachmentPtr     createAttachment    (void) const;

        virtual void dump(      UInt32    uiIndent = 0, 
                          const BitVector bvFlags  = 0) const;
    };

    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainer 
    {
      public:
        virtual       FieldContainerType &getType    (void);

        virtual const FieldContainerType &getType    (void) const;

                      UInt32              getTypeId  (void) const;

                      UInt16              getGroupId (void) const;

                const Char8              *getTypeName(void) const;

        virtual UInt32  getContainerSize(void) const = 0;


                Field  *getField        (      UInt32 fieldId  );

                Field  *getField        (const Char8 *fieldName);

        virtual FieldContainerPtr shallowCopy(void) const = 0;

      protected:
        FieldContainer(void);

        FieldContainer(const FieldContainer &obj);

        virtual ~FieldContainer (void);

    };
    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainerFactory
    {
      public :

        static FieldContainerFactory *the(void);
            
        FieldContainerType *findType    (      UInt32  uiTypeId) const;
        FieldContainerType *findType    (const Char8  *szName  ) const;
        UInt32              getNumTypes (void                  ) const;

              UInt16  findGroupId  (const Char8  *szName   ) const;
        const Char8  *findGroupName(      UInt16  uiGroupId) const;
            
              UInt16  getNumGroups (      void             ) const;


        FieldContainerPtr getContainer      (UInt32 uiFieldContainerId) const;

        FieldContainerPtr createFieldContainer(const Char8 *name) const;
        NodePtr           createNode          (const Char8 *name) const;
        NodeCorePtr       createNodeCore      (const Char8 *name) const;
        AttachmentPtr     createAttachment    (const Char8 *name) const;

      protected:
        FieldContainerFactory(void);

        virtual ~FieldContainerFactory(void); 
    };
    /******************************************************/
    /*                    AttachmentContainerPtr          */
    /******************************************************/
    class AttachmentContainerPtr : 
        public FieldContainerPtr
    {
      public:

        AttachmentContainerPtr(      void                          );
        AttachmentContainerPtr(const AttachmentContainerPtr &source);
        /*AttachmentContainerPtr(const NullFieldContainerPtr  &source);*/
        ~AttachmentContainerPtr(void);

        AttachmentContainer *operator->(void);
      protected:
    };

    /******************************************************/
    /*                    AttachmentContainer             */
    /******************************************************/
    class AttachmentContainer : public FieldContainer 
    {
      public:
        void          addAttachment (const AttachmentPtr &fieldContainerP, 
                                           UInt16         binding        = 0);

        void          subAttachment (const AttachmentPtr &fieldContainerP,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(      UInt32         groupId,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(const FieldContainerType &type,
                                       UInt16              binding   = 0);
      protected:
        AttachmentContainer(void);
        AttachmentContainer(const AttachmentContainer &source);
        ~AttachmentContainer(void);
    };

    const Char8 *getName(      AttachmentContainerPtr  container);
    
          void   setName(      AttachmentContainerPtr  container, 
                         const Char8                  *name     );

    /******************************************************/
    /*                    NodeCore                        */
    /******************************************************/
    class NodeCore : public AttachmentContainer
    {
      public:
        virtual void invalidateVolume(void);

      protected:
        NodeCore(void);
        NodeCore(const NodeCore &obj);
        virtual ~NodeCore(void);
    };
    /******************************************************/
    /*              NodePtr                               */
    /******************************************************/
    class NodePtr : public AttachmentContainerPtr
    {
      public:
         NodePtr(void);
         NodePtr(const NodePtr               &source);
         /*NodePtr(const NullFieldContainerPtr &source);*/


        ~NodePtr(void); 
        Node *operator->(void);
    };

    /******************************************************/
    /*              Node                                  */
    /******************************************************/
    class Node : public AttachmentContainer 
    {
      public:
        typedef NodePtr Ptr;

        NodeCorePtr getCore(      void             );

        void        setCore(const NodeCorePtr &core);
        
        NodePtr getParent(void);

        UInt32  getNChildren  (void                     ) const;
        
        void    addChild      (const NodePtr &childP    );

        void    insertChild   (      UInt32   childIndex, 
                               const NodePtr &childP    );

        void    replaceChild  (      UInt32   childIndex,    
                               const NodePtr &childP    );

        bool    replaceChildBy(const NodePtr &childP, 
                               const NodePtr &newChildP );

        Int32   findChild     (const NodePtr &childP    ) const;

        void    subChild      (const NodePtr &childP    );
        void    subChild      (      UInt32   childIndex);

        NodePtr getChild      (      UInt32   childIndex);
        
        bool   getActive  (void      ) const;

        void   setActive  (bool   val);

        void   setTravMask(UInt32 val);
        UInt32 getTravMask(void      ) const;

        void   setOcclusionMask(UInt8 val);
        UInt8  getOcclusionMask(void      ) const;

        NodePtr clone(void);
        
        Matrix getToWorld(void          );
        
        void   getToWorld(Matrix &result);
               DynamicVolume &getVolume       (bool update          );
               /*BoxVolume     &editVolume      (bool update          );*/
        /*const  BoxVolume     &getVolume       (void                 ) const;*/
               /*void           getWorldVolume  (BoxVolume     &result);*/
        
               void           updateVolume    (void                 );

               void           invalidateVolume(void                 );
      protected:
        Node(void);
        Node(const Node &source);
        virtual ~Node (void);
    };
    
    
    FieldContainerPtr getFieldContainer(const std::string &namestring);
}

