/*
    File: simpleclient.cpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/11

    Simple client main program for MP2 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

#include "reqchannel.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string localRequestHandler(string request)
{
    return request;
}

void executeClient() {

    cout << "CLIENT STARTED:" << endl;

    cout << "Establishing control channel... " << flush;
    RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
    cout << "done." << endl;

    /* -- Start sending a sequence of requests */

    string reply1 = chan.send_request("hello");
    cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

    // string reply2 = chan.send_request("data Joe Smith");
    // cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;
    //
    // string reply3 = chan.send_request("data Jane Smith");
    // cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;
    clock_t clientRunTime = clock();
    int numberOfDataReqs = 10000;
    for(int i = 0; i < numberOfDataReqs; i++)
    {
      string request_string("data TestPerson" + int2string(i));
      clock_t requestRunTime = clock();
      string reply_string = chan.send_request(request_string);
    //   string reply_string = localRequestHandler(request_string);
      requestRunTime = clock() - requestRunTime;
      printf("Request %i RunTime: %f seconds\n", i, ((float)clientRunTime)/CLOCKS_PER_SEC);

    cout << "reply to request " << i << ":" << reply_string << endl;
    }
    clientRunTime = clock() - clientRunTime;
    string reply4 = chan.send_request("quit");
    cout << "Reply to request 'quit' is '" << reply4 << "'" <<endl;

    printf("Total Requests created by the client: %d\n", numberOfDataReqs);
    printf("Client RunTime: %f seconds\n", ((float)clientRunTime)/CLOCKS_PER_SEC);


    usleep(100000);
}

void executeServer()
{
    execl("./dataserver", "./dataserver", NULL);
}


/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

    pid_t pid = fork();

    if(pid == 0)/*Child Process*/
    {
        // executeClient();
        executeServer();

    }
    else /*Parent Process*/
    {
        // executeServer();

        executeClient();
    }

    return 0;
}
