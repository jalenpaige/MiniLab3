#include "user.h"
#include <iostream>
#include <vector>
#include <algorithm>

User::User()
{
    id_ = 0;
    name_ = "";
    year_ = -1;
    zip_ = -1;
    friends = std::vector<std::size_t>();
}

User::User(std::size_t i, std::string un, int b_y, int zc, std::vector<std::size_t> f)
{
    id_ = i;
    name_ = un;
    year_ = b_y;
    zip_ = zc;
    friends = f;
}

//Getters
std::size_t User::get_id() {
    return id_;
}

int User::get_bday() {
    return year_;
}

void User::print() {
    for (auto e: friends)
        std::cout<<e<<" ";
}

std::string User::get_name() {
    return name_;
}

int User::get_zip(){
    return zip_;
}

std::vector<std::size_t> User::friend_list() {
    return friends;
}

//Methods

// pre: none
// post: if friend_ID is not already in the friend list, it is added to the vector; otherwise, do nothing
void User::add_friend(std::size_t friend_ID)
{
    if (std::find(friends.begin(), friends.end(), friend_ID) == friends.end())
        friends.push_back(friend_ID);
}

// pre: none
// post: if friend_ID is in the friends vector, erase it; otherwise, do nothing
void User::delete_friend(std::size_t friend_ID)
{
    if (std::find(friends.begin(), friends.end(), friend_ID) != friends.end())
        friends.erase(find(friends.begin(), friends.end(), friend_ID));
}