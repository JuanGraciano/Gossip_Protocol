//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#define PORT 7200

int open_socket();
int bind_to_port(int, int);

using namespace std;

int main()
{
  char * advice[]= {"Hoy se bebe\n\r",
                    "Vamono pal monte\n\r",
                    "Vamo a ponerno loco\n\r",
                    "Manga tu caminao\n\r",
                    "Rubia aunque sea de farmacia\n\r"}

  int listener = open_socket();

  if(listener < 0){
    cout << "Error establishing socket..." << endl;
    exit(1);
  }

  bind_to_port(listener, PORT);
  if(listen (listener, 10) < 0){
    cout << "I cant to listen the port" << endl;
    exit(2);
  }

  cout << "Linking port" << endl;
  while(1){
    struct sockaddr_storage client;
    unsigned int address_size = sizeof(client);
    cout << "Waiting client" << endl;
    int connect = accept(listener, (struct sockeaddr*)&client, &addres_size);
    if(connect < 0){
      cout << "Error connectiong second socket" << endl;
    }
    cout << "Serving the client" << endl;
    char * msg = advice[rand()%5];
    send(connect, msg, strlen(msg), 0);
    msg = NULL;
    close(connect);
  }

  return 0;

}

int open_socket(){
  int s = socket(PF_INET, SOCK_STREAM, 0);
  return s;
}

void bind_to_port(int socket, int port){
  struct sockaddr_in  name;
  name.sin_family = PF_INET;
  name.sin_port = (int_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int reuse = -1;
  if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)) < 0){
    cout << "Error reusing socket..." << endl;
  }

  int c = bind(socket, (struct sockaddr*) &name, sizeof(name));
  if(c < 0){
    cout << "Error connecting port." << endl;
  }
}
