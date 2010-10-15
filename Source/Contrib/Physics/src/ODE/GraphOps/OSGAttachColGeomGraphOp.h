/*---------------------------------------------------------------------------*\
*                                OpenSG                                     *
*                                                                           *
*                                                                           *
*             Copyright (C) 2000-2002 by the OpenSG Forum                   *
*                                                                           *
*                            www.opensg.org                                 *
*                                                                           *
*                   contact: dan.guilliams@gmail.com                        *
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
/*---------------------------------------------------------------------------*\
*                                Changes                                    *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
\*---------------------------------------------------------------------------*/


#ifndef _OSGATTACHCOLGEOMGRAPHOP_H_
#define _OSGATTACHCOLGEOMGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGContribPhysicsDef.h"
#include "OSGAction.h"
#include <boost/xpressive/xpressive_dynamic.hpp>

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! AttachColGeomGraphOp class

class OSG_CONTRIBPHYSICS_DLLMAPPING AttachColGeomGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    enum GeoType
    {
        TRI_MESH_GEOM = 0,
        BOX_GEOM      = 1,
        SPHERE_GEOM   = 2,
        CAPSULE_GEOM  = 4,
        REMOVE_GEOM   = 5
    };

    enum BitComparisionOps
    {
        BIT_EQUAL     = 0,
        BIT_AND       = 1,
        BIT_OR        = 2,
        BIT_XOR       = 3,
        BIT_NOT       = 4,
        BIT_NOT_EQUAL = 5
    };

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef AttachColGeomGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(AttachColGeomGraphOp);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "AttachColGeomGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create();

    virtual GraphOpTransitPtr clone (void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

	/*! Sets the string to search for in a node's name. 
	*	Only the end of the node's name is checked.
	*	@param MatchName String to look for in a node's name. 
	*
	*/
    void setMatchRegex(const std::string& MatchRegex);
    void setMatchRegex(const boost::xpressive::cregex& MatchRegex);
    void setMatchWholeName(bool value);

	/*! Sets whether or not to check a node's name for the search string.
	*	If true, and a node's name ends in the search string, the new trav mask
	*	will be set.
	*	@param MatchName If true, the name will be checked for the search string.
	*/
	void setMatchName(bool MatchName = true);

	/*! Sets whether or not to check a node current traversal mask.
	*	If true, and a node's traversal mask matches the one set by setCurrentTravMask, 
	*	the new trav mask will be set.
	*	@param MatchCore If true, the node's traversal mask will be checked. 
	*/
	void setMatchCurrentTravMask(bool MatchCurMask = true);
    void setMatchMaskCondition(UInt8 MatchMaskCondition);
    void setCurrentTravMaskValue(UInt32 CurrentTraversalMask);
	void setCreateGeomType(UInt32 TheGeomType);

    
	void setCollideMask(UInt32 CollideMask);
	void setCategoryMask(UInt32 CategoryMask);

	/*! Returns the number of nodes whose traversal masks was changed. 
	 *
	 *	@return Only accurate after the graph op has been completed.
	 */
	UInt32 getNumChanged( void );

	virtual std::string usage(void);
	virtual void setParams(const std::string params);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             AttachColGeomGraphOp();

    virtual ~AttachColGeomGraphOp(void                                );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
    //Name matching criteria
	bool mMatchName;
    boost::xpressive::cregex mMatchRegex;
    bool mMatchWholeName;

    //Mask matching criteria
	bool mMatchCurTravMask;
	UInt32 mMatchCurTravMaskValue;
    UInt8  mMatchMaskCondition;

    
	UInt32 mCollideMask;
	UInt32 mCategoryMask;

    //Parameters for attaching geom
    UInt32 mCreateGeomType;

	UInt32 mNumChanged;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef AttachColGeomGraphOp *AttachColGeomGraphOpP;

OSG_GEN_MEMOBJPTR(AttachColGeomGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGATTACHCOLGEOMGRAPHOP_H_ */
