/*****************************************
** Creates an EReader object and runs handles the main program
** reads in from file to create books. Allows user to add said books
** to their LQueue.
** 
***********************************************/

#include "EReader.h"
const int THREE=3,FOUR=4,FIVE=5;
 //Name: EReader - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new EReader
  EReader::EReader(){

  }
  //Name: EReader - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new EReader and passes the book filename
  EReader::EReader(string filename){
    LoadCatalog(filename);
    cout<<"Welcome to UMBC E-Reader"<<endl;
  }
  //Name: ~EReader - Destructor
  //Precondition: None
  //Postcondition: Creates a new EReader
  EReader::~EReader(){
    //delete *m_readList;
    for(int i=ZERO;i<(int)m_bookCatalog.size();i++){
      delete m_bookCatalog.at(i);
    }
  }
  //Name: LoadCatalog(string filename)
  //Precondition: Requires filename
  //Postcondition: Loads the file into the m_bookCatalog (as books)
  void EReader::LoadCatalog(string filename){
    ifstream myFile;
    myFile.open(filename);
    string title, temp, author;
    int rank;
    double price;
    Book* newBook;
    while(getline(myFile,title,',')){
      getline(myFile,author,',');
      getline(myFile,temp,',');
      rank=stoi(temp);
      getline(myFile,temp,'\n');
      price=stod(temp);
      newBook=new Book(title,author,rank,price);
      m_bookCatalog.push_back(newBook);
    }
    cout<<"Catalog populated with "<<m_bookCatalog.size()<<" books."<<endl;
  }
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the application and the menu
  void EReader::MainMenu(){
    int choice;
    do{
      cout<<"1. Display All Books"<<endl
          <<"2. Add Book to Readlist"<<endl
          <<"3. Display Readlist"<<endl
          <<"4. Sort Readlist by Price"<<endl
          <<"5. Quit"<<endl;
      cin>>choice;
      while(choice>FIVE||choice<ONE){
        cout<<"Invalid number. Please choose a valid choice"<<endl;
        cin>>choice;
      }
      switch(choice){
        case ONE:
          DisplayBooks();
          break;
        case TWO:
          AddBook();
          break;
        case THREE:
          DisplayReadlist();
          break;
        case FOUR:
          SortReadlist();
          break;
        default:
          break;
      }
    }while(choice!=FIVE);
    cout<<"Thank you for using the UMBC E-Reader"<<endl;
  }
  //Name: DisplayBooks
  //Precondition: Displays all 150 books
  //Postcondition: Lists all books (numbered)
  void EReader::DisplayBooks(){
    for (int i=ZERO;i<(int)m_bookCatalog.size();i++){
      cout<<i+ONE<<"."<<*m_bookCatalog.at(i);
    }
  }
  //Name: AddBook
  //Precondition: m_bookCatalog is populated
  //Postcondition: Displays the current list and adds a book
  //               to the m_readList
  void EReader::AddBook(){
    DisplayBooks();
    int choice;
    cout<<"Enter the number of the book you would like to add:"<<endl;
    cin>>choice;
    while(choice>(int)m_bookCatalog.size()||choice<ONE){
      cout<<"Invalid choice. Please enter a valid choice."<<endl;
      cin>>choice;
    }
    choice--;
    m_readList.Push(*m_bookCatalog.at(choice),true);
  }
  //Name: DisplayReadlist
  //Precondition: None (can be empty)
  //Postcondition: Displays the readlist
  void EReader::DisplayReadlist(){
    m_readList.Display();
  }
  //Name: SortReadlist()
  //Precondition: Requires Readlist
  //Postcondition: Uses the overloaded < operator in Book to sort
  //               the prices from high to low in the m_readList
  void EReader::SortReadlist(){
    //If there are only two books, swap head and tail
    if(m_readList.GetSize()==TWO){
      if(!(m_readList[ZERO]<m_readList[ONE])){
        m_readList.Swap(ONE);
      }
    }
    else{
    int i=ZERO; 
    bool swapped=true; 
    int size=m_readList.GetSize();
    while((i<size-ONE)&&(swapped!=false)){ 
     swapped = false; 
     for (int x = ZERO; x < size-i-ONE; x++) 
     { 
        if (m_readList[x] < m_readList[x+ONE]) 
        { 
          m_readList.Swap(x+ONE);
          swapped=true;
        }
     } 
     i++;
   }
  }
  cout<<"Done Sorting List"<<endl;
}