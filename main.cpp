#include "user.h"
#include "network.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

int main()
{
    Network network = Network();
    std::string s;
    std::cout << "Options: " << std::endl;
    std::cout << "1: add new user" << std::endl;
    std::cout << "2: friend two users" << std::endl;
    std::cout << "3: remove two users from each other's friend list" << std::endl;
    std::cout << "4: display current users" << std::endl;
    std::cout << "5: display a user's friend list" << std::endl;
    std::cout << "6: write the network information to a given file" << std::endl;
    std::cout << "7 (or any other entry): exit program" << std::endl;
    std::cout << "8: print out disjointed sets in this network" << std::endl;
    std::cout << "9 (or any other entry): exit program" << std::endl;
    while (getline(std::cin, s))
    {
        std::cout << "Options: " << std::endl;
        std::cout << "1: add new user" << std::endl;
        std::cout << "2: friend two users" << std::endl;
        std::cout << "3: remove two users from each other's friend list" << std::endl;
        std::cout << "4: display current users" << std::endl;
        std::cout << "5: display a user's friend list" << std::endl;
        std::cout << "6: write the network information to a given file" << std::endl;
        std::cout << "7: Find the shortest path between two users along their friends." << std::endl;
        std::cout << "8: print out disjointed sets in this network" << std::endl;
        std::cout << "9 (or any other entry): exit program" << std::endl;

        User user;
        User user2;
        std::stringstream is(s);
        int c;
        std::string name1;
        std::string name2;
        std::string temp_s;
        std::string bday;
        std::string zip;
        is >> zip;
        c = stoi(zip);
        std::vector<std::size_t> temp;
        std::vector<std::vector<int> > groups;
        std::vector<int> v;
        bool found1 = false;
        bool found2 = false;
        switch (c)
        {
        case 1:
            is >> name1;
            is >> name2;
            name1 = name1 + " " + name2;
            is >> bday;
            is >> zip;
            network.add_user(User(network.num_users() + 1, name1, stoi(bday), stoi(zip), std::vector<std::size_t>()));
            break;

        case 2:
            is >> name1;
            is >> name2;
            temp_s = name1 + " " + name2;
            is >> name1;
            is >> name2;
            name1 = name1 + " " + name2;
            if (network.add_connection(temp_s, name1) == -1)
                std::cout << "Name not found." << std::endl;
            break;

        case 3:
            is >> name1;
            is >> name2;
            temp_s = name1 + " " + name2;
            is >> name1;
            is >> name2;
            name1 = name1 + " " + name2;
            temp = network.get_user(network.get_id(temp_s)).friend_list();
            for (auto e : temp)
            {
                if (network.get_user(e).get_name() == name1)
                    found1 = true;
            }
            temp = network.get_user(network.get_id(name1)).friend_list();
            for (auto e : temp)
            {
                if (network.get_user(e).get_name() == temp_s)
                    found2 = true;
            }
            if (found1 || found2)
            {
                if (network.remove_connection(name1, temp_s) == -1)
                    std::cout << "Name not found" << std::endl;
            }
            else
                std::cout << "They aren't friends yet, or user does not exist!" << std::endl;

            break;

        case 4:
            std::cout << "ID Name       Year   Zip" << std::endl;
            std::cout << "=========================================================" << std::endl;
            for (std::size_t i = 1; i <= network.num_users(); i++)
            {
                user = network.get_user(i);
                if (user.get_zip() != -1)
                    std::cout << user.get_id() << " " << user.get_name() << " " << user.get_bday() << " " << user.get_zip() << std::endl;
            }
            break;

        case 5:
            is >> name1;
            is >> name2;
            name1 = name1 + " " + name2;
            user = network.get_user(network.get_id(name1));
            if (user.get_zip() == -1)
            {
                std::cout << "User not found" << std::endl;
            }
            else
            {
                std::cout << "ID Name       Year   Zip" << std::endl;
                std::cout << "=========================================================" << std::endl;
                for (auto e : user.friend_list())
                {
                    user2 = network.get_user(e);
                    std::cout << user2.get_id() << " " << user2.get_name() << " " << user2.get_bday() << " " << user2.get_zip() << std::endl;
                }
            }
            break;

        case 6:
            is >> name1;
            try
            {
                network.write_friends(name1);
                std::cout<<"Users added: "<<network.num_users()<<std::endl;
            }
            catch (...)
            {
                std::cout << "File name invalid." << std::endl;
            }
            break;

        case 7: 
            is >> name1;
            is >> name2;
            temp_s = name1 + " " + name2;
            is >> name1;
            is >> name2;
            name1 = name1 + " " + name2;
            v = network.shortest_path(network.get_id(temp_s), network.get_id(name1));
            if (name1== temp_s) {
                std::cout<<"Distance: 0"<<std::endl;
            }
            else std::cout<<"Distance: "<<v.size() - 1 <<std::endl;
            if (v.size() == 0) {
                std::cout<<network.get_user(network.get_id(temp_s)).get_name()<<std::endl;
            } else {
            for (int i = 0; i < v.size(); i++) {
                std::cout<<network.get_user(v[i]).get_name();
                if (i < v.size() - 1)
                    std::cout<<" -> ";
            }
            std::cout<<std::endl;
            }
            break;

        case 8:
            std::cout<<std::endl;
            c = 0;
            groups = network.groups();
            for (auto e: groups) {
                c++;
                std::cout<<"Set "<<c<<" => ";
                for (int i = 0; i < e.size(); i++) {
                    std::cout<<network.get_user(e[i]).get_name();
                    if (i < e.size() - 1)
                        std::cout<<", ";
                }
                std::cout<<std::endl;
            }
            break;

        default:
            exit(1);
            break;
        }
        std::cout<<std::endl;
    }
    return 0;
}