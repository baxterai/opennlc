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
 * File Name: NLClibrary.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q14f 02-September-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY
#define HEADER_NLC_LIBRARY

#include "../NLClibrary/NLClibraryBase.hpp"
#ifdef NLC_USE_LIBRARY_STANDARD
#include "../NLClibrary/NLClibraryStandard.hpp"
#endif
#ifdef NLC_USE_LIBRARY_USER
#include "../NLClibrary/NLClibraryUser.hpp"
#endif
#include "../NLCgenerated/NLCgenerated.hpp"
#include "../source/XMLparserClass.h"

#define NLC_DEBUG_LIBRARY

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
