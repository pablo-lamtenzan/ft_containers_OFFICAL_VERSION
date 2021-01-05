/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:24:05 by pablo             #+#    #+#             */
/*   Updated: 2021/01/05 09:40:31 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <allocator.hpp>
# include <LegacyBidirectionalIterator.hpp>
# include <reverse_iterator.hpp>
# include <lexicographical_compare.hpp>

/*
** Implementation of list ussing a doubly-linked-lint with a countrol node (nil)
** pointinf to the head and the tail.
**
** Documentation: https://en.cppreference.com/w/cpp/container/list
*/

# define NIL	nil
# define HEAD	nil->next
# define TAIL	nil->prev

namespace ft

// TO DO: Handle ressources in construct destructor
// TO DO: Add an atribute --> curr_lenght
{
	template <class T, class Allocator = allocator<T>>
	class list
	{
		/* Member types */
		
		typedef T							value_type;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef Allocator::reference		reference;
		typedef Allocator::const_reference	const_reference;
		typedef Allocator::pointer			pointer;
		typedef Allocator::const_pointer	const_pointer;

		typedef LegacyBidirectionalIterator<value_type>			iterator;
		typedef LegacyBidirectionalIterator<const value_type>	const_iterator;
		typedef	reverse_iterator<iterator>						reverse_iterator;
		typedef reverse_iterator<const_iterator>				const_reverse_iterator;

		protected:

		/* Core */
		
		Allocator			memory;
		Node*				lst;
		Node*				NIL;
		size_type			lenght;

		/*
		** Allocates a new node of lst and return its address.
		** If allocations fails freeresuts. the ressources and throw an exeption.
		**
		** Note: Call new_node wihout a NIL defined may cuases indefined behaviours.
		*/
		Node*				new_node(const_reference d = value_type())
		{
			Node*	node;
			try {
				node = Node(NIL, NIL, d);
			} catch (std::bad_alloc& e) { if (lst != NIL) this->~list(); throw ; }
			lenght++;
			return (node);
		}

		/*
		** Links target between prev and next.
		*/
		void				link(Node* target, Node* prev, Node* next)
		{
			target->prev = prev;
			prev->next = target;
			target->next = next;
			next->prev = target;
		}

		/*
		** Unlink target without deallocating memory.
		*/
		void					unlink(Node* target)
		{
			target->next->prev = target->prev;
			target->prev->next = target->next;
		}
		
		public:

		/* Member function */

			/* Constructor */
		list() : memory(Allocator), lenght(0ul)
		{
			try {
				NIL = Node();
			} catch (const std::bad_alloc& e) { throw ; }
			HEAD = NIL;
			TAIL = NIL;
			lst = NIL;
		}

		explicit list(const Allocator& alloc) : memory(alloc), lenght(0ul)
		{
			try {
				NIL = Node();
			} catch (const std::bad_alloc& e) { throw ; }
			HEAD = NIL;
			TAIL = NIL;
			lst = NIL;
		}

		template <class InputIt>
		list(InputIt first, InputIt last, const Allocator& alloc = Allocator()): memory(alloc)
		{
			// To do
			assign(first, last);
		}

		list(const list& other)
		{
			if (this != &other)
			{
				memory = other.memory;
				lenght = other.lenght;
				NIL = other.NIL;
				// To do: List dup (check if insert of assign can do the job)
			}
		}

			/* Destructor */
		~list()
		{
			for (Node* i = HEAD ; i != NIL ; i = i->next)
				memory.destroy(i);
			memory.destroy(NIL);
		}

			/* Operator= */
		list&					operator=(const list& other);
	
			/* Assign */
		void					assign(size_type count, const_reference value);
		template <class InputIt>
		void					assign(InputIt first, InputIt last);

			/* No implement get_allocator (subject rules) */
		
		/* Member functions: Element access */
		
			/* Front */
		reference				front();
		const_reference			front() const;

			/* Back */
		reference				back();
		const_reference			back() const;

		/* Member functions: Iterators */

			/* Begin */
		iterator				begin();
		const_iterator			begin() const;

			/* End */
		iterator				end();
		const_iterator			end() const;

			/* Rbegin */
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;

			/* Rend */
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/* Member functions: Capacity */

			/* Empty */
		bool					empty() const;

			/* Size */
		size_type				size() const;

			/* Max size */
		size_type				max_size() const;

		/* Member functions: Modifiers */

			/* Clear */
		void					clear();

			/* Insert */
		iterator				insert(iterator pos, const_reference value);
		void					insert(iterator pos, size_type count, const_reference value);
		template <class InputIt>
		void					insert(iterator pos, InputIt first, InputIt last);

			/* Erase */
		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);

			/* Push back */
		void					push_back(const_reference value);

			/* Pop back */
		void					pop_back();

			/* Push front */
		void					push_front(const_reference value);

			/* Pop front */
		void 					pop_front();

			/* Resize */
		void					resize(size_type count);
		void					resize(size_type count, value_type value = value_type());

			/* Swap */
		void					swap(list& other);
		
		/* Member functions: Operations */

			/* Merge */
		void					merge(list& other);
		template <class Compare>
		void					merge(list& other, Compare comp);

			/* Splice */
		void					splice(const_iterator pos, list& other);
		void					splice(const_iterator pos, list& other, const_iterator it);
		void					splice(const_iterator pos, list& other, const_iterator first, const_iterator last);

			/* Remove */
		void					remove(const_reference value);
		template <class UnaryPredicate>
		void					remove_if(UnaryPredicate p);

			/* Reverse */
		void					reverse();

			/* Unique */
		void					unique();
		template <class BinaryPredicate>
		void					unique(BinaryPredicate p);

			/* Sort */
		void					sort();
		template <class Compare>
		void					sort(Compare comp);

		/* Non-member functions */

		template<class T, class Alloc>
		bool					operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		template<class T, class Alloc>
		bool					operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		template<class T, class Alloc>
		bool					operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		template<class T, class Alloc>
		bool					operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		template<class T, class Alloc>
		bool					operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		template<class T, class Alloc>
		bool					operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	};

	/* Operator= */
	template <class T, class Allocator>
	list<T, Allocator>&						list<T, Allocator>::operator=(const list& other)
	{
		if (this != &other)
		{
			memory = other.memory;
			clear();
			for (Node* i = other.HEAD ; i != other.NIL ; i = i->next)
				push_back(i->data);
		}
		return (*this);
	}
	
	/* Assign */
	template <class T, class Allocator>
	void									list<T, Allocator>::assign(size_type count, const_reference value)
	{
		
	}

	/* Assign */
	template <class T, class Allocator>
	template <class InputIt>
	void									list<T, Allocator>::assign(InputIt first, InputIt last)
	{
		
	}

	/* Front */
	template <class T, class Allocator>
	list<T, Allocator>::reference			list<T, Allocator>::front()
	{
		return (HEAD);
	}

	/* Front */
	template <class T, class Allocator>
	list<T, Allocator>::const_reference		list<T, Allocator>::front() const
	{
		return (HEAD);
	}

	/* Back */
	template <class T, class Allocator>
	list<T, Allocator>::reference			list<T, Allocator>::back()
	{
		return (TAIL);
	}
	
	/* Back */
	template <class T, class Allocator>
	list<T, Allocator>::const_reference			list<T, Allocator>::back() const
	{
		return (TAIL);
	}

	/* Begin */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::begin()
	{
		return (iterator(front());)
	}

	/* Begin */
	template <class T, class Allocator>
	list<T, Allocator>::const_iterator				list<T, Allocator>::begin() const
	{
		return (const_iterator(front()));
	}

	/* End */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::end()
	{
		return (iterator(back()));
	}

	/* End */
	template <class T, class Allocator>
	list<T, Allocator>::const_iterator			list<T, Allocator>::end() const
	{
		return (const_iterator(back()));
	}

	/* Rbegin */
	template <class T, class Allocator>
	list<T, Allocator>::reverse_iterator		list<T, Allocator>::rbegin()
	{
		return (reverse_iterator(back()));
	}

	/* Rbegin */
	template <class T, class Allocator>
	list<T, Allocator>::const_reverse_iterator	list<T, Allocator>::rbegin() const
	{
		return (const_reverse_iterator(back()));
	}

	/* Rend */
	template <class T, class Allocator>
	list<T, Allocator>::reverse_iterator		list<T, Allocator>::rend()
	{
		return (reverse_iterator(front()));
	}

	/* Rend */
	template <class T, class Allocator>
	list<T, Allocator>::const_reverse_iterator	list<T, Allocator>::rend() const
	{
		return (const_reverse_iterator(front()));
	}

	/* Empty */
	template <class T, class Allocator>
	bool										list<T, Allocator>::empty() const
	{
		return (lenght == 0);
	}

	/* Size */
	template <class T, class Allocator>
	list<T, Allocator>::size_type				list<T, Allocator>::size() const
	{
		return (lenght);
	}

	/* Max size */
	template <class T, class Allocator>
	list<T, Allocator>::size_type				list<T, Allocator>::max_size() const
	{
		return (std::numeric_limits<difference_type>::max() / sizeof(Node));
	}

	/* Clear */
	template <class T, class Allocator>
	void										list<T, Allocator>::clear()
	{
		for (Node* i = HEAD ; i != NIL ; i = i->next)
		{
			unlink(i);
			i->~Node();
		}
	}

	/* Insert */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::insert(iterator pos, const_reference value)
	{
		
	}

	/* Insert */
	template <class T, class Allocator>
	void										list<T, Allocator>::insert(iterator pos, size_type count, const_reference value)
	{

	}

	/* Insert */
	template <class T, class Allocator>
	template <class InputIt>
	void										list<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
	{
		
	}

	/* Erase */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::erase(iterator pos)
	{
		
	}

	/* Erase */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::erase(iterator firts, iterator last)
	{
		
	}

	/* Push back */
	template <class T, class Allocator>
	void										list<T, Allocator>::push_back(const_reference value)
	{
		Node* node = new_node(value);
		link(node, TAIL, NIL);
		TAIL = node;
	}

	/* Pop back */
	template <class T, class Allocator>
	void										list<T, Allocator>::pop_back()
	{
		Node* target = TAIL;
		TAIL = TAIL->prev;
		unlink(target);
		link(TAIL, TAIL->prev, NIL);
		target->~Node();
		lenght--;
	}

	/* Push front */
	template <class T, class Allocator>
	void										list<T, Allocator>::push_front(const_reference value)
	{
		Node* node = new_node(value);
		link(node, NIL, HEAD);
		HEAD = node;
	}

	/* Pop front */
	template <class T, class Allocator>
	void										list<T, Allocator>::pop_front()
	{
		Node* target = HEAD;
		HEAD = HEAD->next;
		unlink(target);
		link(HEAD, NIL, HEAD->next);
		target->~Node();
		lenght--;
	}

	/* Resize */
	template <class T, class Allocator>
	void										list<T, Allocator>::resize(size_type count)
	{
		// TO DO: Check if this are default-inserted elements 
		resize(count);
	}

	/* Resize */
	template <class T, class Allocator>
	void										list<T, Allocator>::resize(size_type count, value_type value = value_type())
	{
		while (count--)
			push_back(value);
	}

	/* Swap */
	template <class T, class Allocator>
	void										list<T, Allocator>::swap(list& other)
	{
		std::swap(memory, other.memory);
		std::swap(lst, other.lst);
		std::swap(NIL, other.NIL);
		std::swap(lenght, other.lenght);
	}

	/* Merge */
	template <class T, class Allocator>
	void										list<T, Allocator>::merge(list& other)
	{
		// to do
	}

	/* Merge */
	template <class T, class Allocator>
	template <class Compare>
	void										list<T, Allocator>::merge(list& other, Compare comp)
	{

	}

	/* Splice */
	template <class T, class Allocator>
	void										list<T, Allocator>::splice(const_iterator pos, list& other)
	{
		Node* start_insertion = HEAD;

		// Get start insertion point // TO DO: Check for overflow ? 
		while (pos-- < 0) // Check when stop!!!!
			start_insertion = start_insertion->next;

		// Get end insertion point
		Node* end_insertion = start_insertion->next;

		// Link the start
		start_insertion->next = other.HEAD;
		other.HEAD->next = start_insertion;

		// Link the end
		end_insertion->prev = other.TAIL;
		other.TAIL->next = end_insertion;

		// Resize
		lenght += other.lenght;
		other.lenght = 0;
		
		// Empty
		other.TAIL = other.NIL;
		other.HEAD = other.NIL;
	}

	/* Splice */
	template <class T, class Allocator>
	void										list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator it)
	{
		// To do
	}
	
	/* Splice */
	template <class T, class Allocator>
	void										list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
	{
		// To do
	}
	
	/* Remove */
	template <class T, class Allocator>
	void										list<T, Allocator>::remove(const_reference value)
	{
		for (Node* first = HEAD, first != NIL ; first = first->next)
		{
			if (first.data == value)
			{
				unlink(first);
				first->~Node();
			}
		}
	}

	/* Remove if */
	template <class T, class Allocator>
	template <class UnaryPredicate>
	void										list<T, Allocator>::remove_if(UnaryPredicate p)
	{
		for (Node* first = HEAD, first != NIL ; first = first->next)
		{
			if (p(first.data))
			{
				unlink(first);
				first->~Node();
			}
		}
	}

	/* Reverse */
	template <class T, class Allocator>
	void										list<T, Allocator>::reverse()
	{
		// WHAT SHOULD I DO IF IS EMPTY

		// lenght isn't pair add a node to make it pear
		if (lenght % 2 == 0)
		{
			Node* tmp;
			link(tmp, TAIL, NIL);
		}

		// Proceed to reverse
		Node* rev = back();
		for (Node* i = front() ; i != rev ;)
		{
			// Tmp for operate
			Node* remember = rev;
			Node* rem_i = i;

			i = i->next;

			// Swap nodes
			unlink(rev);
			link(rev, i->prev->next, i->next->prev);
			unlink(rem_i);
			link(rem_i, remember->prev->next, remember->next->prev);
	
			rev = rev->prev;
		}
		
		// Remove to added node
		if (lenght % 2 == 0)
			pop_front();

		// Swap Head and TAIL
		unlink(HEAD);
		unlink(TAIL);
		link(HEAD, NIL, NIL->next);
		link(TAIL, NIL->prev, NIL);
		
	}

	/* Unique */
	template <class T, class Allocator>
	void										list<T, Allocator>::unique()
	{
		// rm all identical elems
	}

	/* Unique */
	template <class T, class Allocator>
	template <class BinaryPredicate>
	void										list<T, Allocator>::unique(BinaryPredicate p)
	{

	}

	/* Sort */
	template <class T, class Allocator>
	void										list<T, Allocator>::sort()
	{
		
	}

	/* Sort */
	template <class T, class Allocator>
	template <class Compare>
	void										list<T, Allocator>::sort(Compare comp)
	{
		
	}

	/* Non-member booleans */

	// To define (need research about how declare them)


	/* Non-member swap */
	template <class T, class Alloc>
	void						swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
};