#pragma once
#include<memory>
#include<vector>
#include"BasicCommand.h"
#include"Observer.h"
using std::shared_ptr;
using std::vector;
class Observable {
private:
	vector<shared_ptr<Observer>> ObserverList;
public:
	Observable(){}

	void AddObserver(shared_ptr<Observer> observer) 
	{
		ObserverList.push_back(observer);
	}

	void RemoveObserver(shared_ptr<Observer> observer) {
		for (auto it = ObserverList.begin(); it != ObserverList.end(); it++) 
		{
			if (*it == observer)
			{
				ObserverList.erase(it);
				break;
			}
		}
	}

	void notify(const Params& params) {
		for (auto it : ObserverList) {
			it->Update(params);
		}
	}
};