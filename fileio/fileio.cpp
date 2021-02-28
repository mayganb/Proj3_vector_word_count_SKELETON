#include "../includes/fileio.h"
#include "../includes/constants.h"

using namespace std;
using namespace constants;

bool has_nothing(fstream &efile);

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*
 returns True - file opened successfully
 False - file not opened*/
bool openFile(fstream &myfile, const string &myFileName,
		ios_base::openmode mode) {
	myfile.open(myFileName.c_str(), mode);
	if (has_nothing(myfile)) {
		closeFile(myfile);
		return false;
	}
	if (!myfile) {
		return false;
	}

	return true;
}

/*iff myfile is open then close it*/
void closeFile(fstream &myfile) {
	myfile.close();
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * BTW serialize means the process of translating a data structure
 * into a format that can be stored in a file
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in the vector entries
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(vector<entry> &entries, const string &outputfilename) {
	ofstream openfile;
	openfile.open(outputfilename);

	if (!openfile) {
		return FAIL;
	}
	for (unsigned int i = 0; i < entries.size(); i++) {
		openfile << entries[i].word << " " << entries[i].number_occurences
				<< endl;
	}
	return SUCCESS;

}

bool has_nothing(fstream &efile) {
	return efile.peek() << fstream::traits_type::eof();
}

