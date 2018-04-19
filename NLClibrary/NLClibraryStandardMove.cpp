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
 * File Name: NLClibraryStandardMove.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f2a 04-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardMove.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "NLCgenerated.hpp"

//e.g. Move the chicken from the pie to the apple.
void moveFunction(vector<NLCgenericEntityClass*>& moveClassList, vector<NLCgenericEntityClass*>& moveObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = moveClassList.begin(); iter1 < moveClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* moveAction = *iter1;

		for(vector<NLCgenericEntityClass*>::iterator iter2 = moveObjectClassList.begin(); iter2 < moveObjectClassList.end(); iter2++) 
		{
			NLCgenericEntityClass* moveObject = *iter2;
			
			//see redistributeStanfordRelationsConnectToAndFromConditions{} and GIA_DYNAMICALLY_LINK_FROM_CONDITIONS:linkEntitiesDynamicFromConditions{} for necessary preprocessing of to and from conditions
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityFromConditionList = getConditionListByConditionName(moveAction, NLC_LIBRARY_FUNCTION_ACTION_CONDITION_FROM_NAME); 
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(moveAction, NLC_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityFromConditionList != NULL)
			{
				if(NLCgenericEntityToConditionList != NULL)
				{	
					//eg "Move the chicken from the pie to the apple."
					for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityFromConditionList->begin(); iter3 != NLCgenericEntityFromConditionList->end(); iter3++)
					{
						NLCgenericEntityClass* fromConditionObject = iter3->second;
						bool foundFromPropertyConnection = false;
						bool foundFromConditionConnection = false;
						if(removePropertyGeneric(fromConditionObject, moveObject))		//remove all properties between fromConditionObject and moveObject
						{
							foundFromPropertyConnection = true;
						}
						if(removeConditionObjectsGeneric(moveObject, fromConditionObject))	//remove all conditions between moveObject and fromConditionObject (NB inverse to the above)
						{
							foundFromConditionConnection = true;
						}
						if(foundFromPropertyConnection || foundFromConditionConnection)
						{
							for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter4 = NLCgenericEntityToConditionList->begin(); iter4 != NLCgenericEntityToConditionList->end(); iter4++)
							{
								NLCgenericEntityClass* toConditionObject = iter4->second;
								if(foundFromPropertyConnection)
								{
  									addPropertyGeneric(toConditionObject, moveObject);
								}
								else if(foundFromConditionConnection)
								{
									NLCgenericEntityClass* condition = generateObjectByName(NLC_LIBRARY_FUNCTION_ACTIONOBJECT_CONDITION_AT_NAME);	//CHECKTHIS; or replicate existing conditionType?
									addConditionGeneric(moveObject, condition, toConditionObject);
								}
								#ifdef NLC_DEBUG_LIBRARY
								cout << "moveFunction{} pass: moveParentOld (fromConditionObject) = " << fromConditionObject->name << ", moveObject = " << moveObject->name << "moveParentNew (toConditionObject) = " << toConditionObject->name << endl;
								#endif
							}
						}
						else
						{
							cout << "moveFunction{} error: !(foundFromPropertyConnection || foundFromConditionConnection)" << endl;
						}
					}
				}
				else
				{
					//cout << "move() error: move action 'to' condition not found" << endl;
				}
			}
			else
			{
	
				if(NLCgenericEntityToConditionList != NULL)
				{
					//eg "Move the bike to the car."
					
					//FUTURE NLC - don't assume bike currently is a property of an entity [this will not necessarily hold]
					bool foundPropertyParentConnection = false;
					if(removePropertyParentsGeneric(moveObject))
					{
						foundPropertyParentConnection = true;
					}
					else
					{
						cout << "moveFunction{} error: !foundPropertyParentConnection" << endl;
					}
					
					if(foundPropertyParentConnection)
					{
						for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
						{
							NLCgenericEntityClass* toConditionObject = iter3->second;
							addPropertyGeneric(toConditionObject, moveObject);
				
							#ifdef NLC_DEBUG_LIBRARY
							cout << "moveFunction{} pass: moveObject = " << moveObject->name << "moveParentNew (toConditionObject) = " << toConditionObject->name << endl;
							#endif
						}
					}
				}
				else
				{
					//eg "Move the bike near the car."
	
					//FUTURE NLC - don't assume bike currently is a condition of an entity [this will not necessarily hold]
					bool foundConditionParentConnection = false;
					if(removeConditionParentsGeneric(moveObject))	//FUTURE NLC - need to only remove condition connections of a particular enum type (position1,position2,position3,position4)
					{
						foundConditionParentConnection = true;
					}
					else
					{
						cout << "moveFunction{} error: !foundConditionParentConnection" << endl;
					}
					
					if(foundConditionParentConnection)
					{
						//eg "Move the bike near the car." - note this case is ambigious - note stanford connects the "near" preposition to the car object (instead of the move action)
						for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter3 = moveAction->conditionLists.begin(); iter3 != moveAction->conditionLists.end(); iter3++)
						{
							/*	//not used
							pair<string, string>* key = iter3->first;
							string conditionName = key->first; 		
							string conditionObjectName = key->second;
							*/
							unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* arbitraryConditionList = iter3->second;
							for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter4 = arbitraryConditionList->begin(); iter4 != arbitraryConditionList->end(); iter4++)
							{
								NLCgenericEntityClass* condition = iter4->first;
								NLCgenericEntityClass* conditionNew = generateObjectByName(condition->name);		//OR conditionName
								NLCgenericEntityClass* conditionObject = iter4->second;
								addConditionGeneric(moveObject, conditionNew, conditionObject);
								
								#ifdef NLC_DEBUG_LIBRARY
								cout << "moveFunction{} pass: moveObject = " << moveObject->name << "moveLocation (conditionObject) = " << conditionObject->name << endl;
								#endif
							}
						}
					}
				}
			}
		}
	}
}




