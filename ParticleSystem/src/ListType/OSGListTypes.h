#ifndef _OSGLISGTYPES_H_
#define _OSGLISGTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGParticleSystemDef.h"
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFieldType.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGBaseFieldDataType.h>

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

#include "OSGBaseListTypes.h"

#include <string.h>

OSG_BEGIN_NAMESPACE

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldDataTraits<Vec3fList> : 
    public FieldTraitsRecurseBase<Vec3fList>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFVec3fList"; }
    static Char8          *getMName     (void) { return "MFVec3fList"; }

    // Create a default instance of the class, needed for Field creation
    static Vec3fList       getDefault   (void) { return Vec3fList();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const Vec3fList   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types
        typedef TypeTraits<UInt32> tt;

        outVal.append(tt::putToString(static_cast<UInt32>(inVal.size())));

        Vec3fList::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal.append(";");
            FieldDataTraits<Vec3f>::putToString( (*Itor), tempOut );
            outVal.append(tempOut);
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      Vec3fList  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 Size(0);
        
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

        const Char8 *curInString(inVal);
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            curInString = strchr(curInString, ';');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            outVal.push_back(Vec3f());
            FieldDataTraits<Vec3f>::getFromString( outVal.back(), curInString );
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const Vec3fList & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        return sizeof(UInt32) + obj.size()*sizeof(Vec3f::ValueType);
    }

    static UInt32 getBinSize (const Vec3fList *obj, UInt32 num)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        //Multiplied by the num of Vec3fLists
        return (sizeof(UInt32) + obj->size()*sizeof(Vec3f::ValueType)) * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Vec3fList         &obj)
    {
        //Number of items in the list
        bdh.putValue(static_cast<UInt32>(obj.size()));

        Vec3fList::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            FieldDataTraits<Vec3f>::copyToBin( bdh, (*Itor) );
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Vec3fList         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            Vec3fList         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            obj.push_back(Vec3f());
            FieldDataTraits<Vec3f>::copyFromBin( bdh, obj.back() );
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            Vec3fList         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

template <>
struct FieldDataTraits<Pnt3fList> : 
    public FieldTraitsRecurseBase<Pnt3fList>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFPnt3fList"; }
    static Char8          *getMName     (void) { return "MFPnt3fList"; }

    // Create a default instance of the class, needed for Field creation
    static Pnt3fList       getDefault   (void) { return Pnt3fList();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const Pnt3fList   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types
        typedef TypeTraits<UInt32> tt;

        outVal.append(tt::putToString(static_cast<UInt32>(inVal.size())));

        Pnt3fList::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal.append(";");
            FieldDataTraits<Pnt3f>::putToString( (*Itor), tempOut );
            outVal.append(tempOut);
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      Pnt3fList  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 Size(0);
        
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

        const Char8 *curInString(inVal);
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            curInString = strchr(curInString, ';');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            outVal.push_back(Pnt3f());
            FieldDataTraits<Pnt3f>::getFromString( outVal.back(), curInString );
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const Pnt3fList & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        return sizeof(UInt32) + obj.size()*sizeof(Pnt3f::ValueType);
    }

    static UInt32 getBinSize (const Pnt3fList *obj, UInt32 num)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        //Multiplied by the num of Pnt3fLists
        return (sizeof(UInt32) + obj->size()*sizeof(Pnt3f::ValueType)) * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Pnt3fList         &obj)
    {
        //Number of items in the list
        bdh.putValue(static_cast<UInt32>(obj.size()));

        Pnt3fList::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            FieldDataTraits<Pnt3f>::copyToBin( bdh, (*Itor) );
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Pnt3fList         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            Pnt3fList         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            obj.push_back(Pnt3f());
            FieldDataTraits<Pnt3f>::copyFromBin( bdh, obj.back() );
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            Pnt3fList         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

template <>
struct FieldDataTraits<Color4fList> : 
    public FieldTraitsRecurseBase<Color4fList>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFColor4fList"; }
    static Char8          *getMName     (void) { return "MFColor4fList"; }

    // Create a default instance of the class, needed for Field creation
    static Color4fList       getDefault   (void) { return Color4fList();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const Color4fList   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types
        typedef TypeTraits<UInt32> tt;

        outVal.append(tt::putToString(static_cast<UInt32>(inVal.size())));

        Color4fList::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal.append(";");
            FieldDataTraits<Color4f>::putToString( (*Itor), tempOut );
            outVal.append(tempOut);
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      Color4fList  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 Size(0);
        
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

        const Char8 *curInString(inVal);
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            curInString = strchr(curInString, ';');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            outVal.push_back(Color4f());
            FieldDataTraits<Color4f>::getFromString( outVal.back(), curInString );
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const Color4fList & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        return sizeof(UInt32) + obj.size()*sizeof(Color4f::ValueType);
    }

    static UInt32 getBinSize (const Color4fList *obj, UInt32 num)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        //Multiplied by the num of Color4fLists
        return (sizeof(UInt32) + obj->size()*sizeof(Color4f::ValueType)) * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Color4fList         &obj)
    {
        //Number of items in the list
        bdh.putValue(static_cast<UInt32>(obj.size()));

        Color4fList::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            FieldDataTraits<Color4f>::copyToBin( bdh, (*Itor) );
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Color4fList         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            Color4fList         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            obj.push_back(Color4f());
            FieldDataTraits<Color4f>::copyFromBin( bdh, obj.back() );
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            Color4fList         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

template <>
struct FieldDataTraits<Real32List> : 
    public FieldTraitsRecurseBase<Real32List>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFReal32List"; }
    static Char8          *getMName     (void) { return "MFReal32List"; }

    // Create a default instance of the class, needed for Field creation
    static Real32List       getDefault   (void) { return Real32List();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const Real32List   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types

        outVal.append(TypeTraits<UInt32>::putToString(static_cast<UInt32>(inVal.size())));

        Real32List::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal.append(";");
            outVal.append(TypeTraits<Real32>::putToString(static_cast<UInt32>((*Itor))));
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      Real32List  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 Size(0);
        
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

        const Char8 *curInString(inVal);
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            curInString = strchr(curInString, ';');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            outVal.push_back(0.0);
            if(sscanf(curInString,"%d", &outVal.back()) != 1)
            {
                return false;
            }
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const Real32List & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        return sizeof(UInt32) + obj.size()*sizeof(Real32);
    }

    static UInt32 getBinSize (const Real32List *obj, UInt32 num)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        //Multiplied by the num of Real32Lists
        return (sizeof(UInt32) + obj->size()*sizeof(Real32)) * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Real32List         &obj)
    {
        //Number of items in the list
        bdh.putValue(static_cast<UInt32>(obj.size()));

        Real32List::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            bdh.putValue((*Itor));
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Real32List         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            Real32List         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            obj.push_back(0.0);
            bdh.getValue(obj.back());
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            Real32List         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

template <>
struct FieldDataTraits<UInt64List> : 
    public FieldTraitsRecurseBase<UInt64List>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFUInt64List"; }
    static Char8          *getMName     (void) { return "MFUInt64List"; }

    // Create a default instance of the class, needed for Field creation
    static UInt64List       getDefault   (void) { return UInt64List();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const UInt64List   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types

        outVal.append(TypeTraits<UInt32>::putToString(static_cast<UInt32>(inVal.size())));

        UInt64List::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal.append(";");
            outVal.append(TypeTraits<UInt64>::putToString(static_cast<UInt32>((*Itor))));
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      UInt64List  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 Size(0);
        
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

        const Char8 *curInString(inVal);
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            curInString = strchr(curInString, ';');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            outVal.push_back(0.0);
            if(sscanf(curInString,"%d", &outVal.back()) != 1)
            {
                return false;
            }
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const UInt64List & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        return sizeof(UInt32) + obj.size()*sizeof(UInt64);
    }

    static UInt32 getBinSize (const UInt64List *obj, UInt32 num)
    {
        //Size:
        //Size of a UInt32 -> number of items in the list
        //Size of all of all the ValueType Items
        //Multiplied by the num of UInt64Lists
        return (sizeof(UInt32) + obj->size()*sizeof(UInt64)) * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const UInt64List         &obj)
    {
        //Number of items in the list
        bdh.putValue(static_cast<UInt32>(obj.size()));

        UInt64List::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            bdh.putValue((*Itor));
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const UInt64List         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            UInt64List         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            obj.push_back(0.0);
            bdh.getValue(obj.back());
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            UInt64List         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<Vec3fList> SFVec3fList;
typedef MField<Vec3fList> MFVec3fList;
typedef SField<Pnt3fList> SFPnt3fList;
typedef MField<Pnt3fList> MFPnt3fList;
typedef SField<Color4fList> SFColor4fList;
typedef MField<Color4fList> MFColor4fList;
typedef SField<Real32List> SFReal32List;
typedef MField<Real32List> MFReal32List;
typedef SField<UInt64List> SFUInt64List;
typedef MField<UInt64List> MFUInt64List;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILEPARTICLESYSTEMINST

// Declare the functions/classes/methods Windows needs
OSG_DLLEXPORT_DECL1(SField, Vec3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(MField, Vec3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(SField, Pnt3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(MField, Pnt3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(SField, Color4fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(MField, Color4fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(SField, Real32List, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(MField, Real32List, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(SField, UInt64List, OSG_PARTICLESYSTEMLIB_DLLMAPPING )
OSG_DLLEXPORT_DECL1(MField, UInt64List, OSG_PARTICLESYSTEMLIB_DLLMAPPING )

#endif


OSG_END_NAMESPACE

#define OSGLISGTYPES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGLISGTYPES_H_ */
