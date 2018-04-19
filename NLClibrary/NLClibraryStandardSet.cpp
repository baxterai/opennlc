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
 * File Name: NLClibraryStandardSet.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f2a 04-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#include "NLClibraryStandardSet.hpp"
#include "NLClibraryStandardMath.hpp"
#include "NLClibraryStandardOperations.hpp"

//e.g. Set the value to 5.
void setFunction(vector<NLCgenericEntityClass*>& setClassList, vector<NLCgenericEntityClass*>& setObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = setClassList.begin(); iter1 < setClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* setAction = *iter1;

		for(vector<NLCgenericEntityClass*>::iterator iter2 = setObjectClassList.begin(); iter2 < setObjectClassList.end(); iter2++) 
		{
			NLCgenericEntityClass* setObject = *iter2;
			
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(setAction, NLC_LIBRARY_SET_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityToConditionList != NULL)
			{	
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
				{
					NLCgenericEntityClass* toConditionObject = iter3->second;
					
					#ifdef NLC_MATH_OBJECTS				
					//eg "Set the mathObjectNumericalValue to 5."
					if(isStringNumberOrFractional(toConditionObject->name))
					{
						setObject->mathObjectNumericalValue = atof(toConditionObject->name.c_str());
					}
					else
					{
					#endif
						addPropertyGeneric(setObject, toConditionObject);
					#ifdef NLC_MATH_OBJECTS				
					}
					#endif
				}
			}
		}
	}
}



