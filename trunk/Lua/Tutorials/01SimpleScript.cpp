
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
    
"    vec1 = OSGBase.Vec3f(0.0,1.0,0.0)\n"
"    pnt1 = OSGBase.Pnt3f(0.0,1.0,0.0)\n"
"    pnt2 = OSGBase.Pnt3f(1.0,0.0,0.0)\n"
"    print(pnt1:dist(pnt2))\n"
"    print(pnt1:isZero())\n"

"    color1 = OSGBase.Color3f(0.0, 1.0, 0.0)\n"
"    color2 = OSGBase.Color3f(1.0, 0.0, 0.0)\n"
"    color3 = color1 + color2\n"
"    print(color3:red())\n"
"    print(color3:green())\n"
"    print(color3:blue())\n"

"    print(\"random number:\")\n"
"    print(OSGBase.osgrand())\n"
"    print(OSGBase.osgrand())\n"
"    print(OSGBase.osgrand())\n");

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

