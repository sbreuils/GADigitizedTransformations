// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// GeometricExplicit.hpp
// This file is part of the Garamon for e3ga.
// Authors: Stephane Breuils and Vincent Nozick
// Conctat: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file GeometricExplicit.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Explicit precomputed per grades geometric products of e3ga.


#ifndef E3GA_GEOMETRIC_PRODUCT_EXPLICIT_HPP__
#define E3GA_GEOMETRIC_PRODUCT_EXPLICIT_HPP__
#pragma once

#include <Eigen/Core>

#include "e3ga/Mvec.hpp"
#include "e3ga/Constants.hpp"


/*!
 * @namespace e3ga
 */
namespace e3ga {
    template<typename T> class Mvec;

    /// \brief Compute the geometric product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something else.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1 mv2 whose grade is 2
	template<typename T>
	void geometric_2_2_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(1)*mv2.coeff(2) + mv1.coeff(2)*mv2.coeff(1);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(0)*mv2.coeff(1) + mv1.coeff(1)*mv2.coeff(0);
	}


	
    template<typename T>
	std::array<std::array<std::array<std::function<void(const Eigen::Matrix<T, Eigen::Dynamic, 1> & , const Eigen::Matrix<T, Eigen::Dynamic, 1> & , Eigen::Matrix<T, Eigen::Dynamic, 1>&)>, 4>, 4>, 4> geometricFunctionsContainer =
	{{
		{{
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}}
		}},
		{{
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}}
		}},
		{{
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},geometric_2_2_2<T>,{}}},
			{{{},{},{},{}}}
		}},
		{{
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}},
			{{{},{},{},{}}}
		}}
	}};

}/// End of Namespace

#endif // E3GA_GEOMETRIC_PRODUCT_EXPLICIT_HPP__