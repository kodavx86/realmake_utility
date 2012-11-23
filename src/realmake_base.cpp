/*
 * This is the base class of the realmake utility. This is where
 * all of the basic functionality should be defined.
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

 #include <dirent.h> 
 #include <strings.h>
 #include <sstream>
 #include "../headers/realmake_base.h"
 #include "../headers/misc.h"

 #include <iostream>
 using namespace std;
 
 //class constructor(s) for realmake_base class
 realmake_base::realmake_base(const std::string n_src_dir) {
 
 	source_dir = (n_src_dir.empty()) ? "." : n_src_dir;
	language = "";
	verbose = false;
	k_makef = false;
	name = "";
	comp = "";
	m_util = "";
	flags = "";
	makef_name = "";
 }
 
 //class destructor(s) for realmake_base class
 realmake_base::~realmake_base() {
 	source_dir = "";
 	language = "";
 	verbose = false;
	k_makef = false;
 	name = "";
	comp = "";
	m_util = "";
	flags = "";
	makef_name = "";
 }
 
 //mutators
 void realmake_base::set_src_dir(const std::string n_src_dir) {
 
 	source_dir = n_src_dir;
 }
 
 void realmake_base::set_lang(const std::string n_lang) {
 
 	language = n_lang;
 }

 void realmake_base::set_verbose(bool flag) {

	verbose = flag;
 }

 void realmake_base::set_k_makef(bool flag) {

	k_makef = flag;
 }

 void realmake_base::set_comp(std::string n_comp) {
	
	comp = n_comp;
 }

 void realmake_base::set_m_util(std::string n_m_util) {
	
	m_util = n_m_util;
 }
 
 void realmake_base::set_flags(std::string n_flags) {
 
 	flags = n_flags;
 }
 
 void realmake_base::set_makef_name(std::string n_makef_name) {
 
 	makef_name = n_makef_name;
 }
 
 //getters (functions that read attributes
 std::string realmake_base::get_src_dir() {
 	
 	return source_dir;
 }
 
 std::string realmake_base::get_lang() {
 
 	return language;
 }

 bool realmake_base::get_verbose() {

	return verbose;
 }
 
 void realmake_base::set_name(std::string n_name) {
 	
 	name = n_name;
 }
 
 std::string realmake_base::get_name() {
 	
 	return name;
 }

 bool realmake_base::get_k_makef() {

	return k_makef;
 }

 std::string realmake_base::get_comp() {

	return comp;
 }

 std::string realmake_base::get_m_util() {

	return m_util;
 }
 
 std::string realmake_base::get_flags() {
 
 	return flags;
 }
 
 std::string realmake_base::get_makef_name() {
 
 	return makef_name;
 }
 
std::string realmake_base::toString() {
 
 	std::stringstream convert,convert2;
	convert << verbose;
	convert2 << k_makef;
 	return "REALMAKE_C => compiler: (" + comp + "), code_dir: (" + source_dir +
			"), flags: (" + flags + "), name: (" + name + "), verbose: (" +
			convert.str() + "), " + "language: (" + language + "), k_makef: (" + convert2.str() +
			"), make util: (" + m_util + "), makef_name: (" + makef_name + ")";
 }

int realmake_base::deduce_lang() {

	//If the language is already known, just return
	if(!language.empty())
	 return STATUS_OK;

	//First, let's open the source directory
	DIR *dir = 0; 					//This will be the directory pointer
	struct dirent *dir_entry = 0;	//This will be the pointer to the directory contents
	std::string ext("");
	
	dir = opendir(source_dir.c_str());
	if(NULL == dir) {
	 cerr << "realmake error: the directory " << source_dir << " cannot be opened" << endl;
	 return STATUS_FILE_IO_ERR;
	}
	
	//Now, read each file from the directory
	while (NULL != (dir_entry = readdir(dir))) {
	
	 if(DT_REG == dir_entry->d_type) { //Is this entry a "regular file"?
	  std::string buf(dir_entry->d_name);
	   if((buf.find_last_of(".") + 1) < buf.length()) {
	    if(ext.empty() && (!match_lang(buf.substr(buf.find_last_of(".") + 1)).empty()))
	     ext = buf.substr(buf.find_last_of(".") + 1);
	    else {
	     if(!match_lang(buf.substr(buf.find_last_of(".") + 1)).empty()) {
	      if(strcasecmp(ext.c_str(),(buf.substr(buf.find_last_of(".") + 1)).c_str())) {
	       cerr << "realmake error: cannot determine programming language to compile" << endl;
	       cerr << "directory (" << source_dir << ") contains " << ext << " and " <<
			buf.substr(buf.find_last_of(".") + 1) << " files" << endl;
	       return STATUS_INVALID_OPT;
	      }
	     }
	    }
	   }
	 }
	}
	
	//check if the resulting language is still blank
	if(ext.empty()) {
	 cerr << "realmake error: cannot determine programming language to compile" << endl;
	 cerr << "files in directory (" << source_dir << ") don't have familiar file extension" << endl;
	 return STATUS_INVALID_OPT;
	}
	
	//set the language
	language = ext;
	
	//Close the directory
	closedir(dir);
	
	//return an OK status
	return STATUS_OK;
}

