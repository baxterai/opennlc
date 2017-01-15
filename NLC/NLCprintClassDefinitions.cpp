/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprintClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u9a 29-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintClassDefinitions.h"
#include "NLCprintDefs.h"


/*
class className
{
public:

	className(void);
	~className(void);

	string name;

	vector<somevar* > somevarPropertyList;	//subclass
	....

	vector<somevar* > somevarDefinitionList;	//inherited parents

	...
	vector<somevar* > somevarFunctionList;
	...
};
*/
bool printClassDefinitions(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, bool generatingAPIclassList, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	#ifdef NLC_USE_LIBRARY
	printLine(progLangDependenciesNLClibary[progLang], 0, code);
	printLine("", 0, code);
	#else
	printLine(progLangDependenciesStandardLibaries[progLang], 0, code);
	printLine("", 0, code);
	printLine("", 0, code);
	#endif
	bool stillUnprintedClassDefinitions = true;
	while(stillUnprintedClassDefinitions)
	{
		bool printedClassDefinitionThisRound = false;
		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
		{
			NLCclassDefinition* classDefinition = *classDefinitionIter;

			if(!(classDefinition->printed))
			{
				if(printClassHeirarchyValidDefinitionClassChecks(classDefinition))
				{
					#ifdef NLC_DEBUG
					//cout << "printClassDefinitions{}: classDefinition->name:" << classDefinition->name << endl;
					#endif

					bool printedParentClassDefinitions = true;

					#ifdef NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES
					//only print class definitions once their parent class definitions have been printed
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
					{
						NLCclassDefinition* targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							#ifdef NLC_USE_LIBRARY
							if(targetClassDefinition->name != generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE))
							{
							#endif
								printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
							#ifdef NLC_USE_LIBRARY
							}
							#endif
						}
					}
					#ifdef NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES_RETAIN_OLD_CODE_FOR_DEBUGGING
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
					{
						NLCclassDefinition* targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
					{
						NLCclassDefinition* targetClassDefinition = *localListIter;

						bool foundClassDefinitionConditionClass;
						NLCclassDefinition* targetClassDefinitionConditionClass = findClassDefinition(classDefinitionList, targetClassDefinition->name, &foundClassDefinitionConditionClass);
						if(foundClassDefinitionConditionClass)
						{
							if(!(targetClassDefinitionConditionClass->printed))
							{
								printedParentClassDefinitions = false;
							}
						}
						else
						{
							cout << "printClassDefinitions{} error: !foundClassDefinitionConditionClass, targetClassDefinition->name = " << targetClassDefinition->name << endl;
							exit(0);
						}
						
						//OLD: not possible with 1m3a implementation (use of findClassDefinitionCondition and isConditionInstance) as targetClassDefinition will be a condition instance and will therefore not be printed
						//if(!(targetClassDefinition->printed))
						//{
						//	printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						//}

						#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
						//requries NLClibrary such that printClassDefinitions() can generate classes in separate files such that they can reference each other (bidirectional)
						#else
						//isConditionObjectPrinted() is required because conditions are stored as a tuple (to prevent use of isConditionObjectPrinted, NLCclassDefinition conditionLists could be stored as an array[2]; ie vector<NLCclassDefinition* > conditionList[2])
						if(!isConditionObjectPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
						#endif
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
					{
						NLCclassDefinition* targetClassDefinition = *localListIter;
						#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
						if(!(targetClassDefinition->isLibraryFunctionDefinition))
						{
						#endif
							if(!arefunctionArgumentsPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
							{
								printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
							}
						#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
						}
						#endif
					}
					#endif
					#endif

					#ifdef NLC_API
					if(classDefinition->APIclass)
					{
						if(!printedParentClassDefinitions)
						{
							printedParentClassDefinitions = true;	//prevents failure due to recursion eg GIAsentenceClass -> nextClass -> GIAsentenceClass
						}
					}
					#endif

					if(printedParentClassDefinitions)
					{//only print class definitions once their parent class definitions have been printed

						string printedClassDefinitionSourceText = "";
						string printedClassDefinitionHeaderText = "";
						#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
						vector<string> printedClassDefinitionTextHeaderTopForwardDeclarationList;
						string printedClassDefinitionTextHeaderTop = "";
						#endif
						#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
						bool implicitlyDeclaredFunctionDetected = false;
						string printedCodeBlocksHeaderMainFunctionText = progLangMainFunctionDeclaration[progLang] + progLangEndLine[progLang] + CHAR_NEWLINE;	//int main();
						#endif

						string className = classDefinition->name;

						#ifdef NLC_DEBUG
						cout << "printClassDefinitions: className:" << className << endl;
						#endif

						bool foundDefinition = false;
						string classTitleText = "";

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;

							if(!foundDefinition)
							{
								foundDefinition = true;
								classTitleText = classTitleText + " : ";
							}
							else
							{
								classTitleText = classTitleText + ", ";
							}
							string targetName = targetClassDefinition->name;
							classTitleText = classTitleText + progLangClassInheritanceHeader[progLang] + targetName;

							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							if(targetName == generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE))
							{
								printedClassDefinitionTextHeaderTop = printedClassDefinitionTextHeaderTop + generateCodeHashIncludeReferenceLibrary(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_GENERIC_ENTITY_CLASS_NAME, progLang);
							}
							else
							{
								printedClassDefinitionTextHeaderTop = printedClassDefinitionTextHeaderTop + generateCodeHashIncludeReferenceGenerated(targetName, progLang);
							}
							#endif
						}

						string classNameRaw = removeClassTextFromClassDefinitionName(className);
						//string classNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//eg string name = "dog";

						#ifdef NLC_API
						if(classDefinition->APIclass)
						{
							printedClassDefinitionTextHeaderTop = printedClassDefinitionTextHeaderTop + generateCodeHashIncludeReference(classDefinition->APIsourceFileFullPath, progLang);	//eg #include "APIsourceFileFullPath"
						}
						#endif

						printedClassDefinitionThisRound = true;
						classDefinition->printed = true;

						string classDefinitionEntryText = progLangClassTitlePrepend[progLang] + className + classTitleText;

						printLine(classDefinitionEntryText, 0, &printedClassDefinitionHeaderText);
						printLine(progLangOpenClass[progLang], 0, &printedClassDefinitionHeaderText);
						printLine(progLangClassIntro[progLang], 0, &printedClassDefinitionHeaderText);
						string classConstructorDeclaration = className + progLangClassConstructorDestructorAppend[progLang] + progLangEndLine[progLang];
						printLine(classConstructorDeclaration, 1, &printedClassDefinitionHeaderText);
						#ifdef NLC_USE_DESTRUCTORS
						string classDestructorDeclaration = progLangClassDestructorPrepend[progLang] + className + progLangClassConstructorDestructorAppend[progLang] + progLangEndLine[progLang];
						printLine(classDestructorDeclaration, 1, &printedClassDefinitionHeaderText);
						#endif

						#ifdef NLC_API
						if(classDefinition->APIclass)
						{
							printedClassDefinitionHeaderText = printedClassDefinitionHeaderText + *(classDefinition->APIwrapperHeaderText);
						}
						#endif

						#ifndef NLC_USE_LIBRARY
						#ifndef NLC_NONOO
						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						if(classDefinition->definitionList.empty())
						{//top level NLClibraryEntity class found
						#endif
							string classDefinitionNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangEndLine[progLang];	//string name;
							printLine(classDefinitionNameCode, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
							string classDefinitionLastSentenceReferencedCode = progLangClassLastSentenceReferencedVariableType[progLang] + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangEndLine[progLang];	//stack<int> lastSentenceReferenced;
							printLine(classDefinitionLastSentenceReferencedCode, 1, &printedClassDefinitionHeaderText);
							#endif
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
							string classDefinitionAliasListCode = progLangAliasListVariableType[progLang] + string(NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION) + progLangEndLine[progLang];	//vector<string> aliasList;
							printLine(classDefinitionAliasListCode, 1, &printedClassDefinitionHeaderText);
							#endif
							#ifdef NLC_USE_MATH_OBJECTS
							string classDefinitionValueCode = progLangInteger[progLang] + string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NAME) + progLangEndLine[progLang];	//int mathObjectType;
							printLine(classDefinitionValueCode, 1, &printedClassDefinitionHeaderText);
							classDefinitionValueCode = progLangDecimalType[progLang] + string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_NAME) + progLangEndLine[progLang];	//double mathObjectNumericalValue;
							printLine(classDefinitionValueCode, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
							#ifdef NLC_USE_MATH_OBJECTS_STRING
							classDefinitionValueCode = progLangStringType[progLang] + string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_NAME) + progLangEndLine[progLang];	//string mathObjectStringValue;
							printLine(classDefinitionValueCode, 1, &printedClassDefinitionHeaderText);
							#endif
							#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
							classDefinitionValueCode = progLangBooleanType[progLang] + string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_NAME) + progLangEndLine[progLang];	//boolean mathObjectBooleanValue;
							printLine(classDefinitionValueCode, 1, &printedClassDefinitionHeaderText);
							#endif
							#endif
							#endif
							#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
							string classDefinitionInverseConditionCode = progLangBoolType[progLang] + string(NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS_NAME) + progLangEndLine[progLang];	//bool inverseConditionTwoWay;
							printLine(classDefinitionInverseConditionCode, 1, &printedClassDefinitionHeaderText);
							#endif

							#ifdef NLC_USE_LIBRARY
							string allListDeclarationText = generateCodeAllPropertyListDefinitionText(progLang);	//unordered_map<string, vector<NLCgenericEntityClass*>*> propertyLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllPropertyIncomingListDefinitionText(progLang);	//vector<NLCgenericEntityClass*> propertyIncomingList;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllConditionListDefinitionText(progLang);		//e.g. unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> conditionLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllConditionIncomingListDefinitionText(progLang);	//unordered_map<string, NLCgenericEntityClass*> conditionIncomingList;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_RECORD_ACTION_HISTORY
							allListDeclarationText = generateCodeAllActionListDefinitionText(progLang);		//unordered_map<string, vector<NLCgenericEntityClass*>*> actionLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllActionIncomingListDefinitionText(progLang);	//unordered_map<string, vector<NLCgenericEntityClass*>*> actionIncomingLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllActionSubjectListDefinitionText(progLang);	//unordered_map<string, vector<NLCgenericEntityClass*>*> actionSubjectLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							allListDeclarationText = generateCodeAllActionObjectListDefinitionText(progLang);	//unordered_map<string, vector<NLCgenericEntityClass*>*> actionObjectLists;
							printLine(allListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#endif
							#endif
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_CHECK_PARENT_CLASS_FUNCTION
							string parentClassListName = string(NLC_CLASS_PARENT_CLASS_LIST_NAME);
							string parentClassListClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
							string parentClassListDeclarationText = generateCodeEntityListDefinitionText(parentClassListClassName, parentClassListName, progLang) + progLangEndLine[progLang];  	//vector<NLCgenericEntityClass*> parentClassList;
							printLine(parentClassListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#endif

							#ifdef NLC_API
							string thirdpartyAPIobjectDeclarationText = progLangGenericPointerType[progLang] + string(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME) + progLangEndLine[progLang];	//void* thirdpartyAPIobject;
							printLine(thirdpartyAPIobjectDeclarationText, 1, &printedClassDefinitionHeaderText);
							#endif

						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						}
						#endif
						#endif
						#endif

						#ifndef NLC_NONOO
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string propertyClassName = targetClassDefinition->name;
							//NLCitem* param1 = targetClassDefinition->parameters.at(0);	//not required to be used
							string localListDeclarationText = generateCodePropertyListDefinitionText(propertyClassName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, propertyClassName);
							#endif
						}

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							//string targetName = targetClassDefinition->name;	//condition instance name not used
							NLCitem* param1 = targetClassDefinition->parameters.at(0);
							string localListDeclarationText = generateCodeConditionListDefinitionText(param1->className, param1->className2, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, param1->className);
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, param1->className2);
							#endif
						}
						#endif

						#ifdef NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
						string printedClassDefinitionSourceTextUndefinedFunctions = "";
						#endif
						
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
							if(!(targetClassDefinition->isLibraryFunctionDefinition))	//isLibraryFunctionDefinition function declarations are not added to classDefinition (ie class function are not defined) - this is required to ensure generated code references the library function rather than the class function
							{
							#endif

								string targetName = targetClassDefinition->functionNameSpecial;
								string functionArguments = "";
								
								#ifdef NLC_DEBUG
								//cout << "\tclassDefinition->functionList; classDefinition = " << classDefinition->name << endl;
								#endif
								generateFunctionDeclarationArgumentsWithActionNetworkIndexInheritanceString(&(targetClassDefinition->parameters), &functionArguments, progLang);
								string functionHeaderText = targetName + progLangClassMemberFunctionParametersOpen[progLang] + functionArguments + progLangClassMemberFunctionParametersClose[progLang];
								string functionDeclarationText = progLangClassMemberFunctionTypeDefault[progLang] + functionHeaderText + progLangEndLine[progLang];
								printLine(functionDeclarationText, 1, &printedClassDefinitionHeaderText);

								#ifdef NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
								NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
								bool undefinedFunctionDetected = true;
								while(currentNLCfunctionInList->next != NULL)
								{
									#ifdef NLC_DEBUG
									cout << "currentNLCfunctionInList->NLCfunctionName = " << currentNLCfunctionInList->NLCfunctionName << endl;
									cout << "functionNameSpecial = " << targetClassDefinition->functionNameSpecial << endl;
									#endif
									string functionName = "";
									bool hasFunctionOwnerClass = false;
									string functionOwnerName = "";
									bool hasFunctionObjectClass = false;
									string functionObjectName = "";
									parseFunctionNameFromNLCfunctionName(currentNLCfunctionInList->NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
									bool foundMatchedFunction = true;
									for(vector<NLCitem*>::iterator parametersIterator = targetClassDefinition->parameters.begin(); parametersIterator < targetClassDefinition->parameters.end(); parametersIterator++)
									{
										NLCitem* currentItem = *parametersIterator;
										if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER)
										{
											if(currentItem->name != functionOwnerName)
											{
												foundMatchedFunction = false;
											}
										}
										else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION)
										{
											if(currentItem->name != functionName)
											{
												foundMatchedFunction = false;
											}
										}
										else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT)
										{
											if(currentItem->name != functionObjectName)
											{
												foundMatchedFunction = false;
											}
										}
									}
									if(foundMatchedFunction)
									{
										#ifdef NLC_DEBUG
										cout << "foundMatchedFunction" << endl;
										#endif
										undefinedFunctionDetected = false;
									}
									currentNLCfunctionInList = currentNLCfunctionInList->next;
								}
								#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
								if(classDefinition->name == generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME))
								{
									NLCitem* functionDefinitionFunctionArgumentTemp = NULL;
									if(findFunctionArgument(&(targetClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, &functionDefinitionFunctionArgumentTemp))
									{
										if(functionDefinitionFunctionArgumentTemp->className == generateClassName(NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
										{
											undefinedFunctionDetected = false;
											#ifdef NLC_DEBUG
											cout << "implicitlyDeclaredFunctionDetected" << endl;
											#endif
										}
									}
								}
								#endif
								if(undefinedFunctionDetected)
								{
									string functionDefinitionTextHeader = progLangClassMemberFunctionTypeDefault[progLang] + classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + functionHeaderText;
									string functionDefinitionText = functionDefinitionTextHeader;
									functionDefinitionText = functionDefinitionText + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;
									functionDefinitionText = functionDefinitionText + CHAR_TAB + "cout << \"" + NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS_WARNING_TEXT + functionDefinitionTextHeader + "\" << endl;";	//eg cout << "warning: function has not been defined: void tomClass::rideFunction(vector<tomClass*>& tomClassList, vector<rideClass*>& rideClassList, vector<bikeClass*>& bikeClassList)" << endl;
									functionDefinitionText = functionDefinitionText + CHAR_NEWLINE + progLangCloseBlock[progLang] + CHAR_NEWLINE;
									printedClassDefinitionSourceTextUndefinedFunctions = printedClassDefinitionSourceTextUndefinedFunctions + functionDefinitionText;
								}
								#endif
								
								#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
								for(vector<NLCitem*>::iterator parametersIterator = targetClassDefinition->parameters.begin(); parametersIterator < targetClassDefinition->parameters.end(); parametersIterator++)
								{
									NLCitem* currentItem = *parametersIterator;
									if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
									{
										#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
										addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, currentItem->className);
										#endif
									}
									#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
									if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
									{
										#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
										if(currentItem->className != generateClassName(NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
										{
										#endif
											#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
											addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, currentItem->className);
											#endif
										#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
										}
										#endif

										#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
										if(currentItem->className == generateClassName(NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
										{
											implicitlyDeclaredFunctionDetected = true;
										}
										#endif
									}
									else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
									{
										#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
										addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, currentItem->className);
										#endif
									}
									#endif
									#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
									cout << "printClassDefinitions error{}: NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS has been depreciated" << endl;
									#endif
								}
								#endif
							#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
							}
							#endif
						}

						#ifndef NLC_NONOO
						#ifdef NLC_RECORD_ACTION_HISTORY
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionList.begin(); localListIter != classDefinition->actionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							GIAentityNode entityAction;
							entityAction.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamAction(&entityAction, NLC_ITEM_TYPE_OBJECT);
							entityParamAction.genericObjectName = generateClassName(entityAction.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTION_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamAction, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, entityParamAction.className);
							#endif
							#ifdef NLC_DEBUG
							//cout << "classDefinition->name = " << classDefinition->name << endl;
							//cout << "entityParamAction.className = " << entityParamAction.className << endl;
							#endif
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionIncomingList.begin(); localListIter != classDefinition->actionIncomingList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							GIAentityNode entityAction;
							entityAction.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamAction(&entityAction, NLC_ITEM_TYPE_OBJECT);
							entityParamAction.genericObjectName = generateClassName(entityAction.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamAction, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, entityParamAction.className);
							#endif
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionSubjectList.begin(); localListIter != classDefinition->actionSubjectList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							GIAentityNode entityActionSubject;
							entityActionSubject.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamActionSubject(&entityActionSubject, NLC_ITEM_TYPE_OBJECT);
							entityParamActionSubject.genericObjectName = generateClassName(entityActionSubject.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamActionSubject, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, entityParamActionSubject.className);
							#endif
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionObjectList.begin(); localListIter != classDefinition->actionObjectList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							GIAentityNode entityActionObject;
							entityActionObject.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamActionObject(&entityActionObject, NLC_ITEM_TYPE_OBJECT);
							entityParamActionObject.genericObjectName = generateClassName(entityActionObject.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamActionObject, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, &printedClassDefinitionHeaderText);
							#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
							addToForwardDeclarationList(&printedClassDefinitionTextHeaderTopForwardDeclarationList, entityParamActionObject.className);
							#endif
						}
						#endif
						#endif

						printLine(progLangCloseClass[progLang], 0, &printedClassDefinitionHeaderText);
						printLine("", 0, &printedClassDefinitionHeaderText);

						string classConstructorEntryText = classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + classDefinition->name + progLangClassMemberFunctionParametersOpen[progLang] + progLangClassConstructorParameters[progLang] + progLangClassMemberFunctionParametersClose[progLang];
						printLine(classConstructorEntryText, 0, &printedClassDefinitionSourceText);
						printLine(progLangOpenBlock[progLang], 0, &printedClassDefinitionSourceText);
						#ifndef NLC_NONOO
						string classConstructorNameCode = progLangClassNameVariableName[progLang] + progLangClassNameVariableEquals[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//name = "dog";
						printLine(classConstructorNameCode, 1, &printedClassDefinitionSourceText);
						#ifdef NLC_USE_ADVANCED_REFERENCING
						#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
						//string classConstructorLastSentenceReferencedCode = "";
						//classConstructorLastSentenceReferencedCode = classConstructorLastSentenceReferencedCode + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + "0" + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];	//lastSentenceReferenced.push(0);
						//printLine(classConstructorLastSentenceReferencedCode, 1, &printedClassDefinitionSourceText);
						#else
						string classConstructorLastSentenceReferencedCode = "";
						classConstructorLastSentenceReferencedCode = classConstructorLastSentenceReferencedCode + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangClassNameVariableEquals[progLang] + "0" + progLangEndLine[progLang];	//lastSentenceReferenced = 0;
						printLine(classConstructorLastSentenceReferencedCode, 1, &printedClassDefinitionSourceText);
						#endif
						#endif
						#endif
						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						if(classDefinition->definitionList.empty())
						{//top level NLClibraryEntity class found
						#endif
							#ifdef NLC_USE_MATH_OBJECTS
							string setValueCode = string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NAME) + progLangEquals[progLang] + string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN_DEFNAME) + progLangEndLine[progLang];	//mathObjectType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
							printLine(setValueCode, 1, &printedClassDefinitionHeaderText);
							setValueCode = string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_NAME) + progLangEquals[progLang] + progLangDefaultDecimalValue[progLang] + progLangEndLine[progLang];	//mathObjectNumericalValue = INT_DEFAULT_VALUE;
							printLine(setValueCode, 1, &printedClassDefinitionSourceText);
							#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
							#ifdef NLC_USE_MATH_OBJECTS_STRING
							setValueCode = string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_NAME) + progLangEquals[progLang] + progLangDefaultStringValue[progLang] + progLangEndLine[progLang];	//mathObjectStringValue = "";
							printLine(setValueCode, 1, &printedClassDefinitionSourceText);
							#endif
							#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
							setValueCode = string(NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_NAME) + progLangEquals[progLang] + progLangDefaultBooleanValue[progLang] + progLangEndLine[progLang];	//mathObjectBooleanValue = false;
							printLine(setValueCode, 1, &printedClassDefinitionSourceText);
							#endif
							#endif
							#endif
							
							#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
							string classDefinitionInverseConditionCode = string(NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS_NAME) + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];	//inverseConditionTwoWay = false;
							printLine(classDefinitionInverseConditionCode, 1, &printedClassDefinitionSourceText);
							#endif

							#ifdef NLC_API
							string thirdpartyAPIobjectInitialisationText = string(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//thirdpartyAPIobject = NULL;
							printLine(thirdpartyAPIobjectInitialisationText, 1, &printedClassDefinitionSourceText);
							#endif

						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						}
						#endif

						#ifdef NLC_USE_LIBRARY
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string propertyClassName = targetClassDefinition->name;
							//NLCitem* param1 = targetClassDefinition->parameters.at(0);	//not required to be used
							string codeAllPropertyListAddText = generateCodeAllPropertyListAddText(propertyClassName, progLang);
							printLine(codeAllPropertyListAddText, 1, &printedClassDefinitionSourceText);
						}

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							//string targetName = targetClassDefinition->name;	//condition instance name not used
							NLCitem* param1 = targetClassDefinition->parameters.at(0);
							string codeAllConditionListAddText = generateCodeAllConditionListAddText(param1->className, param1->className2, progLang);
							printLine(codeAllConditionListAddText, 1, &printedClassDefinitionSourceText);
						}

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionList.begin(); localListIter != classDefinition->actionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string actionClassName = targetClassDefinition->name;
							string codeAllActionListAddText = generateCodeAllActionListAddText(actionClassName, progLang);
							printLine(codeAllActionListAddText, 1, &printedClassDefinitionSourceText);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionIncomingList.begin(); localListIter != classDefinition->actionIncomingList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string actionIncomingClassName = targetClassDefinition->name;
							string codeAllActionIncomingListAddText = generateCodeAllActionIncomingListAddText(actionIncomingClassName, progLang);
							printLine(codeAllActionIncomingListAddText, 1, &printedClassDefinitionSourceText);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionSubjectList.begin(); localListIter != classDefinition->actionSubjectList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string actionSubjectClassName = targetClassDefinition->name;
							string codeAllActionSubjectListAddText = generateCodeAllActionSubjectListAddText(actionSubjectClassName, progLang);
							printLine(codeAllActionSubjectListAddText, 1, &printedClassDefinitionSourceText);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionObjectList.begin(); localListIter != classDefinition->actionObjectList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string actionObjectClassName = targetClassDefinition->name;
							string codeAllActionObjectListAddText = generateCodeAllActionObjectListAddText(actionObjectClassName, progLang);
							printLine(codeAllActionObjectListAddText, 1, &printedClassDefinitionSourceText);
						}
						#endif

						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_CHECK_PARENT_CLASS_FUNCTION
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
						{
							NLCclassDefinition* targetClassDefinition = *localListIter;
							string parentClassName = targetClassDefinition->name;
							string parentEntityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							/*
							string parentEntityDefinitionText = generateCodeNewEntity(parentClassName, parentEntityName, progLang);	//parentClassDefinitionClass* parentClassDefinition = new parentClassDefinitionClass();
							printLine(parentEntityDefinitionText, 1, &printedClassDefinitionSourceText);
							*/
							string parentClassListName = string(NLC_CLASS_PARENT_CLASS_LIST_NAME);
							string parentClassListClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
							string addParentEntityToParentClassListText = parentClassListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + generateStaticCastOfNewEntity(parentClassName, parentClassListClassName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new parentClassDefinition));
							printLine(addParentEntityToParentClassListText, 1, &printedClassDefinitionSourceText);
						}
						#endif

						printLine(progLangCloseBlock[progLang], 0, &printedClassDefinitionSourceText);
						printLine("", 0, &printedClassDefinitionSourceText);

						#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
						if(classDefinition->name == generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME))
						{
							if(implicitlyDeclaredFunctionDetected)
							{
								string printedCodeBlocksHeaderMainFunctionText = progLangMainFunctionDeclaration[progLang] + progLangEndLine[progLang] + CHAR_NEWLINE;	//int main();
								printedClassDefinitionHeaderText = printedClassDefinitionHeaderText + printedCodeBlocksHeaderMainFunctionText;
							}
						}
						#endif

						#ifdef NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
						printedClassDefinitionSourceText = printedClassDefinitionSourceText + printedClassDefinitionSourceTextUndefinedFunctions;
						#endif
								
						#ifdef NLC_API
						if(classDefinition->APIclass)
						{
							printedClassDefinitionSourceText = printedClassDefinitionSourceText + *(classDefinition->APIwrapperSourceText);
						}
						#endif

						#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
						string printedClassDefinitionHeaderFileName = generateCodeClassDefinitionHeaderFileName(classDefinition->name);		//eg NLCgeneratedmoveClass.hpp
						string printedClassDefinitionSourceFileName = generateCodeClassDefinitionSourceFileName(classDefinition->name);		//eg NLCgeneratedmoveClass.cpp

						string printedClassDefinitionTextCPPheader = "";
						printedClassDefinitionTextCPPheader = printedClassDefinitionTextCPPheader + generateCodeHashIncludeReferenceGenerated(classDefinition->name, progLang);		//eg #include "NLCgeneratedmoveClass.hpp"
						#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
						printedClassDefinitionTextCPPheader = printedClassDefinitionTextCPPheader + generateCodeHashIncludeReferenceLibrary(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_LIBRARY_HEADER_NAME, progLang);	//eg #include "NLClibrary.hpp"
						#endif
						printedClassDefinitionTextCPPheader = printedClassDefinitionTextCPPheader + CHAR_NEWLINE;
						printedClassDefinitionSourceText = printedClassDefinitionTextCPPheader + printedClassDefinitionSourceText;

						printedClassDefinitionTextHeaderTop = printedClassDefinitionTextHeaderTop + CHAR_NEWLINE;	//add a space between #include file (definition parent ) and foward declarations
						for(vector<string>::iterator printedClassDefinitionTextCPPforwardDeclarationListIter = printedClassDefinitionTextHeaderTopForwardDeclarationList.begin(); printedClassDefinitionTextCPPforwardDeclarationListIter != printedClassDefinitionTextHeaderTopForwardDeclarationList.end(); printedClassDefinitionTextCPPforwardDeclarationListIter++)
						{
							string forwardDeclarationClassName = *printedClassDefinitionTextCPPforwardDeclarationListIter;
							printedClassDefinitionTextHeaderTop = printedClassDefinitionTextHeaderTop + generateForwardDeclaration(forwardDeclarationClassName, progLang);
						}
						string preprocessorName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_PREPROCSSOR_NAME_PREPEND) + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_PREPROCSSOR_NAME_DELIMITER + classDefinition->name;
						printedClassDefinitionHeaderText = generateCodeHeaderCheckOpen(preprocessorName) + printedClassDefinitionTextHeaderTop + printedClassDefinitionHeaderText + generateCodeHeaderCheckClose();

						writeStringToFile(printedClassDefinitionHeaderFileName, &printedClassDefinitionHeaderText);
						writeStringToFile(printedClassDefinitionSourceFileName, &printedClassDefinitionSourceText);
						#else
						*code = *code + printedClassDefinitionHeaderText;
						*code = *code + printedClassDefinitionSourceText;
						#endif
					}
				}
			}
		}
		if(!printedClassDefinitionThisRound)
		{
			stillUnprintedClassDefinitions = false;
		}
	}

	#ifdef NLC_USE_LIBRARY
	//print generateObjectByName
	int level = 0;

	#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
	string NLCgeneratedCodeSource = "";
	string NLCgeneratedCodeSourceFileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND) + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP;	//NLCgenerated.cpp
	string NLCgeneratedCodeHeaderFileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND) + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;	//NLCgenerated.hpp
	NLCgeneratedCodeSource = NLCgeneratedCodeSource + generateCodeHashIncludeReferenceGenerated(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND_BASE, progLang) + CHAR_NEWLINE;	//NLCgenerated.hpp
	generateCodeGenerateObjectByNameNewFunction(classDefinitionList, progLang, &NLCgeneratedCodeSource, level);
	generateCodeCopyObjectByNameNewFunction(classDefinitionList, progLang, &NLCgeneratedCodeSource, level);
	writeStringToFile(NLCgeneratedCodeSourceFileName, &NLCgeneratedCodeSource);

	string NLCgeneratedCodeHeader = "";
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeHeaderCheckOpen(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_PREPROCSSOR_NAME_PREPEND);
	string NLClibraryGenericClassHeaderfileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_GENERIC_ENTITY_CLASS_NAME) + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeHashIncludeReferenceLibrary(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_GENERIC_ENTITY_CLASS_NAME, progLang);
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		if(classDefinition->printed)
		{
			string printedClassDefinitionHeaderFileName = generateCodeClassDefinitionHeaderFileName(classDefinition->name);
			NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeHashIncludeReferenceGenerated(classDefinition->name, progLang);	//eg #include "NLCgeneratedmoveClass.hpp"
		}
	}
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + CHAR_NEWLINE;
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeGenerateObjectByNameDeclareFunction(progLang) + progLangEndLine[progLang] + CHAR_NEWLINE;
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeCopyObjectByNameDeclareFunction(progLang) + progLangEndLine[progLang] + CHAR_NEWLINE;
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + CHAR_NEWLINE;
	NLCgeneratedCodeHeader = NLCgeneratedCodeHeader + generateCodeHeaderCheckClose();
	writeStringToFile(NLCgeneratedCodeHeaderFileName, &NLCgeneratedCodeHeader);

	string NLCgeneratedCodeSourceFileNameList = "";
	#ifdef NLC_API
	if(generatingAPIclassList)
	{
	#endif
		NLCgeneratedCodeSourceFileNameList = NLCgeneratedCodeSourceFileNameList + NLCgeneratedCodeSourceFileName + CHAR_SPACE;
	#ifdef NLC_API
	}
	#endif
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		if(classDefinition->printed)
		{
			string printedClassDefinitionSourceFileName = generateCodeClassDefinitionSourceFileName(classDefinition->name);
			NLCgeneratedCodeSourceFileNameList = NLCgeneratedCodeSourceFileNameList + printedClassDefinitionSourceFileName + CHAR_SPACE;
		}
	}
	string NLCgeneratedCodeSourceFileNameListFileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_LIST_NAME);
	#ifdef NLC_API
	if(!generatingAPIclassList)
	{
		appendStringToFile(NLCgeneratedCodeSourceFileNameListFileName, &NLCgeneratedCodeSourceFileNameList);
	}
	else
	{
	#endif
		writeStringToFile(NLCgeneratedCodeSourceFileNameListFileName, &NLCgeneratedCodeSourceFileNameList);
	#ifdef NLC_API
	}
	#endif
	#else
	string NLCgeneratedCodeSource = "";
	generateCodeGenerateObjectByNameNewFunction(classDefinitionList, progLang, &NLCgeneratedCodeSource, level);
	generateCodeCopyObjectByNameNewFunction(classDefinitionList, progLang, &NLCgeneratedCodeSource, level);
	*code = *code + NLCgeneratedCodeSource;
	#endif

	#endif

	return result;
}

#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES

string generateCodeHeaderCheckOpen(string headerCheckOpenDefinition)
{
	string headerCheckOpen = string("") + "#ifndef " + headerCheckOpenDefinition + CHAR_NEWLINE + "#define " + headerCheckOpenDefinition + CHAR_NEWLINE + CHAR_NEWLINE;
	return headerCheckOpen;
}

string generateCodeHeaderCheckClose()
{
	string headerCheckClose = string("") + "#endif" + CHAR_NEWLINE;
	return headerCheckClose;
}

string generateCodeHashIncludeReferenceGenerated(string className, int progLang)
{
	string includeFileName = string(NLC_USE_LIBRARY_GENERATED_FOLDER) + generateCodeClassDefinitionHeaderFileName(className);
	string hashIncludeReference = generateCodeHashIncludeReference(includeFileName, progLang);
	return hashIncludeReference;
}

string generateCodeClassDefinitionHeaderFileName(string className)
{
	string printedClassDefinitionHeaderFileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND) + className + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;
	return printedClassDefinitionHeaderFileName;
}

string generateCodeClassDefinitionSourceFileName(string className)
{
	string printedClassDefinitionHeaderFileName = string(NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND) + className + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP;
	return printedClassDefinitionHeaderFileName;
}

string generateCodeHashIncludeReferenceLibrary(string libraryFileNameWithoutFolderOrExtension, int progLang)
{
	string includeFileName = string(NLC_USE_LIBRARY_LIBRARY_FOLDER) + libraryFileNameWithoutFolderOrExtension + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;
	string hashIncludeReference = generateCodeHashIncludeReference(includeFileName, progLang);
	return hashIncludeReference;
}
string generateCodeHashIncludeReference(string referenceFolder, string includeFileNameWithoutFolder, int progLang)
{
	string includeFileName = referenceFolder + includeFileNameWithoutFolder;
	string hashIncludeReference = generateCodeHashIncludeReference(includeFileName, progLang);
	return hashIncludeReference;
}
string generateCodeHashIncludeReference(string includeFileName, int progLang)
{
	string hashIncludeReference = progLangIncludeStart[progLang] + includeFileName + progLangIncludeEnd[progLang] + CHAR_NEWLINE;
	return hashIncludeReference;
}

string generateForwardDeclaration(string className, int progLang)
{
	string forwardDeclaration = progLangClassTitlePrepend[progLang] + className + progLangEndLine[progLang] + CHAR_NEWLINE;
	return forwardDeclaration;
}

void addToForwardDeclarationList(vector<string>* printedClassDefinitionTextHeaderTopForwardDeclarationList, string className)
{
	if(find(printedClassDefinitionTextHeaderTopForwardDeclarationList->begin(), printedClassDefinitionTextHeaderTopForwardDeclarationList->end(), className) == printedClassDefinitionTextHeaderTopForwardDeclarationList->end())
	{
		printedClassDefinitionTextHeaderTopForwardDeclarationList->push_back(className);
	}
}
#endif

bool printClassHeirarchyValidDefinitionClassChecks(NLCclassDefinition* classDefinition)
{
	bool validClass = true;
	if(classDefinition->isActionOrConditionInstanceNotClass)
	{
		validClass = false;
	}
	#ifdef NLC_USE_LIBRARY
	if(classDefinition->name == generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE))
	{
		validClass = false;
	}
	#endif
	#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
	if(classDefinition->name == generateClassName(NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
	{
		validClass = false;
	}
	#endif
	/*//OLD: 1q6aTEMP1
	#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
	if(classDefinition->isLibraryFunctionDefinition)
	{
		validClass = false;
	}
	#endif
	cout << "classDefinition->name " << classDefinition->name << endl;
	cout << "\tclassDefinition->isActionOrConditionInstanceNotClass " << classDefinition->isActionOrConditionInstanceNotClass << endl;
	cout << "\tclassDefinition->isLibraryFunctionDefinition " << classDefinition->isLibraryFunctionDefinition << endl;
	*/

	return validClass;
}

void generateFunctionDeclarationArgumentsWithActionNetworkIndexInheritanceString(vector<NLCitem*>* parameters, string* functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: add: if(functionArgumentCertified)?

		NLCitem* currentItem = *parametersIterator;

		#ifdef NLC_DEBUG
		//cout << "generateFunctionDeclarationArgumentsWithActionNetworkIndexInheritanceString{}: " << endl;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->className = " << currentItem->className << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		#endif

		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			#ifdef NLC_DEBUG
			//cout << "generateFunctionDeclarationArgumentsWithActionNetworkIndexInheritanceString; NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER = " << currentItem->name << endl;
			#endif
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
			#endif
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
		{
			#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
			if(currentItem->className != generateClassName(NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
			{
			#endif
				if(*functionArguments != "")
				{
					*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
				}
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
				*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
				#else
				*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
				#endif
			#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
			}
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
			#endif
		}
		#endif
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairDefinitionText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#endif
	}
}

string generateCodePluralDefinitionText(NLCitem* currentItem, int progLang)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	string backupClassName = currentItem->className;
	if(currentItem->functionArgumentPassCastRequired)
	{
		currentItem->className = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	#endif
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE
	string codePluralDefinitionText = generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
	#else
	string codePluralDefinitionText = generateCodeEntityListDefinitionText(currentItem, progLang);
	#endif
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	currentItem->className = backupClassName;
	#endif
	#endif
	return codePluralDefinitionText;
}

string generateCodeSingularDefinitionText(NLCitem* currentItem, int progLang)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	string backupClassName = currentItem->className;
	if(currentItem->functionArgumentPassCastRequired)
	{
		currentItem->className = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	#endif
	string codeSingularDefinitionText = generateCodeEntityDefinitionText(currentItem, progLang);
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	currentItem->className = backupClassName;
	#endif
	#endif
	return codeSingularDefinitionText;
}

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairDefinitionText(NLCitem* currentItem, int progLang)
{
	string conditionClassName = currentItem->className;
	string conditionObjectClassName = currentItem->className2;
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + STRING_SPACE + conditionClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DMapTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang]+ STRING_SPACE + generateConditionPairDefinitionName(conditionClassName, conditionObjectClassName);
	#endif
	return codeConditionListDefinitionText;
}
#endif



bool arefunctionArgumentsPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters)
{
	bool functionArgumentsPrinted = true;

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: add: if(functionArgumentCertified)?

		NLCitem* currentItem = *parametersIterator;

		#ifdef NLC_DEBUG
		//cout << "arefunctionArgumentsPrinted{}: " << endl;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->className = " << currentItem->className << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		#endif

		bool functionArgumentFound = false;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			functionArgumentFound = true;
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			functionArgumentFound = true;
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
		{
			functionArgumentFound = true;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
		{
			functionArgumentFound = true;
		}
		#endif
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			functionArgumentFound = true;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			functionArgumentFound = true;
		}
		#endif

		if(functionArgumentFound)
		{
			bool foundLocalClassDefinition = false;
			NLCclassDefinition* localClassDefinition = findClassDefinition(classDefinitionList, currentItem->className, &foundLocalClassDefinition);	//see if class definition already exists
			if(foundLocalClassDefinition)
			{
				if(!(localClassDefinition->printed))
				{
					#ifdef NLC_DEBUG
					//cout << "!printed: localClassDefinition->name = " << localClassDefinition->name << endl;
					#endif
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					if(currentItem->itemType != NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)	//NB function subject entity cant be printed without its function, and function cant be printed without its subject
					{
					#endif
						functionArgumentsPrinted = false;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					}
					#endif
				}
				else
				{
					#ifdef NLC_DEBUG
					//cout << "arefunctionArgumentsPrinted{}: foundLocalClassDefinition && (localClassDefinition->printed): localClassDefinition->name = " << localClassDefinition->name << endl;
					#endif
				}
			}
			else
			{
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
				if(!((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)))
				{//NB function definition/declaration names and function object names will not necessarily have a class definition (they will if the function is executed, or if the function object is used)
				#endif
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					if(currentItem->itemType != NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
					{
					#endif
						cout << "arefunctionArgumentsPrinted{}: error: !foundLocalClassDefinition; currentItem->className = " << currentItem->className << endl;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					}
					#endif
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
				}
				#endif
			}
		}
	}
	return functionArgumentsPrinted;
}

bool isConditionObjectPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters)
{
	bool functionArgumentsPrinted = true;

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST)
		{
			bool foundLocalClassDefinition = false;
			NLCclassDefinition* localClassDefinition = findClassDefinition(classDefinitionList, currentItem->className2, &foundLocalClassDefinition);	//see if class definition already exists
			if(foundLocalClassDefinition)
			{
				if(!(localClassDefinition->printed))
				{
					functionArgumentsPrinted = false;
				}
			}
			else
			{
				cout << "isConditionObjectPrinted{}: error: !foundLocalClassDefinition; currentItem->className2 = " << currentItem->className2 << endl;
			}
		}
	}
	return functionArgumentsPrinted;
}

void generateCodeGenerateObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level)
{
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	NLCitem* itemName = new NLCitem(progLangClassNameVariableType[progLang], NLC_ITEM_TYPE_OBJECT);
	itemName->name = progLangClassNameVariableName[progLang];
	string codeBlockTextFunctionHeader = generateCodeGenerateObjectByNameDeclareFunction(progLang);	//NLCgenericEntity* generateObjectByName(string name)
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
	level++;

	NLCitem* newGenericObject = new NLCitem(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, NLC_ITEM_TYPE_OBJECT);
	newGenericObject->instanceName = "newGenericObject";
	string codeBlockTextDeclareNewGenericObject = generateCodeEntityDefinitionText(newGenericObject, progLang) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//NLCgenericEntity* newGenericObject = NULL;
	printLine(codeBlockTextDeclareNewGenericObject, level, code);
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		if(printClassHeirarchyValidDefinitionClassChecks(classDefinition))
		{
			string classNameCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + itemName->name + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + removeClassTextFromClassDefinitionName(classDefinition->name) + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];	//if(name == classDefinitionName)
			printLine(classNameCheckText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			level++;
			string newSpecificObjectName = string("new") + classDefinition->name;
			string codeBlockTextDeclareNewSpecificObject = generateCodeEntityDefinitionText(classDefinition->name, newSpecificObjectName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + classDefinition->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//classDefinitionClassName* newSpecificObject = new classDefinitionClassName();
			printLine(codeBlockTextDeclareNewSpecificObject, level, code);
			string codeBlockCastNewSpecificObject = newGenericObject->instanceName + progLangClassNameVariableEquals[progLang] + progLangReinterpretCastStart[progLang] + genericEntityClassName + progLangPointer[progLang] + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + newSpecificObjectName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newSpecificObject);
			printLine(codeBlockCastNewSpecificObject, level, code);
			level--;
			printLine(progLangCloseBlock[progLang], level, code);
		}
	}
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_UPDATE_GENERATE_OBJECT_BY_NAME
	string ifNewGenericObjectNotNullText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + newGenericObject->instanceName + progLangIsNotEqualTo[progLang] + progLangNullPointer[progLang] + progLangCloseParameterSpace[progLang];	 //if(newGenericObject != NULL)
	printLine(ifNewGenericObjectNotNullText, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
	string codeBlockUpdateLastSentenceReferencedText = newGenericObject->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangOpenParameterSpace[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_DEFAULT_SENTENCE_INDEX + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//newGenericObject->lastSentenceReferenced.push(0);
	printLine(codeBlockUpdateLastSentenceReferencedText, level+1, code);
	printLine(progLangCloseBlock[progLang], level, code);	//}
	#endif
	string codeBlockTextReturnNewVector = progLangReturn[progLang] + newGenericObject->instanceName + progLangEndLine[progLang];		//return newGenericObject;
	printLine(codeBlockTextReturnNewVector, level, code);
	level--;
	printLine(progLangCloseBlock[progLang], level, code);	//}
	printLine("", level, code);
}

string generateCodeGenerateObjectByNameDeclareFunction(int progLang)
{
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	NLCitem* itemName = new NLCitem(progLangClassNameVariableType[progLang], NLC_ITEM_TYPE_OBJECT);
	itemName->name = progLangClassNameVariableName[progLang];
	string codeBlockTextFunctionHeader =  genericEntityClassName + progLangPointer[progLang] + STRING_SPACE + NLC_USE_LIBRARY_GENERATE_OBJECT_BY_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeNameVariableDefinitionText(itemName, progLang) + progLangCloseParameterSpace[progLang];	//NLCgenericEntity* generateObjectByName(string name)
	return codeBlockTextFunctionHeader;
}

void generateCodeCopyObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level)
{
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	NLCitem* itemName = new NLCitem(progLangClassNameVariableType[progLang], NLC_ITEM_TYPE_OBJECT);
	itemName->name = progLangClassNameVariableName[progLang];
	NLCitem* itemEntityToCopy = new NLCitem(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, NLC_ITEM_TYPE_OBJECT);
	itemEntityToCopy->instanceName = "entityToCopy";
	string codeBlockTextFunctionHeader = generateCodeCopyObjectByNameDeclareFunction(progLang);	//NLCgenericEntity* copyObjectByName(string name, NLCgenericEntity* itemEntityToCopy)
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
	level++;

	NLCitem* newGenericObject = new NLCitem(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, NLC_ITEM_TYPE_OBJECT);
	newGenericObject->instanceName = "newGenericObject";
	string codeBlockTextDeclareNewGenericObject = generateCodeEntityDefinitionText(newGenericObject, progLang) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//NLCgenericEntity* newGenericObject = NULL;
	printLine(codeBlockTextDeclareNewGenericObject, level, code);
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		if(printClassHeirarchyValidDefinitionClassChecks(classDefinition))
		{
			string classNameCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + itemName->name + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + removeClassTextFromClassDefinitionName(classDefinition->name) + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];	//if(name == classDefinitionName)
			printLine(classNameCheckText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			level++;
			string newSpecificObjectName = string("new") + classDefinition->name;
			string codeBlockTextDeclareNewSpecificObject = generateCodeEntityDefinitionText(classDefinition->name, newSpecificObjectName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + classDefinition->name + progLangOpenParameterSpace[progLang] + progLangPointer[progLang] + progLangOpenParameterSpace[progLang] + generateStaticCastOfEntity(itemEntityToCopy->instanceName, classDefinition->name, progLang) + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//classDefinitionClassName* newSpecificObject = new classDefinitionClassName(*(static_cast<classDefinitionClassName*>(itemEntityToCopy)));
			printLine(codeBlockTextDeclareNewSpecificObject, level, code);
			string codeBlockCastNewSpecificObject = newGenericObject->instanceName + progLangClassNameVariableEquals[progLang] + progLangReinterpretCastStart[progLang] + genericEntityClassName + progLangPointer[progLang] + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + newSpecificObjectName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newSpecificObject);
			printLine(codeBlockCastNewSpecificObject, level, code);
			level--;
			printLine(progLangCloseBlock[progLang], level, code);
		}
	}
	string codeBlockTextReturnNewVector = progLangReturn[progLang] + newGenericObject->instanceName + progLangEndLine[progLang];		//return newGenericObject;
	printLine(codeBlockTextReturnNewVector, level, code);
	level--;
	printLine(progLangCloseBlock[progLang], level, code);	//}
	printLine("", level, code);
}

string generateCodeCopyObjectByNameDeclareFunction(int progLang)
{
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	NLCitem* itemName = new NLCitem(progLangClassNameVariableType[progLang], NLC_ITEM_TYPE_OBJECT);
	itemName->name = progLangClassNameVariableName[progLang];
	NLCitem* itemEntityToCopy = new NLCitem(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, NLC_ITEM_TYPE_OBJECT);
	itemEntityToCopy->instanceName = "entityToCopy";
	string codeBlockTextFunctionHeader =  genericEntityClassName + progLangPointer[progLang] + STRING_SPACE + NLC_USE_LIBRARY_COPY_OBJECT_BY_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeNameVariableDefinitionText(itemName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateCodeEntityDefinitionText(itemEntityToCopy, progLang) + progLangCloseParameterSpace[progLang];	//NLCgenericEntity* copyObjectByName(string name, NLCgenericEntity* itemEntityToCopy)
	return codeBlockTextFunctionHeader;
}

