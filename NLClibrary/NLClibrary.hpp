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
 * File Name: NLClibrary.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u9a 29-September-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY
#define HEADER_NLC_LIBRARY

#include "NLClibraryBase.hpp"
#ifdef NLC_USE_LIBRARY_STANDARD
#include "NLClibraryStandard.hpp"
#endif
#ifdef NLC_USE_LIBRARY_USER
#include "NLClibraryUser.hpp"
#endif
#include "NLCgenerated.hpp"
#include "XMLparserClass.h"

#define NLC_RULES_XML_FILE_NAME "NLCrules.xml"	//must sync with XMLrulesClass.cpp

#ifdef NLC_USE_ENUM_LISTS
#define RULES_XML_TAG_rules2 ((string)"rules")	//copy of RULES_XML_TAG_rules from XMLrulesClass.hpp (not available to NLClibrary)
#define RULES_XML_TAG_enum ((string)"enum")
#define RULES_XML_TAG_entity ((string)"entity")
#define RULES_XML_TAG_type ((string)"type")
#define RULES_XML_TAG_instance ((string)"instance")
#define RULES_XML_ATTRIBUTE_name ((string)"name")
#define NLC_ENUM_LIST_ENTITY_NAME_PROPERTY "property"
#define NLC_ENUM_LIST_ENTITY_NAME_CONDITION "condition"
#define NLC_ENUM_LIST_ENTITY_NAME_ACTION "action"
#endif

void initialiseNLClibrary();
#ifdef NLC_USE_ENUM_LISTS
bool parseNLCrulesXMLfile(XMLparserTag* NLCfirstTagInXMLfile);
void initiateEnumTypeTables(XMLparserTag* NLCfirstTagInXMLfile);
#endif

#endif
