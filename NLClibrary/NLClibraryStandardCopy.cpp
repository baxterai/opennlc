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
 * File Name: NLClibraryStandardCopy.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f2a 04-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardCopy.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "NLCgenerated.hpp"

//e.g. Copy the chicken [from the pie] to the apple.
void copyFunction(vector<NLCgenericEntityClass*>& copyClassList, vector<NLCgenericEntityClass*>& copyObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = copyClassList.begin(); iter1 < copyClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* copyAction = *iter1;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityFromConditionList = getConditionListByConditionName(copyAction, NLC_LIBRARY_FUNCTION_ACTION_CONDITION_FROM_NAME); 
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(copyAction, NLC_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME); 

		if(NLCgenericEntityToConditionList != NULL)	//this will fail with Stanford NLP until * has been implemented
		{
			for(vector<NLCgenericEntityClass*>::iterator iter3 = copyObjectClassList.begin(); iter3 < copyObjectClassList.end(); iter3++) 
			{
				NLCgenericEntityClass* copyObject = *iter3;
				//cout << "copyObject = " << copyObject->name << endl;
				
				NLCgenericEntityClass* copyOfCopyObject = copyObjectAndChildren(copyObject);
				bool copyObjectFound = true;	//always true as linkEntitiesDynamicFromConditions will have linked the copy object as the child of the copy function from condition object, and the copy object parent will already have been parsed by NLC before executing the copy funciton

				if(copyObjectFound)
				{
					for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter4 = NLCgenericEntityToConditionList->begin(); iter4 != NLCgenericEntityToConditionList->end(); iter4++)
					{
						NLCgenericEntityClass* toConditionObject = iter4->second;
  						addPropertyGeneric(toConditionObject, copyOfCopyObject);
						#ifdef NLC_DEBUG_LIBRARY
						cout << "copy() pass: addPropertyGeneric, copyOfCopyObject = " << copyOfCopyObject->name << "copyParentNew (toConditionObject) = " << toConditionObject->name << endl;
						#endif
					}
				}
				else
				{
					cout << "copy() error: copy object not not found" << endl;
				}
			}
		}
		else
		{
			cout << "copy() error: copy action 'to' condition not found" << endl;
		}
	}
}

NLCgenericEntityClass* copyObjectAndChildren(NLCgenericEntityClass* objectToCopy)
{
	NLCgenericEntityClass* copyOfCopyObject = copyObjectAndProperties(objectToCopy);
	#ifdef NLC_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
	copyConditionLinks(objectToCopy, objectToCopy, copyOfCopyObject);
	#endif
	return copyOfCopyObject;
}


NLCgenericEntityClass* copyObjectAndProperties(NLCgenericEntityClass* objectToCopy)
{
	NLCgenericEntityClass* copyOfCopyObject = copyObjectByNameWithoutChildren(objectToCopy->name, objectToCopy);
	
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->propertyLists.begin(); iter1 != objectToCopy->propertyLists.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			NLCgenericEntityClass* copyOfProperty = copyObjectAndProperties(property);
			addPropertyGeneric(copyOfCopyObject, copyOfProperty);
		}
	}
	
	return copyOfCopyObject;
}

#ifdef NLC_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
void copyConditionLinks(NLCgenericEntityClass* objectToCopyTopLevel, NLCgenericEntityClass* objectToCopy, NLCgenericEntityClass* copyOfCopyObject)
{
	unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1B = copyOfCopyObject->propertyLists.begin();
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->propertyLists.begin(); iter1 != objectToCopy->propertyLists.end(); iter1++)
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		vector<NLCgenericEntityClass*>* propertyListB = iter1B->second;
		vector<NLCgenericEntityClass*>::iterator iter2B = propertyListB->begin();
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			NLCgenericEntityClass* propertyB = *iter2B;
			copyConditionLinks(objectToCopyTopLevel, property, propertyB);
			iter2B++;
		}
		iter1B++;
	}
	
	//only copy conditions which refer to properties contained in the copy hierachy
	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->conditionLists.begin(); iter1 != objectToCopy->conditionLists.end(); iter1++) 
	{
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter1->second;
		for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList->begin(); iter2 != conditionList->end(); iter2++) 
		{		
			NLCgenericEntityClass* condition = iter2->first;
			NLCgenericEntityClass* conditionObject = iter2->second;
			if(findObjectInPropertyHierarchy(objectToCopyTopLevel, conditionObject))
			{
				NLCgenericEntityClass* copyOfCondition = copyObjectByNameWithoutChildren(condition->name, condition);	//conditions (ie condition types) are just copied in isolation
				NLCgenericEntityClass* copyOfConditionObject = conditionObject;
				addConditionGeneric(copyOfCopyObject, copyOfCondition, copyOfConditionObject);	
			}
		}
	}	
}

bool findObjectInPropertyHierarchy(NLCgenericEntityClass* object, NLCgenericEntityClass* objectToFind)
{
	bool result = false;
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = object->propertyLists.begin(); iter1 != object->propertyLists.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			if(property == objectToFind)
			{
				result = true;
			}
			else
			{
				if(findObjectInPropertyHierarchy(property, objectToFind))
				{
					result = true;
				}
			}
		}
	}
	
	return result;
}

#endif

NLCgenericEntityClass* copyObjectByNameWithoutChildren(string name, NLCgenericEntityClass* entityToCopy)
{
	NLCgenericEntityClass* copyOfEntity = generateObjectByName(name);
	copyOfEntity->name = entityToCopy->name;
	#ifdef NLC_ADVANCED_REFERENCING
	copyOfEntity->lastSentenceReferenced = entityToCopy->lastSentenceReferenced;
	#endif
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	copyOfEntity->aliasList = entityToCopy->aliasList;
	#endif
	#ifdef NLC_MATH_OBJECTS
	copyOfEntity->mathObjectNumericalValue = entityToCopy->mathObjectNumericalValue;
	copyOfEntity->mathObjectStringValue = entityToCopy->mathObjectStringValue;
	#endif
	
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_CHECK_PARENT_CLASS_FUNCTION
	copyOfEntity->parentClassList = entityToCopy->parentClassList;
	#endif
	
	#ifdef NLC_ENUM_LISTS
	//used to store "enums" (ie properties which cannot exist along side other properties of the same enumType, eg red) 
	copyOfEntity->enumType = entityToCopy->enumType;
	#ifdef NLC_ENUM_LISTS_PROPERTIES
	copyOfEntity->enumPropertyLists = entityToCopy->enumPropertyLists;	//store property lists by enum type, eg none, colour, temperature (hot/cold), affect (sad/happy), valence (good/bad), state (on/off), etc
	#endif
	/*not currently supported by copyObjectAndChildren{}
	#ifdef NLC_ENUM_LISTS_CONDITIONS
	#ifdef NLC_CONDITION_LISTS_VECTOR
	copyOfEntity->enumConditionLists = ;
	#else
	copyOfEntity->enumConditionLists = ;	
	#endif
	#endif
	#ifdef NLC_ENUM_LISTS_ACTIONS
	copyOfEntity->enumActionLists = ;
	copyOfEntity->enumActionIncomingLists = ;
	#endif
	*/
	#endif
	
	return copyOfEntity;
}


