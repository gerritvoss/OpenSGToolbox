/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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
#include "OSGGLenumUtils.h"
#include <assert.h>

OSG_BEGIN_NAMESPACE

GLenum fromString(const std::string& value)
{
    assert(false && "Not implemented.");
    return 0x0;
}

std::string toString(const GLenum& value)
{
    switch(value)
    {
    case  0x0 :
        return std::string( "GL_NO_ERROR | GL_FALSE | GL_NONE | GL_POINTS | GL_ZERO" );
        break;
    case  0x1 :
        return std::string( "GL_ONE | GL_CURRENT_BIT | GL_TRUE | GL_CLIENT_PIXEL_STORE_BIT | GL_LINES" );
        break;
    case  0x2 :
        return std::string( "GL_POINT_BIT | GL_LINE_LOOP | GL_CLIENT_VERTEX_ARRAY_BIT" );
        break;
    case  0x3 :
        return std::string( "GL_LINE_STRIP" );
        break;
    case  0x4 :
        return std::string( "GL_TRIANGLES | GL_LINE_BIT" );
        break;
    case  0x5 :
        return std::string( "GL_TRIANGLE_STRIP" );
        break;
    case  0x6 :
        return std::string( "GL_TRIANGLE_FAN" );
        break;
    case  0x7 :
        return std::string( "GL_QUADS" );
        break;
    case  0x8 :
        return std::string( "GL_POLYGON_BIT | GL_QUAD_STRIP" );
        break;
    case  0x9 :
        return std::string( "GL_POLYGON" );
        break;
    case  0x10 :
        return std::string( "GL_POLYGON_STIPPLE_BIT" );
        break;
    case  0x20 :
        return std::string( "GL_PIXEL_MODE_BIT" );
        break;
    case  0x40 :
        return std::string( "GL_LIGHTING_BIT" );
        break;
    case  0x80 :
        return std::string( "GL_FOG_BIT" );
        break;
    case  0x100 :
        return std::string( "GL_DEPTH_BUFFER_BIT | GL_ACCUM" );
        break;
    case  0x101 :
        return std::string( "GL_LOAD" );
        break;
    case  0x102 :
        return std::string( "GL_RETURN" );
        break;
    case  0x103 :
        return std::string( "GL_MULT" );
        break;
    case  0x104 :
        return std::string( "GL_ADD" );
        break;
    case  0x200 :
        return std::string( "GL_NEVER | GL_ACCUM_BUFFER_BIT" );
        break;
    case  0x201 :
        return std::string( "GL_LESS" );
        break;
    case  0x202 :
        return std::string( "GL_EQUAL" );
        break;
    case  0x203 :
        return std::string( "GL_LEQUAL" );
        break;
    case  0x204 :
        return std::string( "GL_GREATER" );
        break;
    case  0x205 :
        return std::string( "GL_NOTEQUAL" );
        break;
    case  0x206 :
        return std::string( "GL_GEQUAL" );
        break;
    case  0x207 :
        return std::string( "GL_ALWAYS" );
        break;
    case  0x300 :
        return std::string( "GL_SRC_COLOR" );
        break;
    case  0x301 :
        return std::string( "GL_ONE_MINUS_SRC_COLOR" );
        break;
    case  0x302 :
        return std::string( "GL_SRC_ALPHA" );
        break;
    case  0x303 :
        return std::string( "GL_ONE_MINUS_SRC_ALPHA" );
        break;
    case  0x304 :
        return std::string( "GL_DST_ALPHA" );
        break;
    case  0x305 :
        return std::string( "GL_ONE_MINUS_DST_ALPHA" );
        break;
    case  0x306 :
        return std::string( "GL_DST_COLOR" );
        break;
    case  0x307 :
        return std::string( "GL_ONE_MINUS_DST_COLOR" );
        break;
    case  0x308 :
        return std::string( "GL_SRC_ALPHA_SATURATE" );
        break;
    case  0x400 :
        return std::string( "GL_FRONT_LEFT | GL_STENCIL_BUFFER_BIT" );
        break;
    case  0x401 :
        return std::string( "GL_FRONT_RIGHT" );
        break;
    case  0x402 :
        return std::string( "GL_BACK_LEFT" );
        break;
    case  0x403 :
        return std::string( "GL_BACK_RIGHT" );
        break;
    case  0x404 :
        return std::string( "GL_FRONT" );
        break;
    case  0x405 :
        return std::string( "GL_BACK" );
        break;
    case  0x406 :
        return std::string( "GL_LEFT" );
        break;
    case  0x407 :
        return std::string( "GL_RIGHT" );
        break;
    case  0x408 :
        return std::string( "GL_FRONT_AND_BACK" );
        break;
    case  0x409 :
        return std::string( "GL_AUX0" );
        break;
    case  0x500 :
        return std::string( "GL_INVALID_ENUM" );
        break;
    case  0x501 :
        return std::string( "GL_INVALID_VALUE" );
        break;
    case  0x502 :
        return std::string( "GL_INVALID_OPERATION" );
        break;
    case  0x503 :
        return std::string( "GL_STACK_OVERFLOW" );
        break;
    case  0x504 :
        return std::string( "GL_STACK_UNDERFLOW" );
        break;
    case  0x505 :
        return std::string( "GL_OUT_OF_MEMORY" );
        break;
    case  0x600 :
        return std::string( "GL_2D" );
        break;
    case  0x601 :
        return std::string( "GL_3D" );
        break;
    case  0x602 :
        return std::string( "GL_3D_COLOR" );
        break;
    case  0x603 :
        return std::string( "GL_3D_COLOR_TEXTURE" );
        break;
    case  0x604 :
        return std::string( "GL_4D_COLOR_TEXTURE" );
        break;
    case  0x700 :
        return std::string( "GL_PASS_THROUGH_TOKEN" );
        break;
    case  0x701 :
        return std::string( "GL_POINT_TOKEN" );
        break;
    case  0x702 :
        return std::string( "GL_LINE_TOKEN" );
        break;
    case  0x703 :
        return std::string( "GL_POLYGON_TOKEN" );
        break;
    case  0x704 :
        return std::string( "GL_BITMAP_TOKEN" );
        break;
    case  0x705 :
        return std::string( "GL_DRAW_PIXEL_TOKEN" );
        break;
    case  0x706 :
        return std::string( "GL_COPY_PIXEL_TOKEN" );
        break;
    case  0x707 :
        return std::string( "GL_LINE_RESET_TOKEN" );
        break;
    case  0x800 :
        return std::string( "GL_EXP | GL_VIEWPORT_BIT" );
        break;
    case  0x801 :
        return std::string( "GL_EXP2" );
        break;
    case  0x900 :
        return std::string( "GL_CW" );
        break;
    case  0x901 :
        return std::string( "GL_CCW" );
        break;
    case  0x1000 :
        return std::string( "GL_TEXTURE_WIDTH | GL_TRANSFORM_BIT" );
        break;
    case  0x1001 :
        return std::string( "GL_TEXTURE_HEIGHT" );
        break;
    case  0x1003 :
        return std::string( "GL_TEXTURE_INTERNAL_FORMAT" );
        break;
    case  0x1004 :
        return std::string( "GL_TEXTURE_BORDER_COLOR" );
        break;
    case  0x1005 :
        return std::string( "GL_TEXTURE_BORDER" );
        break;
    case  0x1100 :
        return std::string( "GL_DONT_CARE" );
        break;
    case  0x1101 :
        return std::string( "GL_FASTEST" );
        break;
    case  0x1102 :
        return std::string( "GL_NICEST" );
        break;
    case  0x1200 :
        return std::string( "GL_AMBIENT" );
        break;
    case  0x1201 :
        return std::string( "GL_DIFFUSE" );
        break;
    case  0x1202 :
        return std::string( "GL_SPECULAR" );
        break;
    case  0x1203 :
        return std::string( "GL_POSITION" );
        break;
    case  0x1204 :
        return std::string( "GL_SPOT_DIRECTION" );
        break;
    case  0x1205 :
        return std::string( "GL_SPOT_EXPONENT" );
        break;
    case  0x1206 :
        return std::string( "GL_SPOT_CUTOFF" );
        break;
    case  0x1207 :
        return std::string( "GL_CONSTANT_ATTENUATION" );
        break;
    case  0x1208 :
        return std::string( "GL_LINEAR_ATTENUATION" );
        break;
    case  0x1209 :
        return std::string( "GL_QUADRATIC_ATTENUATION" );
        break;
    case  0x1300 :
        return std::string( "GL_COMPILE" );
        break;
    case  0x1301 :
        return std::string( "GL_COMPILE_AND_EXECUTE" );
        break;
    case  0x1400 :
        return std::string( "GL_BYTE" );
        break;
    case  0x1401 :
        return std::string( "GL_UNSIGNED_BYTE" );
        break;
    case  0x1402 :
        return std::string( "GL_SHORT" );
        break;
    case  0x1403 :
        return std::string( "GL_UNSIGNED_SHORT" );
        break;
    case  0x1404 :
        return std::string( "GL_INT" );
        break;
    case  0x1405 :
        return std::string( "GL_UNSIGNED_INT" );
        break;
    case  0x1406 :
        return std::string( "GL_FLOAT" );
        break;
    case  0x1407 :
        return std::string( "GL_2_BYTES" );
        break;
    case  0x1408 :
        return std::string( "GL_3_BYTES" );
        break;
    case  0x1409 :
        return std::string( "GL_4_BYTES" );
        break;
    case  0x1500 :
        return std::string( "GL_CLEAR" );
        break;
    case  0x1501 :
        return std::string( "GL_AND" );
        break;
    case  0x1502 :
        return std::string( "GL_AND_REVERSE" );
        break;
    case  0x1503 :
        return std::string( "GL_COPY" );
        break;
    case  0x1504 :
        return std::string( "GL_AND_INVERTED" );
        break;
    case  0x1505 :
        return std::string( "GL_NOOP" );
        break;
    case  0x1506 :
        return std::string( "GL_XOR" );
        break;
    case  0x1507 :
        return std::string( "GL_OR" );
        break;
    case  0x1508 :
        return std::string( "GL_NOR" );
        break;
    case  0x1509 :
        return std::string( "GL_EQUIV" );
        break;
    case  0x1600 :
        return std::string( "GL_EMISSION" );
        break;
    case  0x1601 :
        return std::string( "GL_SHININESS" );
        break;
    case  0x1602 :
        return std::string( "GL_AMBIENT_AND_DIFFUSE" );
        break;
    case  0x1603 :
        return std::string( "GL_COLOR_INDEXES" );
        break;
    case  0x1700 :
        return std::string( "GL_MODELVIEW" );
        break;
    case  0x1701 :
        return std::string( "GL_PROJECTION" );
        break;
    case  0x1702 :
        return std::string( "GL_TEXTURE" );
        break;
    case  0x1800 :
        return std::string( "GL_COLOR" );
        break;
    case  0x1801 :
        return std::string( "GL_DEPTH" );
        break;
    case  0x1802 :
        return std::string( "GL_STENCIL" );
        break;
    case  0x1900 :
        return std::string( "GL_COLOR_INDEX" );
        break;
    case  0x1901 :
        return std::string( "GL_STENCIL_INDEX" );
        break;
    case  0x1902 :
        return std::string( "GL_DEPTH_COMPONENT" );
        break;
    case  0x1903 :
        return std::string( "GL_RED" );
        break;
    case  0x1904 :
        return std::string( "GL_GREEN" );
        break;
    case  0x1905 :
        return std::string( "GL_BLUE" );
        break;
    case  0x1906 :
        return std::string( "GL_ALPHA" );
        break;
    case  0x1907 :
        return std::string( "GL_RGB" );
        break;
    case  0x1908 :
        return std::string( "GL_RGBA" );
        break;
    case  0x1909 :
        return std::string( "GL_LUMINANCE" );
        break;
    case  0x2000 :
        return std::string( "GL_S | GL_ENABLE_BIT" );
        break;
    case  0x2001 :
        return std::string( "GL_T" );
        break;
    case  0x2002 :
        return std::string( "GL_R" );
        break;
    case  0x2003 :
        return std::string( "GL_Q" );
        break;
    case  0x2100 :
        return std::string( "GL_MODULATE" );
        break;
    case  0x2101 :
        return std::string( "GL_DECAL" );
        break;
    case  0x2200 :
        return std::string( "GL_TEXTURE_ENV_MODE" );
        break;
    case  0x2201 :
        return std::string( "GL_TEXTURE_ENV_COLOR" );
        break;
    case  0x2300 :
        return std::string( "GL_TEXTURE_ENV" );
        break;
    case  0x2400 :
        return std::string( "GL_EYE_LINEAR" );
        break;
    case  0x2401 :
        return std::string( "GL_OBJECT_LINEAR" );
        break;
    case  0x2402 :
        return std::string( "GL_SPHERE_MAP" );
        break;
    case  0x2500 :
        return std::string( "GL_TEXTURE_GEN_MODE" );
        break;
    case  0x2501 :
        return std::string( "GL_OBJECT_PLANE" );
        break;
    case  0x2502 :
        return std::string( "GL_EYE_PLANE" );
        break;
    case  0x2600 :
        return std::string( "GL_NEAREST" );
        break;
    case  0x2601 :
        return std::string( "GL_LINEAR" );
        break;
    case  0x2700 :
        return std::string( "GL_NEAREST_MIPMAP_NEAREST" );
        break;
    case  0x2701 :
        return std::string( "GL_LINEAR_MIPMAP_NEAREST" );
        break;
    case  0x2702 :
        return std::string( "GL_NEAREST_MIPMAP_LINEAR" );
        break;
    case  0x2703 :
        return std::string( "GL_LINEAR_MIPMAP_LINEAR" );
        break;
    case  0x2800 :
        return std::string( "GL_TEXTURE_MAG_FILTER" );
        break;
    case  0x2801 :
        return std::string( "GL_TEXTURE_MIN_FILTER" );
        break;
    case  0x2802 :
        return std::string( "GL_TEXTURE_WRAP_S" );
        break;
    case  0x2803 :
        return std::string( "GL_TEXTURE_WRAP_T" );
        break;
    case  0x2900 :
        return std::string( "GL_CLAMP" );
        break;
    case  0x2901 :
        return std::string( "GL_REPEAT" );
        break;
    case  0x3000 :
        return std::string( "GL_CLIP_PLANE0" );
        break;
    case  0x3001 :
        return std::string( "GL_CLIP_PLANE1" );
        break;
    case  0x3002 :
        return std::string( "GL_CLIP_PLANE2" );
        break;
    case  0x3003 :
        return std::string( "GL_CLIP_PLANE3" );
        break;
    case  0x3004 :
        return std::string( "GL_CLIP_PLANE4" );
        break;
    case  0x3005 :
        return std::string( "GL_CLIP_PLANE5" );
        break;
    case  0x4000 :
        return std::string( "GL_LIGHT0 | GL_COLOR_BUFFER_BIT" );
        break;
    case  0x4001 :
        return std::string( "GL_LIGHT1" );
        break;
    case  0x4002 :
        return std::string( "GL_LIGHT2" );
        break;
    case  0x4003 :
        return std::string( "GL_LIGHT3" );
        break;
    case  0x4004 :
        return std::string( "GL_LIGHT4" );
        break;
    case  0x4005 :
        return std::string( "GL_LIGHT5" );
        break;
    case  0x4006 :
        return std::string( "GL_LIGHT6" );
        break;
    case  0x4007 :
        return std::string( "GL_LIGHT7" );
        break;
    case  0x8000 :
        return std::string( "GL_HINT_BIT" );
        break;
    case  0x8032 :
        return std::string( "GL_UNSIGNED_BYTE_3_3_2" );
        break;
    case  0x8033 :
        return std::string( "GL_UNSIGNED_SHORT_4_4_4_4" );
        break;
    case  0x8034 :
        return std::string( "GL_UNSIGNED_SHORT_5_5_5_1" );
        break;
    case  0x8035 :
        return std::string( "GL_UNSIGNED_INT_8_8_8_8" );
        break;
    case  0x8036 :
        return std::string( "GL_UNSIGNED_INT_10_10_10_2" );
        break;
    case  0x8037 :
        return std::string( "GL_POLYGON_OFFSET_FILL" );
        break;
    case  0x8038 :
        return std::string( "GL_POLYGON_OFFSET_FACTOR" );
        break;
    case  0x8040 :
        return std::string( "GL_LUMINANCE8" );
        break;
    case  0x8041 :
        return std::string( "GL_LUMINANCE12" );
        break;
    case  0x8042 :
        return std::string( "GL_LUMINANCE16" );
        break;
    case  0x8043 :
        return std::string( "GL_LUMINANCE4_ALPHA4" );
        break;
    case  0x8044 :
        return std::string( "GL_LUMINANCE6_ALPHA2" );
        break;
    case  0x8045 :
        return std::string( "GL_LUMINANCE8_ALPHA8" );
        break;
    case  0x8046 :
        return std::string( "GL_LUMINANCE12_ALPHA4" );
        break;
    case  0x8047 :
        return std::string( "GL_LUMINANCE12_ALPHA12" );
        break;
    case  0x8048 :
        return std::string( "GL_LUMINANCE16_ALPHA16" );
        break;
    case  0x8049 :
        return std::string( "GL_INTENSITY" );
        break;
    case  0x8050 :
        return std::string( "GL_RGB5" );
        break;
    case  0x8051 :
        return std::string( "GL_RGB8" );
        break;
    case  0x8052 :
        return std::string( "GL_RGB10" );
        break;
    case  0x8053 :
        return std::string( "GL_RGB12" );
        break;
    case  0x8054 :
        return std::string( "GL_RGB16" );
        break;
    case  0x8055 :
        return std::string( "GL_RGBA2" );
        break;
    case  0x8056 :
        return std::string( "GL_RGBA4" );
        break;
    case  0x8057 :
        return std::string( "GL_RGB5_A1" );
        break;
    case  0x8058 :
        return std::string( "GL_RGBA8" );
        break;
    case  0x8059 :
        return std::string( "GL_RGB10_A2" );
        break;
    case  0x8060 :
        return std::string( "GL_TEXTURE_LUMINANCE_SIZE" );
        break;
    case  0x8061 :
        return std::string( "GL_TEXTURE_INTENSITY_SIZE" );
        break;
    case  0x8063 :
        return std::string( "GL_PROXY_TEXTURE_1D" );
        break;
    case  0x8064 :
        return std::string( "GL_PROXY_TEXTURE_2D" );
        break;
    case  0x8066 :
        return std::string( "GL_TEXTURE_PRIORITY" );
        break;
    case  0x8067 :
        return std::string( "GL_TEXTURE_RESIDENT" );
        break;
    case  0x8068 :
        return std::string( "GL_TEXTURE_BINDING_1D" );
        break;
    case  0x8069 :
        return std::string( "GL_TEXTURE_BINDING_2D" );
        break;
    case  0x8070 :
        return std::string( "GL_PROXY_TEXTURE_3D" );
        break;
    case  0x8071 :
        return std::string( "GL_TEXTURE_DEPTH" );
        break;
    case  0x8072 :
        return std::string( "GL_TEXTURE_WRAP_R" );
        break;
    case  0x8073 :
        return std::string( "GL_MAX_3D_TEXTURE_SIZE" );
        break;
    case  0x8074 :
        return std::string( "GL_VERTEX_ARRAY" );
        break;
    case  0x8075 :
        return std::string( "GL_NORMAL_ARRAY" );
        break;
    case  0x8076 :
        return std::string( "GL_COLOR_ARRAY" );
        break;
    case  0x8077 :
        return std::string( "GL_INDEX_ARRAY" );
        break;
    case  0x8078 :
        return std::string( "GL_TEXTURE_COORD_ARRAY" );
        break;
    case  0x8079 :
        return std::string( "GL_EDGE_FLAG_ARRAY" );
        break;
    case  0x8081 :
        return std::string( "GL_COLOR_ARRAY_SIZE" );
        break;
    case  0x8082 :
        return std::string( "GL_COLOR_ARRAY_TYPE" );
        break;
    case  0x8083 :
        return std::string( "GL_COLOR_ARRAY_STRIDE" );
        break;
    case  0x8085 :
        return std::string( "GL_INDEX_ARRAY_TYPE" );
        break;
    case  0x8086 :
        return std::string( "GL_INDEX_ARRAY_STRIDE" );
        break;
    case  0x8088 :
        return std::string( "GL_TEXTURE_COORD_ARRAY_SIZE" );
        break;
    case  0x8089 :
        return std::string( "GL_TEXTURE_COORD_ARRAY_TYPE" );
        break;
    case  0x8090 :
        return std::string( "GL_COLOR_ARRAY_POINTER" );
        break;
    case  0x8091 :
        return std::string( "GL_INDEX_ARRAY_POINTER" );
        break;
    case  0x8092 :
        return std::string( "GL_TEXTURE_COORD_ARRAY_POINTER" );
        break;
    case  0x8093 :
        return std::string( "GL_EDGE_FLAG_ARRAY_POINTER" );
        break;
    case  0x8126 :
        return std::string( "GL_POINT_SIZE_MIN" );
        break;
    case  0x8127 :
        return std::string( "GL_POINT_SIZE_MAX" );
        break;
    case  0x8128 :
        return std::string( "GL_POINT_FADE_THRESHOLD_SIZE" );
        break;
    case  0x8129 :
        return std::string( "GL_POINT_DISTANCE_ATTENUATION" );
        break;
    case  0x8191 :
        return std::string( "GL_GENERATE_MIPMAP" );
        break;
    case  0x8192 :
        return std::string( "GL_GENERATE_MIPMAP_HINT" );
        break;
    case  0x8362 :
        return std::string( "GL_UNSIGNED_BYTE_2_3_3_REV" );
        break;
    case  0x8363 :
        return std::string( "GL_UNSIGNED_SHORT_5_6_5" );
        break;
    case  0x8364 :
        return std::string( "GL_UNSIGNED_SHORT_5_6_5_REV" );
        break;
    case  0x8365 :
        return std::string( "GL_UNSIGNED_SHORT_4_4_4_4_REV" );
        break;
    case  0x8366 :
        return std::string( "GL_UNSIGNED_SHORT_1_5_5_5_REV" );
        break;
    case  0x8367 :
        return std::string( "GL_UNSIGNED_INT_8_8_8_8_REV" );
        break;
    case  0x8368 :
        return std::string( "GL_UNSIGNED_INT_2_10_10_10_REV" );
        break;
    case  0x8370 :
        return std::string( "GL_MIRRORED_REPEAT" );
        break;
    case  0x8450 :
        return std::string( "GL_FOG_COORDINATE_SOURCE" );
        break;
    case  0x8451 :
        return std::string( "GL_FOG_COORDINATE" );
        break;
    case  0x8452 :
        return std::string( "GL_FRAGMENT_DEPTH" );
        break;
    case  0x8453 :
        return std::string( "GL_CURRENT_FOG_COORDINATE" );
        break;
    case  0x8454 :
        return std::string( "GL_FOG_COORDINATE_ARRAY_TYPE" );
        break;
    case  0x8455 :
        return std::string( "GL_FOG_COORDINATE_ARRAY_STRIDE" );
        break;
    case  0x8456 :
        return std::string( "GL_FOG_COORDINATE_ARRAY_POINTER" );
        break;
    case  0x8457 :
        return std::string( "GL_FOG_COORDINATE_ARRAY" );
        break;
    case  0x8458 :
        return std::string( "GL_COLOR_SUM" );
        break;
    case  0x8459 :
        return std::string( "GL_CURRENT_SECONDARY_COLOR" );
        break;
    case  0x8500 :
        return std::string( "GL_TEXTURE_FILTER_CONTROL" );
        break;
    case  0x8501 :
        return std::string( "GL_TEXTURE_LOD_BIAS" );
        break;
    case  0x8507 :
        return std::string( "GL_INCR_WRAP" );
        break;
    case  0x8508 :
        return std::string( "GL_DECR_WRAP" );
        break;
    case  0x8511 :
        return std::string( "GL_NORMAL_MAP" );
        break;
    case  0x8512 :
        return std::string( "GL_REFLECTION_MAP" );
        break;
    case  0x8513 :
        return std::string( "GL_TEXTURE_CUBE_MAP" );
        break;
    case  0x8514 :
        return std::string( "GL_TEXTURE_BINDING_CUBE_MAP" );
        break;
    case  0x8515 :
        return std::string( "GL_TEXTURE_CUBE_MAP_POSITIVE_X" );
        break;
    case  0x8516 :
        return std::string( "GL_TEXTURE_CUBE_MAP_NEGATIVE_X" );
        break;
    case  0x8517 :
        return std::string( "GL_TEXTURE_CUBE_MAP_POSITIVE_Y" );
        break;
    case  0x8518 :
        return std::string( "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y" );
        break;
    case  0x8519 :
        return std::string( "GL_TEXTURE_CUBE_MAP_POSITIVE_Z" );
        break;
    case  0x8570 :
        return std::string( "GL_COMBINE" );
        break;
    case  0x8571 :
        return std::string( "GL_COMBINE_RGB" );
        break;
    case  0x8572 :
        return std::string( "GL_COMBINE_ALPHA" );
        break;
    case  0x8573 :
        return std::string( "GL_RGB_SCALE" );
        break;
    case  0x8574 :
        return std::string( "GL_ADD_SIGNED" );
        break;
    case  0x8575 :
        return std::string( "GL_INTERPOLATE" );
        break;
    case  0x8576 :
        return std::string( "GL_CONSTANT" );
        break;
    case  0x8577 :
        return std::string( "GL_PRIMARY_COLOR" );
        break;
    case  0x8578 :
        return std::string( "GL_PREVIOUS" );
        break;
    case  0x8580 :
        return std::string( "GL_SOURCE0_RGB" );
        break;
    case  0x8581 :
        return std::string( "GL_SOURCE1_RGB" );
        break;
    case  0x8582 :
        return std::string( "GL_SOURCE2_RGB" );
        break;
    case  0x8588 :
        return std::string( "GL_SOURCE0_ALPHA" );
        break;
    case  0x8589 :
        return std::string( "GL_SOURCE1_ALPHA" );
        break;
    case  0x8590 :
        return std::string( "GL_OPERAND0_RGB" );
        break;
    case  0x8591 :
        return std::string( "GL_OPERAND1_RGB" );
        break;
    case  0x8592 :
        return std::string( "GL_OPERAND2_RGB" );
        break;
    case  0x8598 :
        return std::string( "GL_OPERAND0_ALPHA" );
        break;
    case  0x8599 :
        return std::string( "GL_OPERAND1_ALPHA" );
        break;
    case  0x8622 :
        return std::string( "GL_VERTEX_ATTRIB_ARRAY_ENABLED" );
        break;
    case  0x8623 :
        return std::string( "GL_VERTEX_ATTRIB_ARRAY_SIZE" );
        break;
    case  0x8624 :
        return std::string( "GL_VERTEX_ATTRIB_ARRAY_STRIDE" );
        break;
    case  0x8625 :
        return std::string( "GL_VERTEX_ATTRIB_ARRAY_TYPE" );
        break;
    case  0x8626 :
        return std::string( "GL_CURRENT_VERTEX_ATTRIB" );
        break;
    case  0x8642 :
        return std::string( "GL_VERTEX_PROGRAM_POINT_SIZE" );
        break;
    case  0x8643 :
        return std::string( "GL_VERTEX_PROGRAM_TWO_SIDE" );
        break;
    case  0x8645 :
        return std::string( "GL_VERTEX_ATTRIB_ARRAY_POINTER" );
        break;
    case  0x8764 :
        return std::string( "GL_BUFFER_SIZE" );
        break;
    case  0x8765 :
        return std::string( "GL_BUFFER_USAGE" );
        break;
    case  0x8800 :
        return std::string( "GL_STENCIL_BACK_FUNC" );
        break;
    case  0x8801 :
        return std::string( "GL_STENCIL_BACK_FAIL" );
        break;
    case  0x8802 :
        return std::string( "GL_STENCIL_BACK_PASS_DEPTH_FAIL" );
        break;
    case  0x8803 :
        return std::string( "GL_STENCIL_BACK_PASS_DEPTH_PASS" );
        break;
    case  0x8824 :
        return std::string( "GL_MAX_DRAW_BUFFERS" );
        break;
    case  0x8825 :
        return std::string( "GL_DRAW_BUFFER0" );
        break;
    case  0x8826 :
        return std::string( "GL_DRAW_BUFFER1" );
        break;
    case  0x8827 :
        return std::string( "GL_DRAW_BUFFER2" );
        break;
    case  0x8828 :
        return std::string( "GL_DRAW_BUFFER3" );
        break;
    case  0x8829 :
        return std::string( "GL_DRAW_BUFFER4" );
        break;
    case  0x8830 :
        return std::string( "GL_DRAW_BUFFER11" );
        break;
    case  0x8831 :
        return std::string( "GL_DRAW_BUFFER12" );
        break;
    case  0x8832 :
        return std::string( "GL_DRAW_BUFFER13" );
        break;
    case  0x8833 :
        return std::string( "GL_DRAW_BUFFER14" );
        break;
    case  0x8834 :
        return std::string( "GL_DRAW_BUFFER15" );
        break;
    case  0x8861 :
        return std::string( "GL_POINT_SPRITE" );
        break;
    case  0x8862 :
        return std::string( "GL_COORD_REPLACE" );
        break;
    case  0x8864 :
        return std::string( "GL_QUERY_COUNTER_BITS" );
        break;
    case  0x8865 :
        return std::string( "GL_CURRENT_QUERY" );
        break;
    case  0x8866 :
        return std::string( "GL_QUERY_RESULT" );
        break;
    case  0x8867 :
        return std::string( "GL_QUERY_RESULT_AVAILABLE" );
        break;
    case  0x8869 :
        return std::string( "GL_MAX_VERTEX_ATTRIBS" );
        break;
    case  0x8871 :
        return std::string( "GL_MAX_TEXTURE_COORDS" );
        break;
    case  0x8872 :
        return std::string( "GL_MAX_TEXTURE_IMAGE_UNITS" );
        break;
    case  0x8892 :
        return std::string( "GL_ARRAY_BUFFER" );
        break;
    case  0x8893 :
        return std::string( "GL_ELEMENT_ARRAY_BUFFER" );
        break;
    case  0x8894 :
        return std::string( "GL_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8895 :
        return std::string( "GL_ELEMENT_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8896 :
        return std::string( "GL_VERTEX_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8897 :
        return std::string( "GL_NORMAL_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8898 :
        return std::string( "GL_COLOR_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8899 :
        return std::string( "GL_INDEX_ARRAY_BUFFER_BINDING" );
        break;
    case  0x8914 :
        return std::string( "GL_SAMPLES_PASSED" );
        break;
    case  0x10000 :
        return std::string( "GL_EVAL_BIT" );
        break;
    case  0x20000 :
        return std::string( "GL_LIST_BIT" );
        break;
    case  0x40000 :
        return std::string( "GL_TEXTURE_BIT" );
        break;
    case  0x80000 :
        return std::string( "GL_SCISSOR_BIT" );
        break;
    case  0x20000000 :
        return std::string( "GL_MULTISAMPLE_BIT" );
        break;
    default:
        return std::string("Undifined");
        break;
    }
}

OSG_END_NAMESPACE

