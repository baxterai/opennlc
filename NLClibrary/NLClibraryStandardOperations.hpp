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
 * File Name: NLClibraryStandardOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f4a 14-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_OPERATIONS
#define HEADER_NLC_LIBRARY_STANDARD_OPERATIONS

#include "NLClibraryGenericEntityClass.hpp"

#define NLC_LIBRARY_FUNCTION_ACTION_CONDITION_FROM_NAME "from"
#define NLC_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME "to"
#define NLC_LIBRARY_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME "functionObjectParent"
#define NLC_LIBRARY_FUNCTION_ACTIONOBJECT_CONDITION_AT_NAME "at"
#define NLC_LIBRARY_FUNCTION_ACTIONOBJECT_CONDITION_IN_NAME "in"

//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*>* getPropertyListByName(NLCgenericEntityClass* entity, string propertyName);
	vector<NLCgenericEntityClass*>* getVectorListByName(unordered_map<string, vector<NLCgenericEntityClass*>*>* vectorListAll, string vectorName);
vector<NLCgenericEntityClass*>* getActionListByName(NLCgenericEntityClass* entity, string actionName);
vector<NLCgenericEntityClass*>* getActionIncomingListByName(NLCgenericEntityClass* entity, string actionName);
vector<NLCgenericEntityClass*>* getActionSubjectListByName(NLCgenericEntityClass* entity, string entityName);
vector<NLCgenericEntityClass*>* getActionObjectListByName(NLCgenericEntityClass* entity, string entityName);
unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByName(NLCgenericEntityClass* entity, string conditionName, string conditionObjectName);
unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName);

bool addPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
bool addConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject);
bool removePropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
bool removePropertyParentsGeneric(NLCgenericEntityClass* propertyEntity);
bool removeConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject);
bool removeConditionParentsGeneric(NLCgenericEntityClass* conditionObject);
bool removeConditionObjectsGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* conditionObject); 	//remove all conditions between entity and conditionObject

#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
void addEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity, vector<NLCgenericEntityClass*>* propertyList);
void clearExistingEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
void addEnumConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList);
void clearExistingEnumConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject);
#endif
#endif

bool removeItemFromVectorListGeneric(vector<NLCgenericEntityClass*>* vectorList, NLCgenericEntityClass* itemToRemove);
bool removeItemFromUnorderedMapGeneric(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* unorderedMap, string conditionName, NLCgenericEntityClass* itemToRemove);

#endif
