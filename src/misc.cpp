/*
 * This is the misc.cpp file where extra functions and constants
 * for the realmake utility are defined
 *
 * License: This software is licensed under the GPL. You are
 * free to make any modifications, updates, changes, and distribute
 * this code provided you release all of the source code under the 
 * GPL.
 * 
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED AS IS WITH NO WARRANTIES OR
 * ANY PROMISE TO MAINTAIN DATA INTEGRITY. BY USING THIS SOFTWARE, YOU
 * ACKNOWLEDGE THAT YOU UNDERSTAND THE RISKS INVOLVED AND RELEASE ALL
 * DEVELOPERS, OWNERS, AND ANYONE ASSOCIATION WITH THE DEVELOPMENT OF
 * THIS SOFTWARE FROM ANY LIABILITY.
 */
 
 
 #include <iostream>
 #include <strings.h>
 #include "../headers/misc.h"

//Misc functions
std::string match_lang(const std::string &lang) {

	if(0 == strcasecmp(lang.c_str(),c_lang.c_str()))
        	return c_lang;
        else if(0 == strcasecmp(lang.c_str(),cpp_lang_1.c_str()) ||
                0 == strcasecmp(lang.c_str(),cpp_lang_2.c_str()) ||
                0 == strcasecmp(lang.c_str(),cpp_lang_3.c_str()) ||
                0 == strcasecmp(lang.c_str(),cpp_lang_4.c_str()))
                return cpp_lang_1;
        else if(0 == strcasecmp(lang.c_str(),java_lang.c_str()))
                return java_lang;
	
	return "";
}

// This function tests whether a string is "empty" or not. Empty
// for this fuction means there are no letters or numbers in the string
// (i.e. the string is all whitespace)
bool is_empty(const std::string &t_string) {

	int i = 0;
	int size = t_string.length();
	
	while(i < size) {
	 if (isalnum(t_string[i]))
	  return false;
	 i++;
	}
	
	return true;
}

