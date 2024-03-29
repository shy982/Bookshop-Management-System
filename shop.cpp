Book shop 
#include<fstream.h>
#include<conio.h>              //for clscr() function
#include<ctype.h>              //for toupper() function
#include<string.h>             //for strcpy) and strmpi() function
#include<math.h>               //for pow() function
#include<stdio.h>              //for gets() function

//creating function prototype
void staff();
void customer();
void bill();
void create();
void display();
void append();
void modify();
void total();

//creating class item
class item
{
 public:
 int icode;
 char iname[80];
 int iprice;

 //creating function input() to take the details from the user
 void input()
 {
  cout<<"Enter the code of the item: "<<endl;
  cin>>icode;
  cout<<"Enter the name of the item: "<<endl;
  gets(iname);
  cout<<"Enter the price of the item: "<<endl;
  cin>>iprice;
 }

 //creating function output() to display the details as entered by the user
 void output()
 {
  cout<<"The item code is: "<<icode<<endl;
  cout<<"The item name is: "<<iname<<endl;
  cout<<"The item price is: "<<iprice<<endl<<endl;
 }

 //creating function retname() to return name
 char*retname()
 {
  return iname;
 }

 //creating function retcode() to return code
 int retcode()
 {
  return icode;
 }

 //creating function retprice() to return iprice
 int retprice()
 {
  return iprice;
 }
}; //end of class item

//creating class product
class product
{
 public:
 float price;
 int code;
 char name[80];
 int qty;
 long tot;

 //creating function getdata() to get details of the items to be purchased
 void getdata()
{
 cout<<"Enter the item code to be purchased: "<<endl;
 cin>>code;
 cout<<"Enter the quantity of item to be purchased: "<<endl;
 cin>>qty;
 cout<<endl;
}

//creating function total() to calculate the total
void total()
{
 tot=((qty)*(price));
}

//creating function retotal() to retotal
float retotal()
{
 return tot;
}

//creating function showdata() to display the details of the item purchased
 void showdata()
{
 cout<<"The code of the purchased item is: "<<code<<endl;
 cout<<"The name of the purchased item is: "<<name<<endl;
 cout<<"The quantity iof the purchased item is: "<<qty<<endl;
 cout<<"The price of the purchased item is: "<<price<<endl;
}
}; //end of class product

//function for entering into the program
 void intro()
{
 clrscr();
 int ch;
 do
 {
  cout<<"................         book shop            ..............."<<endl;
  cout<<"���..                                    ����."<<endl;
  cout<<"_________________________________________________________"<<endl;
  cout<<"_________________________________________________________"<<endl;
  cout<<endl<<endl;
  cout<<"YOU WANT TO ENTER AS "<<endl;
  cout<<"1. STAFF"<<endl;
  cout<<"2. CUSTOMER"<<endl;
  cout<<"3. EXIT"<<endl;
  cout<<"Enter your choice"<<endl;
  cin>>ch;
  switch(ch)
  {
            case 1:staff();
                                     break;
            case 2:customer();
                                     break;
            case 3:break;
  }
 } while(ch!=3);
}

//creating function staff() for staff use only
 void staff()
{
 clrscr();
 int ch;
 do
 {
  cout<<"WHICH OPERATION DO YOU WANT TO PERFORM ?"                  <<endl<<endl;
  cout<<" 1.     Create the menu"                                                                                <<endl;
  cout<<" 2.     Display the menu"                                                                               <<endl;
  cout<<" 3.     Add new record in the menu"                                                <<endl;
  cout<<" 4.     Modify a record"                                                                                <<endl;
  cout<<" 5.     Go to the menu"                                                                                              <<endl;
  cout<<"Enter your choice"                                                                                                   <<endl;
  cin>>ch;
  switch(ch)
  {
            case 1:create();
                                     break;
            case 2:display();
                                     break;
            case 3:append();
                                     break;
            case 4:modify();
                                     break;
            case 5:break;
  }
 } while(ch!=5);
}

//creating function create() to write the records
void create()
{
 clrscr();
 fstream fil;
 char ch;
 item s;
 fil.open("ITEM.DAT",ios::out|ios::binary);
 do
 {
  s.input();
  fil.write((char*)&s,sizeof (s));
  cout<<"Do you want to enter more records?(y/n)"<<endl;
  cin>>ch;
  cout<<endl;
 }
 while(ch=='y'||ch=='Y');
 fil.close();
}

//creating function display() to display the records
void display()
{
 clrscr();
 item s;
 fstream fil;
 fil.open("ITEM.DAT",ios::in|ios::binary);
 while(fil.read((char*)&s,sizeof s))
 {
 s.output();
 }
 fil.close();
}

//creating function append() to append record
void append()
{
 clrscr();
 item s;
 char ch;
 fstream fil;
 fil.open("ITEM.DAT",ios::app|ios::binary);
 do
 {
 s.input();
 fil.write((char*)&s,sizeof s);
 cout<<"Do you want to append more records?"<<endl;
 cin>>ch;
 }while(ch=='y'||ch=='Y');
 fil.close();
}

 //creating function modify() to modify a record
 void modify()
{
 clrscr();
 int code;
 item s;
 fstream fil;
 cout<<"Enter the code of the item to be modified:"<<endl;
 cin>>code;
 fil.open("ITEM.DAT",ios::in|ios::out|ios::binary);
 while(fil.read((char*)&s,sizeof s))
 {
  if (s.retcode()==code)
  {
            fil.seekp(fil.tellg()-sizeof(s),ios::beg);
            s.input();
            fil.write((char*)&s,sizeof(s));
  }
 }
 fil.close();
 }


  //creating function customer()
  void customer()
  {
            clrscr();
            long gtot=0;
            display();
            char ch;
            product s;
            fstream fil,ifil;
            item a;
            fil.open("cust.dat",ios::out|ios::binary);
            do
            {
             s.getdata();
             ifil.open("ITEM.DAT",ios::in|ios::binary);
             while(ifil.read((char*)&a,sizeof (a)))
             {
              if(a.retcode()==s.code)
              {
                        s.price=a.retprice();
                        strcpy(s.name,a.retname());
                        s.total();
                        fil.write((char*)&s,sizeof (s));
              }
             }
             gtot+=(s.retotal());
             cout<<"Do you want to continue purchasing?(y/n)"<<endl;
             cin>>ch;
             ifil.close();
            }while(ch=='y'||ch=='Y');
            fil.close();
            fil.open("cust.dat",ios::in|ios::binary);
            cout<<endl;
            cout<<"$$$$$$$$$$$$$$$$          BILL       $$$$$$$$$$$$$$$$$"<<endl;
            cout<<endl;
            cout<<"your bill goes as............"<<endl;
            while(fil.read((char*)&s,sizeof (s)))
            {
             s.showdata();
             cout<<endl;
            }
            cout<<endl;
            cout<<"GRAND TOTAL                                          Rs."<<gtot<<endl;
            cout<<endl;
            cout<<"===============THANKS FOR VISITING==============="<<endl;
            }

  //creating function main()
            void main()
  {
            intro();
  }
