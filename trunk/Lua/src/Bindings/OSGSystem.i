%include <OSGBase.i>
%module OSG
%{
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGAttachmentContainerPtr.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
%}

namespace osg {

    class FieldDescription;
    class FieldContainerPtr;
    class FieldContainerType;
    class FieldContainer;
    class AttachmentContainer;
    class Attachment;
    class AttachmentPtr;
    class AttachmentContainerPtr;
    class NodePtr;
    class NodeCorePtr;
    class Node;
    class Matrix;
    class DynamicVolume;
    class BoxVolume;
    /******************************************************/
    /*              FieldDescription                    */
    /******************************************************/
    class FieldDescription
    {
      public :


        FieldDescription(const FieldDescription &source                     );

        virtual ~FieldDescription(void); 

        const Char8     *getCName       (void                ) const;

              UInt32     getTypeId      (void                ) const;  

              /*BitVector  getFieldMask   (void                ) const;*/
              /*void       setFieldMask   (BitVector vFieldMask);*/

              UInt32     getFieldId     (void                ) const;
              void       setFieldId     (UInt32 uiFieldId    );

        const Char8     *getDefaultValue(void                ) const;

        const TypeBase  &getFieldType   (void                ) const;

              bool       isInternal     (void                ) const;

              bool       isValid        (void                ) const;

    };

    /******************************************************/
    /*              FieldContainerPtr                    */
    /******************************************************/
    class FieldContainerPtr
    {
      public:

        typedef FieldContainer        StoredObjectType;
        typedef FieldContainerPtr     ObjectType;

        typedef FieldContainerPtrBase Inherited;

        FieldContainer *operator->(void);

        FieldContainerPtr(      void                         );
        /*FieldContainerPtr(const NullFieldContainerPtr &      );*/
        FieldContainerPtr(const FieldContainerPtr     &source);

        ~FieldContainerPtr(void); 

    };
    /******************************************************/
    /*              FieldContainerType                    */
    /******************************************************/
    class FieldContainerType : public DataType
    {
      public :

        FieldContainerType(const FieldContainerType &source);

        virtual ~FieldContainerType(void); 

        UInt16              getGroupId(void) const;
        FieldContainerType *getParent (void) const;

              FieldDescription *getFieldDescription (UInt32 uiFieldId);

              FieldDescription *findFieldDescription(const Char8 *szFieldName);

        const FieldDescription *findFieldDescription(
            const Char8 *szFieldName) const; 

        UInt32                 getNumFieldDescs(void) const;

        UInt32                 addDescription  (const FieldDescription &desc     );
        bool                   subDescription  (      UInt32            uiFieldId);

        FieldContainerPtr getPrototype(void                        ) const;
        bool              setPrototype(FieldContainerPtr pPrototype);

        bool isInitialized(void                           ) const;

        bool isAbstract   (void                           ) const;

        bool isDerivedFrom(const TypeBase           &other) const;
        bool isDerivedFrom(const FieldContainerType &other) const;    

        bool isNode       (void                           ) const;
        bool isNodeCore   (void                           ) const;
        bool isAttachment (void                           ) const;

        FieldContainerPtr createFieldContainer(void) const;
        NodePtr           createNode          (void) const;
        /*NodeCorePtr       createNodeCore      (void) const;*/
        /*AttachmentPtr     createAttachment    (void) const;*/

        virtual void dump(      UInt32    uiIndent = 0, 
                          const BitVector bvFlags  = 0) const;
    };

    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainer 
    {
      public:
        virtual       FieldContainerType &getType    (void);

        virtual const FieldContainerType &getType    (void) const;

                      UInt32              getTypeId  (void) const;

                      UInt16              getGroupId (void) const;

                const Char8              *getTypeName(void) const;

        virtual UInt32  getContainerSize(void) const = 0;


                Field  *getField        (      UInt32 fieldId  );

                Field  *getField        (const Char8 *fieldName);

        virtual FieldContainerPtr shallowCopy(void) const = 0;

      protected:
        FieldContainer(void);

        FieldContainer(const FieldContainer &obj);

        virtual ~FieldContainer (void);

    };
    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainerFactory
    {
      public :

        static FieldContainerFactory *the(void);
            
        FieldContainerType *findType    (      UInt32  uiTypeId) const;
        FieldContainerType *findType    (const Char8  *szName  ) const;
        UInt32              getNumTypes (void                  ) const;

              UInt16  findGroupId  (const Char8  *szName   ) const;
        const Char8  *findGroupName(      UInt16  uiGroupId) const;
            
              UInt16  getNumGroups (      void             ) const;


        FieldContainerPtr getContainer      (UInt32 uiFieldContainerId) const;

        FieldContainerPtr createFieldContainer(const Char8 *name) const;
        NodePtr           createNode          (const Char8 *name) const;
        /*NodeCorePtr       createNodeCore      (const Char8 *name) const;*/
        /*AttachmentPtr     createAttachment    (const Char8 *name) const;*/

      protected:
        FieldContainerFactory(void);

        virtual ~FieldContainerFactory(void); 
    };
    /******************************************************/
    /*                    AttachmentContainerPtr          */
    /******************************************************/
    /*class AttachmentContainerPtr : */
        /*public FieldContainerPtr*/
    /*{*/
      /*public:*/

        /*AttachmentContainerPtr(      void                          );*/
        /*AttachmentContainerPtr(const AttachmentContainerPtr &source);*/
        /*[>AttachmentContainerPtr(const NullFieldContainerPtr  &source);<]*/
        /*~AttachmentContainerPtr(void); */

        /*AttachmentContainer *operator->(void);*/
      /*protected:*/
    /*};*/

    /******************************************************/
    /*                    AttachmentContainer             */
    /******************************************************/
    class AttachmentContainer : public FieldContainer 
    {
      public:
        void          addAttachment (const AttachmentPtr &fieldContainerP, 
                                           UInt16         binding        = 0);

        void          subAttachment (const AttachmentPtr &fieldContainerP,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(      UInt32         groupId,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(const FieldContainerType &type,
                                       UInt16              binding   = 0);
      protected:
        AttachmentContainer(void);
        AttachmentContainer(const AttachmentContainer &source);
        ~AttachmentContainer(void);
    };
    /******************************************************/
    /*                    NodeCore                        */
    /******************************************************/
    class NodeCore : public AttachmentContainer
    {
      public:
        virtual void invalidateVolume(void);

        virtual void accumulateMatrix(Matrix &result);

      protected:
        NodeCore(void);
        NodeCore(const NodeCore &obj);
        virtual ~NodeCore(void);
    };
    /******************************************************/
    /*              NodePtr                               */
    /******************************************************/
    class NodePtr : public AttachmentContainerPtr
    {
      public:
         NodePtr(void);
         NodePtr(const NodePtr               &source);
         /*NodePtr(const NullFieldContainerPtr &source);*/


        ~NodePtr(void); 
        Node *operator->(void);
    };

    /******************************************************/
    /*              Node                                  */
    /******************************************************/
    class Node : public AttachmentContainer 
    {
      public:
        typedef NodePtr Ptr;

        NodeCorePtr getCore(      void             );

        void        setCore(const NodeCorePtr &core);
        
        NodePtr getParent(void);

        UInt32  getNChildren  (void                     ) const;
        
        void    addChild      (const NodePtr &childP    );

        void    insertChild   (      UInt32   childIndex, 
                               const NodePtr &childP    );

        void    replaceChild  (      UInt32   childIndex,    
                               const NodePtr &childP    );

        bool    replaceChildBy(const NodePtr &childP, 
                               const NodePtr &newChildP );

        Int32   findChild     (const NodePtr &childP    ) const;

        void    subChild      (const NodePtr &childP    );
        void    subChild      (      UInt32   childIndex);

        NodePtr getChild      (      UInt32   childIndex);
        
        bool   getActive  (void      ) const;

        void   setActive  (bool   val);

        void   setTravMask(UInt32 val);
        UInt32 getTravMask(void      ) const;

        void   setOcclusionMask(UInt8 val);
        UInt8  getOcclusionMask(void      ) const;

        NodePtr clone(void);
        
        Matrix getToWorld(void          );
        
        void   getToWorld(Matrix &result);
               DynamicVolume &getVolume       (bool update          );
               /*BoxVolume     &editVolume      (bool update          );*/
        /*const  BoxVolume     &getVolume       (void                 ) const;*/
               /*void           getWorldVolume  (BoxVolume     &result);*/
        
               void           updateVolume    (void                 );

               void           invalidateVolume(void                 );
      protected:
        Node(void);
        Node(const Node &source);
        virtual ~Node (void);
    };
}

