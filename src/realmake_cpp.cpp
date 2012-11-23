/*
 * This is the C++ class of the realmake utility. This is where
 * all of the basic functionality should be defined for user code
 * written in C++.
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
 #include <sstream>
 #include <fstream>
 #include <ctime>
 #include <dirent.h>
 #include <strings.h>
 #include <map>
 #include <sys/stat.h>
 #include <stdlib.h>
 #include "../headers/realmake_cpp.h"
 #include "../headers/misc.h"
 
 //constructors
 realmake_cpp::realmake_cpp(realmake_base &rb) {
 
 	source_dir = rb.get_src_dir();
 	language = rb.get_lang();			
	verbose = rb.get_verbose();			
	name = rb.get_name();				
	k_makef = rb.get_k_makef();					
	comp = rb.get_comp();		
	m_util = rb.get_m_util();		
	flags = rb.get_flags();			
	makef_name = rb.get_makef_name();
 }
 
 //destructors
 realmake_cpp::~realmake_cpp() {
 
 	source_dir.clear();
 	language.clear();
	verbose = false;		
	name.clear();		
	k_makef = false;			
	comp.clear();	
	m_util.clear();
	flags.clear();
	makef_name.clear();
 }
 		
 //Here are where the real methods start
 int realmake_cpp::output_makefile() {

 	//First, we need to figure out what kind of C++ compiler is available
 	int rc = 0;		//This is the return code from the system command
	std::string tmp = "";	//This is a string buffer
	struct stat finfo;	//This is used to check if a file exists
 	
 	//Can we find a C++ compiler on our own?
 	if(verbose)
	 std::cout << "Checking for a C++ compiler..." << std::endl;

	if(!comp.empty())
 	 rc = stat(comp.c_str(),&finfo);
	else {
	 comp = GPP;
	 tmp = "which " + GPP + " > /dev/null";
	 rc = system(tmp.c_str());
	}

 	if(0 != rc) {
 	 std::cerr << "realmake error: cannot determine what C++ compiler to use" << std::endl;
	 std::cerr << "use the -c option to specify a compiler (i.e. -c /usr/bin/g++)" << std::endl;
 	 return STATUS_MAKEFILE_ERR;
 	}
 		
 	//Can we find a make program on our own?
 	if(verbose)
 		std::cout << "Checking for a make utility..." << std::endl;

	if(!m_util.empty()) {
	 rc = stat(m_util.c_str(),&finfo);
	 if(0 != rc) {
	  std::cerr << "realmake error: cannot determine what make utility to use " << std::endl;
	  std::cerr << "use the -m option to specify a make utility (i.e. -m /usr/bin/make)" << std::endl;
 	  return STATUS_MAKEFILE_ERR;
	 }
	}
	else {
	 m_util = make;
	 tmp = "which " + make + " > /dev/null";
	 rc = system(tmp.c_str());
	}

 	if(0 != rc) {
 		tmp = "which " + gmake;
 		rc = system(tmp.c_str());	
 		if(0 != rc) {
 			std::cerr << "realmake error: cannot determine which make utility to use" << std::endl;
 			return STATUS_MAKEFILE_ERR;
 		}
 		else
 			m_util = gmake;
 	}

	//open a handle to the source code directory
	DIR *dir = 0;                                   
    	struct dirent *d_entry = 0;

    	dir = opendir(source_dir.c_str());
    	if(NULL == dir) {
     	 std::cerr << "realmake error: the directory " << source_dir << " cannot be opened" << std::endl;
     	 return STATUS_MAKEFILE_ERR;
    	}
    
    	//Now, check if the given directory actually has C++ files
	if(verbose)
	 std::cout << "Checking source files in (" << source_dir << ")..." << std::endl;
	std::map <std::string,std::string> files;
	while(NULL != (d_entry = readdir(dir))) {
	 if(DT_REG == d_entry->d_type) {
	  std::string buf(d_entry->d_name);
	  if((buf.find_last_of(".") + 1) < buf.length()) {
	   if((0 == strcasecmp("cc",buf.substr(buf.find_last_of(".") + 1).c_str())) ||
	      (0 == strcasecmp("cpp",buf.substr(buf.find_last_of(".") + 1).c_str())) ||
	      (0 == strcasecmp("c++",buf.substr(buf.find_last_of(".") + 1).c_str())) ||
	      (0 == strcasecmp("cxx",buf.substr(buf.find_last_of(".") + 1).c_str())))
	    files[buf.substr(0,buf.find_last_of(".")) + ".o"] = buf;
	  }
	 }
	}

	if(files.empty()) {
	 std::cout << "realmake error: no C++ files found in the (" << source_dir << ") directory" << std::endl;
	 std::cout << "Use " << src_dir << " argument to specify the source code directory" << std::endl;
	 closedir(dir);
	 return STATUS_MAKEFILE_ERR;
	}

	//open a file stream
	srand(time(0));
	std::stringstream convert;
	convert << rand();
	std::string filename = "Makefile." + convert.str();
	std::ofstream makefile(filename.c_str());
	if(!makefile) {
	 std::cerr << "realmake error: cannot open makefile for writing" << std::endl;
	 closedir(dir);
	 return STATUS_FILE_IO_ERR;
	}

	//Now, write data to the makefile
	if(verbose)
	 std::cout << "Writing makefile..." << std::endl;
	makefile << m_header << std::endl << std::endl;
	makefile << "CC=" + comp << std::endl;
	if(!flags.empty())
	 makefile << "CFLAGS=" + flags << std::endl;
	else
	 makefile << "CFLAGS=-c" << std::endl;
	if(!name.empty())
	 makefile << "NAME=" + source_dir + "/" + name << std::endl;
	else
	 makefile << "NAME=" + source_dir + "/a.out" << std::endl;
	makefile << "OBJ=";
	for(std::map <std::string,std::string>::iterator ii=files.begin(); ii != files.end(); ii++)
	 makefile << source_dir + "/" + (*ii).first << " ";
	makefile << std::endl << std::endl;
	makefile << "all: $(NAME)" << std::endl << std::endl;
	makefile << "$(NAME): $(OBJ)" <<  std::endl;
	makefile << "\t$(CC) $(OBJ) -o $(NAME)" << std::endl << std::endl;
	for(std::map <std::string,std::string>::iterator ii=files.begin(); ii != files.end(); ii++) {
	 makefile << (*ii).first << ": " << source_dir + "/" << (*ii).second << std::endl;
	 makefile << "\t$(CC) $(CFLAGS) " << source_dir + "/" << (*ii).second << std::endl << std::endl;
	}
	makefile << "clean:" << std::endl;
	makefile << "\trm -f $(NAME) $(OBJ)" << std::endl;

	//Be sure to close the file stream
	makefile.close();
	closedir(dir);
	makef_name = filename;
 	
 	if(verbose)
	 std::cout << "Finished writing makefile..." << std::endl;
	
 	return STATUS_OK;
 }
 
 int realmake_cpp::execute_makef() {

 	int rc = 0;	//This is the return code from the system command
 	std::string tmp = "";
 	
 	if(verbose) {
 	 std::cout << "Executing the makefile..." << std::endl;
 	 tmp = m_util + " -f " + makef_name;
 	}
 	else
 	 tmp = m_util + " -s -f " + makef_name;
 	rc = system(tmp.c_str());
 	if(0 != rc) {
 	 std::cerr << "realmake error: cannot execute generated makefile" << std::endl;
 	 //If the user did not set realmake to keep the makefile, let's delete it
 	 if(!k_makef) {
 	  if(verbose)
 	   std::cout << "Removing the generated makefile..." << std::endl;
 	  tmp = "rm -f " + makef_name;
 	  rc = system(tmp.c_str());
 	 }
 	 return STATUS_EXEC_MAKEFILE_ERR;
 	}
 	
 	if(verbose)
 	 std::cout << "Finished executing the makefile..." << std::endl;
 	 
 	if(!k_makef) {
 	 if(verbose)
 	  std::cout << "Removing the generated makefile..." << std::endl;
 	 tmp = "rm -f " + makef_name;
 	 rc = system(tmp.c_str());
 	 if(0 != rc) {
 	  std::cerr << "realmake error: cannot remove generated makefile" << std::endl;
 	  return STATUS_EXEC_MAKEFILE_ERR;
 	 }
 	}
 	
 	if(verbose)
 	 std::cout << "Compilation complete!" << std::endl;
 
 	return STATUS_OK;
 }

