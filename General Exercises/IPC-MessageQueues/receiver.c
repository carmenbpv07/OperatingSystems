#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define MAXSIZE 128

void die(char *s) {
  perror(s);
  exit(1);
}

struct msgbuf {
  long mtype;
  char mtext[MAXSIZE];
};

void main() {
  int msqid;
  key_t key;
  struct msgbuf rcvbuffer;

  key = 1234;

  // msgget -> Returns the ID of the message queue associated with the key
  if ((msqid = msgget(key, 0666)) < 0) die("msgget()");

  // Receive an answer of message type 1
  // msgrcv -> Removes a message from the queue specified by msqid and puts it
  // in the buffer pointed to by rcvbuffer
  if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0) die("msgrcv");

  printf("%s\n", rcvbuffer.mtext);
  exit(0);
}
