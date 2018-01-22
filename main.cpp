/* Author: Yassine Maalej
   email: maalej.yessine@gmail.com.
*/



/*
    you will find makefile, logger.hpp, logger.cpp, warning_log.txt, error_log.txt         {redirect thread warning messages to warning_log.txt  ,  redirect threads error messages to error_log.txt}
    to compile and build # make                                                            {three user defined loggin types error warning information}
    to run # ./MAIN_LOGGER_RIGHTWARE error warning information                             {for all three type of logging, 2 arguments will give two type of logging}
    to run # ./MAIN_LOGGER_RIGHTWARE error                                                 {for logging only errors and showing them in error_log.txt}
    to run # ./MAIN_LOGGER_RIGHTWARE warning                                               {for logging only warnings and showing them in warning_log.txt}
    to run # ./MAIN_LOGGER_RIGHTWARE information                                           {for logging only infotmations and showing them standard output}
    failure to write the arguments correctly (order does not matter) will prevent you from continuing, with error message.
    failure to write more than three arguments or duplicate logging types or any unacceptable type (other than error warning information) will prevent you from continuing, with error message.

    I AM NOT AWARE OF ANY BUG IN THE CODE.
    PLEASE LET ME KNOW IF YOU NEED ANY CLARIFICATION.
    THANKS,
    YASSINE MAALEJ (maalej.yessine@gmail.com)

*/

#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<iostream>
#include<math.h>
#include <thread>
#include<string>

// Programmer Defined Header Files
#include "logger.hpp"





// total number of threads
#define TotalNumberThreads 15


using namespace std;
int main(int argc, char* argv[])
{
        cout << "Yassine Maalej *** RIGHTWARE LOGGER ASSIGNMENT *** maalej.yessine@gmail.com" << endl;

        LOG::Logger log;

        // check c++ 11 used or higher
        log.checkCPlusPlusEleven();

        // set to false all the logging types
        log.setIsWarningLogged(false);
        log.setIsInformationLogged(false);
        log.setIsErrorLogged(false);

        // check the arguments (error and/or warning and/or information) that the user gave in argument in terminal, and set if accurate the logger
        log.checkSetUserLoggingTypes(argc, argv);

        #if TotalNumberThreads < 1
        cout<<"-- 0 or negative total number of threads" << endl;
        exit(EXIT_FAILURE);
        #endif

        ////
        // we will run three group of threads, each group has TotalNumberThreads and in every time we will make specific logging
        ////


        // array of threads writing errors, if error was given as argument
        if(log.getIsErrorLogged()){
            std::thread threads1[TotalNumberThreads];
            for (unsigned int i=0; i<TotalNumberThreads; ++i){
                 threads1[i] = thread(LOG::Logger::LogThreadErros,i);
                 /* putting both the LogThreadErros and the logThreadWarnings have gave me an error during the execution related to threads execution.
                if(log.getIsWarningLogged()){
                    threads1[i] = thread(LOG::Logger::LogThreadWarnings,i);
                 }*/
            }
            for (auto& th : threads1){
                th.join();
            }
        }

        // array of threads writing warnings, if warning was given as argument
        if(log.getIsWarningLogged()){
            std::thread threads2[TotalNumberThreads];
            for (unsigned int i=0; i<TotalNumberThreads; ++i){
                 threads2[i] = thread(LOG::Logger::LogThreadWarnings,i);
             }
            for (auto& th : threads2){
                th.join();
            }
        }

        // array of threads writing Information, if information was given as argument
        if(log.getIsInformationLogged()){
            std::thread threads3[TotalNumberThreads];
            for (unsigned int i=0; i<TotalNumberThreads; ++i){
                 threads3[i] = thread(LOG::Logger::LogThreadInformations,i);
            }
            for (auto& th : threads3){
                th.join();
            }
         }



        return 0;
}
