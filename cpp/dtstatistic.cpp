#include <iostream>
#include <vector>
#include <cstdlib>
#include "directory.h"
#include "parsing.h"
#include "molecule.h"
#include "sort.h"
#include "clustering.h"
#include "log.h"
/***********************************************************************************
									GLOBAL VARIABLES
***********************************************************************************/
std::string label_name="";
std::string path_name="";
std::string output_name="dtstatistic.log";
int nruns=1;
unsigned int number_of_ligands=1;
float rmsd_clustering=2.0;
bool analysis_by_total_energy=true;
bool analysis_by_internal_energy=false;
bool print_help=false;
std::vector<std::string>  log_files;
std::vector<std::string>  pdb_files;
std::vector<molecule*> *leaders;
std::vector<molecule*> *molecules;
DIR * dir=NULL;
/**********************************************************************************/



int main(int argc, char * argv[])
{
	/* 
		Parsing input command
	*/
	parse(argc, argv, &label_name, &path_name, &output_name, &number_of_ligands, &analysis_by_total_energy, &analysis_by_internal_energy, &rmsd_clustering,&print_help);

	
	/* 
		Check and open directory in -d flag
	*/
	if(path_name.empty()) // If is path_name is empty opens "." directory
		path_name=".";
	dir=check_directory(path_name.c_str());
	
	
	/*
		Select available files set in -l flag or all .log files in the directory opened
	*/
	list_directory(dir,label_name, &log_files, &pdb_files);
	nruns=pdb_files.size();


	/*
		Change to the path set in -d flag
	*/
	chdir(path_name.c_str());					 
	

	/*
		Create a vector of all molecules set in -d flag and -l flag
	*/
	molecules=create_molecule_vector(log_files);

	/*
	*	Sorting molecules by energy
	*/
	sort_molecule(molecules,analysis_by_total_energy);

	/*
	*   Clustering leaders
	*/
	leaders = clustering(*molecules , rmsd_clustering);

	/*
	*	Logging leader in output file
	*/
	write_output_clustering(*leaders, output_name, number_of_ligands);

	// for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// {
	// 	std::cout<<"Total energy: "<<(*it)->get_total_energy()<<std::endl;

	// 	for(std::vector<atom*>::iterator it1 = (*it)->atom_list.begin(); it1 !=  (*it)->atom_list.end(); it1++)
	// 	{
	// 	 	std::cout<< (*it1)->get_type() << ":"<< (*it1)->get_x()<< " "<< (*it1)->get_y()<< " " << (*it1)->get_z() << std::endl;
	// 	}
		
	// }		
	// sort_molecule(molecules,analysis_by_total_energy);
	// for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// {
	// 	std::cout<<"Total energy depois: "<<(*it)->get_total_energy()<<std::endl;
	// }		


}


































	// if(analysis_by_total_energy)	
	// {
	// 	for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// 	{
	// 		std::cout<<"Total energy: "<<(*it)->get_total_energy()<<std::endl;
	// 	}	
	// 	sort_vector(molecules,analysis_by_total_energy);

	// 	for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// 	{
	// 		std::cout<<(*it)->get_total_energy()<<std::endl;
	// 	}	
	// }
	// else
	// {
	// 	for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// 	{
	// 		std::cout<<"Internal energy: "<<(*it)->get_interaction_energy()<<std::endl;
	// 	}	
	// 	sort_vector(molecules,analysis_by_total_energy);

	// 	for (std::vector<molecule*>::iterator it = molecules->begin(); it !=  molecules->end(); it++)
	// 	{
	// 		std::cout<<(*it)->get_interaction_energy()<<std::endl;
	// 	}	
	// }
	
