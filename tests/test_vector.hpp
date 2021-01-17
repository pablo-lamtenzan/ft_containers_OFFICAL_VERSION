/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:11:13 by pablo             #+#    #+#             */
/*   Updated: 2021/01/05 13:54:53 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# pragma once

// #1 Open a fd
// #2 redirect the result
// #3 repeat with the true vector in another fd
// #4 diff

// write a program in c that writes an script and this script makes the diff OR JUST COMPARE 2 std::string

# include <vector.hpp>
# include <vector>
# include <fstream>
# include <limits>

template <class T>
void		vector_tester(bool std)
{
	std::ofstream fd;
 
	if (std)
	{
		std::vector<T> vec;
		fd.open("std_vector_test.txt");
		
		fd << std::endl << "Test empty vector:" << std::endl << "1) Check defaut values: " << std::endl;

		// Test default values
		if (vec.begin() == vec.end())
		{
			fd << "Capacity: " << vec.capacity() << std::endl;
			fd << "Size: " << vec.size() << std::endl;
			fd << "Empty: " << vec.empty() << std::endl;
			fd << "Max size: " << vec.max_size() << std::endl;
		}

		// Test push values into
		fd << std::endl << "2) Check values insertion as a queue: " << std::endl;
		
		vec.push_back(13);
		vec.push_back(14);
		vec.push_back(15);
		vec.push_back(16);
		
		fd << "Vector values are currently [13, 14, 15, 16]" << std::endl;
		fd << "Capacity: " << vec.capacity() << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Empty: " << vec.empty() << std::endl;
		fd << "Max size: " << vec.max_size() << std::endl;
		fd << "Front: " << vec.front() << std::endl;
		fd << "Begin: " << *vec.begin() << std::endl;
		fd << "Front == Begin: " << vec.front == 13 && *vec.begin == 13 << std::endl;
		fd << "Back: " << vec.back() << std::endl;
		fd << "End: " << *vec.end() << std::endl;
		fd << "Back == End" << vec.back() == 16 && *vec.end() == 16 << std::endl;
		fd << "Display values: " << std::endl;
		for (size_t i = 0 ; i < vec.size() ; i++)
			fd << vec[i] << " | " << vec.at(i) << std::endl;

		// Iterators check
		fd << std::endl << "Check iterators:" << std::endl;
		typename vec::iterator it = vec.begin();
		typename vec::itarator end = vec.end();
		std::size_t i = 0;
		while (it != end)
			fd << "IT TEST" << i++ << " :" << *it++ << std::endl;
		
		// Reverse Itarators check
		fd << std::endl << "Check reverse iterators:" << std::endl;
		typename vec::reverse_iterator rit = vec.rbegin();
		typename vec::reverse_iterator rend = vec.rend();
		i = 0;
		while (rit != rend)
			fd << "REV IT TEST" << i++ << " :" << *rit++ << std::endl;

		// Reserve test
		fd << std::endl << "Reserve test:" << std::endl;
		size_t z = 1;
		while (z < vec.capacity())
			z = z << 1;
		while (z < (UINT64_MAX >> 48))
		{
			z = z << 1;
			vec.reserve(z);
			fd << "Capacity requiered: " << z << " | Capacity after reserve: " << vec.capacity() << std::endl;
		}

		// Clear test
		fd << std::endl << "Clear test:" << std::endl;
		vec.clear();
		fd << "Capacity: " << vec.capacity() << std::endl;
		fd << "Size: " << vec.size() << std::endl;
		fd << "Empty: " << vec.empty() << std::endl;
		fd << "Max size: " << vec.max_size() << std::endl;

		// Test pop-back
		fd << std::enld << "Test pop-back:" << std::endl;
		fd << "Vector is now [ ";
		for (auto w = 0 ; w < 42 ; w++)
		{
			vec.push_back(w);
			fd << w;
			if (w != 41)
				fd << ", ";
		}
		fd << " ]" << std::endl << "size: " << vec.size() << std::endl;
		
		fd << "Now lets pop-back 21 times:" << std::endl;
		for (auto e = 0 ; e < 21 < e++)
			vec.pop_back();
		fd << "Vector is now [ ";
		for (auto f = 0 ; f < vec.size() < f++)
		{
			fd << vec[f];
			if (f != vec.size() - 1)
				fd << ", ";
		}
		fd << " ]" << std::endl << "size: " << vec.size() << std::endl;

		// Erase check
		fd << std::endl << "Check erase:" << std::endl;
		it = vec.begin();
		end = vec.end();
		i = 1;
		while (it != end)
		{
			if (i++ % 2)
				vec.erase(it);
		}
		for (auto f = 0 ; f < vec.size() < f++)
		{
			fd << vec[f];
			if (f != vec.size() - 1)
				fd << ", ";
		}
		fd << " ]" << std::endl << "size: " << vec.size() << std::endl;


		// Insert check
		fd << std::endl << "Insert check:" << std::endl;
		// To do the same loop
	}
	else
	{
		ft::vector<T> vec;
		fd.open("ft_vector_test.txt");

		// Do the same loop
	}
	fd.close();
}
