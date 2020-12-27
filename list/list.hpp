/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:24:05 by pablo             #+#    #+#             */
/*   Updated: 2020/12/27 21:39:21 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <allocator.hpp>
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

		// TO DO LegacyBidirectionalIterator
		typedef T									iterator; // tmp
		typedef T									const_iterator; // tmp
		typedef	reverse_iterator<iterator>			reverse_iterator;
		typedef reverse_iterator<const_iterator>	const_reverse_iterator;

		protected:

		/* Core */
		
		typedef struct		s_node
		{
			value_type		data;
			struct s_node*	next;
			struct s_node*	prev;
		}					Node;

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
		Node*				new_node(value_type d)
		{
			Node*	node;
			try {
				node = memory.allocate(sizeof(*node));
			} catch (std::bad_alloc& e) { if (lst != NIL) this->~list(); throw ; }
			*node = (Node){.next=NIL, .prev=NIL};
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
				NIL = memory.allocate(sizeof(*NIL));
			} catch (const std::bad_alloc& e) { throw ; }
			HEAD = NIL;
			TAIL = NIL;
			lst = NIL;
		}

		explicit list(const Allocator& alloc) : memory(alloc), lenght(0ul)
		{
			try {
				NIL = memory.allocate(sizeof(*NIL));
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
			{
				memory.destroy(i);
				memory.deallocate(i);
			}
			memory.deallocate(NIL);
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
		
	}

	/* Front */
	template <class T, class Allocator>
	list<T, Allocator>::const_reference		list<T, Allocator>::front() const
	{
		
	}

	/* Back */
	template <class T, class Allocator>
	list<T, Allocator>::reference			list<T, Allocator>::back()
	{
		
	}
	
	/* Back */
	template <class T, class Allocator>
	list<T, Allocator>::const_reference			list<T, Allocator>::back() const
	{
		
	}

	/* Begin */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::begin()
	{
		
	}

	/* Begin */
	template <class T, class Allocator>
	list<T, Allocator>::const_iterator				list<T, Allocator>::begin() const
	{
		
	}

	/* End */
	template <class T, class Allocator>
	list<T, Allocator>::iterator				list<T, Allocator>::end()
	{
		
	}

	/* End */
	template <class T, class Allocator>
	list<T, Allocator>::const_iterator			list<T, Allocator>::end()
	{
		
	}

	/* Rbegin */
	template <class T, class Allocator>
	list<T, Allocator>::reverse_iterator		list<T, Allocator>::rbegin()
	{
		
	}

	/* Rbegin */
	template <class T, class Allocator>
	list<T, Allocator>::const_reverse_iterator	list<T, Allocator>::rbegin() const
	{
		
	}

	/* Rend */
	template <class T, class Allocator>
	list<T, Allocator>::reverse_iterator		list<T, Allocator>::rend()
	{
		
	}

	/* Rend */
	template <class T, class Allocator>
	list<T, Allocator>::const_reverse_iterator	list<T, Allocator>::rend() const
	{
		
	}

	/* Empty */
	template <class T, class Allocator>
	bool										list<T, Allocator>::empty() const
	{
		
	}

	/* Size */
	template <class T, class Allocator>
	list<T, Allocator>::size_type				list<T, Allocator>::size() const
	{
		
	}

	/* Max size */
	template <class T, class Allocator>
	list<T, Allocator>::size_type				list<T, Allocator>::max_size() const
	{
		
	}

	/* Clear */
	template <class T, class Allocator>
	void										list<T, Allocator>::clear()
	{

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

	}

	/* Pop back */
	template <class T, class Allocator>
	void										list<T, Allocator>::pop_back()
	{

	}

	/* Push front */
	template <class T, class Allocator>
	void										list<T, Allocator>::push_front(const_reference value)
	{

	}

	/* Pop front */
	template <class T, class Allocator>
	void										list<T, Allocator>::pop_front()
	{

	}

	/* Resize */
	template <class T, class Allocator>
	void										list<T, Allocator>::resize(size_type count)
	{

	}

	/* Resize */
	template <class T, class Allocator>
	void										list<T, Allocator>::resize(size_type count, value_type value = value_type())
	{

	}

	/* Swap */
	template <class T, class Allocator>
	void										list<T, Allocator>::swap(list& other)
	{

	}

	/* Merge */
	template <class T, class Allocator>
	void										list<T, Allocator>::merge(list& other)
	{

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

	}

	/* Splice */
	template <class T, class Allocator>
	void										list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator it)
	{

	}
	
	/* Splice */
	template <class T, class Allocator>
	void										list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
	{

	}
	
	/* Remove */
	template <class T, class Allocator>
	void										list<T, Allocator>::remove(const_reference value)
	{

	}

	/* Remove if */
	template <class T, class Allocator>
	template <class UnaryPredicate>
	void										list<T, Allocator>::remove_if(UnaryPredicate p)
	{

	}

	/* Reverse */
	template <class T, class Allocator>
	void										list<T, Allocator>::reverse()
	{

	}

	/* Unique */
	template <class T, class Allocator>
	void										list<T, Allocator>::unique()
	{

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