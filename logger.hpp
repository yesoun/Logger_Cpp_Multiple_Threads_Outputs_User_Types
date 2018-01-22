#include<cstring>
#include<vector>
#include<mutex>
#include<fstream>

#ifndef LOGGER_HPP
#define LOGGER_HPP

/*
    three default types of outputs:
    Standard output for Information messages
    warning_log.txt     for warning messages
    error_log.txt      for error messages

    if the user give an argument, then all the three types of messages will be redirected to it.


*/
using namespace std;
namespace LOG

{
    struct FileParser{
        ofstream myfile;
        string fileName;
        mutex mutexLock;
        FileParser(){};
        FileParser(string fN){fileName=fN;};
    };

    class Logger
    {
        /// private objects
        private:
            char* logMessage;
            bool isLogMessageDefined;
            bool isErrorLogged;
            bool isWarningLogged ;
            bool isInformationLogged;

            // static objects
            const static unsigned int lengthLogMessage = 50; // set the length of all the logging message (same size of message for warning , error and ingormation)
            static string errorFileName;
            static string WarningFileName;
            static FileParser* errorFileParser;
            static FileParser* WarningFileParser;
            static FileParser* InformationFileParser;



        /// Mutators (Setters)
        public:
            void setLogMessage(char* lM);
            void setlengthLogMessage(int lLM);
            void setIsLogMessageDefined(bool iLMD);
            void setIsErrorLogged(bool iEL);
            void setIsWarningLogged(bool iWL);
            void setIsInformationLogged(bool iIL);



        /// Accessors (Getters)
        public:
            char* getLogMessage();
            int getlengthLogMessage();
            bool getIsLogMessageDefined();
            bool getIsErrorLogged();
            bool getIsWarningLogged();
            bool getIsInformationLogged();


        /// Constructors and destructor
        public:
            Logger();
            ~Logger();


        /// Public methods
        public:
            void checkCPlusPlusEleven();
            void checkSetUserLoggingTypes(int argc, char* argv[]); // checks the the types of logging that the user will give as arguments while running the program.
            static void LogThreadErros(const unsigned int threadId); // log the errors of the threads in the file "error_log.txt"
            static void LogThreadWarnings(const unsigned int threadId); // log the warnings of the threads in the file "warning_log.txt"
            static void LogThreadInformations(const unsigned int threadId); // log the informations of the threads to the standar doutput
            static char* threadMessage(const char* errBuff, const char* errNumBuff, const char* threadIdBuff, const char* msgId, const char* newLine); // prepare the three type of logging message for each thread, and called from LogThreadsErrors and LogThreadWarnings and LogThreadInformations


    };

}




#endif // LOGGER_HPP







