#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include<sys/wait.h> 	
#include<pthread.h>
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

#define BUFSIZE 1024

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
	char buff[1024];
	char str[1024];
	int fd=0,opt;
	struct sockaddr_in cli;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt));
	cli.sin_family = AF_INET;
	cli.sin_port =  htons(8003);
	cli.sin_addr.s_addr=htonl(INADDR_ANY);
	 static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
    pa_simple *s, *s1 = NULL;
    int ret = 1;
    int error;
	while(connect(fd, (struct sockaddr *)&cli, sizeof(cli)));
	{		
		
		while(1)
			{
				
				//fgets(buff, 1024, stdin);
				//send(fd,buff,sizeof(buff),0);
				//recv(fd,str,sizeof(str),0);
				//printf("%s\n",str);
				 uint8_t buf[1024];

        /* Record some data ... */
	s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error);
	pa_simple_write(s, buf, sizeof(buf),&error);
	pa_simple_drain(s,&error);
	pa_simple_read(s, buf, sizeof(buf), &error);
	//pa_usec_t pa_simple_get_latency((pa_simple*)&s,&error);
	pa_simple_flush(s,&error);
			}
	}
				

	return 0;
}	
