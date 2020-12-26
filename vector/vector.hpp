/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:37:12 by pablo             #+#    #+#             */
/*   Updated: 2020/12/26 21:32:29 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
** Implemtation using a array with a block size who is *= 2
** each time a new performed insertion is out of bounds.
**
** Documentation: https://en.cppreference.com/w/cpp/container/vector
*/

# include <allocator.hpp>
# include "LegacyRandomAccessIterator.hpp"

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

		private:
	
		/* Core */

		Allocator				memory;
		size_type				max_size;
		pointer					array;
		size_type				curr_size;

		/*
		** Like a kind of realloc, creates a new array and perform a deep copy
		** of all the current elements stored in the current array (size of max_size).
		**
		** Note: Need to be called each time the max size is updated
		*/
		void					array_reserve()
		{
			try {
				pointer	new_array = memory.allocate(max_size);
			} catch (const std::bad_alloc& e) { if (array) this->~vector(); throw ; }
			for (size_type i = 0 ; i < curr_size ; i++)
			{
				// check if i m allowed to play God with std::move
				new_array = std::move(operator[](i));
				memory.destroy(operator[](i));
			}
			memory.deallocate(array);
			array = new_array;
		}

		/*
		** Duplicates the max_size and call array_reserve to perform the reallocation.
		*/
		void				array_resize()
		{
			if (curr_size > max_size)
			{
				max_size *= 2;
				array_reserve();
			}
		}

		public:

		/* Member functions */

			/* Constructor */
		explicit vector(const Allocator& alloc = nullptr) : memory(alloc), max_size(0ul), array(nullptr), curr_size(0ul) { }

		explicit vector(size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator())
		: memory(alloc), max_size(count), curr_size(cout)
		{
			try {
				array = memory.allocate(max_size);
			} catch (const std::bad_alloc& e) { throw ; }
			for (size_type i = 0 ; i < max_size)
				memory.construct(array + i, value);
		}

		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: memory(alloc), max_size(0ul), array(nullptr), curr_size(0ul) { assign(first, last); }

			/* Destructor */
		~vector()
		{
			for (size_type i = 0 ; i < curr_size ; i++)
				memory.destroy(&operator[](i));
			memory.deallocate(array, max_size);
		}

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

			/* rbegin */
		// to do

			/* rend */
		// to do

		/* Member functions: Capacity */

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

			/* erase */
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

	/* Operator= */
	template <class T, class Allocator>
	vector<T, Allocator>&	vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
	{
		
	}

	/* Assign */
	template <class T, class Allocator>
	void					vector<T, Allocator>::assign(size_type count, const reference value)
	{
		
	}

	/* Assign */
	template <class T, class Allocator>
	template <class InputIt>
	void					vector<T, Allocator>::assign(InputIt first, InputIt last)
	{
		
	}

	/* At */
	template <class T, class Allocator>
	vector<T, Allocator>::reference				vector<T, Allocator>::at(size_type pos)
	{
		if (!(pos < size))
			throw std::out_of_range(std::string("Error: Out of bounds."));
		return (operator[](pos));
	}

	/* At */
	template <class T, class Allocator>
	vector<T, Allocator>::const_reference		vector<T, Allocator>::at(size_type pos) const
	{
		if (!(pos < size))
			throw std::out_of_range(std::string("Error: Out of bounds"));
		return (operator[](pos));
	}

	/* Operator[] */
	template <class T, class Allocator>
	vector<T, Allocator>::reference				vector<T, Allocator>::operator[](size_type pos)
	{
		return (array + pos);
	}

	/* Operator[] */
	template <class T, class Allocator>
	vector<T, Allocator>::const_reference		vector<T, Allocator>::operator[](size_type pos) const
	{
		return (array + pos);
	}
	
	/* Front */
	template <class T, class Allocator>
	vector<T, Allocator>::reference				vector<T, Allocator>::back()
	{
		
		return (operator[](0));
	}

	/* Front */
	template <class T, class Allocator>
	vector<T, Allocator>::const_reference		vector<T, Allocator>::back() const
	{
		return (operator[](0));
	}
	
	/* Back */
	template <class T, class Allocator>
	vector<T, Allocator>::reference				vector<T, Allocator>::back()
	{
		
		return (operator[](curr_size - 1));
	}

	/* Back */
	template <class T, class Allocator>
	vector<T, Allocator>::const_reference		vector<T, Allocator>::back() const
	{
		return (operator[](curr_size - 1));
	}

	// TO DO begin

	// TO DO end

	/* Empty*/
	template <class T, class Allocator>
	bool										vector<T, Allocator>::empty() const
	{
		return (curr_size == 0);
	}

	/* Size */
	template <class T, class Allocator>
	vector<T, Allocator>::size_type				vector<T, Allocator>::size() const
	{
		return (curr_size);
	}

	/* Max size */
	template <class T, class Allocator>
	vector<T, Allocator>::size_type				vector<T, Allocator>::max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(value_type));
	}

	/* Reserve */
	template <class T, class Allocator>
	void										vector<T, Allocator>::reserve(size_type new_cap)
	{
		if (new_cap > max_size())
			throw std::length_error(std::string("Error: Not enought physical memory in the device to perform this reserve allocation"))
		max_size = new_cap;
		array_reserve();
	}

	/* Capacity */
	template <class T, class Allocator>
	vector<T, Allocator>::size_type				vector<T, Allocator>::capacity() const
	{
		return (max_size);
	}

	/* Clear */
	template <class T, class Allocator>
	void										vector<T, Allocator>::clear()
	{
		while (curr_size-- < 0)
			memory.destruct(&operator[](curr_size));
	}

	/* Push back */
	template <class T, class Allocator>
	void										vector<T, Allocator>::push_back(const_reference value)
	{
		curr_size++;
		array_resize();
		operator[](curr_size) = value_type;
	}

	/* Pop back */
	template <class T, class Allocator>
	void										vector<T, Allocator>::pop_back()
	{
		if (!empty())
		{
			curr_size--;
			operator[](curr_size) = value_type;
		}
	}

	/* Resize */
	template <class T, class Allocator>
	void										vector<T, Allocator>::resize(size_type count, value_type value = value_type())
	{
		std::swap(curr_size, count);
		array_resize();
		for (size_type i = count ; i < max_size ; i++)
			operator[](i) = value;
	}

	/* Booleans */

	template <class T, class Alloc>
	bool				operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (auto i = 0ul ; i < lhs.size() < i++)
				if (lhs.operator[](i) != rhs.operator[](i))
					return (false);
			return (true);
		}
		return (false);
	}
	
	template <class T, class Alloc>
	bool				operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		// think about it
	}

	template <class T, class Alloc>
	bool				operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (operator==(lhs, rhs) || operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator<=(lhs, rhs));
	}

	template <class T, class Alloc>
	bool				operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}
};

