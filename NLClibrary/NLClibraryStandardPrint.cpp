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
 * File Name: NLClibraryStandardPrint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q14l 02-September-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardPrint.hpp"

void printFunction(vector<NLCgenericEntityClass*>& printClassList, vector<NLCgenericEntityClass*>& printObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = printObjectClassList.begin(); iter1 < printObjectClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* printObject = *iter1;
		printEntity(printObject, 0);
	}
}

void printEntity(NLCgenericEntityClass* printObject, int level)
{
	cout << createIndentationBasedOnLevel(level);
	cout << printObject->name << endl;	//print the entity name
	if(!std::isnan(printObject->value))
	{
		cout << createIndentationBasedOnLevel(level);
		cout << printObject->value << endl;	//print the entity value
	}
		
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = printObject->propertyLists.begin(); iter1 != printObject->propertyLists.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			printEntity(property, level+1);
		}
	}
	
	#ifdef NLC_LIBRARY_STANDARD_PRINT_CONDITIONS_TEMP
	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = printObject->conditionLists.begin(); iter1 != printObject->conditionLists.end(); iter1++) 
	{
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter1->second;
		for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList->begin(); iter2 != conditionList->end(); iter2++) 
		{
			NLCgenericEntityClass* condition = iter2->first;
			NLCgenericEntityClass* conditionObject = iter2->second;	//conditionObject
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
			if(!(condition->inverseConditionTwoWay))	//do not write inverse conditions
			{
			#endif
				cout << createIndentationBasedOnLevel(level+1);
				cout << condition->name << endl;	//print the entity name
				printEntity(conditionObject, level+2);
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
			}
			#endif				
		}
	}	
	#endif	
}

string createIndentationBasedOnLevel(int level)
{
	string indentation = "";
	for(int i=0; i<level; i++)
	{
		indentation = indentation + CHAR_TAB;
	}
	return indentation;
}

//mathText function (macro)
void print(double value)
{
	cout << value << endl;	//print the mathText value
}


