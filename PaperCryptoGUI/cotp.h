#ifndef COTP_H
#define COTP_H

#include <stdio.h> /* printf */
#include <stdlib.h> /* getenv */
#include <iostream>
#include <string>
#include <stdexcept>
#include <time.h>  //for randomizing
#include <assert.h>

using namespace std;

//ready

class cOTP {
    public:
        static string ProgramName;
        static string ProgramVersion;
        void menu ();	// main menu of program
        string get_enc_mess(string);
        string enc_menu(string, bool);	//encryption menu
        string pad;
        string dec(string,string);
        string conv_mess(string); //conversion message

    private:
        static string alpha;
        string gen (size_t _mess);//random pad generator

        void alpha_test(); // simple alphabet testing
        void base ();	// basic table to manually generate pad with 1k6 and 1k8 dices
        void coding_print(); //printing coding table
        void decoding_print();	//printing decoding table
        string enc(string,string); //encoding function

        void dec_menu(); 	//decoding menu





};
/*
//VARIABLES
string cOTP::ProgramName = "Paper-Crypto";
string cOTP::ProgramVersion = "0.1wip";
string cOTP::alpha = "ABCDEFGHiJKLMNoPQRSTUVWXYZ0123456789^?!.*+-/=@$:";
*/

#endif // COTP_H
