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
 * File Name: NLClibraryStandardOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v3a 12-October-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardOperations.hpp"

//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*>* getPropertyListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*>* propertyList = getVectorListByName(&(entity->propertyLists), propertyName);
	return propertyList;
}

vector<NLCgenericEntityClass*>* getVectorListByName(unordered_map<string, vector<NLCgenericEntityClass*>*>* vectorListAll, string vectorName)
{
	vector<NLCgenericEntityClass*>* vectorList = NULL;
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = vectorListAll->begin(); iter1 != vectorListAll->end(); iter1++) 
	{
		string key = iter1->first;
		if(key == vectorName)
		{
			vectorList = iter1->second;
		}
	}
	return vectorList;
}

vector<NLCgenericEntityClass*>* getActionListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*>* actionList = getVectorListByName(&(entity->actionLists), actionName);
	return actionList;
}
vector<NLCgenericEntityClass*>* getActionIncomingListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*>* actionIncomingList = getVectorListByName(&(entity->actionIncomingLists), actionName);
	return actionIncomingList;
}
vector<NLCgenericEntityClass*>* getActionSubjectListByName(NLCgenericEntityClass* entity, string entityName)
{
	vector<NLCgenericEntityClass*>* actionSubjectList = getVectorListByName(&(entity->actionSubjectLists), entityName);
	return actionSubjectList;
}
vector<NLCgenericEntityClass*>* getActionObjectListByName(NLCgenericEntityClass* entity, string entityName)
{
	vector<NLCgenericEntityClass*>* actionObjectList = getVectorListByName(&(entity->actionObjectLists), entityName);
	return actionObjectList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByName(NLCgenericEntityClass* entity, string conditionName, string conditionObjectName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = NULL;
	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string>* key = iter1->first;
		if((key->first == conditionName) && (key->second == conditionObjectName))
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = NULL;
	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string>* key = iter1->first;
		if(key->first == conditionName)
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

bool addPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumPropertyGeneric(entity, propertyEntity);
	#endif
	
	vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
	if(propertyList != NULL)
	{
		result = true;
		propertyList->push_back(propertyEntity);
		propertyEntity->propertyIncomingList.push_back(entity);
	}
	else
	{
		cout << "addPropertyGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
	}
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	addEnumPropertyGeneric(entity, propertyEntity, propertyList);
	#endif

	return result;
}
	
bool addConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject) 
{
	bool result = false;

	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumConditionGeneric(entity, condition->name, conditionObject);
	#endif
	
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, condition->name, conditionObject->name);
	if(conditionList != NULL)
	{
		result = true;
		conditionList->insert(pair<NLCgenericEntityClass*, NLCgenericEntityClass*>(condition, conditionObject));
		conditionObject->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, entity));
	}
	else
	{
		cout << "addConditionGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << condition->name << ", conditionObject = " << conditionObject->name << endl;
	}
	
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumConditionGeneric(entity, condition, conditionObject, conditionList);
	#endif

	return result;
}


bool removePropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumPropertyGeneric(entity, propertyEntity);
	#endif
	
	vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
	if(propertyList != NULL)
	{
		result = true;
		//parse propertyIncomingList and remove reference to this property from them
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyEntity->propertyIncomingList.begin(); iter2 < propertyEntity->propertyIncomingList.end(); ) 
		{
			NLCgenericEntityClass* propertyParent = *iter2;
			if(propertyParent == entity)
			{
				iter2 = propertyEntity->propertyIncomingList.erase(iter2);
			}
			else
			{
				iter2++;
			}
		}
		//note this is inefficient; getPropertyListByName has already determined this iter
		removeItemFromVectorListGeneric(propertyList, propertyEntity);
	}
	else
	{
		cout << "addPropertyGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
	}

	return result;
}

bool removePropertyParentsGeneric(NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	for(vector<NLCgenericEntityClass*>::iterator iter1 = propertyEntity->propertyIncomingList.begin(); iter1 < propertyEntity->propertyIncomingList.end(); iter1++) 
	{
		NLCgenericEntityClass* entity = *iter1;
		#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
		clearExistingEnumPropertyGeneric(entity, propertyEntity);
		#endif

		vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
		if(propertyList != NULL)
		{
			result = true;

			//note this is inefficient; getPropertyListByName has already determined this iter
			removeItemFromVectorListGeneric(propertyList, propertyEntity);
		}
		else
		{
			cout << "removePropertyParentsGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
		}
	}
	
	propertyEntity->propertyIncomingList.clear();

	return result;
}
	
	
bool removeConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject) 
{
	bool result = false;

	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumConditionGeneric(entity, conditionName, conditionObject);
	#endif
	
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, conditionName, conditionObject->name);
	if(conditionList != NULL)
	{
		result = true;
		//parse conditionIncomingList and remove reference to this condition from them
		for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = conditionObject->conditionIncomingList.begin(); iter2 !=  conditionObject->conditionIncomingList.end(); iter2++) 
		{
			string conditionIncomingName = iter2->first;
			NLCgenericEntityClass* conditionParent = iter2->second;
			if(conditionIncomingName == conditionName)
			{
				if(conditionParent == entity)
				{
					iter2 = conditionObject->conditionIncomingList.erase(iter2);
				}
				else
				{
					iter2++;
				}
			}
			else
			{
				iter2++;
			}
		}
		//note this is inefficient; getConditionListByName has already determined this iter
		removeItemFromUnorderedMapGeneric(conditionList, conditionName, conditionObject);
	}
	else
	{
		cout << "addConditionGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << conditionName << ", conditionObject = " << conditionObject->name << endl;
	}

	return result;
}

bool removeConditionParentsGeneric(NLCgenericEntityClass* conditionObject)
{
	bool result = false;
	for(unordered_map<string, NLCgenericEntityClass*>::iterator iter1 = conditionObject->conditionIncomingList.begin(); iter1 != conditionObject->conditionIncomingList.end(); iter1++)
	{
		NLCgenericEntityClass* entity = iter1->second;
		string conditionName = iter1->first;
			
		#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
		clearExistingEnumConditionGeneric(entity, conditionName, conditionObject);
		#endif

		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, conditionName, conditionObject->name);
		if(conditionList != NULL)
		{
			result = true;

			//note this is inefficient; getConditionListByName has already determined this iter
			removeItemFromUnorderedMapGeneric(conditionList, conditionName, conditionObject);
		}
		else
		{
			cout << "removeConditionParentsGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << conditionName << ", conditionObject = " << conditionObject->name << endl;
		}
	}
	
	conditionObject->conditionIncomingList.clear();

	return result;
}


bool removeConditionObjectsGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* conditionObject) 	//remove all conditions between entity and conditionObject
{
	bool result = false;

	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string>* key = iter1->first;
		if(key->second == conditionObject->name)
		{
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter1->second;
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList->begin(); iter2 != conditionList->end();) 
			{
				if(iter2->second == conditionObject)
				{
					NLCgenericEntityClass* condition = iter2->first;
					
					#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
					clearExistingEnumConditionGeneric(entity, condition->name, conditionObject);
					#endif

					result = true;
					//parse propertyIncomingList and remove reference to this property from them
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter3 = conditionObject->conditionIncomingList.begin(); iter3 != conditionObject->conditionIncomingList.end(); iter3++) 
					{
						string conditionIncomingName = iter3->first;
						NLCgenericEntityClass* conditionParent = iter3->second;
						if(conditionIncomingName == condition->name)
						{
							if(conditionParent == entity)
							{
								iter3 = conditionObject->conditionIncomingList.erase(iter3);
							}
							else
							{
								iter3++;
							}
						}
						else
						{
							iter3++;
						}
					}
					
					//note this is inefficient; getConditionListByName has already determined this iter
					iter2 = conditionList->erase(iter2);
				}
				else
				{
					iter2++;
				}
			}
		}
	}

	return result;
}



#ifdef NLC_USE_ENUM_LISTS

#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
void addEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity, vector<NLCgenericEntityClass*>* propertyList)
{
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(propertyEntity->name);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		propertyEntity->enumType = enumTypeTablePropertiesIter->first;
		entity->enumPropertyLists.insert(pair<pair<string, string>*, vector<NLCgenericEntityClass*>*>(new pair<string, string>(propertyEntity->enumType, propertyEntity->name), propertyList));
	}
}

void clearExistingEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	string enumType = propertyEntity->enumType;	//OR calculateEnumTypeProperty(propertyEntity->name);
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		for(unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*>::iterator enumPropertyListsIter = entity->enumPropertyLists.begin(); enumPropertyListsIter != entity->enumPropertyLists.end();) 
		{
			pair<string, string>* key = enumPropertyListsIter->first;
			if(key->first == enumType)
			{
				string propertyListName = key->second;	//NB an entity can have more than one enum type, eg a hot, blue, and healthy squirrel (where each enum type maps to an enumTypePropertyList) (but only one instance per enum type; ie blue and red, hot and cold, healthy and sick, etc is not allowed)
				vector<NLCgenericEntityClass*>* enumTypePropertyList = enumPropertyListsIter->second;

				for(vector<NLCgenericEntityClass*>::iterator iter1 = enumTypePropertyList->begin(); iter1 < enumTypePropertyList->end(); iter1++) 
				{
					//parse propertyIncomingList and remove reference to this property from them <- NB shouldnt be required because enum propertyLists should only contain qualities (eg colour, temperature, etc), and qualities should only be attached as properties of a single entity
					NLCgenericEntityClass* enumTypeProperty = *iter1;
					for(vector<NLCgenericEntityClass*>::iterator iter2 = enumTypeProperty->propertyIncomingList.begin(); iter2 < enumTypeProperty->propertyIncomingList.end(); iter2++) 
					{
						NLCgenericEntityClass* parentEntity = *iter2;
						if(parentEntity != entity)
						{
							cout << "clearExistingEnumPropertyGeneric{} warning: enum property (quality) detected which is a child (property) of more than one entity: entity = " << entity->name << ", property = " << propertyEntity->name << endl;
							vector<NLCgenericEntityClass*>* parentEntityPropertyList = getPropertyListByName(parentEntity, enumTypeProperty->name);
							removeItemFromVectorListGeneric(parentEntityPropertyList, enumTypeProperty);
						}
					}
					if(!(enumTypeProperty->propertyLists.empty()))
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more properties: entity = " << entity->name << ", property = " << propertyEntity->name << endl;
						exit(0);
					}
					if(!(enumTypeProperty->conditionLists.empty()))
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more conditions: entity = " << entity->name << ", property = " << propertyEntity->name << endl;
						exit(0);
					}
					//enumTypeProperty->propertyIncomingList.clear();	//redundant
					delete enumTypeProperty;
				}
				enumPropertyListsIter = entity->enumPropertyLists.erase(enumPropertyListsIter);
			}
			else
			{
				enumPropertyListsIter++;
			}
		}
	}
	
}
#endif

#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
void addEnumConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList) 
{
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(condition->name);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		condition->enumType = enumTypeTableConditionsIter->first;
		entity->enumConditionLists.insert(pair<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new tuple<string, string, string>(condition->enumType, condition->name, conditionObject->name), conditionList));
	}
}

void clearExistingEnumConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject) 
{
	string enumType = calculateEnumTypeCondition(conditionName);	//NB condition enum types are stored with condition, not with conditionObject
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		for(unordered_map<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator enumConditionListsIter = entity->enumConditionLists.begin(); enumConditionListsIter != entity->enumConditionLists.end();) 
		{
			tuple<string, string, string>* key = enumConditionListsIter->first;
			if(get<0>(*key) == enumType)
			{
				string conditionName = get<1>(*key);
				string conditionObjectName = get<2>(*key);
				unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = enumConditionListsIter->second;
					
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = enumTypeConditionList->begin(); iter1 != enumTypeConditionList->end();) 
				{
					//parse conditionIncomingList and remove reference to this condition from them
					NLCgenericEntityClass* enumTypeCondition = iter1->first;
					NLCgenericEntityClass* enumTypeConditionObject = iter1->second;
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = enumTypeConditionObject->conditionIncomingList.begin(); iter2 != enumTypeConditionObject->conditionIncomingList.end();) 
					{
						NLCgenericEntityClass* parentEntity = iter2->second;
						if(parentEntity == entity)
						{
							iter2 = enumTypeConditionObject->conditionIncomingList.erase(iter2);
						}
						else
						{
							iter2++;
						}
					}
					delete enumTypeCondition;
				}
				enumConditionListsIter = entity->enumConditionLists.erase(enumConditionListsIter);
			}
			else
			{
				enumConditionListsIter++;
			}
		}
	}
	
}
#endif
#endif

bool removeItemFromVectorListGeneric(vector<NLCgenericEntityClass*>* vectorList, NLCgenericEntityClass* itemToRemove)
{
	bool result = false;	
	
	vector<NLCgenericEntityClass*>::iterator iter1 = find(vectorList->begin(), vectorList->end(), itemToRemove);
	if(iter1 != vectorList->end())
	{
		vectorList->erase(iter1);
		result = true;
	}
	
	/*inefficient:
	bool result = false;
	for(vector<NLCgenericEntityClass*>::iterator iter1 = vectorList->begin(); iter1 < vectorList->end();) 
	{
		NLCgenericEntityClass* itemTemp = *iter1;
		if(itemToRemove == itemTemp)
		{
			iter1 = vectorList->erase(iter1);
			result = true;
		}
		else
		{
			iter1++;
		}
	}
	*/
	return result;
}

bool removeItemFromUnorderedMapGeneric(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* unorderedMap, string conditionName, NLCgenericEntityClass* itemToRemove)
{
	bool result = false;
	/*efficient (NOT POSSIBLE);
	bool result = false;
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = find(itemToRemove->first);
	if(iter1 != unorderedMap.end())
	{
		unorderedMap.erase(iter1);
		result = true;
	}
	*/
		
	for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = unorderedMap->begin(); iter1 != unorderedMap->end();) 
	{
		NLCgenericEntityClass* first = iter1->first;
		NLCgenericEntityClass* second = iter1->second;
		if(first->name == conditionName)
		{
			if(second == itemToRemove)
			{
				iter1 = unorderedMap->erase(iter1);
				result = true;
			}
			else
			{
				iter1++;
			}
		}
		else
		{
			cout << "removeItemFromUnorderedMapGeneric{} error: this function is designed to be used for conditionLists in which all entities in [first] are of the same name, and all in [second] are of the same name" << endl;
			iter1++;
		}
	}
	return result;
}

