#pragma once
#include<ctime>
#include<iostream>
std::ostream& log(){
    std::cout<<"for debug| "<<"time:"<<time(NULL)<<" ";
    std::cout.flush();
    return std::cout;
}