// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Inner.hpp
// This file is part of the Garamon for e3ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file Inner.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Recursive inner product for e3ga.


#ifndef E3GA_INNER_PRODUCT_HPP__
#define E3GA_INNER_PRODUCT_HPP__
#pragma once

#include "e3ga/Mvec.hpp"
#include "e3ga/Constants.hpp"

/*!
 * @namespace e3ga
 */
namespace e3ga {

   template<typename T> class Mvec;


    /// \brief Recursively compute the left contraction product between two multivectors mv1 and mv2, the result is put into the multivector mv3
    /// \tparam the type of value that we manipulate, either float or double or something.
    /// \param mv1 - the first multivector
    /// \param mv2 - the second multivector
    /// \param mv3 - the multivector that will content the result of the operation mv3 = mv1 * mv2
    /// \param grade_mv1 - the grade of the first multivector
    /// \param grade_mv2 - the grade of the second multivector
    /// \param grade_mv3 - the grade of the result which corresponds to grade_mv2-grade_mv1
    /// \param currentGradeMv1 - the current grade of the traversed tree of mv1
    /// \param currentGradeMv2 - the current grade of the traversed tree of mv2
    /// \param currentGradeMv3 - the current grade of the traversed tree of mv3
    /// \param sign - compute the sign of the geometric product between two blades
    /// \param complement - activate the flip of sign
    /// \param indexLastVector_mv1 - last vector traversed in the multivector mv1
    /// \param indexLastVector_mv2 - last vector traversed in the multivector mv2
    /// \param indexLastVector_mv3 - last vector traversed in the multivector mv3
    /// \param currentMetricCoefficient - coefficient that is used for handling the metric in the recursive formula
    /// \param depth - depth in the resulting multivector tree
    template<typename T>
    void leftContractionProductHomogeneous( const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3, // homogeneous multivectors to be processed
                                            const unsigned int grade_mv1, const unsigned int grade_mv2, const unsigned int grade_mv3,   // grade of the k-vectors
                                            unsigned int currentXorIdx1=0, unsigned int currentXorIdx2=0, unsigned int currentXorIdx3=0,             // position in the prefix tree
                                            unsigned int currentGradeMv1=0, unsigned int currentGradeMv2=0, unsigned int currentGradeMv3=0, // grade relative to the position in the prefix tree
                                            int sign=1, int complement=1,
                                            unsigned int indexLastVector_mv1=0, unsigned int indexLastVector_mv2=1, unsigned int indexLastVector_mv3=0, double currentMetricCoefficient=1.0, int depth=0) {
        // sign updating
        int tmpSign = sign;
        if(complement == -1) {
            tmpSign = -tmpSign;
        }

        // if position in the tree for mv3 is not yet of grade of mv2, just call the recursive calls, without computation
        if(currentGradeMv2 < grade_mv2 ){
            // for each child of the node mv2 (call the recursive function) from the current node until the node has at least one child whose grade is grade_mv2
            for(unsigned int i = indexLastVector_mv2; (i<<(grade_mv2-(currentGradeMv2+1)))<(1<<algebraDimension);i*=2){

                unsigned int xorIndexMv1Child = currentXorIdx1 + i; // xor index of the child of the first tree multivector
                unsigned int xorIndexMv2Child = currentXorIdx2 + i; // xor index of the child of the second tree multivector
                unsigned int xorIndexMv3Child = currentXorIdx3 + i; // xor index of the child of the third tree multivector

                // if we do not reach the grade of mv1 AND if the child of the node of mv1 lead to at least one node whose grade is grade_mv1
                if ( (currentGradeMv1 < grade_mv1) &&  ((i << (grade_mv1 - (currentGradeMv1 + 1))) < (1 << algebraDimension)) ) {
                    leftContractionProductHomogeneous<T>(mv1, mv2, mv3,
                                               grade_mv1, grade_mv2, grade_mv3,
                                               xorIndexMv1Child, xorIndexMv2Child, currentXorIdx3,
                                               currentGradeMv1 + 1, currentGradeMv2 +1 , currentGradeMv3 ,
                                               tmpSign, -complement,
                                               i, i << 1, indexLastVector_mv2,
                                                         currentMetricCoefficient, depth+1);
                }
                // if we do not reach the grade of mv3 AND if the child of the node of mv3 lead to at least one node whose grade is grade_mv3
                if ((currentGradeMv3 < grade_mv3) && ((i << (grade_mv3 - (currentGradeMv3 + 1))) < (1 << algebraDimension)) ) {
                    leftContractionProductHomogeneous<T>(mv1, mv2, mv3,
                                               grade_mv1, grade_mv2, grade_mv3,
                                               currentXorIdx1, xorIndexMv2Child, xorIndexMv3Child,
                                               currentGradeMv1, currentGradeMv2 + 1, currentGradeMv3 + 1,
                                               sign, -complement,
                                               indexLastVector_mv1, i << 1, i,
                                               currentMetricCoefficient, depth+1);
                }
                depth++;
            }
        } else { // currentGradeMv2 = grade_mv2 : compute the result and do not call the recursive process
            mv3(xorIndexToHomogeneousIndex[currentXorIdx3]) += sign * currentMetricCoefficient * mv1(xorIndexToHomogeneousIndex[currentXorIdx1]) * mv2(xorIndexToHomogeneousIndex[currentXorIdx2]);
        }
    }



/// \brief Recursively compute the right contraction product between two multivectors mv1 and mv2, the result is put into the multivector mv3
/// \tparam the type of value that we manipulate, either float or double or something.
/// \param mv1 - the first multivector
/// \param mv2 - the second multivector
/// \param mv3 - the multivector that will content the result of the operation mv3 = mv1 * mv2
/// \param grade_mv1 - the grade of the first multivector
/// \param grade_mv2 - the grade of the second multivector
/// \param grade_mv3 - the grade of the result which corresponds to grade_mv1-grade_mv2
/// \param currentGradeMv1 - the current grade of the traversed tree of mv1
/// \param currentGradeMv2 - the current grade of the traversed tree of mv2
/// \param currentGradeMv3 - the current grade of the traversed tree of mv3
/// \param sign - compute the sign of the geometric product between two blades
/// \param complement - activate the flip of sign
/// \param indexLastVector_mv1 - last vector traversed in the multivector mv1
/// \param indexLastVector_mv2 - last vector traversed in the multivector mv2
/// \param indexLastVector_mv3 - last vector traversed in the multivector mv3
/// \param currentMetricCoefficient - coefficient that is used for handling the metric in the recursive formula
/// \param depth - depth in the resulting multivector tree
    template<typename T>
    void rightContractionProductHomogeneous(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3, // homogeneous multivectors to be processed
                                           const unsigned int grade_mv1,const unsigned int grade_mv2,const unsigned int grade_mv3,   // grade of the k-vectors
                                           unsigned int currentXorIdx1=0, unsigned int currentXorIdx2=0, unsigned int currentXorIdx3=0,             // position in the prefix tree
                                           unsigned int currentGradeMv1=0, unsigned int currentGradeMv2=0, unsigned int currentGradeMv3=0, // grade relative to the position in the prefix tree
                                           int sign=1, int complement=1,
                                           unsigned int indexLastVector_mv1=1, unsigned int indexLastVector_mv2=0, unsigned int indexLastVector_mv3=0, double currentMetricCoefficient=1.0, int depth=0) {

        // sign updating
        int tmpSign = sign;
        if(complement == -1) {
            tmpSign = -tmpSign;
        }

        // if position in the tree for mv3 is not yet of grade of mv3, just call the recursive calls, without computation
        if(currentGradeMv1 < grade_mv1 ){
            // for each child of the node mv1 (call the recursive function) from the current node until the node has at least one child whose grade is grade_mv1
            for(unsigned int i = indexLastVector_mv1; (i<<(grade_mv1-(currentGradeMv1+1)))<(1<<algebraDimension);i*=2){
                unsigned int xorIndexMv1Child = currentXorIdx1 + i; // xor index of the child of the first tree multivector
                unsigned int xorIndexMv2Child = currentXorIdx2 + i; // xor index of the child of the second tree multivector
                unsigned int xorIndexMv3Child = currentXorIdx3 + i; // xor index of the child of the third tree multivector

                // if we do not reach the grade of mv2 AND if the child of the node of mv2 lead to at least one node whose grade is grade_mv2
                if ( (currentGradeMv2 < grade_mv2) &&  ((i << (grade_mv2 - (currentGradeMv2 + 1))) < (1 << algebraDimension)) ) {
                    rightContractionProductHomogeneous<T>(mv1, mv2, mv3,
                                                         grade_mv1, grade_mv2, grade_mv3,
                                                         xorIndexMv1Child, xorIndexMv2Child, currentXorIdx3,
                                                         currentGradeMv1 + 1, currentGradeMv2 +1 , currentGradeMv3 ,
                                                         tmpSign, -complement,
                                                          i << 1,i, indexLastVector_mv3,
                                                         currentMetricCoefficient,depth+1);
                }
                // if we do not reach the grade of mv3 AND if the child of the node of mv3 lead to at least one node whose grade is grade_mv3
                if ((currentGradeMv3 < grade_mv3) && ((i << (grade_mv3 - (currentGradeMv3 + 1))) < (1 << algebraDimension)) ) {
                    rightContractionProductHomogeneous<T>(mv1, mv2, mv3,
                                                         grade_mv1, grade_mv2, grade_mv3,
                                                          xorIndexMv1Child, currentXorIdx2, xorIndexMv3Child,
                                                         currentGradeMv1+1, currentGradeMv2, currentGradeMv3 + 1,
                                                          tmpSign, complement,
                                                          i << 1, indexLastVector_mv2, i,
                                                          currentMetricCoefficient, depth+1);
                }
                depth++;
            }
        } else { // currentGradeMv1 = grade_mv1 : compute the result and do not call the recursive process
           mv3(xorIndexToHomogeneousIndex[currentXorIdx3]) += sign * currentMetricCoefficient * mv1(xorIndexToHomogeneousIndex[currentXorIdx1]) * mv2(xorIndexToHomogeneousIndex[currentXorIdx2]);
        }
    }






























    template<typename T>
    void leftContraction(Mvec<T> &mv3, const Mvec<T> &mv1, const Mvec<T> &mv2, int currentIdx1, int currentIdx2,
                         int currentIdx3, int currentGradeMv1,
                         int currentGradeMv2, int currentGradeMv3, int sign, int complement,
                         int indexLastNodeTraversed, int indexLastNodeTraversedA, int indexLastNodeTraversedB, int indexLastNodeTraversedC, double currentMetricCoefficient) {

        int grade1 = mv1.grade();
        int grade2 = mv2.grade();

        int indexFirstChildMv1 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv1] + currentIdx1];
        int indexFirstChildMv2 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv2] + currentIdx2];
        int indexFirstChildMv3 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv3] + currentIdx3];

        int tmpSign = sign;
        if (complement == -1) {
            tmpSign = -tmpSign;
        }

        // the offset of multivectors is important here
        // Explain the offsetMv1 here
        //
        int offsetMv1 = indexLastNodeTraversed - indexLastNodeTraversedA; // offset mv3 determines the offset for mv2 and mv1
        int offsetMv2 = indexLastNodeTraversed - indexLastNodeTraversedB;
        int offsetMv3 = indexLastNodeTraversed - indexLastNodeTraversedC;

        if (((unsigned int)indexLastNodeTraversed<(algebraDimension))&&(currentGradeMv3<=(grade1+grade2))) {
            // loop over children of the node C
            leftContraction<T>(mv3, mv1, mv2, currentIdx1, currentIdx2,
                               currentIdx3, currentGradeMv1,
                               currentGradeMv2, currentGradeMv3, sign, complement, indexLastNodeTraversed + 1, indexLastNodeTraversedA,
                               indexLastNodeTraversedB,indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB

            if ((indexFirstChildMv2 != -1) && (indexFirstChildMv1 != -1)) {
                leftContraction<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, indexFirstChildMv2 + offsetMv2,
                                   currentIdx3, currentGradeMv1 + 1,
                                   currentGradeMv2 + 1, currentGradeMv3, tmpSign, -complement, indexLastNodeTraversed + 1,
                                   indexLastNodeTraversed + 1,
                                   indexLastNodeTraversed + 1, indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }

            if ((currentGradeMv2 < grade2) && (indexFirstChildMv2 != -1)) {
                leftContraction<T>(mv3, mv1, mv2, currentIdx1, indexFirstChildMv2 + offsetMv2,
                                   indexFirstChildMv3 + offsetMv3, currentGradeMv1,
                                   currentGradeMv2 + 1, currentGradeMv3 + 1, sign, -complement, indexLastNodeTraversed + 1,
                                   indexLastNodeTraversedA,
                                   indexLastNodeTraversed + 1, indexLastNodeTraversed + 1, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }
        } else {

            if(mv1.hasVectorXdComponent(currentGradeMv1) && mv2.hasVectorXdComponent(currentGradeMv2)){
                if ((mv1.at(currentGradeMv1, currentIdx1) != 0) && (mv2.at(currentGradeMv2, currentIdx2) != 0) ) {
                    // test whether the VectorXd was created
                    mv3.createVectorXdIfDoesNotExist(currentGradeMv3);//,currentIdx3,currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2));
                    mv3.at(currentGradeMv3, currentIdx3) += currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2);
                }
            }
        }
    }


    /// a right contraction where we remove the scalar product
    template<typename T>
    void rightContractionModified(Mvec<T> &mv3, const Mvec<T> &mv1, const Mvec<T> &mv2, int currentIdx1, int currentIdx2,
                                  int currentIdx3, int currentGradeMv1,
                                  int currentGradeMv2, int currentGradeMv3, int sign, int complement,
                                  int indexLastNodeTraversed, int indexLastNodeTraversedA, int indexLastNodeTraversedB, int indexLastNodeTraversedC, double currentMetricCoefficient) {

        int grade1 = mv1.grade();
        int grade2 = mv2.grade();

        int indexFirstChildMv1 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv1] + currentIdx1];
        int indexFirstChildMv2 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv2] + currentIdx2];
        int indexFirstChildMv3 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv3] + currentIdx3];

        int coeffRightContraction = (-2*((currentGradeMv1*(currentGradeMv2+1))%2))+1;
        int tmpSign = sign;
        if (complement == -1) {
            tmpSign = -tmpSign;
        }

        // the offset of multivectors is important here
        // Explain the offsetMv1 here
        //
        int offsetMv1 = indexLastNodeTraversed - indexLastNodeTraversedA; // offset mv3 determines the offset for mv2 and mv1
        int offsetMv2 = indexLastNodeTraversed - indexLastNodeTraversedB;
        int offsetMv3 = indexLastNodeTraversed - indexLastNodeTraversedC;

        if (((unsigned int)indexLastNodeTraversed<(algebraDimension))&&(currentGradeMv3<=(grade1+grade2))) {
            // loop over children of the node C
            rightContractionModified<T>(mv3, mv1, mv2, currentIdx1, currentIdx2,
                                        currentIdx3, currentGradeMv1,
                                        currentGradeMv2, currentGradeMv3, sign, complement, indexLastNodeTraversed + 1, indexLastNodeTraversedA,
                                        indexLastNodeTraversedB,indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB

            if ((indexFirstChildMv2 != -1) && (indexFirstChildMv1 != -1)) {
                rightContractionModified<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, indexFirstChildMv2 + offsetMv2,
                                            currentIdx3, currentGradeMv1 + 1,
                                            currentGradeMv2 + 1, currentGradeMv3, tmpSign, -complement, indexLastNodeTraversed + 1,
                                            indexLastNodeTraversed + 1,
                                            indexLastNodeTraversed + 1, indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }

            if ((currentGradeMv2 < grade2) && (indexFirstChildMv2 != -1)) {
                rightContractionModified<T>(mv3, mv1, mv2, currentIdx1, indexFirstChildMv2 + offsetMv2,
                                            indexFirstChildMv3 + offsetMv3, currentGradeMv1,
                                            currentGradeMv2 + 1, currentGradeMv3 + 1, sign, -complement, indexLastNodeTraversed + 1,
                                            indexLastNodeTraversedA,
                                            indexLastNodeTraversed + 1, indexLastNodeTraversed + 1, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }
        } else {
            if(mv1.hasVectorXdComponent(currentGradeMv1) && mv2.hasVectorXdComponent(currentGradeMv2) && (currentGradeMv3!=0) ){
                if ((mv1.at(currentGradeMv1, currentIdx1) != 0) && (mv2.at(currentGradeMv2, currentIdx2) != 0) ) {
                    // test whether the VectorXd was created
                    mv3.createVectorXdIfDoesNotExist(currentGradeMv3);
                    mv3.at(currentGradeMv3, currentIdx3) += coeffRightContraction*currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2);
                }
            }
        }
    }


    /// right contraction
    template<typename T>
    void rightContraction(Mvec<T> &mv3, const Mvec<T> &mv1, const Mvec<T> &mv2, int currentIdx1, int currentIdx2,
                                  int currentIdx3, int currentGradeMv1,
                                  int currentGradeMv2, int currentGradeMv3, int sign, int complement,
                                  int indexLastNodeTraversed, int indexLastNodeTraversedA, int indexLastNodeTraversedB, int indexLastNodeTraversedC, double currentMetricCoefficient) {

        int grade1 = mv1.grade();
        int grade2 = mv2.grade();

        int indexFirstChildMv1 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv1] + currentIdx1];
        int indexFirstChildMv2 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv2] + currentIdx2];
        int indexFirstChildMv3 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv3] + currentIdx3];

        int coeffRightContraction = (-2*((currentGradeMv1*(currentGradeMv2+1))%2))+1;
        int tmpSign = sign;
        if (complement == -1) {
            tmpSign = -tmpSign;
        }

        // the offset of multivectors is important here
        // Explain the offsetMv1 here
        //
        int offsetMv1 = indexLastNodeTraversed - indexLastNodeTraversedA; // offset mv3 determines the offset for mv2 and mv1
        int offsetMv2 = indexLastNodeTraversed - indexLastNodeTraversedB;
        int offsetMv3 = indexLastNodeTraversed - indexLastNodeTraversedC;

        if (((unsigned int)indexLastNodeTraversed<(algebraDimension))&&(currentGradeMv3<=(grade1+grade2))) {
            // loop over children of the node C
            rightContraction<T>(mv3, mv1, mv2, currentIdx1, currentIdx2,
                                        currentIdx3, currentGradeMv1,
                                        currentGradeMv2, currentGradeMv3, sign, complement, indexLastNodeTraversed + 1, indexLastNodeTraversedA,
                                        indexLastNodeTraversedB,indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB

            if ((indexFirstChildMv2 != -1) && (indexFirstChildMv1 != -1)) {
                rightContraction<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, indexFirstChildMv2 + offsetMv2,
                                            currentIdx3, currentGradeMv1 + 1,
                                            currentGradeMv2 + 1, currentGradeMv3, tmpSign, -complement, indexLastNodeTraversed + 1,
                                            indexLastNodeTraversed + 1,
                                            indexLastNodeTraversed + 1, indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }

            if ((currentGradeMv2 < grade2) && (indexFirstChildMv2 != -1)) {
                rightContraction<T>(mv3, mv1, mv2, currentIdx1, indexFirstChildMv2 + offsetMv2,
                                            indexFirstChildMv3 + offsetMv3, currentGradeMv1,
                                            currentGradeMv2 + 1, currentGradeMv3 + 1, sign, -complement, indexLastNodeTraversed + 1,
                                            indexLastNodeTraversedA,
                                            indexLastNodeTraversed + 1, indexLastNodeTraversed + 1, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }
        } else {
            if(mv1.hasVectorXdComponent(currentGradeMv1) && mv2.hasVectorXdComponent(currentGradeMv2)){
                if ((mv1.at(currentGradeMv1, currentIdx1) != 0) && (mv2.at(currentGradeMv2, currentIdx2) != 0) ) {
                    // test whether the VectorXd was created
                    mv3.createVectorXdIfDoesNotExist(currentGradeMv3);
                    mv3.at(currentGradeMv3, currentIdx3) += coeffRightContraction*currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2);
                }
            }
        }
    }



    /// scalar product
    template<typename T>
    void dotProduct(Mvec<T> &mv3, const Mvec<T> &mv1, const Mvec<T> &mv2, int currentIdx1, int currentIdx2,
                       int currentIdx3, int currentGradeMv1,
                       int currentGradeMv2, int currentGradeMv3, int sign, int complement,
                       int indexLastNodeTraversed, int indexLastNodeTraversedA, int indexLastNodeTraversedB, int indexLastNodeTraversedC, double currentMetricCoefficient) {

        int grade1 = mv1.grade();
        int grade2 = mv2.grade();

        int indexFirstChildMv1 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv1] + currentIdx1];
        int indexFirstChildMv2 = 4;//tabIndicesChildren[perGradeStartingIndex[currentGradeMv2] + currentIdx2];



        int tmpSign = sign;
        if (complement == -1) {
            tmpSign = -tmpSign;
        }

        // the offset of multivectors is important here
        // Explain the offsetMv1 here
        //
        int offsetMv1 = indexLastNodeTraversed - indexLastNodeTraversedA; // offset mv3 determines the offset for mv2 and mv1
        int offsetMv2 = indexLastNodeTraversed - indexLastNodeTraversedB;


        if (((unsigned int)indexLastNodeTraversed<(algebraDimension))&&(currentGradeMv3<=(grade1+grade2))) {
            // loop over children of the node C
            dotProduct<T>(mv3, mv1, mv2, currentIdx1, currentIdx2,
                             currentIdx3, currentGradeMv1,
                             currentGradeMv2, currentGradeMv3, sign, complement, indexLastNodeTraversed + 1, indexLastNodeTraversedA,
                             indexLastNodeTraversedB,indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB

            if ((indexFirstChildMv2 != -1) && (indexFirstChildMv1 != -1)) {
                dotProduct<T>(mv3, mv1, mv2, indexFirstChildMv1 + offsetMv1, indexFirstChildMv2 + offsetMv2,
                                 currentIdx3, currentGradeMv1 + 1,
                                 currentGradeMv2 + 1, currentGradeMv3, tmpSign, -complement, indexLastNodeTraversed + 1,
                                 indexLastNodeTraversed + 1,
                                 indexLastNodeTraversed + 1, indexLastNodeTraversedC, currentMetricCoefficient);//indexLastNodeTraversedA+1,indexLastNodeTraversedB
            }

        } else {

            if(mv1.hasVectorXdComponent(currentGradeMv1) && mv2.hasVectorXdComponent(currentGradeMv2)){
                if ((mv1.at(currentGradeMv1, currentIdx1) != 0) && (mv2.at(currentGradeMv2, currentIdx2) != 0) ) {
                    // test whether the VectorXd was created
                    mv3.createVectorXdIfDoesNotExist(currentGradeMv3);//,currentIdx3,currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2));
                    mv3.at(currentGradeMv3, currentIdx3) += currentMetricCoefficient*sign*mv1.at(currentGradeMv1,currentIdx1)*mv2.at(currentGradeMv2,currentIdx2);
                }
            }
        }
    }



} /// End of Namespace

#endif // E3GA_INNER_PRODUCT_HPP__
