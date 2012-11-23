/*
 * This is the header file for the realmake base class
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
 
 #ifndef REALMAKE_BASE_H
 #define REALMAKE_BASE_H
 
 #include <strings.h>
 
 class realmake_base {
 
 	protected:
 	
 		std::string source_dir; 		//location of the source directory
 		std::string language;			//the programming languge of the code
		bool verbose;					//flag to show output or not
		std::string name;				//name of the compiled executable
		bool k_makef;					//flag to keep the makefile or not
		std::string comp;				//the complier to use in the make file
		std::string m_util;				//the make utility to use
		std::string flags;				//the flags to compile code into byte code
		std::string makef_name;			//The name of the generated makefile
 		
 	public:
 		//constructor
 		realmake_base(const std::string n_src_dir="");
 		
 		//destructor
 		~realmake_base();
 		
 		//mutators
 		void set_src_dir(const std::string n_src_dir);
 		void set_lang(const std::string n_lang);
		void set_verbose(bool flag);
		void set_name(std::string n_name);
		void set_k_makef(bool flag);
		void set_comp(std::string n_comp);
		void set_m_util(std::string n_m_util);
		void set_flags(std::string n_flags);
		void set_makef_name(std::string n_makef_name);
 		
 		//getters (functions that read attributes)
 		std::string get_src_dir();
 		std::string get_lang();
		bool get_verbose();
		std::string get_name();
		bool get_k_makef();
		std::string get_comp();
		std::string get_m_util();
		std::string get_flags();
		std::string get_makef_name();

		//specialized functions
		std::string toString();
		int deduce_lang();
 };
 
 #endif
