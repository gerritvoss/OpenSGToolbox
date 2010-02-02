
// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#include <string>
#include "OSGLuaManager.h"

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
"    quat1 = OSG.Quaternion()\n"
"    print('Quat length: ', quat1:length())\n"
"    mat1 = OSG.Matrix(2.0,0.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0, 0.0,0.0,0.0,1.0)\n"
"    print('Matrix Det: ', mat1:det())\n"
"    vec1 = OSG.Vec3f(0.0,1.0,0.0)\n"
"    pnt1 = OSG.Pnt3f(0.0,1.0,0.0)\n"
"    pnt2 = OSG.Pnt3f(1.0,0.0,0.0)\n"
"    print('Distance From pnt1 to pnt2: ',pnt1:dist(pnt2))\n"
"    print('Is pnt1 Zero: ',pnt1:isZero())\n"
"    print('OpenSG Version: ',OSG.version())\n"

"    color1 = OSG.Color3f(0.0, 1.0, 0.0)\n"
"    color2 = OSG.Color3f(1.0, 0.0, 0.0)\n"
"    color3 = color1 + color2\n"
"    print('Color: ',color3:red(), color3:green(), color3:blue())\n"

"    temp2 = OSG.createFieldContainer(\"Transform\")\n"
"    temp2:setFieldValue(\"matrix\",mat1)\n"

"    temp = OSG.createFieldContainer(\"Node\")\n"
"    temp:setFieldValue(\"core\",temp2)\n"

"    print('Matrix Det: ', temp:getFieldValue(\"core\"):getFieldValue(\"matrix\"):det())\n"
"    print('Node TravMask: ',temp:getFieldValue(\"travMask\"))\n");

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

