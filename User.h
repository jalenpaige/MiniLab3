#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <algorithm>

class User
{
public:

    int depth;
    int predecessor;

    User();

    User(std::size_t i, std::string un, int b_y, int zc, std::vector<std::size_t> f);

    std::size_t get_id();

    void print();
    std::string get_name();

    int get_bday();

    int get_zip();

    std::vector<std::size_t> friend_list();

    // pre: none
    // post: if friend_ID is not already in the friend list, it is added to the vector; otherwise, do nothing
    void add_friend(std::size_t friend_ID);

    // pre: none
    // post: if friend_ID is in the friends vector, erase it; otherwise, do nothing
    void delete_friend(std::size_t friend_ID);

private:
    std::size_t id_;
    std::string name_;
    int year_;
    int zip_;
    std::vector<std::size_t> friends;
};

#endif
