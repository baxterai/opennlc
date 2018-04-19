/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryUserPrint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f9b 18-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_USER_PRINT
#define HEADER_NLC_LIBRARY_USER_PRINT

#define NLC_LIBRARY_USER_PRINT_CONDITIONS_TEMP	//this should not be used for deployment to prevent infinite loops

#include "NLClibraryGenericEntityClass.hpp"

void printFunction(vector<NLCgenericEntityClass*>& printClassList, vector<NLCgenericEntityClass*>& printObjectClassList);
	void printEntity(NLCgenericEntityClass* printObject, int level);
		string createIndentationBasedOnLevel(int level);
void print(double mathObjectNumericalValue);
#ifdef NLC_MATH_OBJECTS_ADVANCED
#ifdef NLC_MATH_OBJECTS_STRING
void print(string mathObjectStringValue);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void print(string boolValue);
#endif
#endif

#endif
