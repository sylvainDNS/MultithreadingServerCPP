#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <unistd.h>

using namespace std;

void wait()
{
  this_thread::sleep_for(chrono::seconds(1));
}

void sendMsg(ClientSocket *sock)
{
  while (true)
  {
    try
    {
      string saisie;

      getline(cin, saisie);
      int posSpace = saisie.find(' ', 0);
      string cmdMSG = saisie.substr(0, posSpace);
      string msg = saisie.substr(posSpace + 1, saisie.length());

      if (cmdMSG == "MSG")
      {
        sock->send(saisie);
      }
      else
      {
        cout << "Met la commande MSG avant ton msg genius !" << endl;
      }
    }
    catch (SocketException &e)
    {
      cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
    }
  }
}

void receiveMsg(ClientSocket *sock)
{

  string reply;
  while (true)
  {
    sock->recv(reply);

    cout << "Server : \"" << reply << "\"\n";
  }
  wait();
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cout << "invalid number of arguments: call with `./client IP port`" << endl;
    return 1;
  }

  string saisiePseudo;
  string cmdUser;
  string Pseudo;

  do
  {
    cout << "Donnez moi votre pseudo grace à la commande USER" << endl
         << endl;
    getline(cin, saisiePseudo);

    int posPoint1 = saisiePseudo.find(' ', 0);
    Pseudo = saisiePseudo.substr(posPoint1 + 1, saisiePseudo.length());
    cmdUser = saisiePseudo.substr(0, posPoint1);

  } while (cmdUser != "USER");
  cout << "Bonjour " << Pseudo << " ! Bienvenu sur le Chat :)" << endl
       << endl;

  string host = argv[1];
  int port = atoi(argv[2]);

  try
  {
    ClientSocket *sock = new ClientSocket(host, port);

    thread receiver(receiveMsg, sock);
    thread sender(sendMsg, sock);

    receiver.join();
    sender.join();
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << endl;
  }

  return 0;
}
