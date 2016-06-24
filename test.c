#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1000
#define RESULT_FILENAME "/result.out"

// inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
// {
//     s.erase(0, s.find_first_not_of(t));
//     return s;
// }

// // trim from right
// inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
// {
//     s.erase(s.find_last_not_of(t) + 1);
//     return s;
// }

// // trim from left & right
// inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
// {
//     return ltrim(rtrim(s, t), t);
// }

// void run_cmd (string cmdname, string params, int inp=0, int outp=0 ) {
//     int pfd[2];
//     pipe(pfd);
//     if (inp) {
//         close(pfd[0]);
//         pfd[0] = inp;
//     }
//     if (outp) {
//         close(pfd[1]);
//         pfd[1] = outp;
//     }
//     if( !fork() ){
//         close(STDIN_FILENO);
//         dup2(pfd[0], STDIN_FILENO);
//         close(STDOUT_FILENO);
//         dup2(pfd[1], STDOUT_FILENO);
//         close(pfd[0]);
//         close(pfd[1]);
//         execlp(cmdname, cmdname, params, NULL);
//     } else {

//     }
    
// }

int main(int argc, char **argv) {
    char localfilename[80];
    sprintf(localfilename, "%s%s", getenv("HOME"), RESULT_FILENAME);
    FILE *outfile = fopen(localfilename, "w+");
    
    char buff[BUFFSIZE], result[BUFFSIZE];
    fgets(buff, BUFFSIZE, stdin);
    
    FILE *cmd = popen(buff, "r");
    
    while ( fgets(result, BUFFSIZE, cmd) != NULL ) {
        fputs(result, outfile);
    }
    fclose (outfile);
    //FILE *f = fopen(localfilename, "w");
    // string input = "who | sort | uniq -c | sort -nk1";
    // istringstream ss(input);
    // string token;
    
    // cout << input << endl;
    // while(std::getline(ss, token, '|')) {
    //     token = trim(token);
    //     cout << "--" << token << "--" << endl;
    //     size_t found = token.find(" ");
    //     string cmd_name, params;
    //     if (found!=string::npos) {
    //         cmd_name = token.substr(0, found);
    //         params = token.substr(found);
    //         trim(params);
    //     }
    //     else {
    //         cmd_name = token;
    //         params = "";
    //     }
    //     cout << "Cmdname --" << cmd_name << "--, params ++" << params << "++\n";
        
        
    // }

    
    return 0;
}