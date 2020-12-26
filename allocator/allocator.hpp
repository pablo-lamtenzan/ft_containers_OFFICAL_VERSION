/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:26:51 by pablo             #+#    #+#             */
/*   Updated: 2020/12/26 16:33:52 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
** Documentation: https://en.cppreference.com/w/cpp/memory/allocator
*/

# include <iostream>
# include <limits>
# include <new>

namespace ft
{
	template <class T>
	class allocator
	{
		public:

		/* Member types */

		typedef T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef std::size_t		size_type;
		typedef difference_type	std::ptrdiff_t;

		template <class U>
		struct rebind { typedef allocator<U> other; };

		/* Member functions */

		allocator() throw() { }
		allocator(const allocator& other) throw() { (void)other; }
		template <class U>
		allocator(const allocator<U>& other) throw() { (void)other; }
		~allocator() { };

		pointer			address(reference x) const { return (&x); }
		const_pointer	address(const_pointer x) const { return (&x); }

		// TO DO: What have i to do with hint ?
		pointer		allocate(size_type n, const void* hint = 0)
		{
			if (std::numeric_limits<size_type>::max() / sizeof(T) < n)
				throw std::bad_array_new_length();

			pointer alloc;

			try {
				alloc = (pointer)(::operator new(n * sizeof(value_type));
			} catch (const std::bad_alloc& e) { std::cerr << e.what() << std::endl; throw std::bad_alloc(); }

			return (alloc);
		}

		void		deallocate(pointer p, size_type n) { ::operator delete((void*)p, n); }
		size_type	max_size() const throw() { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
		void		contruct(pointer p, const_reference val) { new (void*)p value_type(val); }
		void		destroy(pointer p) { ((pointer)p)->~value_type(); };

		/* Non-member functions */

		template <class T1, class T2>
		bool		operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() { return (&lhs == &rhs); }
		template <class T1, class T2>
		bool		operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() { return (&lhs != &rhs); }
	};
};
