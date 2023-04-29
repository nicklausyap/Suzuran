// Date created: 28-APR-2023 FRIDAY
// csv_to_suzuran.cpp
// convert csv file to Suzuran file format
// This source file is part of the Suzuran open source project
// Copyright (c) 2023 nicklaus yap ken yik
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // for memcpy
#include <cstdlib> // for exit()
#include <cstdio>
using namespace std;

// structure to hold the csv header column
struct csv_header{
    char *value;
    csv_header* next;
};

//structure to hold the csv row
struct csv_row{
char *value;
csv_row* next;
int col; // indicate column position
unsigned long row; // indicate row position or line number
};

// make a global variable csv_header
struct csv_header *head = NULL;
// make a global variable csv_row
struct csv_row *rowhead = NULL;

///////////////////////////////////////////////////
// rewriter part
///////////////////////////////////////////////////

void displayCSVrow_reverse()
{
    struct csv_row *var;
     var=rowhead;
     printf("list of elements: \n");
     while(var!=NULL)
     {
          cout << var->value << "\n";
          var=var->next;
     }
}

void reverseCSVrow_llist()
{
    struct csv_row *temp,*temp1,*var;
     temp=rowhead;
     var=NULL;
     while(temp!=NULL)
     {
          temp1=var;
          var=temp;
          temp=temp->next;
          var->next=temp1;
     }
     rowhead=var;
}

void CSVrow_inFile()
{
    struct csv_row *var1;
    var1=rowhead;
    // set to -1 to indicate the first encounter with the csv row. The initial state must be -1
    int previousNum = -1;
    ofstream row_suzuranfile;
    row_suzuranfile.open("test.szd", ios::app);
    if (row_suzuranfile.is_open()) { 
    while(var1!=NULL)
     {
        if(var1==NULL){
            break;
        }

        if(previousNum == -1){
            previousNum = var1->row;
            row_suzuranfile << var1->value << "\n";
            var1=var1->next;
        }else if((previousNum != var1->row) && (previousNum != -1)){
            previousNum = var1->row;
            row_suzuranfile << "</data>" << "\n";
            row_suzuranfile << "<data>" << "\n";
            row_suzuranfile << var1->value << "\n";
            var1=var1->next;
        }else{
          row_suzuranfile << var1->value << "\n";
          var1=var1->next;
        }
     }

    }else{
        cout << "error in CSVrow_inFile\n";
        exit(EXIT_FAILURE);
    }
    row_suzuranfile.close();
    
}

void CSVheader_inFile(struct csv_header* head)
{
    ofstream suzuranfile;
    suzuranfile.open("test.szd", ios::app);
    if (suzuranfile.is_open()) { 
        // Base case 
        if (head == NULL){
        suzuranfile.close();
        return;
        }
        // print the list after head node
        CSVheader_inFile(head->next);
 
        // After everything else is printed, print head
        suzuranfile << "any " << head->value << "\n";
    }
    suzuranfile.close();
    
}

void writeDataValue()
{
    // write first <data> tag
    ofstream suzuranfiledatatag;
    suzuranfiledatatag.open("test.szd", ios::app);
    if (suzuranfiledatatag.is_open()) { 
        suzuranfiledatatag << "<data>\n";
    }else{
        // failed to open file
        cout << "writeDataValue() has error\n";
        exit(EXIT_FAILURE);
    }
    suzuranfiledatatag.close();
    CSVrow_inFile();
    // Open the file again for append and check if the file can open. Write last <data> tag
    suzuranfiledatatag.open("test.szd", ios::app);
    if (suzuranfiledatatag.is_open()) { 
        suzuranfiledatatag << "</data>\n";
    }else{
        // failed to open file
        cout << "writeDataValue() has error\n";
        exit(EXIT_FAILURE);
    }
    suzuranfiledatatag.close();
}

void writeDataStructure()
{ 
    CSVheader_inFile(head);
}

void writeSuzuranType()
{
    ofstream suzuranfiletypetag;
    suzuranfiletypetag.open("test.szd", ios::app);
    suzuranfiletypetag << "<type1>\n";
    suzuranfiletypetag.close();
}
///////////////////////////////////////////////////
// end of rewriter part
///////////////////////////////////////////////////

// check if file exist then remove the file
void is_file_exist_remove(const char *fileName)
{
    ifstream infile(fileName);
    if(infile.good()){
        remove(fileName);
    }else{
        // do nothing
    }
    infile.close();
}

void printCSVrow_llist()
{
    struct csv_row *ptr = (struct csv_row*)malloc(sizeof(struct csv_row));
    ptr = rowhead;
    cout<<"The linked list: \n";
    while (ptr != NULL)
    {
        cout<<ptr->value<<"\n";
        cout<<"column number: " << ptr->col << " ";
        cout<<"row number: " << ptr->row <<"\n";
        ptr = ptr->next;
    }
}

// just for debug purpose to check if linked list for csv_header is correct
void printCSVheader_llist()
{
    struct csv_header *ptr = (struct csv_header*)malloc(sizeof(struct csv_header));
    ptr = head;
    cout<<"The linked list: \n";
    while (ptr != NULL)
    {
        cout<<ptr->value<<"\n";
        ptr = ptr->next;
    }
}

void processCSV_row(string inp, int ln)
{
unsigned long line = ln;
// if line equal to 1 that mean is line 2. ln equal to 0 mean is csv header. Row numbering start from 0 but line numbering is start from 1
line = line + 1;
// put the function string inp inside local variable string input
string input = inp;
char *buffer = (char*)malloc((input.length() + 2));
if (buffer == NULL) {
    exit(EXIT_FAILURE);
}
int num = 0; // buffer length
int colm = 1; // column number
int inQuote = 0; // if inside quote do not parse when found comma

for(int a=0;a<input.length();){

    if(inQuote == 1){

        if(input[a] != 34){
            buffer[num] = input[a];
            num++;
            a++;
        }else{
            inQuote = 0;
            buffer[num] = input[a];
            cout<<"we going out of quote from here\n";
            num++;
            a++;
        }
    }
    else if(input[a] == 34){ // 34 mean double quote
        if(inQuote == 1){
            // mean already exit out of string quote and can process like normal
            inQuote = 0;
            buffer[num] = input[a];
            cout<<"we going out of quote\n";
            num++;
            a++;
        }else{
        cout<<"we inside quote from here\n";
        // store in buffer while still in string quote
        inQuote = 1;
        buffer[num] = input[a];
        num++;
        a++;
        }

    }
    else if(input[a] != ',' && inQuote == 0){
	buffer[num] = input[a];
	//cout << buffer[num];
	num++;
	a++;
	}else if ((input[a] == ',') && (inQuote == 0)) {
        // create a temporary csv_header struct to hold the value
        struct csv_row* temp = (struct csv_row*)malloc(sizeof(struct csv_row));
        // failed to malloc struct csv_header for temp 
        if (temp == NULL) {
            cout << "failed";
            exit(EXIT_FAILURE);
        }
        // malloc char value in temp based on the length of num
        temp->value = (char*)malloc(num + 1);
        // exit program when failure to malloc temp->value
        if (temp->value == NULL) {
            cout << "failed";
            exit(EXIT_FAILURE);
        }
        // set temp value with null
        memset(temp->value, '\0', num+1);
        // copy each char in buffer to char value in temp
        for (int b = 0;b < num;) {
            temp->value[b] = buffer[b];
            b++;
        }

        temp->col = colm;
        temp->row = line;
            
        // point it to old first node
        temp->next = rowhead;

        //point first to new first node
        rowhead = temp;
        
        // update the column number position in the local variable
        colm++;
        a++;
        // reset num back to 0
        num = 0;
        // clear string buffer
        memset(buffer, '\0', (input.length()+1));
    }
	
	
}

struct csv_row* temp3 = (struct csv_row*)malloc(sizeof(struct csv_row));
// failed to malloc struct csv_row for temp3
if (temp3 == NULL) {
cout << "failed";
exit(EXIT_FAILURE);
}
temp3->value = (char*)malloc(strlen(buffer) + 1);
// exit program when failure to malloc temp3->value
if (temp3->value == NULL) {
cout << "failed";
exit(EXIT_FAILURE);
}
    // handle last csv row not being parsed cause not find comma
    for(int t=0;t<strlen(buffer);){
        temp3->value[t] = buffer[t];
        t++;
    }

    // update the csv row linked list of the column number and line number
    temp3->col = colm+1;
    temp3->row = line;
    // point it to old first node
    temp3->next = rowhead;

    //point first to new first node
    rowhead = temp3;

    // clear string buffer
    memset(buffer, '\0', (input.length()+1));
}

void processCSV_header(string inp)
{
// put the function string inp inside local variable string input
string input = inp;
char *buffer = (char*)malloc((input.length() + 2));
if (buffer == NULL) {
    exit(EXIT_FAILURE);
}
int num = 0; // buffer length
int count = 0;

for(int a=0;a<input.length();){
	if(input[a] != ','){
	buffer[num] = input[a];
	//cout << buffer[num];
	num++;
	a++;
	}else if (input[a] == ',') {
        // create a temporary csv_header struct to hold the value
        struct csv_header* temp = (struct csv_header*)malloc(sizeof(struct csv_header));
        // failed to malloc struct csv_header for temp 
        if (temp == NULL) {
            cout << "failed";
            exit(EXIT_FAILURE);
        }
        // malloc char value in temp based on the length of num
        temp->value = (char*)malloc(num + 1);
        // exit program when failure to malloc temp->value
        if (temp->value == NULL) {
            cout << "failed";
            exit(EXIT_FAILURE);
        }
        // set temp value with null
        memset(temp->value, '\0', num+1);
        // copy each char in buffer to char value in temp
        for (int b = 0;b < num;) {
            temp->value[b] = buffer[b];
            b++;
        }
        
        if (count == 0) {

            ////create a link
            //struct csv_header* temp2 = (struct csv_header*)malloc(sizeof(struct csv_header));
            //// malloc so temp value can be copied into head value array
            //temp2->value = (char*)malloc(num + 1);
            //// exit program when failure to malloc
            //if (temp2->value == NULL) {
            //    cout << "failed";
            //    exit(EXIT_FAILURE);
            //}
            //memcpy(temp2->value, temp->value, num);
            
            // point it to old first node
            temp->next = head;

            //point first to new first node
            head = temp;
        }
        else {
            //create a link
            struct csv_header* temp2 = (struct csv_header*)malloc(sizeof(struct csv_header));
            if (temp2 == NULL) {
                exit(EXIT_FAILURE);
            }
            // malloc so temp value can be copied into head value array
            temp2->value = (char*)malloc(num + 1);
            // exit program when failure to malloc
            if (temp2->value == NULL) {
                cout << "failed";
                exit(EXIT_FAILURE);
            }
            memset(temp2->value, '\0', num+1);
            memcpy(temp2->value, temp->value, num);

            // point it to old first node
            temp2->next = head;

            //point first to new first node
            head = temp2;
        }
        count++;
        a++;
        // reset num back to 0
        num = 0;
        // clear string buffer
        memset(buffer, '\0', (input.length()+1));
    }
	
	
}

struct csv_header* temp3 = (struct csv_header*)malloc(sizeof(struct csv_header));
// failed to malloc struct csv_header for temp3
if (temp3 == NULL) {
cout << "failed";
exit(EXIT_FAILURE);
}
temp3->value = (char*)malloc(strlen(buffer) + 1);
// exit program when failure to malloc temp3->value
if (temp3->value == NULL) {
cout << "failed";
exit(EXIT_FAILURE);
}
    // handle last csv column not being parsed cause not find comma
    for(int t=0;t<strlen(buffer);){
        temp3->value[t] = buffer[t];
        t++;
    }

    // point it to old first node
    temp3->next = head;

    //point first to new first node
    head = temp3;

    // clear string buffer
    memset(buffer, '\0', (input.length()+1));
}

int main()
{
    // Careful if test.szd exist in your directory it will remove it.
    is_file_exist_remove("test.szd");
    ifstream newfile;
    // open a file to perform read operation using file object.
    newfile.open("xyz.csv", ios::in); 
    
    // start with line 0
    unsigned long linecount=0;
    // Checking whether the file is open.
    if (newfile.is_open()) { 
        string input;
        // Read data from the file object and put it into a string.
        while (getline(newfile, input)) { 
            if(linecount==0){
                processCSV_header(input);
                //printCSVheader_llist();
            }else{
                // don't process anything if input from file is blank line only. csv file may contain blank line
                if (input.empty()){

                }else{
                processCSV_row(input, linecount);
                printCSVrow_llist();
                }
            }
            // increment the line number
            linecount++;
        }

        writeSuzuranType();
        writeDataStructure();
        reverseCSVrow_llist();
        displayCSVrow_reverse();
        writeDataValue();
        
        // Close the file object.
        newfile.close(); 
    }
    else {
        cout << "cannot open file xyz.csv\n";
    }

    return 0;
}
