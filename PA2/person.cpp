
#include "person.h"

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    // TODO: complete the method!
    delete phone;
    delete email;
}


Person::Person(string fname, string lname, string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);
   
    string EmT,EmA,PhT,PhN;

    EmT = email.substr(1,email.find(')')-1);
    EmA = email.substr(email.find(',')+2);
    PhT = phone.substr(1,phone.find(')')-1);
    PhN = phone.substr(phone.find(',')+2);

    this->email = new Email(EmT,EmA);
    this->phone = new Phone(PhT,PhN);
    
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    std::getline (std::cin,type);

    cout << "Email address: ";
    // code here
    std::getline (std::cin,temp);
    email = new Email(type,temp);

    cout << "Type of phone number: ";
    // code here
    std::getline (std::cin,type);

    cout << "Phone number: ";
    // code here
    std::getline (std::cin,temp);

    // code here
    phone = new Phone(type,temp);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream infile;
    infile.open(filename.c_str());
    
    string temp;
    string type;
    string eadr;
    string pnum;
    
    std::getline(infile,temp);
    f_name = temp;
    std::getline(infile,temp);
    l_name = temp;

    std::getline(infile,temp);
    birthdate = new Date(temp);

    std::getline(infile,temp);
    type = temp.substr(1,temp.find(')')-1);
    pnum = temp.substr(temp.find(')')+2);
    phone = new Phone(type,pnum);
    
    std::getline(infile,temp);
    type = temp.substr(1,temp.find(')')-1);
    eadr = temp.substr(temp.find(')')+2);
    email = new Email(type,eadr);

    infile.close();

}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)

    if ( (f_name == rhs.f_name) && (l_name == rhs.l_name) )
      return true;
    else 
      return false;
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    for(int i=0; i<friends.size(); i++)
    {
        cout << friends[i] << endl;
    }
}

void Person::addFriend(Person* newFriend){

    friends.push_back(newFriend);
}

void Person::save_person(ofstream &outfile){

    outfile.open("personlist.txt");
    outfile << l_name <<", " << f_name << endl;
    //outfile << birthdate->print_date("Month D, YYYY");
    //outfile << email->print();
    //outfile << phone->print();
    for(int i=0; i<friends.size(); i++)
    {
        outfile << friends[i] << endl;
    }
    outfile.close();
}