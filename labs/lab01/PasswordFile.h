// PasswordFile.h header

#ifndef PASSWORDFILE_H
#define PASSWORDFILE_H

#include <string>
#include <vector>

class PasswordFile {
public:
    PasswordFile(std::string filename);
    void addpw(std::string newUser, std::string newPassword);
    bool checkpw(std::string usr, std::string pwd);
    static void newsalt(int ns);
private:
    static int salt;
    std::string filename;
    std::vector<std::string> user;
    std::vector<std::string> password;
    void synch();
    std::string encrypt(std::string s);
    std::string decrypt(std::string s);
};

#endif