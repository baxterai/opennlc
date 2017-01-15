/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * BAIPROJECT is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with BAIPROJECT. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardSet.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v4b 12-October-2016
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
			
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(setAction, NLC_USE_LIBRARY_SET_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityToConditionList != NULL)
			{	
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
				{
					NLCgenericEntityClass* toConditionObject = iter3->second;
					
					#ifdef NLC_USE_MATH_OBJECTS				
					//eg "Set the mathObjectNumericalValue to 5."
					if(isStringNumberOrFractional(toConditionObject->name))
					{
						setObject->mathObjectNumericalValue = atof(toConditionObject->name.c_str());
					}
					else
					{
					#endif
						addPropertyGeneric(setObject, toConditionObject);
					#ifdef NLC_USE_MATH_OBJECTS				
					}
					#endif
				}
			}
		}
	}
}



