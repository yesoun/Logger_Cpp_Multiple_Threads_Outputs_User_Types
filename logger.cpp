#ifndef LOGGER_CPP
#define LOGGER_CPP

#include <cstdint>
#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <cstdlib>
#include <cstdio>
// Programmer Defined Header Files
#include "logger.hpp"

using namespace std;




#define SYNTAX_ARGUMENTS_ERROR_MESSAGE  cout<< "-- At least one logger message type required and no more than 3, such as error, warning, information" << endl
#define CHECK_SYNTAX cout << "-- check syntax of arguments" <<endl
#define DUPLICATE_ARGUMENTS cout << "-- check duplicate argument" << endl


#define Cpp11Features  cout << "C++11 found and required by logger" << endl
#define Cpp14Features  cout << "C++14 used, but only C++ 11 required for the logger." << endl
#define Cpp11Missing cout << "-- C++ 11 missing, SYSTEM ERROR, in line " <<__LINE__<<" in file" <<__FILE__<<endl


// the three type of logging error, warning and information (made statically, I could have created like a vector that holds all the ypes of logging messages
// and based on the values in the vector we make the different outputs based on a vector that holds many type of outputs )
string strError= "error";
string strWarning= "warning";
string strInformation= "information";



/// initialise static variables
// both the files "warning_log.txt"; "error_log.txt" are not cleared after code execution, so logging message will stay, thus you need to clear it manually in order to see only the new messages after execution
string LOG::Logger::errorFileName= "error_log.txt";
string LOG::Logger::WarningFileName= "warning_log.txt";

/* each instance from tje data structure have a mutex that is used to prevent more than one thread to write to error_log.txt or to warning_log.txt or to standard output(use "cout")*/

// construct pointer to objects FileParser (struct defined) errorFileParser WarningFileParser with the constructor that has the name of the loggin file, see the contructor of the struct FileParser
LOG::FileParser* LOG::Logger::errorFileParser=new FileParser(LOG::Logger::errorFileName);
LOG::FileParser* LOG::Logger::WarningFileParser=new FileParser(LOG::Logger::WarningFileName);
// default contructor, since we will not have any file to redirect to in case of information outputting
LOG::FileParser* LOG::Logger::InformationFileParser=new FileParser();




/// Constructors and destructor
LOG::Logger::Logger()
{

}

LOG::Logger::~Logger()
{

}


/// Mutators (Setters)

void LOG::Logger::setIsLogMessageDefined(bool iLMD)
{
    isLogMessageDefined=iLMD;
}

void LOG::Logger::setIsErrorLogged(bool iEL)
{
    isErrorLogged=iEL;
}
void LOG::Logger::setIsWarningLogged(bool iWL)
{
    isWarningLogged =iWL;
}
void LOG::Logger::setIsInformationLogged(bool iIL)
{
    isInformationLogged=iIL;
}



/// Accessors (Getters)
bool LOG::Logger::getIsLogMessageDefined()
{
    return isLogMessageDefined;
}

bool LOG::Logger::getIsErrorLogged()
{
    return isErrorLogged;
}

bool LOG::Logger::getIsWarningLogged()
{
    return isWarningLogged;
}

bool LOG::Logger::getIsInformationLogged()
{
    return isInformationLogged;
}




/// public methods
void LOG::Logger::checkCPlusPlusEleven()
{
        #if __cplusplus==201402L
        Cpp14Features;
        #elif __cplusplus==201103L
        //Cpp11Features;
        #else
        Cpp11Missing;
        exit(EXIT_FAILURE);
        #endif

}

void LOG::Logger::checkSetUserLoggingTypes(int argc, char* argv[])
{
    // check if there are arguments or not for the types the user want, statically done for the three types of parameter
    if(argc==1 || argc>4){
        SYNTAX_ARGUMENTS_ERROR_MESSAGE;
        exit(EXIT_FAILURE);
    }


    // check and set the user required types for logger messages.
    for(int i=1;i<argc;++i){
        if(argv[i]== strError){
            if(!this->getIsErrorLogged()){
                this->setIsErrorLogged(true);
            }
            else {
                DUPLICATE_ARGUMENTS ;
                exit(EXIT_FAILURE);

            }
        }

        else if(argv[i]== strWarning){
            if(!this->getIsWarningLogged()){
                this->setIsWarningLogged(true);
            }
            else {
                DUPLICATE_ARGUMENTS ;
                exit(EXIT_FAILURE);
           }
        }

        else if(argv[i]== strInformation){
            if(!this->getIsInformationLogged()){
                this->setIsInformationLogged(true);
            }
            else {
                DUPLICATE_ARGUMENTS ;
                exit(EXIT_FAILURE);
            }
        }

        else {
                CHECK_SYNTAX;
                SYNTAX_ARGUMENTS_ERROR_MESSAGE;
                exit(EXIT_FAILURE);
       }

    }

}

// static method used to log the errors of the threads in the file "error_log.txt"
void LOG::Logger::LogThreadErros(const unsigned int threadId){
    // static variables to hold the total count per type of the logged messages
    static unsigned int msgErrorCount=0;

    // put thread id (unsigned int) into char*
    char tmpthreadIdBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpthreadIdBuff, 12, "%d", threadId);
    const char* threadIdBuff= tmpthreadIdBuff;

    // store total number (of error messages logged) in char pointer
    msgErrorCount+=1;
    char tmpErrNumBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpErrNumBuff, 12, "%d", msgErrorCount);
    const char* errNumBuff=tmpErrNumBuff;


    const char* errBuff= "error n: ";
    const char* msgId=" from thread with id=";
    const char* newLine="\n";

    // retrieve the array of character that has the message formulated in threadMessage method
    char* msgError= threadMessage(errBuff,errNumBuff,threadIdBuff,msgId,newLine);

    // logging error messages into fileName from errorFileParser
    FileParser* b = reinterpret_cast<FileParser*>(errorFileParser);
    (b->mutexLock).lock();
    b->myfile.open(b->fileName, ios::out | ios::app); // it erases every time b->myfile.open(b->fileName);
    b->myfile.write(msgError,strlen(msgError));
    b->myfile.close();
    (b->mutexLock).unlock();

}

// static method usec to log the warnings of the threads in the file "warning_log.txt"
void LOG::Logger::LogThreadWarnings(const unsigned int threadId){
    // static variable to hold the total count per type of the logged messages
    static unsigned int msgWarningCount=0;

    // put thread id (unsigned int) into char*
    char tmpthreadIdBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpthreadIdBuff, 12, "%d", threadId);
    const char* threadIdBuff= tmpthreadIdBuff;

    // store total number (of warning messages logged) in char pointer
    msgWarningCount+=1;
    char tmpWarNumBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpWarNumBuff, 12, "%d", msgWarningCount);
    const char* warNumBuff=tmpWarNumBuff;


    const char* warBuff= "warning n: ";
    const char* msgId=" from thread with id=";
    const char* newLine="\n";

    // retrieve the array of character that has the message formulated in threadMessage method
    char* msgWarning= threadMessage(warBuff,warNumBuff,threadIdBuff,msgId,newLine);

    // logging warning messages into fileName from WarningFileParser
    FileParser* b = reinterpret_cast<FileParser*>(WarningFileParser);
    (b->mutexLock).lock();
    b->myfile.open(b->fileName, ios::out | ios::app); // it erases every time b->myfile.open(b->fileName);
    b->myfile.write(msgWarning,strlen(msgWarning));
    b->myfile.close();
    (b->mutexLock).unlock();

}


// static method used to log the warnings of the threads in the file "warning_log.txt"
void LOG::Logger::LogThreadInformations(const unsigned int threadId){
    // static variable to hold the total count per type of the logged messages
    static unsigned int msgInformationCount=0;

    // put thread id (unsigned int) into char*
    char tmpthreadIdBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpthreadIdBuff, 12, "%d", threadId);
    const char* threadIdBuff= tmpthreadIdBuff;

    // store total number (of Information messages logged) in char pointer
    msgInformationCount+=1;
    char tmpInfNumBuff[12]; // 11 for max int + 1 for null
    snprintf(tmpInfNumBuff, 12, "%d", msgInformationCount);
    const char* infNumBuff=tmpInfNumBuff;


    const char* infBuff= "Information n: ";
    const char* msgId=" from thread with id=";
    const char* newLine="\n";

    // retrieve the array of character that has the message formulated in threadMessage method
    char* msgInformation= threadMessage(infBuff,infNumBuff,threadIdBuff,msgId,newLine);
    // logging warning messages into standard output
    FileParser* b = reinterpret_cast<FileParser*>(WarningFileParser);
    (b->mutexLock).lock();
    cout<< msgInformation << endl;
    (b->mutexLock).unlock();

}




// method used the create all the types of log messages (either warning, errors or information)
char* LOG::Logger::threadMessage(const char* errBuff, const char* errNumBuff, const char* threadIdBuff, const char* msgId,const char* newLine)
{
    char* resultMessage = new char[strlen(errBuff)+strlen(errNumBuff)+strlen(threadIdBuff)+ strlen(newLine)+ strlen(msgId)+1];

    strcpy(resultMessage, newLine);
    strcat(resultMessage, errBuff);
    strcat(resultMessage, errNumBuff);
    strcat(resultMessage, msgId);
    strcat(resultMessage, threadIdBuff);


    return resultMessage;

}




#endif // LOGGER_CPP




















