#include <bits/stdc++.h>
using namespace std;

class bookdatas {
   public:
    string book_code, book_name, subject_name, Author_name;
    int quantity;
};

class borrowBookData {
   public:
    string stid, book_code;
};

class Student
{
    private:
    string book_name, book_code, subject_name, Author_name, stname, stid;
    int quantity;

   public:
    void STUDENT_PANEL();
    void DISPLAY_BOOK();
    void BORROW_BOOK();
    void RETURN_BOOK();
    void st_authentication();
};

void Student:: st_authentication()
{
    int i,f=3;
    string username,pass;
        Here:
        cout<< "Enter Username: ";
        cin>> username;
        cout<<"Enter Password: ";
        cin>> pass;

        ifstream file("student.txt");
        string name,passw;
        int flag = 1;
        while(file >> stname)
        {
            file >> stid;

            if(username == stname && pass == stid)
            {
                flag = 0;
                cout << endl;
                cout << "Welcome " << username << endl;
                STUDENT_PANEL();
            }

        }
        if(flag)
        {
                for(i=2; i>0; i--)
                {
                    cout<<"Wrong username or Password!"<<endl<<endl;
                    if(f!=1)
                    {
                        cout<< "Try Again!"<<endl<<endl;
                    }
                    f-=1;
                    cout<<"You Have "<< f <<" Attempts Left!"<<endl<<endl;
                    cin.ignore();
                    if(f==0)
                    {
                        cout<< "Authentication Failed! Please Run The Program Again!"<<endl;
                        break;
                    }
                    goto Here;
                }
        }
        file.close();
}

void Student :: STUDENT_PANEL()
{
    int option2;
    menustart:

    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t------------ STUDENT PANEL -----------" << endl;
    cout << "\t\t\t--------------------------------------" << endl;
    cout << "\t\t\t\t 1.DISPLAY BOOK" << endl;
    cout << "\t\t\t\t 2.BORROWED BOOK" << endl;
    cout << "\t\t\t\t 3.RETURNED BOOK" << endl;
    cout << "\t\t\t\t 4.LOG OUT" << endl;
    cout << "\n";
    cout << "\t\t\t---------------------------------" << endl;
    cout << "[CHOOSE YOUR OPTION FROM 1 to 4]" << endl;
    cout << "\n";
    cout << "\t\t\t---------------------------------" << endl;
    cout << "CHOOSE YOUR OPTION : " << endl;

    cin >> option2;

    switch(option2)
    {
        case 1:
        {
            char a;
            DISPLAY_BOOK();
            cout << "Press any key character to continue to admin menu" << endl;
            cin >> a;
            goto menustart;
        }
        case 2:
        {
            char a;
            BORROW_BOOK();
            cout << "Press any key character to continue to admin menu" << endl;
            cin >> a;
            goto menustart;
        }
        case 3:
        {
            char a;
            RETURN_BOOK();
            cout << "Press any key character to continue to admin menu" << endl;
            cin >> a;
            goto menustart;
        }
        case 4:
            break;

        default:
            cout << "you have enter the wrong code please choose between 1 to 2" << endl;
            break;
    }
}
void Student :: DISPLAY_BOOK()
{
    fstream file;
    int book_no;

    cout << "\t\t\t--| These are the Book available at that moment |--";
    cout << "\n";

    file.open("book.txt", ios :: in);
    while(file >> book_code)
    {
        file >> book_name;
        file >> subject_name;
        file >> Author_name;
        file >> book_no;

        cout << "Book ID: " << book_code << endl;
        cout << "Book Name: " << book_name << endl;
        cout << "Subject Name: " << subject_name << endl;
        cout << "Author Name: " << Author_name << endl;
        cout << "Books Available: " << book_no << endl;
        cout << "\n";
    }
    file.close();
}

void Student ::BORROW_BOOK() {
    string book_ID;
    vector<bookdatas> book_details;
    int flag = 0;
    cout << "Enter Book ID";
    cout << "\n";
    cin >> book_ID;

    fstream file;
    file.open("book.txt", ios ::in);
    while (file >> book_code) {
        file.ignore();
        getline(file, book_name);
        getline(file, subject_name);
        getline(file, Author_name);
        file >> quantity;
        bookdatas temp_book_data;
        temp_book_data.book_code = book_code;
        temp_book_data.book_name = book_name;
        temp_book_data.subject_name = subject_name;
        temp_book_data.Author_name = Author_name;
        temp_book_data.quantity = quantity;
        book_details.push_back(temp_book_data);
    }
    file.close();

    fstream file2;
    file2.open("book.txt", ios ::out);
    for (int i = 0; i < book_details.size(); i++) {
        if (book_ID == book_details[i].book_code) {
            flag = 1;
            file2 << book_details[i].book_code << endl;
            file2 << book_details[i].book_name << endl;
            file2 << book_details[i].subject_name << endl;
            file2 << book_details[i].Author_name << endl;
            if (book_details[i].quantity == 0) {
                flag = 0;
                file2 << book_details[i].quantity << endl;
            } else {
                file2 << (book_details[i].quantity - 1) << endl;
            }
        } else {
            file2 << book_details[i].book_code << endl;
            file2 << book_details[i].book_name << endl;
            file2 << book_details[i].subject_name << endl;
            file2 << book_details[i].Author_name << endl;
            file2 << book_details[i].quantity << endl;
        }
    }
    file2.close();

    if (flag) {
        fstream file;
        file.open("BorrowBook.txt", ios ::app | ios ::out);
        file << stid << endl;
        file << book_code << endl;
        file.close();
    } else {
        cout << " No book available" << endl;
    }
}

void Student ::RETURN_BOOK() {
    string book_ID, ST_ID;
    int flag = 0;

    cout << "Enter Book ID";
    cout << "\n";
    cin >> book_ID;

    fstream file;
    file.open("BorrowBook.txt", ios ::in);
    while (file >> ST_ID) {
        file.ignore();
        getline(file, book_code);

        if (ST_ID == stid && book_code == book_ID) {
            flag = 1;
            break;
        }
    }
    file.close();

    if (flag) {
        vector<borrowBookData> borrow_Book_Data;
        fstream file0;
        file0.open("BorrowBook.txt", ios ::in);
        while (file0 >> ST_ID) {
            file0.ignore();
            getline(file0, book_code);

            borrowBookData temp_borrow_Book_Data;
            temp_borrow_Book_Data.stid = ST_ID;
            temp_borrow_Book_Data.book_code = book_code;
            borrow_Book_Data.push_back(temp_borrow_Book_Data);
        }
        file0.close();

        fstream file2;
        file2.open("BorrowBook.txt", ios ::out);
        for (int i = 0; i < borrow_Book_Data.size(); i++) {
            if (stid != borrow_Book_Data[i].stid) {
                file2 << borrow_Book_Data[i].stid << endl;
                file2 << borrow_Book_Data[i].book_code << endl;
            } else {
                if (book_ID != borrow_Book_Data[i].book_code) {
                    file2 << borrow_Book_Data[i].stid << endl;
                    file2 << borrow_Book_Data[i].book_code << endl;
                }
            }
        }
        file2.close();

        fstream file3;
        file3.open("book.txt", ios ::in);
        vector<bookdatas> book_details;
        while (file3 >> book_code) {
            file3.ignore();
            getline(file3, book_name);
            getline(file3, subject_name);
            getline(file3, Author_name);
            file3 >> quantity;
            bookdatas temp_book_data;
            temp_book_data.book_code = book_code;
            temp_book_data.book_name = book_name;
            temp_book_data.subject_name = subject_name;
            temp_book_data.Author_name = Author_name;
            temp_book_data.quantity = quantity;
            book_details.push_back(temp_book_data);
        }
        file3.close();

        fstream file4;
        file4.open("book.txt", ios ::out);
        for (int i = 0; i < book_details.size(); i++) {
            if (book_ID == book_details[i].book_code) {
                file4 << book_details[i].book_code << endl;
                file4 << book_details[i].book_name << endl;
                file4 << book_details[i].subject_name << endl;
                file4 << book_details[i].Author_name << endl;
                file4 << (book_details[i].quantity + 1) << endl;
            } else {
                file4 << book_details[i].book_code << endl;
                file4 << book_details[i].book_name << endl;
                file4 << book_details[i].subject_name << endl;
                file4 << book_details[i].Author_name << endl;
                file4 << book_details[i].quantity << endl;
            }
        }
        file4.close();
    }
}
