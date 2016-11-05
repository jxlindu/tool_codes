#include <errno.h>
#include <unistd.h>

ssize_t readn(int fd, void* vptr, size_t len)
{
    if(0 == len)
    {
	return len;
    }

    size_t nleft = len;
    ssize_t nread = 0;
    char* tmp_ptr = static_cast<char*>(vptr);
    while(nleft > 0)
    {
	if((nread = read(fd, tmp_ptr, nleft)) > 0)
	{
	    nleft -= nread;
	    tmp_ptr += nread;
	}
	else if(0 == nread)
	{
	    break;
	}
	else
	{
	    if(EINTR == errno)
	    {
		nread = 0;
	    }
	    else
	    {
		return -1;
	    }
	}
    }

    return len - nleft;
}

ssize_t writen(int fd, const void* vptr, size_t len)
{
    if(0 == len)
    {
	return len;
    }

    size_t nleft = len;
    ssize_t nwritten = 0;
    const char* tmp_ptr = static_cast<const char*>(vptr);
    while(nleft > 0)
    {
	if((nwritten = write(fd, tmp_ptr, nleft)) > 0)
	{
	    nleft -= nwritten;
	    tmp_ptr += nwritten;
	}
	else if(0 == nwritten)
	{
	    break;
	}
	else
	{
	    if(EINTR == errno)
	    {
		nwritten = 0;
	    }
	    else
	    {
		return -1;
	    }
	}
    }

    return len - nleft;
}
