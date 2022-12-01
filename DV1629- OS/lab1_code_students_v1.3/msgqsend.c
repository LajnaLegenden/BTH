#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <limits.h>

#define PERMS 0644
struct my_msgbuf
{
   long mtype;
   int data;
};

int main(void)
{
   srand(time(NULL));
   struct my_msgbuf buf;
   int msqid;
   int len;
   key_t key;
   system("touch /dev/shm/file");

   if ((key = ftok("/dev/shm/file", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1)
   {
      perror("msgget");
      exit(1);
   }
   buf.mtype = 1; /* we don't really care in this case */
   sleep(5);

   for (int i = 0; i < 50; i++)
   {
      // Send a struct my_msgbuf to the queue

      buf.data = rand() % INT_MAX;
      if (msgsnd(msqid, &buf, sizeof(buf), 0) == -1)
      {
         perror("msgsnd");
         exit(1);
      }
      printf("sent: \"%i\"\n", buf.data);
   }
   buf.mtype = 2;
   buf.data = -1;
   if (msgsnd(msqid, &buf, sizeof(buf), 0) == -1)
   {
      perror("msgsnd");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   return 0;
}
