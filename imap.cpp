#include <stdlib.h>

#include<string>
#include<iostream>
#include <curl.h>
#include <utility>
#include <thread>
#include <chrono>
#include<mutex>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iomanip>
#include <sstream>
#include <fstream>  
using namespace std;

#undef FALSE
#define FALSE 0
#undef TRUE
#define TRUE 1

#define MAX_GMAIL_USER_LEN 256
#define MAX_GMAIL_PASS_LEN 256
mutex mtx;
static int NumEmails=1;

struct memobj {
  char *memory;
  size_t size, 

};

size_t write_callback(char *ptr, size_t size, size_t nmemb, FILE *stream)
{ 

 size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
static int ShowGmailFolders(const char *username, const char *password, const char * label_type, int N, FILE *fp)
{ 

 
   auto labels=std::string(label_type);
   std::string url_host ="imaps://imap.gmail.com:993/" + labels + ";UID=";
  url_host=url_host+std::to_string(N);
  const char *url=url_host.c_str();
  
  CURL *curl = NULL;
  CURLcode res = CURLE_FAILED_INIT;
  char errbuf[CURL_ERROR_SIZE] = { 0, };
  
  curl = curl_easy_init();
 
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  
  curl_easy_setopt(curl, CURLOPT_USERNAME, username);
  curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
  
  curl_easy_setopt(curl, CURLOPT_URL, url);


 
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
 try
{
  res = curl_easy_perform(curl);

  if(res == CURLE_OK) {
  NumEmails=NumEmails+1;
  fwrite("\n--------------------------------------------------Mail Finished Mail Finished----------------------------------------------------------------------------\n", sizeof(char), 157, fp);
   
 }
}
 catch(std::logic_error &e) {}  



 curl_easy_cleanup(curl);
}


int main(int argc, char *argv[])
{
ofstream Performance;
Performance.open("Performance.txt");
int Num=1;

  if(argc != 3) {
    fprintf(stderr, "Usage: ShowGmailFolders <username> <password>\n");
    return EXIT_FAILURE;
  }

  if(curl_global_init(CURL_GLOBAL_ALL)) {
    fprintf(stderr, "Fatal: The initialization of libcurl has failed.\n");
    return EXIT_FAILURE;
  }

  if(atexit(curl_global_cleanup)) {
    fprintf(stderr, "Fatal: atexit failed to register curl_global_cleanup.\n");
    curl_global_cleanup();
    return EXIT_FAILURE;
  }

  if(!argv[1]||!argv[2]) {
    fprintf(stderr, "Error: Missing Credential.\n");
    return 0;
  }
FILE *fp1 = fopen("INBOX.txt","a");
FILE *fp2 = fopen("Personal.txt","a");
FILE *fp3 = fopen("Receipts.txt","a");
FILE *fp4 = fopen("Sent.txt","a");
FILE *fp5 = fopen("Trash.txt","a");
auto start = chrono::high_resolution_clock::now(); 
while (NumEmails<5000)
{ 
  
  thread t1(ShowGmailFolders,argv[1], argv[2], "INBOX",std::ref(Num), ref(fp1));
  thread t2(ShowGmailFolders,argv[1], argv[2], "Personal",std::ref(Num),ref(fp2));
  thread t3(ShowGmailFolders,argv[1], argv[2], "Receipts",std::ref(Num),ref(fp3));
  thread t4(ShowGmailFolders,argv[1], argv[2], "Sent",std::ref(Num),ref(fp4));
  thread t5(ShowGmailFolders,argv[1], argv[2],"Trash",std::ref(Num),ref(fp5));
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  Num=Num +1;
}
auto end = chrono::high_resolution_clock::now(); 
auto duration =  std::chrono::duration_cast<std::chrono::seconds>(end - start); 

std::stringstream ss;
ss<<to_string(duration.count());
Performance <<"Total Time Elapsed:  "<<ss.rdbuf()<<"Seconds ";
}

