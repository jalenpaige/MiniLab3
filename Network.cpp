
#include "user.h"
#include "network.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

Network::Network()
{
    users = std::vector<User>();
}

// pre: none
// post: reads and initializes the network information from a file and returns 0; if file is not a valid filename -1 is returned
int Network::read_friends(std::string file)
{
    std::ifstream is;
    std::string line;
    is.open(file);
    if (is.fail())
    {
        return -1;
    }
    std::getline(is, line);
    while (std::getline(is, line))
    {
        int id = std::stoi(line);
        std::getline(is, line);
        std::string name = line.substr(1);
        std::getline(is, line);
        int birthday = stoi(line.substr(1));
        std::getline(is, line);
        int zipcode = stoi(line.substr(1));
        std::getline(is, line);
        std::istringstream stream(line.substr(1));
        std::string temp;
        std::vector<std::size_t> v;
        while (stream >> temp)
        {
            v.push_back(stoi(temp));
        }
        users.push_back(User(id, name, birthday, zipcode, v));
    }
    return 0;
}

// pre: none
// post: writes the network information to a file and returns 0; if file is not a valid filename -1 is returned
int Network::write_friends(std::string file)
{
    std::ofstream os;
    os.open(file);
    if (os.fail())
        return -1;
    else
    {
        os << users.size() << std::endl;
        for (auto e : users)
        {
            os << e.get_id() << std::endl;
            os << "\t" << e.get_name() << std::endl;
            os << "\t" << e.get_bday() << std::endl;
            os << "\t" << e.get_zip() << std::endl;
            os << "\t";
            for (auto w : e.friend_list())
            {
                os << w << " ";
            }
            os << std::endl;
        }
    }
    return 0;
}

// pre: none
// post: adds the user to the network
void Network::add_user(User user)
{
    users.push_back(user);
}

// pre: names are formatted properly (First Last)
// post: makes the user's with the given names friends and returns 0 (or -1 if unsuccessful)
int Network::add_connection(std::string name1, std::string name2)
{
    if (get_id(name1) != -1 && get_id(name2) != -1) {
        get_user(get_id(name1)).add_friend(get_id(name2));
        get_user(get_id(name2)).add_friend(get_id(name1));
        return 0;
    } else return -1;
}

// pre: names are formatted properly (First Last)
// post: removes the user's with the given names friend connection and returns 0 (or -1 if unsuccessful)
int Network::remove_connection(std::string name1, std::string name2)
{
   if (get_id(name1) != -1 && get_id(name2) != -1) {
        get_user(get_id(name1)).delete_friend(get_id(name2));
        get_user(get_id(name2)).delete_friend(get_id(name1));
        return 0;
    } else return -1;
}

// pre: the name is formatted properly (First Last)
// post: returns the id of the user (or -1 if the name is invalid)
int Network::get_id(std::string name)
{
    for (auto e : users)
    {
        if (e.get_name() == name)
            return e.get_id();
    }
    return -1;
}

// pre: none
// post: returns the number of users in this network
std::size_t Network::num_users()
{
    return users.size();
}

// pre: the id provided is valid and in the network;
// post: returns the user with the corresponding id (or an empty user otherwise)
User& Network::get_user(int id)
{
    for (auto &e : users)
    {
        if (e.get_id() == id)
            return e;
    } 
    static User user = User();
    return user;
}

//pre: the ids the ints provide are valid
//post: returns a vector containing the ids of friends (in order) that link the User from to the User to
std::vector<int> Network::shortest_path(int from, int to)
{
    std::vector<int> v;
    if (from == to) {
        return v;
    }
    for (auto &e: users) {
        e.depth = -1;
        e.predecessor = -1;
    }
    std::queue<int> q;
    int front;
    q.push(from);
    get_user(from).depth = 0;
    while (!q.empty()) {
        front = q.front();
        if (front == to)
            break;
        q.pop();
        for (auto &e : get_user(front).friend_list()) {
            if (get_user(e).depth == -1) {
                get_user(e).predecessor = front;
                get_user(e).depth = get_user(front).depth + 1;
                q.push(e);
            }
        }
    }
    get_user(from).predecessor = -1;
    v.push_back(to);
    int temp = to;
    while (get_user(temp).predecessor != -1) {
        temp = get_user(temp).predecessor;
        v.push_back(temp);
    }
    std::cout<<std::endl;
    std::reverse(v.begin(), v.end());
    std::cout<<std::endl;
    return v;
}

//pre: from is a valid id
//post: performs bfs on a given id and returns a vector containing all of the user-ids explored in the search (this is a helper function for groups())
std::vector<int> Network::bfs(int from) 
{
    for (auto &e: users) {
        e.depth = -1;
        e.predecessor = -1;
    }
    std::vector<int> v;
    std::queue<int> q;
    int front;
    q.push(from);
    v.push_back(from);
    get_user(from).depth = 0;
    while (!q.empty()) {
        front = q.front();
        q.pop();
        for (auto &e : get_user(front).friend_list()) {
            if (get_user(e).depth == -1) {
                get_user(e).predecessor = front;
                get_user(e).depth = get_user(front).depth + 1;
                q.push(e);
                v.push_back(e);
            }
        }
    }
    return v;
}

 //pre: none
 //post: returns a vector containing all the seperate disjointed groups of friends
std::vector<std::vector<int> > Network::groups() 
{
    bool found;
    std::vector<std::vector<int> > v;
    for (auto &e : users) {
        found = false;
        for (auto w : v)
            for (auto v : w)
                if (e.get_id() == v)
                    found = true;
        if (!found) {
            v.push_back(bfs(e.get_id()));
        }
    }
    return v;
}