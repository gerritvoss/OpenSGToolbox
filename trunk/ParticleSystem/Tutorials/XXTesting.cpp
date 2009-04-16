// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed



// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGBinaryDataHandler.h>

#include <OpenSG/ParticleSystem/OSGListTypes.h>
#include <fstream>

OSG_USING_NAMESPACE

class BinaryOutputFileHandler : public BinaryDataHandler
{
public:
    BinaryOutputFileHandler(std::ostream &os) :
     BinaryDataHandler(0),
     _os(os)
 {
     _writeMemory.resize(10000);
     writeBufAdd(&_writeMemory[0], _writeMemory.size());
 }

    virtual ~BinaryOutputFileHandler()
    {
    }

    void write(MemoryHandle mem, UInt32 size)
    {
        _os.write((const char *) mem, size);
    }

private:

    std::vector<UInt8> _writeMemory;
    std::ostream &_os;
};

class BinaryInputFileHandler : public BinaryDataHandler
{
public:
    BinaryInputFileHandler(std::istream &is) :
     BinaryDataHandler(0),
     _is(is)
 {
     _readMemory.resize(10000);
     readBufAdd(&_readMemory[0], _readMemory.size());
 }

    virtual ~BinaryInputFileHandler()
    {
    }
    void read(MemoryHandle mem, UInt32 size)
    {
        _is.read((char *) mem, size);
    }

private:

    std::vector<UInt8> _readMemory;
    std::istream &_is;
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osg::osgInit(argc,argv);

    osg::SFVec3fList ListType;

    ListType.getValue().push_back(osg::Vec3f(0.0,0.0,0.0));
    ListType.getValue().push_back(osg::Vec3f(1.0,0.0,0.0));
    ListType.getValue().push_back(osg::Vec3f(2.0,0.0,0.0));
    ListType.getValue().push_back(osg::Vec3f(3.0,0.0,0.0));

    std::string Output("");

    ListType.getValueByStr(Output);

    std::cout << Output << std::endl;

    
    osg::SFVec3fList LoadedList;
    LoadedList.getValue().push_back(osg::Vec3f(3.0,0.0,0.0));
    LoadedList.getValue().push_back(osg::Vec3f(2.0,0.0,0.0));
    LoadedList.getValue().push_back(osg::Vec3f(1.0,0.0,0.0));
    LoadedList.getValue().push_back(osg::Vec3f(0.0,0.0,0.0));

    LoadedList.pushValueByStr(Output.c_str());
    std::string LoadedOutput("");

    LoadedList.getValueByStr(LoadedOutput);

    std::cout << LoadedOutput << std::endl;

    //Save Data to Binary File
    std::ofstream OutFile;
    OutFile.open("TestOutput.osb", std::ios::out | std::ios::binary);
    BinaryOutputFileHandler Writer(OutFile);
    LoadedList.copyToBin(Writer);
    Writer.flush();

    OutFile.close();

    //Load data from binary
    osg::SFVec3fList BinLoadedList;
    BinLoadedList.getValue().push_back(osg::Vec3f(3.0,0.0,0.0));
    BinLoadedList.getValue().push_back(osg::Vec3f(2.0,0.0,0.0));
    BinLoadedList.getValue().push_back(osg::Vec3f(1.0,0.0,0.0));
    BinLoadedList.getValue().push_back(osg::Vec3f(0.0,0.0,0.0));

    std::ifstream InFile;
    InFile.open("TestOutput.osb", std::ios::in | std::ios::binary);
    BinaryInputFileHandler Reader(InFile);
    BinLoadedList.copyFromBin(Reader);

    InFile.close();

    BinLoadedList.pushValueByStr(Output.c_str());

    std::string BinaryLoadedOutput("");
    BinLoadedList.getValueByStr(BinaryLoadedOutput);

    std::cout << "BinLoadedList" << std::endl;
    std::cout << BinaryLoadedOutput << std::endl;


    //OSG exit
    osg::osgExit();

    return 0;
}
