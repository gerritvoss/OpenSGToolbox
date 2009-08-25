
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
    
"    print(\"random number:\")\n"
"    print(osgbase.osgrand())\n"
"    print(osgbase.osgrand())\n"
"    print(osgbase.osgrand())\n");

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

