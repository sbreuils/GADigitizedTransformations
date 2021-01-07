// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Geometric.hpp
// This file is part of the Garamon for e3ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file Geometric.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Recursive geometric product for e3ga.


#ifndef E3GA_GEOMETRIC_PRODUCT_HPP__
#define E3GA_GEOMETRIC_PRODUCT_HPP__
#pragma once

#include "e3ga/Mvec.hpp"
#include "e3ga/Constants.hpp"


/*!
 * @namespace e3ga
 */
namespace e3ga {
	
	template<typename T> class Mvec;


/// \brief Recursively compute the geometric product between two multivectors mv1 and mv2, the result is put into the multivector mv3
/// \tparam the type of value that we manipulate, either float or double or something.
/// \param mv1 - the first multivector
/// \param mv2 - the second multivector
/// \param mv3 - the multivector that will content the result of the operation mv3 = mv1 * mv2
/// \param grade_mv1 - the grade of the first multivector
/// \param grade_mv2 - the grade of the second multivector
/// \param grade_mv3 - could be the grade of the result, however here it is useless due to the fact that the resulting multivector may not be homogeneous
/// \param currentGradeMv1 - the current grade of the traversed tree of mv1
/// \param currentGradeMv2 - the current grade of the traversed tree of mv2
/// \param currentGradeMv3 - the current grade of the traversed tree of mv3
/// \param sign - compute the sign of the geometric product between two blades
/// \param complement - activate the flip of sign
/// \param indexLastVector_mv1 - last vector traversed in the multivector mv1
/// \param indexLastVector_mv2 - last vector traversed in the multivector mv2
/// \param depth - depth in the resulting multivector tree

	template<typename T>
	void geoProduct(const Eigen::Matrix<T, Eigen::Dynamic, 1> &mv1,
					const Eigen::Matrix<T, Eigen::Dynamic, 1> &mv2,
					Mvec<T> &mv3,          // multivectors to be processed
					const unsigned int grade_mv1,
					const int grade_mv2,
					const int grade_mv3,   // grade of the k-vectors
					unsigned int currentXorIdx1=0, unsigned int currentXorIdx2=0, unsigned int currentXorIdx3=0,             // position in the prefix tree
					unsigned int currentGradeMv1=0, unsigned int currentGradeMv2=0, unsigned int currentGradeMv3=0, // grade relative to the position in the prefix tree
					int sign=1, int complement=1,
					unsigned int indexLastVector_mv1=0, unsigned int indexLastVector_mv2=0, unsigned int indexLastVector_mv3=0,
					int depth=0) {

		// sign updating
		int tmpSign = sign;
		if(complement == -1) {
			tmpSign = -tmpSign;
		}

		// when we reach the grade of mv1 and mv2
		if( (currentGradeMv1==grade_mv1) && (currentGradeMv2==grade_mv2) ){
			// do the required computation
			mv3.at(currentGradeMv3, xorIndexToHomogeneousIndex[currentXorIdx3]) += sign * mv1(xorIndexToHomogeneousIndex[currentXorIdx1]) * mv2(xorIndexToHomogeneousIndex[currentXorIdx2]);
		}else {
			// if position in the tree for mv3 is not yet of grade of mv3, just call the recursive calls, without computation
			// for each possible children of the current node whose index is given by depth
			for (unsigned int i = (unsigned int) (1 << depth);
				 i < (1 << algebraDimension); i *= 2) {


				unsigned int xorIndexMv1Child = currentXorIdx1 + i; // xor index of the child of the first tree multivector
				unsigned int xorIndexMv2Child = currentXorIdx2 + i; // xor index of the child of the second tree multivector
				unsigned int xorIndexMv3Child = currentXorIdx3 + i; // xor index of the child of the third tree multivector

				// if we reach neither the grade of mv1 nor the grade of mv2 AND if the child of the node of mv1 lead to at least one node whose grade is grade_mv1
				// AND if the child of the node of mv2 lead to at least one node whose grade is grade_mv2
				if ((currentGradeMv1 < grade_mv1) &&
					((i << (grade_mv1 - (currentGradeMv1 + 1))) < (1 << algebraDimension)) &&
					(currentGradeMv2 < grade_mv2) &&
					((i << (grade_mv2 - (currentGradeMv2 + 1))) < (1 << algebraDimension))) {
					geoProduct<T>(mv1, mv2, mv3,
								  grade_mv1, grade_mv2, grade_mv3,
								  xorIndexMv1Child, xorIndexMv2Child, currentXorIdx3,
								  currentGradeMv1 + 1, currentGradeMv2 + 1, currentGradeMv3,
								  tmpSign, -complement,
								  i, i << 1, indexLastVector_mv3,
								  depth + 1); // scalar product part of the geometric product
				}
				// if we do not reach the grade of mv1 AND if the child of the node of mv1 lead to at least one node whose grade is grade_mv1
				if ((currentGradeMv1 < grade_mv1) &&
					((i << (grade_mv1 - (currentGradeMv1 + 1))) < (1 << algebraDimension))) {
					geoProduct<T>(mv1, mv2, mv3,
								  grade_mv1, grade_mv2, grade_mv3,
								  xorIndexMv1Child, currentXorIdx2, xorIndexMv3Child,
								  currentGradeMv1 + 1, currentGradeMv2, currentGradeMv3 + 1,
								  tmpSign, complement,
								  i, i << 1, indexLastVector_mv3,
								  depth + 1); // outer part of the geometric product to CHECK
				}

				// if we do not reach the grade of mv2 AND if the child of the node of mv2 lead to at least one node whose grade is grade_mv2
				if ((currentGradeMv2 < grade_mv2) &&
					((i << (grade_mv2 - (currentGradeMv2 + 1))) < (1 << algebraDimension))) {
					geoProduct<T>(mv1, mv2, mv3,
								  grade_mv1, grade_mv2, grade_mv3,
								  currentXorIdx1, xorIndexMv2Child, xorIndexMv3Child,
								  currentGradeMv1, currentGradeMv2 + 1, currentGradeMv3 + 1,
								  sign, -complement,
								  indexLastVector_mv1, i << 1, i,
								  depth + 1); // outer part of the geometric product
				}
				depth++;
			}
		}
	}


///// \brief Compute the geometric product between two multivectors mv1 and mv2, the result is put into the multivector mv3
///// \tparam the type of value that we manipulate, either float or double or something.
///// \param mv3 - the multivector that will content the result of the operation mv3 = mv1 * mv2
///// \param mv1 - the first multivector
///// \param mv2 - the second multivector
///// \param currentIdx1
///// \param currentIdx2
///// \param currentIdx3
///// \param currentGradeMv1
///// \param currentGradeMv2
///// \param currentGradeMv3
///// \param sign - compute the sign of the outer product between two blades
///// \param complement - activate the flip of sign
///// \param indexLastNodeTraversed
///// \param indexLastNodeTraversedA
///// \param indexLastNodeTraversedB
///// \param indexLastNodeTraversedC
//	template<typename T>
//	void geoProduct(Mvec<T> &mv3, const Mvec<T> &mv1, const Mvec<T> &mv2,
//                    int currentIdx1, int currentIdx2, int currentIdx3,
//                    int currentGradeMv1, int currentGradeMv2, int currentGradeMv3,
//                    int sign, int complement,
//					int indexLastNodeTraversed, int indexLastNodeTraversedA, int indexLastNodeTraversedB, int indexLastNodeTraversedC) {
//
//		int grade1 = mv1.grade();
//		int grade2 = mv2.grade();
//
//		int indexFirstChildMv1 = tabIndicesChildren[perGradeStartingIndex[currentGradeMv1] + currentIdx1];
//		int indexFirstChildMv2 = tabIndicesChildren[perGradeStartingIndex[currentGradeMv2] + currentIdx2];
//		int indexFirstChildMv3 = tabIndicesChildren[perGradeStartingIndex[currentGradeMv3] + currentIdx3];
//
//
//		int tmpSign = sign;
//		if (complement == -1) {
//			tmpSign = -tmpSign;
//		}
//
//		//
//
//
//		// the offset of multivectors is important here
//		// Explain the offsetMv1 here
//		//
//		int offsetMv1 = indexLastNodeTraversed - indexLastNodeTraversedA; // offset mv3 determines the offset for mv2 and mv1
//		int offsetMv2 = indexLastNodeTraversed - indexLastNodeTraversedB;
//		int offsetMv3 = indexLastNodeTraversed - indexLastNodeTraversedC;
//
//
//		if (((unsigned int)indexLastNodeTraversed<(algebraDimension))&&(currentGradeMv3<=(grade1+grade2))) {
//            // corresponds to the recursive product ai*bi
//            geoProduct<T>(mv3, mv1, mv2, currentIdx1, currentIdx2,
//						  currentIdx3, currentGradeMv1,
//						  currentGradeMv2, currentGradeMv3, sign, complement, indexLastNodeTraversed + 1, indexLastNodeTraversedA,
//						  indexLastNodeTraversedB,indexLastNodeTraversedC);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
//
//			if ((indexFirstChildMv2 != -1) && (indexFirstChildMv1 != -1)) {
//				geoProduct<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, indexFirstChildMv2 + offsetMv2,
//							  currentIdx3, currentGradeMv1 + 1,
//							  currentGradeMv2 + 1, currentGradeMv3, tmpSign, -complement, indexLastNodeTraversed + 1,
//							  indexLastNodeTraversed + 1,
//							  indexLastNodeTraversed + 1, indexLastNodeTraversedC);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
//			}
//			if ((currentGradeMv1 < grade1) && (indexFirstChildMv1 != -1)) {
//				geoProduct<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, currentIdx2,
//							  indexFirstChildMv3 + offsetMv3, currentGradeMv1 + 1,
//							  currentGradeMv2, currentGradeMv3 + 1, tmpSign, complement, indexLastNodeTraversed + 1,
//							  indexLastNodeTraversed + 1,
//							  indexLastNodeTraversedB,indexLastNodeTraversed + 1);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
//			}
//			if ((currentGradeMv2 < grade2) && (indexFirstChildMv2 != -1)) {
//				geoProduct<T>(mv3, mv1, mv2, currentIdx1, indexFirstChildMv2 + offsetMv2,
//							  indexFirstChildMv3 + offsetMv3, currentGradeMv1,
//							  currentGradeMv2 + 1, currentGradeMv3 + 1, sign, -complement, indexLastNodeTraversed + 1,
//							  indexLastNodeTraversedA,
//							  indexLastNodeTraversed + 1, indexLastNodeTraversed + 1);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
//			}
//		} else {
//
//			if(mv1.hasVectorXdComponent(currentGradeMv1) && mv2.hasVectorXdComponent(currentGradeMv2)){
//				if ((mv1.at(currentGradeMv1, currentIdx1) != 0) && (mv2.at(currentGradeMv2, currentIdx2) != 0) ) {
//					// test whether the VectorXd was created
//					mv3.createVectorXdIfDoesNotExist(currentGradeMv3);
//					mv3.at(currentGradeMv3, currentIdx3) += sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2);
//				}
//			}
//		}
//	}

}/// End of Namespace

#endif // E3GA_GEOMETRIC_PRODUCT_HPP__