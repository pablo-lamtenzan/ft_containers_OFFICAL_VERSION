/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LegacyRandomAccessIterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:49:10 by pablo             #+#    #+#             */
/*   Updated: 2020/12/26 18:53:08 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
** LegacyRandomAccessIterator is a LegacyBidirectionalIterator that can be moved
** to point to any element in constant time.
** A pointer to an element of an array satisfies all requeriment of LegacyBidirectionalAccessIterator
**
** Documentation: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
*/

# include <cstddef>

namespace ft
{
	template <typename It>
	class LegacyRandomAccessIterator
	{
		public:

		/* Member types */

		typedef It				value_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		// TO DO: (to change + more o add + remove the const)
		typedef It				reference;
		typedef It				const_reference;
		typedef It				pointer;
		typedef It				const_pointer;
		typedef std::bidirectional_iterator_tag	iterator_category;
		
		/* Iterator (current address in the array) */
		private:
		
		pointer					curr;

		public:

		/* Member functions */

		reference							get_curr() const { return (curr); }

		LegacyRandomAccessIterator() : curr(nullptr) { }
		LegacyRandomAccessIterator(pointer ptr) : curr(ptr) { }
		//LegacyRandomAccessIterator() TO DO
		~LegacyRandomAccessIterator() { }

		/* Handle assignation */
		//LegacyRandomAccessIterator&		operator=() { }
		/* Handle address addition */
		LegacyRandomAccessIterator			operator+(difference_type n) { return (LegacyRandomAccessIterator(curr + n)); }
		/* Handle integer addition with no const iterator */
		//size_type							operator+() { }
		/* Handle integer addtion with const iterator */
		//size_type							operator+() { }
		/* Handle address substraction */
		LegacyRandomAccessIterator			operator-(difference_type n) { return (LegacyRandomAccessIterator(curr - n)); }
		/* Handle integer substraction with no const iterator */
		//size_type							operator-() { }
		/* Handle integer substraction with const iterator */
		//size_type							operator-() { }
		/* Handle self addition */
		LegacyRandomAccessIterator			operator+=(difference_type n) { curr += n; return (*this); }
		/* Handle self substraction */
		LegacyRandomAccessIterator			operator-=(difference_type n) { curr -= n; return (*this); }
		/* Handle post-incrementation */
		LegacyRandomAccessIterator			operator++(int) { LegacyRandomAccessIterator aux(curr); operator++(); return (aux); }
		/* Handle pre-incrementation */
		LegacyRandomAccessIterator&			operator++() { curr++; return (*this); }
		/* Handle post-decrementation */
		LegacyRandomAccessIterator			operator--(int) { LegacyRandomAccessIterator aux(curr); operator--(); return (aux); }
		/* Handle pre-decrementation */
		LegacyRandomAccessIterator&			operator--() { curr--; return (*this); }
		/* Handle self dereference by pointer */
		reference							operator*() { if (!curr) throw::std::out_of_range(std::string("Error: Out of bounds.")); return (*this); }
		/* Handle self dereference by squared brackets */
		reference							operator[](difference_type pos) { return (curr + pos); }
		/* Handle boolean equity */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() == rhs.get_curr()); }
		/* Handle boolean inequity */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() != rhs.get_curr()); }
		/* Handle boolean leeser */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() < rhs.get_curr()); }
		/* Handle boolean leeser equity */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() <= rhs.get_curr()); }
		/* Hanlde boolean greather */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() > rhs.get_curr()); }
		/* Handle boolean greather equity */
		template <class It1, class it2>
		bool								operator==(const LegacyRandomAccessIterator<It1>& lhs, const LegacyRandomAccessIterator<It2>& rhs) { return (lhs.get_curr() >= rhs.get_curr()); }
	};
};
