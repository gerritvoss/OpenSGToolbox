%module OSGBase
%{
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGVector.h>
%}

namespace osg {
    typedef char           Char8;
    typedef unsigned char UChar8;
    typedef signed char   SChar8;
    typedef int8_t     Int8;
    typedef uint8_t   UInt8;
    typedef int16_t    Int16;
    typedef uint16_t  UInt16;
    typedef int    Int32;
    typedef unsigned int  UInt32;
    typedef long    Int64;
    typedef unsigned long  UInt64;
    typedef float      Real32;
    typedef double     Real64;
    typedef long double Real128;

    Real32 osgrand(void);

    void osgGetHostname(char *szBuffer, UInt32 uiSize);


    /******************************************************/
    /*              Colors                                */
    /******************************************************/
    template <class ValueType>
    class Color3
    {
        public:
        static void   convertFromHSV(      ValueType     *rgbP,
                                     const Real32         h,
                                     const Real32         s,
                                     const Real32         v   );


        static void   convertToHSV  (const ValueType     *rgbP,
                                           Real32        &h,
                                           Real32        &s,
                                           Real32        &v   );

        static UInt32 minPart       (const ValueType     *rgbP);
        static UInt32 maxPart       (const ValueType     *rgbP);
        Color3(      void             );
        Color3(const Color3    &source);
        Color3(      ValueType  red,
                     ValueType  green,
                     ValueType  blue  );
        void clear        (     void               );

        void setValuesRGB(const ValueType  red,
                          const ValueType  green,
                          const ValueType  blue    );

        void setValuesHSV(const Real32     h,
                          const Real32     s,
                          const Real32     v       );

        void setRandom   (      void               );
        void setRGB      (      UInt32     rgbPack );

        void setValue    (      Char8     *szString);
              UInt32     getRGB       (void           ) const;

              void       getValuesRGB(ValueType &red,
                                      ValueType &green,
                                      ValueType &blue ) const;

              void       getValuesHSV(Real32    &h,
                                      Real32    &s,
                                      Real32    &v    ) const;

              ValueType  red         (void            ) const;
              ValueType  green       (void            ) const;
              ValueType  blue        (void            ) const;

              ValueType *getValuesRGB(void            );
        const ValueType *getValuesRGB(void            ) const;
          Color3     operator * (const ValueType  val      ) const;
          Color3     operator / (const ValueType  val      ) const;
          Color3     operator + (const ValueType  val      ) const;
          Color3     operator - (const ValueType  val      ) const;
          Color3     operator * (const Color3    &other    ) const;
          Color3     operator / (const Color3    &other    ) const;
          Color3     operator + (const Color3    &other    ) const;
          Color3     operator - (const Color3    &other    ) const;
           bool      equals     (const Color3    &other, 
                                 const ValueType  tolerance) const;
           bool      operator < (const Color3    &other    ) const;
           bool      operator ==(const Color3    &other    ) const;
    };

    %template(Color3f) Color3<Real32>;

    template <class ValueTypeT>
    class Color4
    {
      public:

        typedef ValueTypeT ValueType;
        Color4(      void             );
        Color4(const Color4    &source);
        Color4(const ValueType  red,
               const ValueType  green,
               const ValueType  blue,
               const ValueType  alpha );
        ~Color4(void);
        void clear        (      void           );

        void setValuesRGBA(const ValueType red,
                           const ValueType green,
                           const ValueType blue,
                           const ValueType alpha);

        void setValuesHSV (const Real32 h,
                           const Real32 s,
                           const Real32 v       );

        void setRandom    (      void           );
        void setRGBA      (      UInt32 rgbPack );    

        void setValue     (      Char8 *szString);
              UInt32    getRGBA       (void            ) const;

              void      getValuesRGBA (ValueType &red,
                                       ValueType &green,
                                       ValueType &blue,
                                       ValueType &alpha) const;

              void      getValuesHSV  (Real32    &h,
                                       Real32    &s,
                                       Real32    &v    ) const;

              ValueType red           (void            ) const;
              ValueType green         (void            ) const;
              ValueType blue          (void            ) const;
              ValueType alpha         (void            ) const;

              ValueType *getValuesRGBA(void            );
              Color4     operator * (const ValueType  val      ) const;
              Color4     operator / (const ValueType  val      ) const;
              Color4     operator + (const ValueType  val      ) const;
              Color4     operator - (const ValueType  val      ) const;
              Color4     operator * (const Color4    &other    ) const;
              Color4     operator / (const Color4    &other    ) const;
              Color4     operator + (const Color4    &other    ) const;
              Color4     operator - (const Color4    &other    ) const;
              bool       equals     (const Color4    &other, 
                                     const ValueType  tolerance) const;

              bool       operator < (const Color4    &other    ) const;
              bool       operator ==(const Color4    &other    ) const;
    };
    %template(Color4f) Color4<Real32>;

    /******************************************************/
    /*              Pnts                                  */
    /******************************************************/
    template<class ValueTypeT, UInt32 SizeI>
    class Point
    {
    public:
        typedef          ValueTypeT                             ValueType;
        typedef          Vector    <ValueTypeT, 
                                    SizeI     >                 VectorType;
        typedef          Point     <ValueTypeT, 
                                    SizeI     >                 PointType;
        typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;
        Point(void);
        
        Point(      ValueTypeT     *pVals );
        Point(const Point &source);
        Point(const ValueTypeT rVal1, const ValueTypeT rVal2);
        ~Point(void);

        Point(const ValueTypeT rVal1, const ValueTypeT rVal2,
              const ValueTypeT rVal3);

        Point(const ValueTypeT rVal1, const ValueTypeT rVal2,
              const ValueTypeT rVal3, const ValueTypeT rVal4);

        Point(const ValueTypeT rVal1);
        void setNull (void);
        void setValue           (const Point              &vec     );
        void setValue           (      ValueTypeT         *pVals   );
        void setValueFromCString(      Char8              *szString);
              ValueTypeT *getValues(void);
              bool            isZero  (      void                 ) const;

              void            negate  (      void                 );

              bool            equals  (const Point      &vec,
                                       const ValueTypeT  tolerance) const;

              VectorType     &subZero (      void                 );

              ValueType  dist    (const Point      &vec      ) const;
              ValueType  dist2   (const Point      &vec      ) const;

              ValueType  maxValue(      void                 ) const;
    };
    %template(Pnt4f) Point<Real32,4>;
    %template(Pnt3f) Point<Real32,3>;
    %template(Pnt2f) Point<Real32,2>;
    /******************************************************/
    /*              Pnts                                  */
    /******************************************************/
    template<class ValueTypeT, UInt32 SizeI>
    class Vector : public Point<ValueTypeT, SizeI>
    {
      public:

        typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

        typedef          ValueTypeT                             ValueType;

        /*---------------------------------------------------------------------*/
        /*! \name                   Constructors                               */
        /*! \{                                                                 */

        Vector(      void                               );

        Vector(      ValueTypeT                  *pVals );

        Vector(const Vector                      &source);

        Vector(const ValueTypeT                   rVal1 );
        Vector(const ValueTypeT rVal1, const ValueTypeT rVal2);

        Vector(const ValueTypeT rVal1, const ValueTypeT rVal2,
               const ValueTypeT rVal3);

        Vector(const ValueTypeT rVal1, const ValueTypeT rVal2,
               const ValueTypeT rVal3, const ValueTypeT rVal4);
        ~Vector(void);
        ValueType  length       (      void            ) const;
        ValueType  squareLength (      void            ) const;

        void            normalize    (      void            );

        Vector          cross        (const Vector    &vec  ) const;

        void            crossThis    (const Vector    &vec  );

        ValueTypeT      dot          (const Vector    &vec  ) const;
        ValueTypeT      operator *   (const Vector    &vec  ) const;
        ValueTypeT      dot          (const PointType &pnt  ) const;
        ValueTypeT      operator *   (const PointType &pnt  ) const;

        ValueTypeT  enclosedAngle(const Vector    &vec  ) const;

        ValueTypeT  projectTo    (const Vector    &toVec);
              PointType &addToZero (void);
              Vector    &subZero   (void);
        Vector operator - (const Vector     &vec ) const;
        Vector operator + (const Vector     &vec ) const;

        Vector operator * (const ValueTypeT  rVal) const;

        Vector operator - (      void            ) const;
        bool operator <  (const Vector &other) const;

        bool operator == (const Vector &other) const;
    };
    %template(Vec4f) Vector<Real32,4>;
    %template(Vec3f) Vector<Real32,3>;
    %template(Vec2f) Vector<Real32,2>;
}

