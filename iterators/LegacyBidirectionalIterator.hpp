/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LegacyBidirectionalIterator.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:15:52 by pablo             #+#    #+#             */
/*   Updated: 2020/12/28 17:49:57 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
** Documentation: https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator
*/

# include <cstddef>
# include <exception>

namespace ft
{
	/*
	** Struct used as doubly-linked-lst for list.
	** Throws bad alloc.
	**
	** Note: prev and next must be redifined to NIL after it use of all the functional nodes.
	*/
	template <class T>
	struct Node
	{
		typedef	T		value_type;

		value_type		data;
		Node*			prev;
		Node*			next;

		Node() { }
		Node(Node* p = nullptr, Node* n = nullptr,  const value_type& d = value_type()) : data(d), prev(p), next(n)
		{
			Node*	node;
			try {
				node = memory.allocate(sizeof(*node));
			} catch (std::bad_alloc& e) { throw std::bad_alloc(); }
			*node = (Node){.data=d, .prev=p, .next=n};
		}
		
		Node&	operator=(const Node& other)
		{
			if (this != &src)
			{
				data = other.data;
				prev = other.prev;
				next = other.next;
			}
			return (*this);
		}
	};
	
	template <class It>
	class LegacyBidirectionalIterator
	{
		public:
		
		/* Member types */

		typedef It								value_type;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef std::bidirectional_iterator_tag	iterator_category;

		protected:

		/* Iterator (current node in the doubly-linked-list) */

		typedef Node<It>						Node;
		
		Node*									it;

		public:

		/* Member functions */
		
		LegacyBidirectionalIterator() : it(nullptr) { }
		LegacyBidirectionalIterator(Node* ptr) : it(ptr) { }
		LegacyBidirectionalIterator(const LegacyBidirectionalIterator& other) : it(other.it) { }
		~LegacyBidirectionalIterator() { }

		/* Handle assignation */
		LegacyBidirectionalIterator&		operator=(const LegacyBidirectionalIterator& other) { it = other.it; return (*this); }
		/* Handle address addition */
		LegacyBidirectionalIterator			operator+(difference_type n)
		{
			Node*	aux(it);
			// Problem here i don't have NIL
			while (--n) // && != NIL
				aux = aux->next;
			if (n) // Error not space
				; // raise exeception
			return (LegacyBidirectionalIterator(aux));
		}
		/* Handle integer addition with no const iterator */
		size_type							operator+(LegacyBidirectionalIterator& other)
		{
			Node*	aux(it);
			// Problem here i dont't have NIL
			size_type size = 0;
			while (aux != other) // && != NIL
			{
				aux = aux->next;
				size++;
			}
			// Handle nil error
			return (size);
		}
		/* Handle integer addtion with const iterator */
		size_type							operator+(const LegacyBidirectionalIterator& other)
		{
			Node*	aux(it);
			// Problem here i dont't have NIL
			size_type size = 0;
			while (aux != other) // && != NIL
			{
				aux = aux->next;
				size++;
			}
			// Handle nil error
			return (size);
		}
		/* Handle address substraction */
		LegacyBidirectionalIterator			operator+(difference_type n)
		{
			Node*	aux(it);
			// Problem here i don't have NIL
			while (--n > 0) // && != NIL
				aux = aux->prev;
			if (n) // Error not space
				; // raise exeception
			return (LegacyBidirectionalIterator(aux));
		}
		/* Handle integer substraction with no const iterator */
		// HOW IMPLEMENT THIS ?
		/* Handle integer substraction with const iterator */
		// HOW IMPLEMENT THIS ?
		// Check if i have to do +, -, +=, -=
		
		/* Handle post-incrementation */
		LegacyBidirectionalIterator			operator++(int)
		{
			LegacyBidirectionalIterator aux(it); 
			operator++();
			return (aux);
		}
		/* Handle pre-incrementation */
		LegacyBidirectionalIterator&		operator++()
		{
			// Need NIL to check out of bounds

			it = it->next;
			return (*this);
		}
		/* Handle post-decrementation */
		LegacyBidirectionalIterator			operator--(int)
		{
			LegacyBidirectionalIterator aux(it); 
			operator--();
			return (aux);
		}
		/* Handle pre-decrementation */
		LegacyBidirectionalIterator&		operator++()
		{
			// Need NIL to check out of bounds

			it = it->prev;
			return (*this);
		}
		/* Handle self dereference by pointer */
		reference							operator*()
		{
			// Need NIL to check out of bounds
			if (it == NIL)
				throw::std::out_of_range(std::string("Error: Out of bounds."));
			return (*it);
		}
		const_reference						operator*() const
		{
			// Need NIL to check out of bounds
			if (it == NIL)
				throw::std::out_of_range(std::string("Error: Out of bounds."));
			return (*it);
		}
		/* Handle pointing to self methods */
		reference							operator->() { return (it); }
		const_pointer						operator->() const { return (it); }
		/* Handle self dereference by squared brackets */
		reference							operator[](difference_type pos)
		{
			Node* aux(HEAD); // NEED TO START IN THE BEGIN (need HEAD)
			
			while (pos-- > 0) // && pos != NIL
				aux = aux->next;
			if (pos)
				; // Out of bounds
			return (aux);
		}
		const_reference						operator[](difference_type pos) const
		{
			Node* aux(HEAD); // NEED TO START IN THE BEGIN (need HEAD)
			
			while (pos-- > 0) // && pos != NIL
				aux = aux->next;
			if (pos)
				; // Out of bounds
			return (aux);
		}

		// TO DO: Not sure about this implementation
	
		/* Handle boolean equity */
		template <class It1, class It2>
		bool								operator==(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it == rhs.it); }
		/*Handle boolean inequity */
		template <class It1, class It2>
		bool								operator!=(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it != rhs.it); }
		/* Handle boolean lesser */
		template <class It1, class It2>
		bool								operator<(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it < rhs.it); }
		/* Handle boolean leeser equity */
		template <class It1, class It2>
		bool								operator<=(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it <= rhs.it); }
		/* Handle boolean greather */
		template <class It1, class It2>
		bool								operator>(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it > rhs.it); }
		/* Hnalde boolean greather equity */
		template <class It1, class It2>
		bool								operator>=(const LegacyBidirectionalIterator<It1>& lhs, const LegacyBidirectionalIterator<It2>& rhs) { return (lhs.it >= rhs.it); }
	};
};