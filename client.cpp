#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cout << "invalid number of arguments: call with `./client IP port`" << endl;
    return 1;
  }

  string host = argv[1];
  int port = atoi(argv[2]);


  try
  {
    ClientSocket client_socket(host, port);
    string saisiePseudo;
     string cmdUser;
     string Pseudo;

    do
    {
      cout << "Donnez moi votre pseudo grace à la commande USER" << endl << endl;
      getline(cin, saisiePseudo);
      
    
      int posPoint1= saisiePseudo.find(' ',0);
      Pseudo= saisiePseudo.substr(posPoint1+1,saisiePseudo.length());
      cmdUser = saisiePseudo.substr(0,posPoint1);
      
     
      
    }while(cmdUser != "USER");
    cout <<"Bonjour " << Pseudo << " ! Bienvenu sur le Chat :)" << endl << endl;

    while(true){
      string reply;
      string saisie;
      getline(cin, saisie);
      int posSpace= saisie.find(' ',0);
      string cmdMSG = saisie.substr(0,posSpace);
      string msg= saisie.substr(posSpace+1,saisie.length());
      //  cout << cmdMSG << endl;
      //  cout << msg << endl;
      
      if(cmdMSG == "MSG")
      {
        try
        {
          client_socket << msg;
          client_socket >> reply;
        }
        catch (SocketException &)
        {
          cout << "error";
        }
        cout << "We received this response from the server:\n"<< Pseudo << ": "<< reply <<  "\n" << endl ;
      }
      else{
        cout << "Met la commande MSG avant ton msg genius !" << endl;
      }
    }
    
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << endl;
  }

  return 0;
}
