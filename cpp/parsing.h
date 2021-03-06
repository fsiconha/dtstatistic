
#ifndef parsing
#define parsing

#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

void parse(int argc , char * argv[] , std::string *label_name , std::string *path_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clustering, bool *print_help);
void fprint_help();

#endif