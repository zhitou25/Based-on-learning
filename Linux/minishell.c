
// shell模拟--minishell
//标准输出重定向
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    while(1) {
        char cmd[1024] = {0};
        printf("minishell: ");
        fflush(stdout);
        //scanf读取缓冲区数据时候，默认遇到空格终止
        //%[^\n]:将\n之前的数据放入到cmd中 设置遇到\n终止
        //%*c:将剩下的字符全都从缓冲区取出来，丢弃
        if (scanf("%[^\n]%*c", cmd) != 1) 
		{
            getchar();
        }
        int pid = fork();
        if (pid < 0)
		{
            exit(-1);
        }else if (pid == 0) 
		{
            //解析是否有重定向  >   >>
            char *ptr = cmd;
            int redirect_flag = 0;
            char *file;
            while(*ptr != '\0') 
			{
                if (*ptr == '>') 
				{
                    *ptr++ = '\0';
                    redirect_flag = 1;
                    if (*ptr == '>')
					{
                        *ptr++ = '\0';
                        redirect_flag = 2;
                    }
                    while(*ptr != '\0' && isspace(*ptr))
                        ptr++;
                    file = ptr;
                    while(*ptr != '\0' && !isspace(*ptr))
                        ptr++;
                    *ptr = '\0';
                }
                ptr++;
            }
            int fd = -1;
            if (redirect_flag == 1) 
			{
                fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0664);
                dup2(fd, 1);
            }
			else
				if (redirect_flag == 2)
			{
                fd = open(file, O_CREAT|O_APPEND|O_WRONLY,0664);
                dup2(fd, 1);
            }
            
            ptr = cmd;
            char *argv[32] = {NULL};
            int argc = 0;
            while(*ptr != '\0') 
			{
                //*ptr非空白字符则为参数首地址 l位置
                //isspace判断字符是否是空白字符
                if (!isspace(*ptr)) 
				{
                    argv[argc++] = ptr;
                    while(!isspace(*ptr) && *ptr != '\0')
                        ptr++;
                    continue;
                }
				else
				{
                    *ptr = '\0';
                }
                ptr++;
            }
            execvp(argv[0], argv);
            exit(-1);
        }
		else
		{
            waitpid(pid, NULL, 0);
        }
	}
    return 0;
}

