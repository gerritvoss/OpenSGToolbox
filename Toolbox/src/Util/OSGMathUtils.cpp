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
#include "OSGMathUtils.h"

OSG_BEGIN_NAMESPACE

void makeViewFromUVND(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Vec3f& D)
{
   //Set up the Rotation matrix
   //Put U in the 1st row
   Result[0][0] = U.x();
   Result[1][0] = U.y();
   Result[2][0] = U.z();
   
   //Put V in the 2nd row
   Result[0][1] = V.x();
   Result[1][1] = V.y();
   Result[2][1] = V.z();
   
   //Put N in the 3rd row
   Result[0][2] = N.x();
   Result[1][2] = N.y();
   Result[2][2] = N.z();

   //Put D in the 4th column
   Result[3][0] = D.x();
   Result[3][1] = D.y();
   Result[3][2] = D.z();

   //Clear up the rest of the matrix
   Result[3][3] = 1.0;
   Result[0][3] = Result[1][3] = Result[2][3] = 0.0;
}

void getUVNDFromMat(const Matrix& Mat,Vec3f& U,Vec3f& V,Vec3f& N,Vec3f& D)
{
   //get U in the 1st row
   U.setValues(Mat[0][0],
         Mat[1][0],
         Mat[2][0]);
   //get V in the 2nd row
   V.setValues(Mat[0][1],
         Mat[1][1],
         Mat[2][1]);
   //get N in the 3rd row
   N.setValues(Mat[0][2],
         Mat[1][2],
         Mat[2][2]);

   //get D in the 4th column
   D.setValues(Mat[3][0],
         Mat[3][1],
         Mat[3][2]);
}

void makeViewFromUVNP(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Pnt3f& P)
{
	makeViewFromUVND(Result, U,V,N, Vec3f(-Vec3f(P).dot(U), -Vec3f(P).dot(V), -Vec3f(P).dot(N)));
}

void getUVNPFromMat(const Matrix& Mat,Vec3f& U,Vec3f& V,Vec3f& N,Pnt3f& P)
{
   //Get U, V, N, D from the mat
   Vec3f D;
   getUVNDFromMat(Mat,U,V,N,D);

   //Calculate the Eye position from U, V, N, D
   P = Pnt3f(-((D.x()*U) + (D.y()*V) + (D.z()*N)));
}

void getPFromViewMat(Pnt3f& P, const Matrix& Mat)
{
   //Get U, V, N, D from the mat
   Vec3f U,V,N;
   getUVNPFromMat(Mat,U,V,N,P);
}


void setViewMatEyePos(Matrix& Result,const Pnt3f& P)
{
   //Get U, V, N, D from the mat
   Vec3f U,V,N,D;
   getUVNDFromMat(Result,U,V,N,D);

   Vec3f TempP(P[0],P[1],P[2]);
   Result[3][0] = -TempP.dot(U);
   Result[3][1] = -TempP.dot(V);
   Result[3][2] = -TempP.dot(N);
}
OSG_END_NAMESPACE

