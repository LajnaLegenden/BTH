#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644
struct my_msgbuf
{
   long mtype;
   int data;
};

int main(void)
{
   struct my_msgbuf buf;
   int msqid;
   int toend;
   key_t key;
   system("touch /dev/shm/file");
   if ((key = ftok("/dev/shm/file", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS)) == -1)
   { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
   printf("message queue: ready to receive messages.\n");

   for (;;)
   { /* normally receiving never ends but just to make conclusion */
      // recive message using msgrev
      if (msgrcv(msqid, &buf, sizeof(buf), 0, 0) == -1)
      {
         perror("msgrcv");
         exit(1);
      }
      printf("recived: %i\n", buf.data);
      if (buf.mtype == 2)
         break;
   }
   if (msgctl(msqid, IPC_RMID, NULL) == -1)
   {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done receiving messages.\n");
   system("rm /dev/shm/file");
   return 0;
}
