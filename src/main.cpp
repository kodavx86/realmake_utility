/*
 * This is the main execution file for the realmake utility.
 * Execution of the utility begins and ends here.
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
 #include "../headers/realmake_base.h"
 #include "../headers/realmake_c.h"
 #include "../headers/realmake_cpp.h"
 #include "../headers/realmake_java.h"
 
 using namespace std;

 //function prototypes
 int get_params(int argc, char* argv[], Parameters &p);
 int run_makefile(Parameters p);
 
 //This function parses the command arguments from the user
 int get_params(int argc, char* argv[], Parameters &p) {
 
 	string arg; 			//The current argument under investigation
 	short flag_c = 0;		//Flag checks if compiler option set without flags option
 	for (int i = 0; i < argc; i++) {
 	
 		arg = argv[i];
 		
 		if(0 == arg.compare(src_dir)) {
 			if((i + 1) == argc) {
 				cerr << "realmake error: the -s option must specify a directory" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			else if(is_empty(argv[i + 1])) {
 				cerr << "realmake error: the -s option must specify a directory" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			p.a_source = argv[i + 1];
 			i++;
 		}
		else if(0 == arg.compare(p_verbose)) {
			p.a_verbose = true;
		}
 		else if(0 == arg.compare(p_lang)) {
 			if((i + 1) == argc) {
 				cerr << "realmake error: the -l option must specify a language" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			else if(match_lang(argv[i + 1]).empty()) {
 				cerr << "realmake error: the value (" << argv[i + 1] << ") for -l does not " <<
 						"match a known language" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			p.a_lang = argv[i + 1];
 			i++;
 		}
 		else if(0 == arg.compare(exec_name)) {
 			if((i + 1) == argc) {
 				cerr << "realmake error: the -n option must specify a name" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			else if(is_empty(argv[i + 1])) {
 				cerr << "realmake error: the -n option must specify a name" << endl;
 				return STATUS_INVALID_OPT;
 			}
 			p.a_name = argv[i + 1];
 			i++;
 		}
		else if(0 == arg.compare(k_makef)) {
			p.k_makef = true;
		}
		else if(0 == arg.compare(comp)) {
			if((i + 1) == argc) {
			 cerr << "realmake error: the -c option must specify a path like /usr/local/gcc" << endl;
			 return STATUS_INVALID_OPT;
			}
			else if(is_empty(argv[i + 1])) {
			 cerr << "realmake error: the -c option must specify a path like /usr/local/gcc" << endl;
			 return STATUS_INVALID_OPT;
			}
			p.comp = argv[i + 1];
			i++;
			flag_c++;
		}
		else if(0 == arg.compare(m_util)) {
			if((i + 1) == argc) {
			 cerr << "realmake error: the -m option must specify a path like /usr/bin/make" << endl;
			 return STATUS_INVALID_OPT;
			}
			else if(is_empty(argv[i + 1])) {
			 cerr << "realmake error: the -m option must specify a path like /usr/bin/make" << endl;
			 return STATUS_INVALID_OPT;
			}
			p.m_util = argv[i + 1];
			i++;
		}
		else if(0 == arg.compare(n_flags)) {
			if((i + 1) == argc) {
			 cerr << "realmake error: the -f option must specify compile flags in quotes ";
			 cerr << "like \"-c -g\"" << endl;
			 return STATUS_INVALID_OPT;
			}
			else if(is_empty(argv[i + 1])) {
			 cerr << "realmake error: the -f option must specify compile flags in quotes ";
			 cerr << "like \"-c -g\"" << endl;
			 return STATUS_INVALID_OPT;
			}
			p.n_flags = argv[i + 1];
			i++;
			flag_c--;
		}
		else if(0 == arg.compare(help)) {
			cout << "Usage: realmake -[svlncmfkh] [file ...]" << endl;
			cout << "version " << c_version << endl;
			cout << "arguments: " << endl;
			cout << "\t-s <directory>\tSpecify source code directory location" << endl;
			cout << "\t-v\t\tSet realmake to verbose mode" << endl;
			cout << "\t-l <language>\tSpecify programming language the code uses" << endl;
			cout << "\t-n <name>\tSpecify name of the final executable" << endl;
			cout << "\t-c <compiler>\tSpecify the compiler (i.e. -c /usr/local/gcc)" << endl;
			cout << "\t-m <make util>\tSpecify the make utility (i.e. -m /usr/bin/make)" << endl;
			cout << "\t-f <flags>\tSpecify the compile flags for each file (i.e. -f \"-c -g\")" << endl;
			cout << "\t-k\t\tSet realmake to keep the generated makefile" << endl;
			cout << "\t-h\t\tGeneral help for realmake utility" << endl;
			return STATUS_STOP;
		}
		else if('-' == arg[0]) { //What should we do if given a non-exiting option parameter?
			cerr << "realmake error: (" << arg << ") is not a valid option" << endl;
			return STATUS_INVALID_OPT;
		}
 	}
 	
 	if(0 < flag_c) {
 	 cerr << "realmake error: cannot set " << comp << " option without the ";
 	 cerr <<  n_flags << " option" << endl;
	 return STATUS_INVALID_OPT;
 	}
 	
 	return STATUS_OK;
 }

 int run_makefile(Parameters p) {

 	//First, let's make a realmake object
	realmake_base rm(p.a_source);
	
	//Set whether the program should sound out everything it's doing
	rm.set_verbose(p.a_verbose);
	
	//Set the name of the final executable
	rm.set_name(p.a_name);

	//Set whether the program should keep the makefile or delete it
	rm.set_k_makef(p.k_makef);

	//Set the compiler to use
	rm.set_comp(p.comp);

	//Set the make utility to use
	rm.set_m_util(p.m_util);
	
	//Set the flags to use with the compiler
	rm.set_flags(p.n_flags);

	//Next, we need to find out what programming language to use
	int rc = 0;
	if(rm.get_verbose())
	 cout << "Checking programming language..." << endl;
	rm.set_lang(match_lang(p.a_lang));
	rc = rm.deduce_lang();
	if(STATUS_OK != rc)
	 return rc;

	//Now, let's create the actual makefile
	if(0 == match_lang(rm.get_lang()).compare(c_lang)) {
	 rc = 0;
	 if(rm.get_verbose())
	  cout << "Generating a C makefile..." << endl;
	 realmake_c rm_c(rm); 
	 rc = rm_c.output_makefile();
	 if(STATUS_OK != rc)
	  return rc;
	 rc = rm_c.execute_makef();
	 if(STATUS_OK != rc)
	  return rc;
	}
	else if(0 == match_lang(rm.get_lang()).compare(cpp_lang_1)) {
	 rc = 0;
	 if(rm.get_verbose())
	  cout << "Generating a C++ makefile..." << endl;
	 realmake_cpp rm_cpp(rm);
	 rc = rm_cpp.output_makefile();
	 if(STATUS_OK != rc)
	  return rc;
	 rc = rm_cpp.execute_makef();
	 if(STATUS_OK != rc)
	  return rc;
	}
	else if(0 == match_lang(rm.get_lang()).compare(java_lang)) {rc = 0;
	 if(rm.get_verbose())
	  cout << "Generating a Java makefile..." << endl;
	 realmake_java rm_java(rm);
	 rc = rm_java.output_makefile();
	 if(STATUS_OK != rc)
	  return rc;
	 rc = rm_java.execute_makef();
	 if(STATUS_OK != rc)
	  return rc;
	}

	return STATUS_OK;
 }
 
 int main(int argc, char* argv[]) {
 	
 	//First, get the parameters from the user
 	Parameters p = {"","","",false}; int status;
 	status = get_params(argc,argv,p);
 	if(STATUS_OK != status)
 	 return status;

	//Next, use the parameters to create and execute a Makefile
	status = run_makefile(p);
	if(STATUS_OK != status)
	 return status;
 	
 	return STATUS_OK;
 } 
