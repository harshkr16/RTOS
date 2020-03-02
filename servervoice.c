
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <pulse/sample.h>
#include <pulse/def.h>
#include <pulse/mainloop-api.h>
#include <pulse/cdecl.h>
#include <pulse/operation.h>
#include <pulse/proplist.h>
#include <pulse/version.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define CLADDR_LEN 100

static ssize_t loop_write(int fd, const void*data, size_t size) {
    ssize_t ret = 0;

    while (size > 0) {
        ssize_t r;

        if ((r = write(fd, data, size)) < 0)
            return r;

        if (r == 0)
            break;

        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }

    return ret;
}
int main(int argc, char *argv[])
{
	int fd = 0;
	struct timespec start,finish;
	///Create Socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
    	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}

	//Structure to store details
	struct sockaddr_in server;
	struct sockaddr_in cl_addr; 
	memset(&server, '0', sizeof(server)); 

	//Initialize	
	server.sin_family = AF_INET;
	server.sin_port = htons(8003); 
        server.sin_addr.s_addr = htonl(INADDR_ANY);
   

	bind(fd, (struct sockaddr*)&server, sizeof(server)); 

	
	int in;
	listen(fd, 100); 
	//while(in = accept(fd, (struct sockaddr*)NULL, NULL)){
	//len=sizeof(cl_addr);
	 static const pa_sample_spec ss = {
						.format = PA_SAMPLE_S16LE,
						.rate = 44100,
						.channels = 2
   					  };
	 pa_simple *s = NULL;
    int ret = 1;
    int error;

    /* Create the recording stream */
    

        /* Record some data ... */
       
        /* And write it to STDOUT */
       
    

    //ret = 0;

//finish:

  //  if (s)
    //    pa_simple_free(s);

   // return ret;
uint8_t buf[1024];
	while(in = accept(fd, NULL, NULL))
	{
			if(in<0)
			{
				printf("error in accepting");	
				exit(1);
			}
		//printf("Connection accepted from %s:%d\n",inet_ntoa(server.sin_addr),ntoa(server.sin_port));
		printf("Connection accepted\n");	
		//int n;
		//inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
			 
			//while (pa_simple_read(const char*)s, buf, sizeof(buf), &error) > 0)
			while(1)
			{ 
				uint8_t buf[1024];
					pa_simple_read(s, buf, sizeof(buf), &error);
					//pa_simple_write(s, buf, sizeof(buf),&error);
					pa_simple_write(s, buf, sizeof(buf), &error); 
					//pa_simple_drain(s,&error);
				   
				//{
				  //  fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
				    //goto finish;
				//}
		  		//clock_t begin=clock();
	
				
				//printf("Received from client %s: %s\n",clientAddr,buff);
				
				//char nbuff[1000] = toupper(buff);
			        //fgets(str, 1024, stdin);
				
				//clock_t end=clock();
				//time_spent+=(end-begin);
				//printf("processing time by server: %f microseconds\n",time_spent);
				   //loop_write(STDOUT_FILENO, buf, sizeof(buf)) != sizeof(buf) 
					//{
					  //  fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
					    //goto finish;
					//}

	
				
										
			}
			
		
		}

	
		
return 0;	
}

