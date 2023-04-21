#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Network
{
public:
    Network();

    // pre: none
    //post: reads and initializes the network information from a file and returns 0; if file is not a valid filename -1 is returned
    int read_friends(std::string file);

    // pre: none
    //post: writes the network information to a file and returns 0; if file is not a valid filename -1 is returned
    int write_friends(std::string file);

    //pre: none
    //post: adds the user to the network
    void add_user(User user);

    //pre: names are formatted properly (First Last)
    //post: makes the user's with the given names friends and returns 0 (or -1 if unsuccessful)
    int add_connection(std::string name1, std::string name2);

    //pre: names are formatted properly (First Last)
    //post: removes the user's with the given names friend connection and returns 0 (or -1 if unsuccessful)
    int remove_connection(std::string name1, std::string name2);

    //pre: the name is formatted properly (First Last)
    //post: returns the id of the user (or -1 if the name is invalid)
    int get_id(std::string name);

    //pre: none
    //post: returns the number of users in this network
    std::size_t num_users();

    //pre: the id provided is valid
    //post: returns the user with the corresponding id
    User& get_user(int id);

    //pre: the ids the ints provide are valid
    //post: returns a vector containing the (in order) that link User from to User to
    std::vector<int> shortest_path(int from, int to);

    //pre: none
    //post: returns a vector containing all the seperate disjointed groups of friends
    std::vector<std::vector<int> > groups();

private:

    //pre: from is a valid id
    //post: performs bfs on a given id and returns a vector containing all of the user-ids explored in the search (this is a helper function for groups())
    std::vector<int> bfs(int from);

    std::vector<User> users;
};

#endif