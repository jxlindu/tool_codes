/** 
 * * (C) Copyright 2016, 林都 
 * * @version  v1.0 
 * * @author   林都 
 * * @brief   异常拓展类 
 * */  

#ifndef __EXCEPTIONX_H__
#define __EXCEPTIONX_H__

#include<cstdio>
#include<string>
#include<ostream>
#include<exception>

inline int stdErrno() { return errno; } 
inline const char* stdErrmsg() { return strerror(errno); }

class ExceptionX : public std::exception
{
    public:
	ExceptionX(int err_no, const std::string& err_msg, int line=0, const std::string& file="") throw()
	    : m_err_no(err_no), m_err_msg(err_msg), m_line(line), m_file(file)
	{
	}

	virtual ~ExceptionX() throw() {}

	int errNo() const { return m_err_no; }
	const std::string& errMsg() const { return m_err_msg; }

	const std::string& file() const { return m_file; }
	int line() const { return m_line; }

	virtual const char* what() const throw() { return m_err_msg.c_str(); }
	friend std::ostream& operator << (std::ostream& os, const ExceptionX& e);

    private:
	int m_err_no;
	std::string m_err_msg;
	int m_line;
	std::string m_file;
};

inline std::ostream& operator << (std::ostream& os, const ExceptionX& e)
{
    os<< e.m_file<< ":"<< e.m_line<< " [ "<< e.m_err_no<< ":"<< e.m_err_msg<< " ]";

    return os;
}

#define THROW_EXCEPTIONX(ErrNO, Fmt, ...) {\
    char msg[4096] = {0};\
    snprintf(msg, sizeof(msg), Fmt, ##__VA_ARGS__);\
    throw ExceptionX(ErrNO, msg, __FILE__, __LINE__);}

#endif // __EXCEPTIONX_H__
