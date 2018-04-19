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
 * File Name: NLClibraryGenericEntityClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f2a 04-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY_GENERIC_ENTITY_CLASS
#define HEADER_NLC_LIBRARY_GENERIC_ENTITY_CLASS

#include "NLCglobalDefs.hpp"

#define NLC_ENUM_LIST_DEFAULT_TYPE "none"

class NLCgenericEntityClass
{
public:
	NLCgenericEntityClass(void);
	string name;
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	stack<int> lastSentenceReferenced;
	#endif
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	vector<string> aliasList;
	#endif
	#ifdef NLC_MATH_OBJECTS
	int mathObjectType;
	double mathObjectNumericalValue;	//numerical value (eg 0, 1, 2, 3, 4.56 etc)
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	#ifdef NLC_MATH_OBJECTS_STRING
	string mathObjectStringValue;
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	bool mathObjectBooleanValue;
	#endif
	#endif
	#endif
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	bool inverseConditionTwoWay;
	#endif
		
	#ifdef NLC_LIBRARY
	unordered_map<string, vector<NLCgenericEntityClass*>*> propertyLists;
	vector<NLCgenericEntityClass*> propertyIncomingList;
	#ifdef NLC_CONDITION_LISTS_VECTOR
	unordered_map<pair<string, string>*, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*> conditionLists;
	#else
	unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> conditionLists;	
	#endif
	unordered_map<string, NLCgenericEntityClass*> conditionIncomingList;
	#ifdef NLC_RECORD_ACTION_HISTORY
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionIncomingLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionSubjectLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionObjectLists;
	#endif
	#endif

	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_CHECK_PARENT_CLASS_FUNCTION
	vector<NLCgenericEntityClass*> parentClassList;
	#endif
	
	#ifdef NLC_ENUM_LISTS
	//used to store "enums" (ie properties which cannot exist along side other properties of the same enumType, eg red) 
	string enumType;
	#ifdef NLC_ENUM_LISTS_PROPERTIES
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumPropertyLists;	//store property lists by enum type, eg none, colour, temperature (hot/cold), affect (sad/happy), valence (good/bad), state (on/off), etc
	#endif
	#ifdef NLC_ENUM_LISTS_CONDITIONS
	#ifdef NLC_CONDITION_LISTS_VECTOR
	unordered_map<tuple<string, string, string>*, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*> enumConditionLists;
	#else
	unordered_map<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> enumConditionLists;	
	#endif
	#endif
	#ifdef NLC_ENUM_LISTS_ACTIONS
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumActionLists;
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumActionIncomingLists;
	#endif
	#endif
	
	#ifdef NLC_API
	void* thirdpartyAPIobject;
	#endif
};

#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
extern unordered_map<string, string> enumTypeTableProperties;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
extern unordered_map<string, string> enumTypeTableConditions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_ENUM_LISTS_ACTIONS
extern unordered_map<string, string> enumTypeTableActions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#endif

#ifdef NLC_REDEFINITIONS
bool checkParentClassName(NLCgenericEntityClass* object, string className);
#endif
#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
void addEntityToReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex);
void clearReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList);
#endif


//These functions are not hard coded (unlike those in NLClibraryBase):

#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
string calculateEnumTypeProperty(string entityName);
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
string calculateEnumTypeCondition(string entityName);
#endif
#endif

#ifdef NLC_MATH_OBJECTS_ADVANCED
#ifdef NLC_MATH_OBJECTS_ADVANCED_DYNAMIC_DETERMINE_MATH_OBJECT_VARIABLE_TYPE
void detectMathObjectVariableType(NLCgenericEntityClass* object, double* mathObjectVariableNumericalPointer, string* mathObjectVariableStringPointer, bool* mathObjectVariableBooleanPointer, int* sentenceMathObjectVariableType);	//not used
#endif
void assignMathObjectValue(NLCgenericEntityClass* targetObject, NLCgenericEntityClass* sourceObject);
void assignMathObjectValue(NLCgenericEntityClass* targetObject, double sourceObjectNumerical);
#ifdef NLC_MATH_OBJECTS_STRING
void assignMathObjectValue(NLCgenericEntityClass* targetObject, string sourceObjectString);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void assignMathObjectValue(NLCgenericEntityClass* targetObject, bool sourceObjectBoolean);
#endif
#ifdef NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
void assignMathTextValue(double* targetObject, NLCgenericEntityClass* sourceObject);
#ifdef NLC_MATH_OBJECTS_STRING
void assignMathTextValue(string* targetObject, NLCgenericEntityClass* sourceObject);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void assignMathTextValue(bool* targetObject, NLCgenericEntityClass* sourceObject);
#endif
#else
double getMathObjectValue(NLCgenericEntityClass* targetObject);
#ifdef NLC_MATH_OBJECTS_STRING
string getMathObjectValue(NLCgenericEntityClass* targetObject);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
bool getMathObjectValue(NLCgenericEntityClass* targetObject);
#endif
#endif
#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, NLCgenericEntityClass* objectB);
NLCgenericEntityClass* addMathObjectValue(double objectA, NLCgenericEntityClass* objectB);
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, double objectB);
NLCgenericEntityClass* addMathObjectValue(double objectA, double objectB);
#ifdef NLC_MATH_OBJECTS_STRING
NLCgenericEntityClass* addMathObjectValue(string objectA, NLCgenericEntityClass* objectB);
NLCgenericEntityClass* addMathObjectValue(NLCgenericEntityClass* objectA, string objectB);
NLCgenericEntityClass* addMathObjectValue(string objectA, string objectB);
#endif
#endif
#ifdef NLC_MATH_OBJECTS_ADVANCED_COMPARISONS
bool testMathObjectValue(NLCgenericEntityClass* targetObject, NLCgenericEntityClass* sourceObject);
bool testMathObjectValue(NLCgenericEntityClass* targetObject, double sourceObject);
bool testMathObjectValue(double targetObject, NLCgenericEntityClass* sourceObject);
bool testMathObjectValue(double targetObject, double sourceObject);
#ifdef NLC_MATH_OBJECTS_STRING
bool testMathObjectValue(NLCgenericEntityClass* targetObject, string sourceObject);
bool testMathObjectValue(string targetObject, NLCgenericEntityClass* sourceObject);
bool testMathObjectValue(string targetObject, string sourceObject);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
bool testMathObjectValue(NLCgenericEntityClass* targetObject, bool sourceObject);
bool testMathObjectValue(bool targetObject, NLCgenericEntityClass* sourceObject);
bool testMathObjectValue(bool targetObject, bool sourceObject);
bool testMathObjectValue(NLCgenericEntityClass* object);
#endif
#endif
#endif
#endif

#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION
void verifyDefiniteReferenceExistence(bool empty, string entityName, string genericListAppendName);
#endif

#endif
