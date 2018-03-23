/*
 * interval_manager.h
 *
 *  Created on: Mar 22, 2018
 *      Author: Dan
 */

#ifndef INTERVAL_MANAGER_H_
#define INTERVAL_MANAGER_H_


#include <assert.h>
#include <map>
#include <limits>

template<class K, class V>
class interval_manager {

    friend void interval_manager_test();

private:

    std::map<K,V> _map;

public:
    // Constructor - it makes an association for value to the whole range of K
    interval_manager(V const& value) {
        _map.insert(_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), value));
    }

    void add(K const& key_begin, K const& key_end, V const& value) noexcept {

    	if (!(key_begin < key_end))
    		return; // NOP

    	// An iterator which we use as a temporary variable several times
    	typename std::map<K, V>::iterator iter;

    	std::pair<typename std::map<K, V>::iterator, bool> pos_begin;
		try {

			pos_begin = _map.insert(typename std::pair<K, V>(key_begin, value));
		}
    	catch(...) {

    		return;
    	}

    	std::pair<typename std::map<K, V>::iterator, bool> pos_end;
    	try {

    		pos_end = _map.insert(typename std::pair<K, V>(key_end, value));
    	}
    	catch(...) {

    		// We leave the map structure as before and then we return
    		if (pos_begin.second) _map.erase(pos_begin.first);

    		return;
    	}

    	// We fix the value for the key_end
    	if (pos_end.second) {

    		iter = pos_end.first;
    	    --iter; // This is safe since posEnd is always behind posBegin

    	    if (iter != pos_begin.first) pos_end.first->second = iter->second;
    	    else {

    	    	if (!pos_begin.second) pos_end.first->second = iter->second;
    	    	else {

    	    		--iter; // This is safe because pos_begin.second flag is true
    	    		pos_end.first->second = iter->second;
    	    	}
    	    }
    	}

    	// We fix the value for the key_begin
    	if (!pos_begin.second)
    		pos_begin.first->second = value;

    	// We delete all the elements from [pos_begin + 1 to pos_end) because
    	// they are overwritten by the new interval
    	iter = pos_begin.first;
    	_map.erase(++iter, pos_end.first);


    	// We make the _map canonical again if it's not canonical anymore
    	if (pos_begin.first->second == pos_end.first->second)
    		_map.erase(pos_end.first);

    	if (pos_begin.first != _map.begin()) {

    		iter = pos_begin.first;
    		--iter; // This is safe because pos_begin is not _map.begin()

    	    if (pos_begin.first->second == iter->second)
    	    	_map.erase(pos_begin.first);
    	}

    	return;
    }

    // Lookup of the value associated with key
    V const& operator[](K const& key) const {
        return (--_map.upper_bound(key))->second;
    }
};

#endif /* INTERVAL_MANAGER_H_ */
