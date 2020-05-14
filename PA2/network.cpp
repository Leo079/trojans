
#include "network.h"
#include <limits>
#include "misc.h"
#include "person.h"
#include <fstream>
#include <list> 
#include <dirent.h> // directory+entry

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    this-> loadDB(fileName);
}

Network::~Network(){
    // TODO: Complete this method
    // Destructure delete all the Person
    while(head != NULL){
      Person* temp = head;
      delete temp;
      head = head -> next;
    }
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // TODO: Complete this method!
    // Adds a new Person (newEntry) to the back of LL
    newEntry->prev = tail;
    newEntry->next = NULL;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    
    tail = newEntry;
    count++;
}


void Network::printDB(){
    // Don't change this method
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of persons: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // TODO: Complete this method!
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.db as a template
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    // now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2.

    ofstream outfile;
    outfile.open(filename.c_str());
    Person *hh = head; 
    
    while(hh!= NULL)
    {
      outfile << hh->f_name << ", " << hh->l_name << endl;
      outfile << hh->birthdate->get_date() << endl;
      outfile << hh-> email -> get_contact() << endl;
      outfile << hh-> phone -> get_contact() << endl;
      outfile << "------------------" << endl;
      hh = hh -> next;
      
    }

    outfile.close();
}


void Network::loadDB(string filename){
    // TODO: Complete this method!
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
    Person* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate;
    
    // TODO: Decalre other vairiable if needed
    string email, phone;

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        // TODO: read email and phone
        getline(infile,email);
        getline(infile,phone);
        // this line is to read the dash line
        getline(infile, buff);
        // TODO: use the constructor Person::Person(fname, lname, bdate, email, phone) to modify the following line
        Person* newEntry = new Person(fname, lname, bdate, email, phone);
        
        this->push_back(newEntry);
    }
}

Person* Network::search(string fname, string lname, string bdate){
    // TODO: Complete this method!
    // Search the Network for the given fname, lname, bdate
    // You may create a new person, say searchEntry, with fname, lname and bdate. Think about what Person constructor will be helpful with these arguments.
    // And use == overloaded operator between two persons
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.
    Person* pointer = head;
    while (pointer != NULL){
       if((pointer -> f_name == fname) && (pointer -> l_name == lname))
       {
           return pointer;
       }
       else{
           pointer = pointer->next;
       }
    }
    return NULL;
}

Person* Network::search(string queryid){

    string id;
    Person* pointer = head;
    while (pointer != NULL){
        id = IDName(pointer -> f_name, pointer -> l_name);
        if(id.compare(queryid) == 0)
        {
            return pointer;
        }
        else
        {
            pointer = pointer->next;
        }
    }
    return NULL;

    }

bool Network::remove(string fname, string lname, string bdate){
    // TODO: Complete this method! Follow these steps:
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!

    Person* ppl = search(fname, lname, bdate);

    if (ppl == NULL){
      return false;
    }
    else if (ppl -> prev == NULL){
      ppl -> next == NULL;
      count--;
      delete ppl;
      return true;
    }
    else if (ppl -> next == NULL){
      ppl -> next == NULL;
      count--;
      delete ppl;
      return true;
    }
    else{
      ppl -> prev -> next = ppl -> next;
      ppl -> next -> prev = ppl -> prev;
      count--;
      delete ppl;
      return true;
    }

}

void Network::friends_recommendation(int k)
{
    /*bool *visited = new bool[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Create a queue for BFS 
    list<int> queue; 
  
    // Mark the current node as visited and enqueue it 
    visited[s] = true; 
    queue.push_back(s); 
  
    // 'i' will be used to get all adjacent 
    // vertices of a vertex 
    list<int>::iterator i; 
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        cout << s << " "; 
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    }*/
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Load network database \n";
        cout << "2. Save network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Search \n";
        cout << "5. Remove a person \n";
        cout << "6. Print database \n";
        cout << "7. Add friends \n";
        cout << "8. Friends Recommendation \n";
        
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp

            string dirname[5];

            for(int d=0; d<2; d++)
            {

            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            int l=0;
            if ((dir = opendir ("./")) != NULL) {
                while ((ent = readdir (dir)) != NULL) {
                    if(strstr(ent->d_name, ".db") != NULL){
                        dirname[l] = ent -> d_name;
                        l++;
                        cout << ent->d_name << endl;
                    }
                }
                closedir (dir);
            } 
            else {
                /* could not open directory */
                perror ("No directory!");
                //return 1;
            }
            
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            int flag=0;

            for(int h=0; h<l; h++)
            {
                if(fileName == dirname[h])
                {
                    flag = 1;
                    break;
                }
            }
            // If file with name FILENAME does not exist: 
            if(flag == 0){
            cout << "File FILENAME does not exist!" << endl;
            }
            // If file is loaded successfully, also print the count of person in it: 
            else if(flag == 1){
               loadDB(fileName);
               cout << "Network loaded from " << fileName << " with " << count << " person \n";
            }
            } 
            
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Saving network database \n";
            ifstream infile;
            infile.open("personlist.txt");
            while(infile >> fileName)
            {
                saveDB(fileName);
                cout << "Network saved in " << fileName << endl;
            }
            //cout << "Enter the name of the save file: ";
            //std::getline(std::cin,fileName);
            
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new person ONLY if it does not exists!
            cout << "Adding a new person \n";
            Person* newEntry = new Person();
            this->push_front(newEntry);
        }
        else if (opt == 4){
            // TODO: Complete me!
            string fname, lname, bdate;

            cout << "Searching: \n";
            cout << "First Name: ";
            std::getline(std::cin, fname);
            cout << "Last Name: ";
            std::getline(std::cin, lname);
            cout << "Birthdate (M/D/YYYY): ";
            std::getline(std::cin, bdate);
            Person* ptr = search(fname, lname, bdate);
            // if found: print person's firstname, lastname, bdate, email, phone using print_person()
            if(ptr != NULL)
            {
               ptr -> print_person();
            }
            else
            {
            cout << "Not found! \n";
            }
            // if not, cout << "Not found! \n";
            
        }
        else if (opt==5){
            // TODO: Complete me!
            string fname, lname, bdate;

            cout << "Removing a person \n";
            cout << "First Name: ";
            std::getline(std::cin, fname);
            cout << "Last Name: ";
            std::getline(std::cin, lname);
            cout << "Birthdate (M/D/YYYY): ";
            std::getline(std::cin, bdate);
            Person* ptr = search(fname, lname, bdate);
            // if found, cout << "Remove Successful! \n";
            if(remove(fname,lname,bdate))
            {
               cout << "Remove Successful! \n";
            }
            else
            {
            cout << "Person not found! \n";
            }
            // if not found: cout << "Person not found! \n";
        }
        else if (opt==6){
            // TODO: Complete me!
            cout << "Network Database: \n";
            cout << "Network Database: \n";
            this->printDB();
        }
        else if (opt==7){
            string fid, sid;
            
            cout << "Add friends \n";
            cout << "What is id of first person? \n";
            cin >> fid;

            Person* first = search(fid);
            if (first != NULL)
            {
                cout << "What is id of second person? \n";
                cin >> sid;
                Person* second = search(sid);
                if (second != NULL)
                {
                    Person* pointer = head;
                    while (pointer != NULL){
                        if(pointer == first)
                        {
                            pointer->addFriend(second);
                        }
                        else if(pointer == second)
                        {
                            pointer->addFriend(first);
                        }
                        else
                        {
                            pointer = pointer -> next;
                        }
                    }
                }
            }
            else
            {
                cout << "Person not found \n";
            }


        }
        else if (opt==8)
        {
            cout << "Friends Recommendation for: ";
            

        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


