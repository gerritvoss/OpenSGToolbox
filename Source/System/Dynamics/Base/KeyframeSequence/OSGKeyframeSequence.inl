/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

/*!
 * \brief Get the Key
 *
 * \param[in] index The index of the key
 */
inline
Real32 KeyframeSequence::getKey(UInt32 index)
{
    return getInternalKeys(index);
}

/*!
 * \brief Get the Key
 *
 * \param[in] index The index of the key
 */
inline
Real32 KeyframeSequence::getKey(UInt32 index) const
{
    return getInternalKeys(index);
}

/*!
 * \brief Get the Key
 *
 * \param[in] index The index of the key
 * \param[out] val Replaced with the key
 */
inline
void KeyframeSequence::getKey( Real32 &val, UInt32 index)
{
    val = getInternalKeys(index);
}

/*!
 * \brief Get the Key
 *
 * \param[in] index The index of the key
 * \param[out] val Replaced with the key
 */
inline
void KeyframeSequence::getKey( Real32 &val, UInt32 index) const
{
    val = getInternalKeys(index);
}

/*!
 * \brief Get the Keys
 *
 * \returns An uneditable reference to a MultiField of Real32
 */
inline
const MFReal32 &KeyframeSequence::getKeys(void) const
{
    return *getMFInternalKeys();
}

/*!
 * \brief Get the Keys
 *
 * \returns An editable reference to a MultiField of Real32
 */
inline
MFReal32 *KeyframeSequence::editKeys(void)
{
	return editMFInternalKeys();
}

OSG_END_NAMESPACE
