#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netinet/in.h>
#include <ev.h>

#define PORT_NO 3033
#define BUFFER_SIZE 1024

int total_clients = 0;  // Total number of connected clients

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
char* readFile(char *filename);
char* parameter;

int main(int argc, char** argv)
{
  if (!(!strcmp(argv[1],"20kb") || !strcmp (argv[1],"500b"))) {
    printf("Please use \"20kb\" or \"500kb\" as second parameter\n");
    return 0;
  }
  else {
    parameter = argv[1];
  }
  struct ev_loop *loop = ev_default_loop(0);
  int sd;
  struct sockaddr_in addr;
  int addr_len = sizeof(addr);
  struct ev_io w_accept;

  // Create server socket
  if( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
  {
    perror("socket error");
    return -1;
  }

  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT_NO);
  addr.sin_addr.s_addr = INADDR_ANY;

  // Bind socket to address
  if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) != 0)
  {
    perror("bind error");
  }

  // Start listing on the socket
  if (listen(sd, 2) < 0)
  {
    perror("listen error");
    return -1;
  }

  // Initialize and start a watcher to accepts client requests
  ev_io_init(&w_accept, accept_cb, sd, EV_READ);
  ev_io_start(loop, &w_accept);

  // Start infinite loop
  while (1)
  {
    ev_loop(loop, 0);
  }

  return 0;
}

/* Accept client requests */
void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int client_sd;
  struct ev_io *w_client = (struct ev_io*) malloc (sizeof(struct ev_io));

  if(EV_ERROR & revents)
  {
    perror("got invalid event");
    return;
  }

  // Accept client request
  client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);

  if (client_sd < 0)
  {
    perror("accept error");
    return;
  }

  total_clients ++; // Increment total_clients count
  printf("Successfully connected with client.\n");
  printf("%d client(s) connected.\n", total_clients);

  // Initialize and start watcher to read client requests
  ev_io_init(w_client, read_cb, client_sd, EV_READ);
  ev_io_start(loop, w_client);
}

/* Read client message */
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents){
  char buffer[BUFFER_SIZE];
  ssize_t read;

  if(EV_ERROR & revents)
  {
    perror("got invalid event");
    return;
  }

  // Receive message from client socket
  read = recv(watcher->fd, buffer, BUFFER_SIZE, 0);

  if(read < 0)
  {
    perror("read error");
    return;
  }

  if(read == 0)
  {
    // Stop and free watchet if client socket is closing
    ev_io_stop(loop,watcher);
    close(watcher->fd);
    free(watcher);
    perror("peer might closing");
    total_clients --; // Decrement total_clients count
    printf("%d client(s) connected.\n", total_clients);
    return;
  }
  else
  {
    printf("message:%s\n",buffer);
  }

  char* httpHeader =
      "HTTP/1.1 200 OK\n"
      "Content-type: text/html\n"
      "\n";
      char *externalHtml = "";
      if (!strcmp(parameter,"20kb")) {
        externalHtml = readFile("content/file_20kb.html");
      }
      else {
        externalHtml = readFile("content/file_500b.html");
      }

  if (externalHtml) {
      char* httpResponse;
      httpResponse = malloc(strlen(httpHeader)+1+strlen(externalHtml));
      strcpy(httpResponse, httpHeader);
      strcat(httpResponse,externalHtml);

      int len = strlen(httpResponse);
      send(watcher->fd, httpResponse, len, 0);
      bzero(buffer, read);

      free(httpResponse);
      free(externalHtml);

      ev_io_stop(loop,watcher);
      close(watcher->fd);
      free(watcher);

  }
}

char* readFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}
