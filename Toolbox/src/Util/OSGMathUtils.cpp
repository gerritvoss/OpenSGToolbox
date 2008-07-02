#include "OSGMathUtils.h"

OSG_BEGIN_NAMESPACE

void makeViewFromUVND(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Vec3f& D)
{
   //Set up the Rotation matrix
   //Put U in the 1st row
   Result[0][0] = U.x();
   Result[0][1] = U.y();
   Result[0][2] = U.z();
   
   //Put V in the 2nd row
   Result[1][0] = V.x();
   Result[1][1] = V.y();
   Result[1][2] = V.z();
   
   //Put N in the 3rd row
   Result[2][0] = N.x();
   Result[2][1] = N.y();
   Result[2][2] = N.z();

   //Put D in the 4th column
   Result[0][3] = D.x();
   Result[1][3] = D.y();
   Result[2][3] = D.z();

   //Clear up the rest of the matrix
   Result[3][3] = 1.0;
   Result[3][0] = Result[3][1] = Result[3][2] = 0.0;
}

void getUVNDFromMat(const Matrix& Mat,Vec3f& U,Vec3f& V,Vec3f& N,Vec3f& D)
{
   //get U in the 1st row
   U.setValues(Mat[0][0],
         Mat[0][1],
         Mat[0][2]);
   //get V in the 2nd row
   V.setValues(Mat[1][0],
         Mat[1][1],
         Mat[1][2]);
   //get N in the 3rd row
   N.setValues(Mat[2][0],
         Mat[2][1],
         Mat[2][2]);

   //get D in the 4th column
   D.setValues(Mat[0][3],
         Mat[1][3],
         Mat[2][3]);
}

void makeViewFromUVNP(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Vec3f& P)
{
   //Set up the Rotation matrix
   //Put U in the 1st row
   Result[0][0] = U.x();
   Result[0][1] = U.y();
   Result[0][2] = U.z();
   
   //Put V in the 2nd row
   Result[1][0] = V.x();
   Result[1][1] = V.y();
   Result[1][2] = V.z();
   
   //Put N in the 3rd row
   Result[2][0] = N.x();
   Result[2][1] = N.y();
   Result[2][2] = N.z();

   //Put calculate D and put it in the 4th column
   Result[0][3] = -P.dot(U);
   Result[1][3] = -P.dot(V);
   Result[2][3] = -P.dot(N);

   //Clear up the rest of the matrix
   Result[3][3] = 1.0;
   Result[3][0] = Result[3][1] = Result[3][2] = 0.0;
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
   Result[0][3] = -TempP.dot(U);
   Result[1][3] = -TempP.dot(V);
   Result[2][3] = -TempP.dot(N);
}
OSG_END_NAMESPACE

