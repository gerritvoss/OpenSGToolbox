
// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>

#include <string>
#include <OpenSG/Lua/OSGLuaManager.h>

// activate the opensg namespace
OSG_USING_NAMESPACE

std::string genHelloWorldScript(void)
{
    return std::string("print(\"Hello World\")");
}

std::string genFactorialScript(void)
{
    std::string Script(
"    -- defines a factorial function\n"
"    function fact (n)\n"
"      if n == 0 then\n"
"        return 1\n"
"      else\n"
"        return n * fact(n-1)\n"
"      end\n"
"    end\n"
    
"    print(\"enter a number:\")\n"
"    a = io.read(\"*number\")        -- read a number\n"
"    print(fact(a))");

    return Script;

}

std::string genOpenSGScript(void)
{
    std::string Script(
"    -- call OpenSG's osgrand function\n"
    

"    quat1 = OSG.Quaternion()\n"
"    print( quat1:length())\n"
"    mat1 = OSG.Matrix(2.0,0.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0, 0.0,0.0,0.0,1.0)\n"
"    print( mat1:det())\n"
"    vec1 = OSG.Vec3f(0.0,1.0,0.0)\n"
"    pnt1 = OSG.Pnt3f(0.0,1.0,0.0)\n"
"    pnt2 = OSG.Pnt3f(1.0,0.0,0.0)\n"
"    print(pnt1:dist(pnt2))\n"
"    print(pnt1:isZero())\n"
"    print(OSG.version())\n"

"    color1 = OSG.Color3f(0.0, 1.0, 0.0)\n"
"    color2 = OSG.Color3f(1.0, 0.0, 0.0)\n"
"    color3 = color1 + color2\n"
"    print(color3:red())\n"
"    print(color3:green())\n"
"    print(color3:blue())\n"
"    FCFact = OSG.FieldContainerFactory_the()\n"
"    temp = FCFact:createFieldContainer(\"Node\")\n"
"    --print(temp:getTypeId())\n");

    return Script;

}

int main(int argc, char **argv)
{
    osgInit(argc, argv);

    LuaManager::the()->runScript(genHelloWorldScript());

    //LuaManager::the()->runScript(genFactorialScript());

    LuaManager::the()->runScript(genOpenSGScript());

    osgExit();
    return 0;
}

