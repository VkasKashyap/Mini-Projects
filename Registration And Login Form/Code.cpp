#include<iostream> 
#include<fstream>  
#include<string>    
#include<limits>   

using namespace std;

class temp {
    string Username, Password, Email;
    string searchName, searchPassword, searchEmail;
    fstream file; 
public:
    void Login();
    void SignUp();
    void ForgotPassword();
} obj; 

int main() {
    char choice;
    cout << "\n1- Login";
    cout << "\n2- Sign-Up";
    cout << "\n3- Forgot Password";
    cout << "\n4- Exit";
    cout << "\nEnter Your Choice : ";
    cin >> choice; 

    // IMPORTANT!! this line fixes the bug where it skips asking for username
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // switch to check what the user picked
    switch (choice) {
    case '1':
        obj.Login(); // call login function
        break;
    case '2':
        obj.SignUp(); // call signup function
        break;
    case '3':
        obj.ForgotPassword(); // call forgot password function
        break;
    case '4':
        return 0; // exit the program
        break;
    default:
        cout << "Invalid Selection !!!.....";
    }
    return 0;
}

// function to sign up a new user
void temp::SignUp() {
    // asking for details
    cout << "\nEnter Your User Name :: ";
    getline(cin, Username);
    cout << "Enter Your Email Address :: ";
    getline(cin, Email);
    cout << "Enter Your Password :: ";
    getline(cin, Password);

    // open file to write in it
    file.open("loginData.txt", ios::out | ios::app);
    // putting the username, email, and password into the file
    file << Username << "*" << Email << "*" << Password << endl;
    file.close(); // always close the file
    cout << "\nSign-Up Successful!" << endl;
}

// function to login
void temp::Login() {
    cout << "----------Login----------" << endl;
    cout << "Enter Your User Name :: ";
    getline(cin, searchName); // get the username they type
    cout << "Enter Your Password :: ";
    getline(cin, searchPassword); // get the password

    // open file to read from it
    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error: Data file not found." << endl;
        return;
    }

    bool found = false; // check if user is found or not

    // this loop reads the file line by line
    while (getline(file, Username, '*') && getline(file, Email, '*') && getline(file, Password, '\n')) {
        // if the name from the file matches what the user typed
        if (Username == searchName) {
            found = true;
            // if the password also matches
            if (Password == searchPassword) {
                cout << "\nAccount Login Successful!" << endl;
                cout << "Username :: " << Username << endl;
                cout << "Email :: " << Email << endl;
            } else {
                cout << "\nPassword Is Incorrect." << endl;
            }
            break; // stop searching
        }
    }

    file.close();

    // if after the whole loop, user was not found
    if (!found) {
        cout << "\nUsername not found." << endl;
    }
}

// for when the user forgets their password
void temp::ForgotPassword() {
    cout << "\n----------Forgot Password----------" << endl;
    cout << "Enter Your Username :: ";
    getline(cin, searchName);
    cout << "Enter Your Email :: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in); // open file to read
    if (!file.is_open()) {
        cout << "Error: Data file not found." << endl;
        return;
    }

    bool found = false; // check if we find the account

    // another loop to read the file
    while (getline(file, Username, '*') && getline(file, Email, '*') && getline(file, Password, '\n')) {
        // if username and email both match
        if (Username == searchName && Email == searchEmail) {
            found = true;
            cout << "\nAccount Found!" << endl;
            cout << "Your Password is :: " << Password << endl; // show the password
            break; // found it, so stop the loop
        }
    }
    
    file.close();

    // if the account was never found
    if (!found) {
        cout << "\nAccount not found with the given credentials." << endl;
    }
}