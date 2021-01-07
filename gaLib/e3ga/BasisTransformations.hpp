// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Inner.hpp
// This file is part of the Garamon for e3ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

// \file BasisTransformations.hpp
// \author V. Nozick, S. Breuils
// \brief this files generates and load the elements of the transformation matrices into array of Eigen matrices 


#ifndef E3GA_BASISTRANSFORMATIONS_HPP__
#define E3GA_BASISTRANSFORMATIONS_HPP__
#pragma once


#include <Eigen/Sparse>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>


/*!
 * @namespace e3ga
 */
namespace e3ga{

	/// Decode the string encodedPerGradeMatrixComponents to a vector of T. This vector will contain the components of the transformation matrices
	template<typename T>
	const std::vector<T> decodeStringToVecOfT(std::string encodedPerGradeMatrixComponents) {
	    std::vector<T> resultDecodedGrade;
	    std::istringstream streamStringOverFloat(encodedPerGradeMatrixComponents);
	    std::copy(std::istream_iterator<float>(streamStringOverFloat),
		std::istream_iterator<float>(),
		std::back_inserter(resultDecodedGrade));
	    return resultDecodedGrade;
	}





	/// initialize all the direct transformation matrices using array of eigen sparse matrices


	/// initialize all the inverse transformation matrices using array of eigen sparse matrices


}/// End of Namespace

#endif // E3GA_BASISTRANSFORMATIONS_HPP__
