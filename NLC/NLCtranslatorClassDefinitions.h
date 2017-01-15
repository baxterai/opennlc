/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLCtranslatorClassDefinitions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f9a 11-April-2014
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS
#define HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS

//#define NLC_NOT_NECESSARY

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

bool generateClassHeirarchy(vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
	#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
	string generateSubstanceConceptClassName(GIAentityNode * substanceConceptEntity);
	void generateSubstanceConceptClassNameRecurse(GIAentityNode * substanceConceptEntity, string * substanceConceptClassName);
	#endif		
	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition * classDefinition, vector<NLCclassDefinition*> * classDefinitionSublist, int variableType);
		bool findVariableInParentClass(NLCclassDefinition * classDefinition, string variableName, int variableType);
	#endif
	
#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, vector<NLCitem*> * parameters);
void generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, vector<NLCitem*> * parameters, bool performChildActionDuplicateCheck);
	bool checkDuplicateProperty(GIAentityNode * propertyEntity, vector<NLCitem*> * parameters);
	bool checkDuplicateCondition(GIAentityNode * conditionEntity, vector<NLCitem*> * parameters);
#endif

#endif	