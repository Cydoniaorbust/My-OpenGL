#pragma once

#include "Unit.h"
#include <map>
#include <string>
#include <exception>

namespace Exceptions {
	class URINotFound :				public std::runtime_error { public: URINotFound				(const std::string& Message = "The specified URI was not found in the resource index.") : runtime_error(Message) {} };
	class BadResourceAllocation :	public std::runtime_error { public: BadResourceAllocation	(const std::string& Message = "Failed to allocate memory for resource.")				: runtime_error(Message) {} };
}

template <class Resource> class	ResourceManagerB {
	typedef std::pair<std::string, Resource*> ResourcePair;
	typedef std::map<std::string, Resource*> ResourceList;
	ResourceList Resources;
public:
	~ResourceManagerB() { UnloadAll(); }

	std::string& Load(std::string& Unit) {
		if (Resources.find(Unit) == Resources.end()) { 
			Resource* temp = new (std::nothrow) Resource(Unit);
			if (!temp) throw Exceptions::BadResourceAllocation();
			Resources.insert(ResourcePair(Unit, temp));
		}
		return Unit;
	}
	void Unload(std::string& Unit) {
		ResourceList::const_iterator itr = Resources.find(Unit);
		if (itr != Resources.end()) {
			delete itr->second;
			Resources.erase(Unit);
		}
	}
	void UnloadAll() {
		ResourceList::iterator itr;
		for (itr = Resources.begin(); itr != Resources.end(); itr++) delete itr->second;
		Resources.clear();
	}

	Resource* GetPtr(std::string& Unit) {
		ResourceList::const_iterator itr;
		if ((itr = Resources.find(Unit)) != Resources.end()) return itr->second;
		return 0;
	}
	Resource& Get(std::string& Unit) {
		Resource* temp = GetPtr(Unit);
		if (temp) return *temp;
		else throw Exceptions::URINotFound();
	}
};