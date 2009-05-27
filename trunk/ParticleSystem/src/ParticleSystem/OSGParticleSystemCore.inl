/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


inline
ParticleSystemCore::SystemUpdateListener::SystemUpdateListener(ParticleSystemCorePtr TheCore) : _Core(TheCore)
{
}


template <class RandomAccessIterator, class Compare>
void insertionSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{ //performs insertion sort between first and last using comp
	RandomAccessIterator curItor(first), prevItor(first), i(first);
	for(++i; i!= last; ++i)
	{ // outer loop continues until all elements have been sorted
		for(curItor = i; (curItor != first) && (comp(*curItor, *(curItor - 1))) ; curItor--)
		{
			std::swap(*curItor,*(curItor - 1));
		}	
	}
}



/**
**  SmoothSort function template + helper functions.
**
**    Formal type T should have a comparison operator >= with prototype:
**
**      bool T::operator >= (const T &) const throw ();
**
**    which should compare its arguments by the given relation
**     (possibly taking advantage of the type itself).
**
**
**/



/**  Sort an array in ascending order.  **/
template <class T, class C>
void smoothsort (T, unsigned, C) throw ();



namespace

/**
**  Helper function's local namespace (declarations).
**
**/

{
	class LeonardoNumber

		/**
		**  Helper class for manipulation of Leonardo numbers
		**
		**/

	{
	public:
		/**  Default ctor.  **/
		LeonardoNumber (void) throw () : actual (1), companion (1)
		{ return; }

		/**  Copy ctor.  **/
		LeonardoNumber (const LeonardoNumber & _l) throw () : actual (_l.actual), companion (_l.companion)
		{ return; }

		/**  
		**  Return the "gap" between the actual Leonardo number and the
		**  preceding one.
		**/
		unsigned gap (void) const throw ()
		{ return actual - companion; }


		/**  Perform an "up" operation on the actual number.  **/
		LeonardoNumber & operator ++ (void) throw ()
		{ unsigned s = actual; actual = actual + companion + 1; companion = s; return * this; }

		/**  Perform a "down" operation on the actual number.  **/
		LeonardoNumber & operator -- (void) throw ()
		{ unsigned s = companion; companion = actual - companion - 1; actual = s; return * this; }

		/**  Return "companion" value.  **/
		unsigned operator ~ (void) const throw ()
		{ return companion; }

		/**  Return "actual" value.  **/
		operator unsigned (void) const throw ()
		{ return actual; }


	private:
		unsigned actual;   /**  Actual number.  **/
		unsigned companion;   /**  Companion number.  **/
	};


	/**  Perform a "sift up" operation.  **/
	template <class T, class C>
	inline void sift (T, unsigned, LeonardoNumber, C) throw ();

	/**  Perform a "semi-trinkle" operation.  **/
	template <class T, class C>
	inline void semitrinkle (T, unsigned, unsigned long, LeonardoNumber, C) throw ();

	/**  Perform a "trinkle" operation.  **/
	template <class T, class C>
	inline void trinkle (T, unsigned, unsigned long, LeonardoNumber, C) throw ();
}

template <class T, class C>
void smoothsort (T first, unsigned size, C comp) throw ()
{
/**
**  Sorts the given array in ascending order.
**
**    Usage: smoothsort (<array>, <size>)
**
**    Where: <array> pointer to the first element of the array in question.
**            <size> length of the array to be sorted.
**
**
**/

  if (!size) return; // no sorting if there is nothing to sort

  unsigned long p = 1;  
  LeonardoNumber leoNum;

  for (unsigned q = 0; ++q < size ; ++p)
  {
    if (p % 8 == 3)
      {
        sift<T,C> (first, q - 1, leoNum, comp);

        ++++leoNum; p >>= 2;
      }

    else if (p % 4 == 1)
      {
        if (q + ~leoNum < size)  sift<T,C> (first, q - 1, leoNum, comp);
        else  trinkle<T,C> (first, q - 1, p, leoNum, comp);

        for (p <<= 1; --leoNum > 1; p <<= 1)  ;
      }
  }

  trinkle<T,C> (first, size - 1, p, leoNum, comp);

  for (--p; size-- > 1; --p)
  {
    if (leoNum == 1)
	{
      for ( ; !(p % 2); p >>= 1)  ++leoNum;
	}

    else if (leoNum >= 3)
      {
        if (p)  semitrinkle<T,C> (first, size - leoNum.gap (), p, leoNum, comp);

        --leoNum; p <<= 1; ++p;
        semitrinkle<T,C> (first, size - 1, p, leoNum, comp);
        --leoNum; p <<= 1; ++p;
      }
  }


  return;
}

 namespace

/**
**  Helper function's local namespace (definitions).
**
**/

{
  template <class T, class C>
  inline void sift (T first, unsigned root, LeonardoNumber leoNum, C comp) throw ()

   /**
    **  Sifts up the root of the stretch in question.
    **
    **    Usage: sift (<array>, <root>, <number>, <comp>)
    **
    **    Where:     <array> Pointer to the first element of the array in
    **                       question.
    **                <root> Index of the root of the array in question.
    **              <number> Current Leonardo number.
	**				  <comp> Comparing function.
    **
    **
    **/

    {
      unsigned r2;

      while (leoNum >= 3)
        {
          if (comp(*(first + root - leoNum.gap()),*(first + root - 1)))
            r2 = root - leoNum.gap();
          else
            { r2 = root - 1; --leoNum; }

          if (*(first + root) , *(first + r2))  break;
          else
            { std::swap(*(first + root), *(first + r2)); root = r2; --leoNum; }
        }


      return;
    }


  template <class T, class C>
  inline void semitrinkle (T first, unsigned root, unsigned long _p,
                                           LeonardoNumber leoNum, C comp) throw ()

   /**
    **  Trinkles the roots of the stretches of a given array and root when the
    **  adjacent stretches are trusty.
    **
    **    Usage: semitrinkle (<array>, <root>, <standard_concat>, <number>)
    **
    **    Where:           <array> Pointer to the first element of the array in
    **                             question.
    **                      <root> Index of the root of the array in question.
    **           <standard_concat> Standard concatenation's codification.
    **                    <number> Current Leonardo number.
    **
    **
    **/

    {
      if (comp(*(first + root - ~leoNum),*(first + root)))
        {
          std::swap(*(first + root), *(first + root - ~leoNum));
          trinkle<T,C> (first, root - ~leoNum, _p, leoNum, comp);
        }


      return;
    }


  template <class T, class C>
  inline void trinkle (T first, unsigned root, unsigned long _p,
                                        LeonardoNumber leoNum, C comp) throw ()

   /**
    **  Trinkles the roots of the stretches of a given array and root.
    **
    **    Usage: trinkle (<array>, <root>, <standard_concat>, <number>)
    **
    **    Where:           <array> Pointer to the first element of the array in
    **                             question.
    **                      <root> Index of the root of the array in question.
    **           <standard_concat> Standard concatenation's codification.
    **                    <number> Current Leonardo number.
    **
    **
    **/

    {
      while (_p)
        {
          for ( ; !(_p % 2); _p >>= 1)  ++leoNum;

          if (!--_p || (comp(*(first + root), *(first +root - leoNum))))  break;
          else
            if (leoNum == 1)
			{ std::swap(*(first+root), *(first + root - leoNum)); root -= leoNum; }

            else if (leoNum >= 3)
              {
                unsigned r2 = root - leoNum.gap (), r3 = root - leoNum;

                if (comp(*(first + root - 1), *(first+r2)))
                  { r2 = root - 1; _p <<= 1; --leoNum; }

                if (comp(*(first + r3), *(first + r2)))
                { 
					  std::swap(*(first + root), *(first + r3)); 
					  root = r3; 
				}

                else
                  { std::swap(*(first + root), *(first + r2)); root = r2; --leoNum; break; }
              }
        }

      sift<T,C> (first, root, leoNum, comp);


      return;
    }
}




OSG_END_NAMESPACE

#define OSGPARTICLESYSTEMCORE_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

