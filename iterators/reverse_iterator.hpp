/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:08:59 by pablo             #+#    #+#             */
/*   Updated: 2020/12/27 19:07:29 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
** Documentation: https://en.cppreference.com/w/cpp/iterator/reverse_iterator
*/

# include <memory>

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
		/* Poliphorm member types */

		typedef Iter					iterator_type;
		typedef Iter::difference_type	difference_type;
		typedef Iter::value_type		value_type;
		typedef Iter::pointer			pointer;
		typedef Iter::reference			reference;
		typedef Iter::iterator_category	iterator_category;

		protected:

		/* Core */

		iterator_type					it;

		public:
		
		/* Member functions */

		reverse_iterator() { }
		explicit reverse_iterator(iterator_type x) : it(x) { }

		template <class U>
		reverse_iterator(const reverse_iterator<U>& other)
		{
			if (this != &other)
			{
				// To do
			}
		}

		template <class U>
		reverse_iterator&		operator=(const reverse_iterator<U>& other)
		{
			if (this != &other)
				it = other.it;
			return (*this);
		}

		/* Access to underlying iterator */
		iterator_type			base() const { return (it); }

		/* Access to pointed-to element */
		reference				operator*() const { return (*it); }
		pointer					operator->() const { return (std::addressof(operator*())); }

		/* Acess element by index */
		reference				operator[](difference_type n) const { return (base()[-n - 1]); }

		/* Advances or decrementes the iterator */
		reverse_iterator&		operator++() { it++; return (*this); }
		reverse_iterator&		operator--() { it--; return (*this); }
		reverse_iterator&		operator++(int) { reverse_iterator aux(*this); it++; return (aux); }
		reverse_iterator&		operator--(int) { reverse_iterator aux(*this); it--; return (aux); }
		reverse_iterator&		operator+(difference_type n) const { return (reverse_iterator(base() - n)); }
		reverse_iterator&		operator-(difference_type n) const { return (reverse_iterator(base() + n)); }
		reverse_iterator&		operator+=(difference_type n) { it += n; return (*this); }
		reverse_iterator&		operator-=(difference_type n) { it -= n; return (*this); }

		protected:

		/* Member objects */

		iterator_type			get_iterator() { return (it); }

		/* No member functions */

		template <class Iterator1, class Iterator2>
		bool					operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs == rhs); }
		template <class Iterator1, class Iterator2>
		bool					operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs != rhs); }
		template <class Iterator1, class Iterator2>
		bool					operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs < rhs); }
		template <class Iterator1, class Iterator2>
		bool					operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs <= rhs); }
		template <class Iterator1, class Iterator2>
		bool					operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs > rhs); }
		template <class Iterator1, class Iterator2>
		bool					operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs >= rhs); }
		template <class Iter>
		reverse_iterator<Iter>	operator+(typename reverse_ierator<Iter>::difference_type n, const reverse_iterator<Iter>& it) { return (reverse_iterator<Iter>(it.base() - n)); }
		template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base()); }
	};
};
