%module OSG
%native(version) int OSGVersion(lua_State*L);  // registers native_function() with SWIG
%{
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGTypeBase.h>
#include <OpenSG/OSGDataType.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldType.h>
#include <OpenSG/OSGField.h>
#include <OpenSG/OSGFieldFactory.h>
    int OSGVersion(lua_State*L) // my native code
    {
      int SWIG_arg = 0;
      std::string result(OSG_VERSION_STRING);
      SWIG_check_num_args("version",0,0);
      
      lua_pushstring(L,result.c_str()); SWIG_arg++;
      return SWIG_arg;
      
      if(0) SWIG_fail;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
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
    typedef unsigned long  BitVector;
    typedef float      Real32;
    typedef double     Real64;
    typedef long double Real128;



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
    /******************************************************/
    /*              Matricies                             */
    /******************************************************/
    template<class ValueTypeT>
    class TransformationMatrix
    {
      public:

        typedef                 ValueTypeT                ValueType;
        typedef Vector         <ValueTypeT, 4           > VectorType;

        typedef QuaternionBase <ValueType>                QuaternionType;

        typedef Vector         <ValueTypeT, 3           > VectorType3f;
        typedef Point          <ValueTypeT, 4           > PointType;
        typedef Point          <ValueTypeT, 3           > PointType3f;
                               
        /*---------------------------------------------------------------------*/
        static const TransformationMatrix &identity(void);

        /*---------------------------------------------------------------------*/
        TransformationMatrix(void);
        TransformationMatrix(const TransformationMatrix &source );

        TransformationMatrix(const VectorType3f         &vector1,
                             const VectorType3f         &vector2,
                             const VectorType3f         &vector3);    

        TransformationMatrix(const VectorType3f         &vector1,
                             const VectorType3f         &vector2,
                             const VectorType3f         &vector3,
                             const VectorType3f         &vector4);    

        TransformationMatrix(const ValueTypeT            rVal00,
                             const ValueTypeT            rVal10,
                             const ValueTypeT            rVal20,
                             const ValueTypeT            rVal30,
                             
                             const ValueTypeT            rVal01,
                             const ValueTypeT            rVal11,
                             const ValueTypeT            rVal21,
                             const ValueTypeT            rVal31,
                             
                             const ValueTypeT            rVal02,
                             const ValueTypeT            rVal12,
                             const ValueTypeT            rVal22,
                             const ValueTypeT            rVal32,
                             
                             const ValueTypeT            rVal03,
                             const ValueTypeT            rVal13,
                             const ValueTypeT            rVal23,
                             const ValueTypeT            rVal33);
     
        /*---------------------------------------------------------------------*/
        ~TransformationMatrix(void); 

        /*---------------------------------------------------------------------*/
        void setIdentity       (void                                           );

        void setValue          (const TransformationMatrix &mat                );

        void setValue          (const VectorType3f         &vector1,
                                const VectorType3f         &vector2,
                                const VectorType3f         &vector3            );

        void setValue          (const VectorType3f         &vector1,
                                const VectorType3f         &vector2,
                                const VectorType3f         &vector3,
                                const VectorType3f         &vector4            );

        void setValue          (const ValueTypeT            rVal00,
                                const ValueTypeT            rVal10,
                                const ValueTypeT            rVal20,
                                const ValueTypeT            rVal30,
                                
                                const ValueTypeT            rVal01,
                                const ValueTypeT            rVal11,
                                const ValueTypeT            rVal21,
                                const ValueTypeT            rVal31,
                                
                                const ValueTypeT            rVal02,
                                const ValueTypeT            rVal12,
                                const ValueTypeT            rVal22,
                                const ValueTypeT            rVal32,
                                
                                const ValueTypeT            rVal03,
                                const ValueTypeT            rVal13,
                                const ValueTypeT            rVal23,
                                const ValueTypeT            rVal33             );

        void setValueTransposed(const ValueTypeT            rVal00,
                                const ValueTypeT            rVal01,
                                const ValueTypeT            rVal02,
                                const ValueTypeT            rVal03,
                                
                                const ValueTypeT            rVal10,
                                const ValueTypeT            rVal11,
                                const ValueTypeT            rVal12,
                                const ValueTypeT            rVal13,
                                
                                const ValueTypeT            rVal20,
                                const ValueTypeT            rVal21,
                                const ValueTypeT            rVal22,
                                const ValueTypeT            rVal23,
                                
                                const ValueTypeT            rVal30,
                                const ValueTypeT            rVal31,
                                const ValueTypeT            rVal32,
                                const ValueTypeT            rVal33             );

        void setValue          (const ValueTypeT           *pMat,
                                      bool                  bTransposed = true );

        void setValue          (const VectorType           *pMat               );

        void setValue           (const Char8               *string,
                                       bool                 bTransposed = true );

        /*---------------------------------------------------------------------*/
              ValueTypeT *getValues(void);
        
        /*---------------------------------------------------------------------*/
        void setScale    (const ValueTypeT      s               );

        void setScale    (const ValueTypeT      sx,
                          const ValueTypeT      sy, 
                          const ValueTypeT      sz              );

        void setScale    (const VectorType3f   &s               );


        void setTranslate(const ValueTypeT      tx,
                          const ValueTypeT      ty,
                          const ValueTypeT      tz              );

        void setTranslate(const VectorType3f   &t               );

        void setTranslate(const PointType3f    &t               );


        void setRotate   (const QuaternionType &q               );


        void setTransform(const VectorType3f   &t               );

        void setTransform(const QuaternionType &r               );

        void setTransform(const VectorType3f   &t, 
                          const QuaternionType &r               );

        void setTransform(const VectorType3f   &t, 
                          const QuaternionType &r,
                          const VectorType3f   &s               );

        void setTransform(const VectorType3f   &t, 
                          const QuaternionType &r,
                          const VectorType3f   &s, 
                          const QuaternionType &so              );

        void setTransform(const VectorType3f   &translation,
                          const QuaternionType &rotation,
                          const VectorType3f   &scaleFactor,
                          const QuaternionType &scaleOrientation,
                          const VectorType3f   &center          );

        void getTransform(      VectorType3f         &translation, 
                                QuaternionType       &rotation,
                                VectorType3f         &scaleFactor, 
                                QuaternionType       &scaleOrientation,
                          const VectorType3f         &center) const;

        void getTransform(      VectorType3f         &translation, 
                                QuaternionType       &rotation,
                                VectorType3f         &scaleFactor, 
                                QuaternionType       &scaleOrientation) const;

        bool factor      (      TransformationMatrix &r, 
                                VectorType3f         &s, 
                                TransformationMatrix &u,
                                VectorType3f         &t, 
                                TransformationMatrix &proj) const;
        
        void mult    (const PointType    &pntIn, PointType    &pntOut) const;
        void multFull(const PointType3f  &pntIn, PointType3f  &pntOut) const;
        void mult    (const PointType3f  &pntIn, PointType3f  &pntOut) const;
        
        void mult    (const VectorType   &vecIn, VectorType   &vecOut) const;
        void multFull(const VectorType3f &vecIn, VectorType3f &vecOut) const;
        void mult    (const VectorType3f &vecIn, VectorType3f &vecOut) const;
        
        void mult3x3 (const PointType3f  &pntIn, PointType3f  &pntOut) const;
        void mult3x3 (const VectorType3f &vecIn, VectorType3f &vecOut) const;
        
        PointType    operator *(const PointType    &pntIn) const;
        PointType3f  operator *(const PointType3f  &pntIn) const;
                 
        VectorType   operator *(const VectorType   &vecIn) const;
        VectorType3f operator *(const VectorType3f &vecIn) const;

        
        bool       equals       (const TransformationMatrix &matrix, 
                                 const ValueType             tol   ) const;

        ValueTypeT det3         (      void                        ) const;
        ValueTypeT det          (      void                        ) const;

        bool       inverse      (      TransformationMatrix &result) const;
        bool       invert       (      void                        );
        bool       invertFrom   (const TransformationMatrix &matrix);

        bool       inverse3     (      TransformationMatrix &result) const;
        bool       invert3      (      void                        );
        bool       invertFrom3  (const TransformationMatrix &matrix);

        bool       transposed   (      TransformationMatrix &result) const;
        bool       transpose    (      void                        );
        bool       transposeFrom(const TransformationMatrix &matrix);

        void       mult         (const TransformationMatrix &matrix);
        void       multLeft     (const TransformationMatrix &matrix);
        
        void       add          (const TransformationMatrix &matrix);
        void       scale        (      ValueTypeT            s     );
        void       addScaled    (const TransformationMatrix &matrix, 
                                       ValueTypeT            s     );
        void       negate       (      void                        );
        
        ValueTypeT norm1        (      void                        ) const;
        ValueTypeT norm2        (      void                        ) const;
        ValueTypeT normInfinity (      void                        ) const;
        
        bool       sqrt         (      TransformationMatrix &result) const;
        bool       sqrtOf       (const TransformationMatrix &matrix);
        bool       sqrt         (      void                        );
        
        bool       log          (      TransformationMatrix &result) const;
        bool       logOf        (const TransformationMatrix &matrix);
        
        bool       exp          (      TransformationMatrix &result) const;
        bool       expOf        (const TransformationMatrix &matrix);


        bool operator == (const TransformationMatrix &other) const;

    };

    %template(Matrix) TransformationMatrix<Real32>;
    /******************************************************/
    /*              Quaternion                            */
    /******************************************************/
    template <class ValueTypeT>
    class QuaternionBase
    {
      public:
        typedef Vector              <ValueTypeT, 3> VectorType;
        typedef TransformationMatrix<ValueTypeT   > MatrixType;
        static const QuaternionBase &identity(void                          );

        static       QuaternionBase slerp    (const QuaternionBase &rot0,
                                              const QuaternionBase &rot1,
                                              const ValueTypeT      t       );
                    QuaternionBase(      void                               );
                    QuaternionBase(const QuaternionBase &source             );
        explicit    QuaternionBase(const MatrixType     &matrix             );
                    QuaternionBase(const VectorType     &axis,
                                   const ValueTypeT      angle              );
                    QuaternionBase(const VectorType     &rotateFrom,
                                   const VectorType     &rotateTo           );
        virtual ~QuaternionBase(void);
        void setIdentity      (       void                  );

        void setValueAsAxisRad(const  ValueTypeT *valsP     );
        void setValueAsAxisDeg(const  ValueTypeT *valsP     );
        void setValueAsQuat   (const  ValueTypeT *valsP     );

        void setValueAsAxisRad(const  ValueTypeT  x,
                               const  ValueTypeT  y,
                               const  ValueTypeT  z,
                               const  ValueTypeT  w         );
        void setValueAsAxisDeg(const  ValueTypeT  x,
                               const  ValueTypeT  y,
                               const  ValueTypeT  z,
                               const  ValueTypeT  w         );
        void setValueAsQuat   (const  ValueTypeT  x,
                               const  ValueTypeT  y,
                               const  ValueTypeT  z,
                               const  ValueTypeT  w         );

        void setValue         (const  MatrixType &matrix    );

        void setValueAsAxisRad(const  VectorType &axis,    
                                      ValueTypeT  angle     );
        void setValueAsAxisDeg(const  VectorType &axis,
                                      ValueTypeT  angle     );

        void setValue         (const  VectorType &rotateFrom,
                               const  VectorType &rotateTo  );

        void setValueAsAxisRad(const  Char8       *str      );
        void setValueAsAxisDeg(const  Char8       *str      );
        void setValueAsQuat   (const  Char8       *str      );

        void setValue         (const  ValueTypeT alpha,
                               const  ValueTypeT beta,
                               const  ValueTypeT gamma      );
        const ValueTypeT *getValues        (void               ) const;

              void        getValueAsAxisDeg(ValueTypeT &x,
                                            ValueTypeT &y,
                                            ValueTypeT &z,
                                            ValueTypeT &w      ) const;
              void        getValueAsAxisRad(ValueTypeT &x,
                                            ValueTypeT &y,
                                            ValueTypeT &z,
                                            ValueTypeT &w      ) const;
              void        getValueAsQuat   (ValueTypeT &x,
                                            ValueTypeT &y,
                                            ValueTypeT &z,
                                            ValueTypeT &w      ) const;

              void       getValueAsAxisRad (VectorType &axis, 
                                            ValueTypeT &radians) const;
              void       getValueAsAxisDeg (VectorType &axis, 
                                            ValueTypeT &degrees) const;
              void       getValue          (MatrixType &matrix ) const;
              void       getValuesOnly     (MatrixType &matrix ) const;

              ValueTypeT x                 (void               ) const;
              ValueTypeT y                 (void               ) const;
              ValueTypeT z                 (void               ) const;
              ValueTypeT w                 (void               ) const;
              ValueTypeT      length    (void                        ) const;
              void            normalize (void                        );

              void            invert    (void                        );
        const QuaternionBase  inverse   (void                        ) const;

              void            multVec   (const VectorType &src,
                                               VectorType &dst       ) const;

              void            scaleAngle(      ValueTypeT scaleFactor);

              void            slerpThis (const QuaternionBase &rot0,
                                         const QuaternionBase &rot1,
                                         const ValueTypeT      t     );

              void            mult      (const QuaternionBase &other );
              void            multLeft  (const QuaternionBase &other );

              bool            equals    (const QuaternionBase &rot,
                                         const ValueTypeT tolerance  ) const;

        bool operator == (const QuaternionBase &other) const;

    };

    %template(Quaternion) QuaternionBase<Real32>;
    /******************************************************/
    /*              TypeBase                              */
    /******************************************************/
    class TypeBase
    {
      public :
        TypeBase(const Char8  *szName, 
                 const Char8  *szParentName,
                 const UInt32  uiNameSpace = 0);
        virtual ~TypeBase(void);

              UInt32    getId         (void) const;

        const Char8    *getCName      (void) const;

        const Char8    *getCParentName(void) const;

              UInt32    getNameSpace  (void) const;

        virtual bool isDerivedFrom(const TypeBase &other) const;

        bool operator ==(const TypeBase &other) const;
    };
    /******************************************************/
    /*              DataType                              */
    /******************************************************/
    class DataType : public TypeBase
    {
      public :
        DataType(const Char8  *szName, 
                 const Char8  *szParentName,
                 const UInt32  uiNameSpace = 0);
        virtual ~DataType(void);

        bool operator ==(const DataType &other) const;
    };
    /******************************************************/
    /*              TypeFactory                           */
    /******************************************************/
    class TypeFactory
    {
      public :
        static TypeFactory *the(void);

        UInt32    registerType  (      TypeBase *pType          );

        UInt32    findTypeId    (const Char8    *szName,
                                 const UInt32    uiNameSpace = 0);

        TypeBase *findType      (      UInt32    uiTypeId       );
        TypeBase *findType      (const Char8    *szName  ,
                                 const UInt32    uiNameSpace = 0);


        UInt32    getNumTypes   (      void                     );

        void      writeTypeGraph(const Char8    *szFilename     );
    protected:
        TypeFactory(void);

        virtual ~TypeFactory(void);

    };
    /******************************************************/
    /*              Volumes                               */
    /******************************************************/
    /******************************************************/
    /*              FieldType                             */
    /******************************************************/
    class FieldType : public DataType
    {
      public:
        enum Cardinality 
        { 
            SINGLE_FIELD, 
            MULTI_FIELD 
        };


        virtual ~FieldType(void);

        const DataType    &getContentType(void) const;
              Cardinality  getCardinality(void) const;

              UInt32       getScanTypeId (void) const;
    };
    /******************************************************/
    /*              Field                                 */
    /******************************************************/
    class Field
    {
      public:
        virtual ~Field(void); 

        virtual const FieldType              &getType       (void) const = 0;
                const DataType               &getContentType(void) const;

                      FieldType::Cardinality  getCardinality(void) const;

        virtual       bool                    isEmpty       (void) const = 0;

        virtual       UInt32                  getSize       (void) const = 0;

        virtual void          pushValueByStr(const Char8       *str  )       = 0;
        virtual std::string  &getValueByStr (      std::string &str  ) const = 0;

        /*virtual std::string  &getValueByStr (      std::string &str,*/
                                                   /*UInt32       index) const = 0;*/

        virtual void setAbstrValue(const Field &obj) = 0;
        virtual void dump(void) const = 0;


      protected:

        Field(void);
        Field(const Field &source);
    };
    /******************************************************/
    /*              FieldFactory                          */
    /******************************************************/
    class FieldFactory 
    {
      public:
        virtual ~FieldFactory (void);

        Field *createField(      UInt32  typeId);
        Field *createField(const Char8  *szName);

        static UInt32     getNFieldTypes  (void                );
        
        static FieldType *getFieldType    (      UInt32  typeId);
        static FieldType *getFieldType    (const Char8  *szName);

        const  Char8     *getFieldTypeName(UInt32 typeId       );

        static FieldFactory &the(void);

      protected:

        FieldFactory (void);
      private:
        FieldFactory(const FieldFactory &source);
    };
}

