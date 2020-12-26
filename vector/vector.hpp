/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:37:12 by pablo             #+#    #+#             */
/*   Updated: 2020/12/26 17:42:46 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
** Documentation: https://en.cppreference.com/w/cpp/container/vector
*/

# include <allocator.hpp>

// A vector works like malloc: pre-allocates mem blocks to handle future grow (MUST DO IT)
// 		for that check: capacity() and reserve()

namespace ft
{
	template <class T, class Allocator = allocator<T>>
	class vector
	{
		public:

		/* Member types */

		typedef T				value_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		// TO DO: iterators

		/* Member functions */

			/* Constructor */
		vector();
		explicit vector(const Allocator& alloc);
		explicit vector(size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator());
		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator& = Allocator());

			/* Destructor */
		~vector();

			/* Operator= */
		vector&		operator=(const vector& other);

			/* Assign */
		void		assign(size_type count, const reference value);
		template <class InputIt>
		void		assign(InputIt first, InputIt last);

			/* No implement get_allocator (subject rules) */

		/* Member functions: Element access */

			/* At */
		reference			at(size_type pos);
		const_reference		at(size_type pos) const;

			/* Operator[] */
		reference			operator[](size_type pos);
		const_reference		operator[](size_type pos) const;

			/* Front */
		reference			front();
		const_reference		front() const;

			/* Back */
		reference			back();
		const_reference		back() const;

			/* begin */
		// to do

			/* end */
		// to do

		/* Member fucntions: Capacity */

			/* empty */
		bool				empty() const;

			/* size */
		size_type			size() const;

			/* max size */
		size_type			max_size() const;

			/* reserve */
		void				reserve(size_type new_cap);

			/* capacity */
		size_type			capacity() const;

		/* Member functions: Modifiers */

			/* clear */
		void				clear();

			/* insert */
		// to do

			/* ease */
		// to do

			/* Push_back */
		void				push_back(const_reference value);

			/* Pop_back */
		void				pop_back();

			/* Resize */
		void				resize(size_type count, value_type value = value_type());
		
		/* Non-member functions */
		template <class T, class Alloc>
		bool				operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		template <class T, class Alloc>
		bool				operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		template <class T, class Alloc>
		bool				operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		template <class T, class Alloc>
		bool				operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		template <class T, class Alloc>
		bool				operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		template <class T, class Alloc>
		bool				operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
		
	};
};
