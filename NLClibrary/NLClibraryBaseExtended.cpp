/*******************************************************************************
 *
 * This file is part of NLC.
 *
 * NLC is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * NLC is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with NLC. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryBaseExtended.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p2c 12-June-2015
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These extended functions are not generally hard coded (unlike those in NLClibraryBase) but are still dual licensed under AGPL
 *
 *******************************************************************************/
 

#include "NLClibraryBaseExtended.h"
#ifdef NLC_USE_GENERIC_FUNCTIONS
#include "NLClibraryStandardOperations.h"
#endif

//Base NLC library Functions (no generic property and condition lists)

#ifdef NLC_USE_LIBRARY_BASE_EXTENDED

template <class E1, class E2>
void addProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	addPropertyGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), dynamic_cast<NLCgenericEntityClass*>(E2Instance));
	#else
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumProperty<E1, E2>(E1Instance, E2Instance);
	#endif
	E2propertyList->push_back(E2Instance);
	E2Instance->conditionPropertyList->push_back(E1Instance);
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	addEnumProperty<E1, E2>(E1Instance, E2Instance, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2propertyList));
	#endif
	#endif
}

template <class E1, class E2, class E3>
void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
{
	/*
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	#ifdef NLC_USE_ENUM_LISTS
	cout << "addCondition{} error: NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS:NLC_USE_ENUM_LISTS not yet implemented" << endl;
	#else
	E2E3conditionList->insert(pair<string, E3*>(E2className, E3));
	E3->conditionIncomingList->insert(pair<string, NLCgenericEntityClass*>(E2className, E1));	
	#endif
	#else
	*/
	E2* condition = new E2();
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	addConditionGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), dynamic_cast<NLCgenericEntityClass*>(condition), dynamic_cast<NLCgenericEntityClass*>(E3Instance));	
	#else
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->name, E3Instance);
	#endif
	E2E3conditionList->insert(pair<E2*, E3*>(E2, E3));
	E3->conditionIncomingList->insert(pair<string, NLCgenericEntityClass*>(condition->name, E1));	//condition->name or use E2className
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumCondition<E1, E2, E3>(E1Instance, condition, E3Instance, reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(E2E3conditionList));
	#endif
	#endif
	/*
	#endif
	*/
}

template <class E1, class E2>
void addActionSubject(E1* E1action, E2* E2actionSubject, vector<E1*>* E1actionList, vector<E2*>* E2actionSubjectList)
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	addActionSubjectGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), dynamic_cast<NLCgenericEntityClass*>(E2Instance));	//FINISHTHIS
	#else
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	clearExistingEnumActionSubject<E1, E2>(E1action, E2actionSubject);	//FINISHTHIS
	#endif
	E1actionSubject->E1actionList.push_back(E1action);
	E1action->E2actionSubjectList.push_back(E2actionSubject);
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	addEnumActionSubject<E1, E2>(E1action, E2actionSubject, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E1actionList), reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2actionSubjectList));	//FINISHTHIS
	#endif
	#endif
}

template <class E1, class E2>
void addActionObject(E1* E1action, E2* E2actionObject, vector<E1*>* E1actionIncomingList, vector<E2*>* E2actionObjectList)
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	addActionSubjectGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), dynamic_cast<NLCgenericEntityClass*>(E2Instance));	//FINISHTHIS
	#else
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	clearExistingEnumActionSubject<E1, E2>(E1action, E2actionObject);	//FINISHTHIS
	#endif
	E2actionObject->moveClassActionIncomingList.push_back(E1action);
	E1action->E2actionObjectList.push_back(E2actionObject);
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	addEnumActionSubject<E1, E2>(E1Instance, E2Instance, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E1actionIncomingList), reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2actionObjectList));	//FINISHTHIS
	#endif
	#endif
}


template <class E1, class E2>
void removeProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	removePropertyGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), dynamic_cast<NLCgenericEntityClass*>(E2Instance));
	#else
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumProperty<E1, E2>(E1Instance, E2Instance);
	#endif
	//parse propertyIncomingList and remove reference to this property from them
	for(vector<NLCgenericEntityClass*>::iterator iter2 = E2Instance->propertyIncomingList.begin(); iter2 < E2Instance->propertyIncomingList.end(); ) 
	{
		NLCgenericEntityClass* propertyParent = *iter2;
		if(propertyParent == dynamic_cast<NLCgenericEntityClass*>(E1Instance))
		{
			iter2 = E2Instance->propertyIncomingList.erase(iter2);
		}
		else
		{
			iter2++;
		}
	}
	removeItemFromVectorList<E2>(E2propertyList, E2Instance);	
	#endif
}

template <class E1, class E2, class E3>
void removeCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
{
	E2 condition;
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	removeConditionGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), E2className, dynamic_cast<NLCgenericEntityClass*>(E3Instance));	
	#else
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->name, E3Instance);
	#endif
	//parse conditionIncomingList and remove reference to this property from them
	for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = E3Instance->conditionIncomingList.begin(); iter2 !=  E3Instance->conditionIncomingList.end(); iter2++) 
	{
		string conditionIncomingName = iter2->first;
		NLCgenericEntityClass* conditionParent = iter2->second;
		if(conditionIncomingName == condition.name)	//condition->name or use E2className
		{
			if(conditionParent == dynamic_cast<NLCgenericEntityClass*>(E1Instance))
			{
				iter2 = E3Instance->conditionIncomingList.erase(iter2);
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
	removeItemFromUnorderedMap<E2, E3>(E2E3conditionList, condition->name, E3Instance);
	#endif
}	

template <class E1, class E2>
void removeProperties(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	vector<NLCgenericEntityClass*>* E2propertyListGeneric = reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2propertyList);
	removeProperties(dynamic_cast<NLCgenericEntityClass*>(E1Instance), E2propertyListGeneric);
	#else
	for(vector<E2*>::iterator iter1 = E2propertyList.begin(); iter1 < E2propertyList.end(); iter1++) 
	{
		E2* property = *iter1;
		#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
		clearExistingEnumProperty<E1, E2>(E1Instance, property);
		#endif
		//parse propertyIncomingList and remove reference to this property from them
		for(vector<NLCgenericEntityClass*>::iterator iter2 = property->propertyIncomingList.begin(); iter2 < property->propertyIncomingList.end(); ) 
		{
			NLCgenericEntityClass* propertyParent = *iter2;
			if(propertyParent == dynamic_cast<NLCgenericEntityClass*>(E1Instance))
			{
				iter2 = property->propertyIncomingList.erase(iter2);
			}
			else
			{
				iter2++;
			}
		}	
	}
	E2propertyList.clear();
	#endif
}

template <class E1, class E2, class E3>
void removeConditions(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
{
	#ifdef NLC_USE_GENERIC_FUNCTIONS
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* E2E3conditionListGeneric = reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(E2E3conditionList);
	removeConditionsGeneric(dynamic_cast<NLCgenericEntityClass*>(E1Instance), E2E3conditionListGeneric);	
	#else
	for(unordered_map<E2*, E3*>::iterator iter1 = E2E3conditionList.begin(); iter1 != E2E3conditionList.end(); iter1++) 
	{
		E2* condition = iter1->first;
		E3* conditionObject = iter1->second;
		#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
		clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->conditionName, conditionObject);
		#endif
		//parse conditionIncomingList and remove reference to this condition from them
		for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = conditionObject->conditionIncomingList.begin(); iter2 !=  conditionObject->conditionIncomingList.end(); iter2++) 
		{
			NLCgenericEntityClass* conditionIncoming = iter2->first;
			NLCgenericEntityClass* conditionParent = iter2->second;
			if(conditionIncoming->name == condition->name)	//condition->name or use E2className
			{
				if(conditionParent == dynamic_cast<NLCgenericEntityClass*>(E1Instance))
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
	}
	E2E3conditionList.clear();
	#endif
}


#ifdef NLC_USE_ENUM_LISTS

#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
template <class E1, class E2>
void addEnumProperty(E1* E1Instance, E2* E2Instance, vector<NLCgenericEntityClass*>* propertyList)
{
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(E2Instance->name);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		E2Instance->enumType = enumTypeTablePropertiesIter->second;
		E1Instance->enumPropertyLists.insert(pair<string, pair<string, vector<E2*>*>>(E2Instance->enumType, pair<string, vector<E2*>*>(E2Instance->name, propertyList)));
	}	
	
}

string calculateEnumTypeProperty(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(entityName);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		enumType = enumTypeTablePropertiesIter->second;
	}
	return enumType;
}

template <class E1, class E2>
void clearExistingEnumProperty(E1* E1Instance, E2* E2Instance)
{
	string enumType = E2Instance->enumType;		//OR calculateEnumTypeProperty(E2Instance->name);
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		unordered_map<string, unordered_map<string, vector<NLCgenericEntityClass*>*>>::iterator enumPropertyListsIter = entity->enumPropertyLists.find(enumType);
		if(enumPropertyListsIter != entity->enumPropertyLists.end())
		{//enumTypePropertyList found
			unordered_map<string, vector<NLCgenericEntityClass*>*>* enumTypePropertyLists = &(enumPropertyListsIter->second);

			for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator enumTypePropertyListsIter = enumTypePropertyLists->begin(); enumTypePropertyListsIter != enumTypePropertyLists->end(); enumTypePropertyListsIter++) 
			{
				string propertyListName = enumTypePropertyListsIter->first;	//NB an entity can have more than one enum type, eg a hot, blue, and healthy squirrel (where each enum type maps to an enumTypePropertyList) (but only one instance per enum type; ie blue and red, hot and cold, healthy and sick, etc is not allowed)
				//vector<NLCgenericEntityClass*>* enumTypePropertyList = getPropertyListByName(entity, propertyListName);
				vector<NLCgenericEntityClass*>* enumTypePropertyList = enumTypePropertyListsIter->second;
				
				for(vector<NLCgenericEntityClass*>::iterator iter1 = enumTypePropertyList.begin(); iter1 < enumTypePropertyList.end(); iter1++) 
				{
					//parse propertyIncomingList and remove reference to this property from them <- NB shouldnt be required because enum propertyLists should only contain qualities (eg colour, temperature, etc), and qualities should only be attached as properties of a single entity
					NLCgenericEntityClass* enumTypeProperty = *iter1;
					for(vector<E1*>::iterator iter2 = enumTypeProperty->propertyIncomingList.begin(); iter2 < enumTypeProperty->propertyIncomingList.end(); iter2++) 
					{
						parentEntity = *iter2;
						if(parentEntity != entity)
						{
							cout << "clearExistingEnumPropertyGeneric{} warning: enum property (quality) detected which is a child (property) of more than one entity: entity = " << entity->name << ", property = " << property->name << endl;
							vector<NLCgenericEntityClass*>* parentEntityPropertyList = getPropertyListByName(parentEntity, enumTypeProperty->name);
							removeItemFromVectorList(parentEntityPropertyList, enumTypeProperty);
						}
					}
					if(!(enumTypeProperty->propertyLists.empty())
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more properties: entity = " << entity->name << ", property = " << property->name << endl;
						exit(0);
					}
					if(!(enumTypeProperty->conditionLists.empty())
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more conditions: entity = " << entity->name << ", property = " << property->name << endl;
						exit(0);
					}
					//enumTypeProperty->propertyIncomingList.clear();	//redundant
					delete enumTypeProperty;
				}
				enumTypePropertyList.clear();
			}

			enumTypePropertyLists->clear();
		}
	}
	
}
#endif

#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
template <class E1, class E2, class E3>
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> conditionList)
{
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(E2Instance->name);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		E2Instance->enumType = enumTypeTableConditionsIter->second;
		E1Instance->enumConditionLists.insert(pair<string, pair<string, unordered_map<E2*, E3*>*>>(E2Instance->enumType, pair<string, unordered_map<E2*, E3*>*>(E2Instance->name, conditionList)));
	}
}

string calculateEnumTypeCondition(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(entityName);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		enumType = enumTypeTableConditionsIter->second;
	}
	return enumType;
}

template <class E1, class E2, class E3>
void clearExistingEnumCondition(E1* E1Instance, string E2className, E3* E3Instance)
{
	string enumType = calculateEnumTypeCondition(E2className);	//NB condition enum types are stored with condition, not with conditionObject
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		unordered_map<string, unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>>::iterator enumConditionListsIter = entity->enumConditionLists.find(enumType);
		if(enumConditionListsIter != entity->enumConditionLists.end())
		{//enumTypePropertyList found
			unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* enumTypeConditionLists = &(enumConditionListsIter->second);

			for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*::iterator enumTypeConditionListsIter = enumTypeConditionLists->begin(); enumTypeConditionListsIter != enumTypeConditionLists->end(); enumTypeConditionListsIter++) 
			{
				pair<string, string>* key = enumTypeConditionListsIter->first;
				string conditionName = key->first;
				string conditionObjectName = key->second; 
				//unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = getConditionListByName(entity, conditionName, conditionObjectName);
				unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = enumTypeConditionListsIter->second;
				
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = enumTypeConditionList.begin(); iter1 != enumTypeConditionList.end();) 
				{
					//parse conditionIncomingList and remove reference to this condition from them
					NLCgenericEntityClass* enumTypeCondition = iter1->first;
					NLCgenericEntityClass* enumTypeConditionObject = iter1->second;
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = enumTypeConditionObject->conditionIncomingList.begin(); iter2 < enumTypeConditionObject->conditionIncomingList.end();) 
					{
						parentEntity = iter2->second;
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
				enumTypeConditionList.clear();
			}

			enumTypeConditionLists->clear();
		}
	}
	
}
#endif

#endif

template <class E1>
E1* addNewEntityToLocalList(string &E1classList)
{
	E1* entity = new E1();
	E1classList.push_back(entity);
	return entity;
}

template <class E1>
void addNewEntityToLocalList(string &E1classList, E1* E1Instance)
{
	E1classList.push_back(E1Instance);
}


#endif


