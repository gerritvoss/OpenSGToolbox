
#ifndef _OSGSFBASELISTDATATYPES_H_
#define _OSGSFBASELISTDATATYPES_H_
#ifdef __sgi
#pragma once
#endif

#include "ParticleSystem/OSGParticleSystemConfig.h"
#include "OSGBaseListTypes.h"
#include <OpenSG/OSGVecFieldDataType.h>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT>
struct FieldTraitsRecurseListBase : public FieldTraits
{
    enum                     { bHasParent = 0x00 };

#ifndef __hpux
    static const UInt32 uiTest = TypeTraits<ValueTypeT>::IsPOD == false;

    typedef typename 
    osgIF<uiTest == 1, 
          const ValueTypeT  , 
          const ValueTypeT & >::_IRet  ArgumentType;
#else
    typedef typename 
    osgIF<!TypeTraits<ValueTypeT>::IsPOD, 
          const ValueTypeT  , 
          const ValueTypeT & >::_IRet  ArgumentType;
#endif
    
    static UInt32 getBinSize (const ValueTypeT &oObject)
    {
        return sizeof(UInt32) +
               oObject.size() * sizeof(typename ValueTypeT::value_type);
    }

    static UInt32 getBinSize (const ValueTypeT *pObjectStore,
                                    UInt32      uiNumObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const ValueTypeT        &oObject)
    {
       //Put the number of List Elements
       pMem.putValue( static_cast<UInt32>(oObject.size()) );
       
       //Loop through Each Element and copy it to binary
       typename ValueTypeT::const_iterator ListIter;
       for(ListIter = oObject.begin() ; ListIter != oObject.end() ; ++ListIter)
       {
          //copyToBin(pMem, (*ListIter));
       }
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        //pMem.putValues(&pObjectStore[0][0], ValueTypeT::_iSize*uiNumObjects);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        &oObject)
    {
        //pMem.getValues(&oObject[0], ValueTypeT::_iSize);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        //pMem.getValues(&pObjectStore[0][0], ValueTypeT::_iSize*uiNumObjects);
    }
};

template <>
struct OSG_PARTICLE_SYSTEM_CLASS_API FieldDataTraits<Vec3fList> : public FieldTraitsRecurseListBase<Vec3fList>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3fList>  Self;


    enum             { StringConvertable = 0x01 };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3fList";           }
    static Char8    *getMName     (void) { return "MFVec3fList";           }

    static Vec3fList    getDefault   (void) { return Vec3fList();             }

    static bool      getFromString(      Vec3fList  &outVal,
                                   const Char8 *&inVal)
    {
        return false;
    }

    static void      putToString  (const      Vec3fList &inVal,
                                         std::string &outStr)
    {
        outStr.assign("Vec3fList");
    }
};

template <>
struct OSG_PARTICLE_SYSTEM_CLASS_API FieldDataTraits<Pnt3fList> : public FieldTraitsRecurseListBase<Pnt3fList>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3fList>  Self;


    enum             { StringConvertable = 0x01 };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3fList";           }
    static Char8    *getMName     (void) { return "MFPnt3fList";           }

    static Pnt3fList    getDefault   (void) { return Pnt3fList();             }

    static bool      getFromString(      Pnt3fList  &outVal,
                                   const Char8 *&inVal)
    {
        return false;
    }

    static void      putToString  (const      Pnt3fList &inVal,
                                         std::string &outStr)
    {
        outStr.assign("Pnt3fList");
    }
};

template <>
struct OSG_PARTICLE_SYSTEM_CLASS_API FieldDataTraits<Color4fList> : public FieldTraitsRecurseListBase<Color4fList>
{
    static  DataType                _type;
    typedef FieldDataTraits<Color4fList>  Self;


    enum             { StringConvertable = 0x01 };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFColor4fList";           }
    static Char8    *getMName     (void) { return "MFColor4fList";           }

    static Color4fList    getDefault   (void) { return Color4fList();             }

    static bool      getFromString(      Color4fList  &outVal,
                                   const Char8 *&inVal)
    {
        return false;
    }

    static void      putToString  (const      Color4fList &inVal,
                                         std::string &outStr)
    {
        outStr.assign("Color4fList");
    }
};

template <>
struct OSG_PARTICLE_SYSTEM_CLASS_API FieldDataTraits<Real32List> : public FieldTraitsRecurseListBase<Real32List>
{
    static  DataType                _type;
    typedef FieldDataTraits<Real32List>  Self;


    enum             { StringConvertable = 0x01 };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFReal32List";           }
    static Char8    *getMName     (void) { return "MFReal32List";           }

    static Real32List    getDefault   (void) { return Real32List();             }

    static bool      getFromString(      Real32List  &outVal,
                                   const Char8 *&inVal)
    {
        return false;
    }

    static void      putToString  (const      Real32List &inVal,
                                         std::string &outStr)
    {
        outStr.assign("Real32List");
    }
};

template <>
struct OSG_PARTICLE_SYSTEM_CLASS_API FieldDataTraits<UInt64List> : public FieldTraitsRecurseListBase<UInt64List>
{
    static  DataType                _type;
    typedef FieldDataTraits<UInt64List>  Self;


    enum             { StringConvertable = 0x01 };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFUInt64List";           }
    static Char8    *getMName     (void) { return "MFUInt64List";           }

    static UInt64List    getDefault   (void) { return UInt64List();             }

    static bool      getFromString(      UInt64List  &outVal,
                                   const Char8 *&inVal)
    {
        return false;
    }

    static void      putToString  (const      UInt64List &inVal,
                                         std::string &outStr)
    {
        outStr.assign("UInt64List");
    }
};
OSG_END_NAMESPACE

#endif /* _OSGSFBASELISTDATATYPES_H_ */
