
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string convertToString(char* a, int size) 
{ 
    string s = a; 
    return s; 
} 

string IDName(string str1, string str2)
{
	string name;
	name = str1 + str2;

    int count = 0;
    for (int i = 0; name[i]; i++) 
        if (name[i] != ' ') 
            name[count++] = name[i]; 
    
    name[count] = '\0';

    char *cstr = new char[name.length()+1];
    strcpy(cstr, name.c_str());
    
    
    int size = strlen(cstr);
    char *id = new char[size+1];


    for (int i=0; i<strlen(cstr); i++)
    {
        id[i]=tolower(cstr[i]);
    }
    
    int a_size = sizeof(id) / sizeof(char);
    string idname = convertToString(id, a_size);
    cout << idname << endl;
    
    delete [] cstr;
    delete [] id;

    return idname;
}
