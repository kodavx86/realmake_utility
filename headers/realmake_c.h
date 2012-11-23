/*
 * This is the header file for the realmake_c.cpp file. Constants and
 * function headers for realmake_c.cpp should go here.
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
 
 #ifndef REALMAKE_C_H
 #define REALMAKE_C_H
 
 #include "realmake_base.h"

 const std::string GCC = "gcc";
 
 class realmake_c : public realmake_base {
 	
 	private:
 
 		realmake_c();		//Make the default constructor private
 		
 	public:
 		//constructors
 		realmake_c(realmake_base &rb);
 		
 		//destructors
 		~realmake_c();
 		
 		//special methods
 		int output_makefile();
 		int execute_makef();
 };
 
 #endif
