#include "array.h"

//open addressing hash table. each position only contains 1 element
template<class T>
class LinearHashTable {
	Array<T> t;
	int n;//counter of data values
	int q;//counter of data + deleted values
	int d;//exponent of 2^d. dimension of hash table
	T null;//null values
	T del;//deleted values

public:
	LinearHashTable(T null, T del) : t(2, null), null(null), del(del), n(0), q(0), d(1) {};
	T find(T x);
	int hash(T x) { return 5; }
	bool add(T x);
	T remove(T x);
	void resize();
};

template<class T>
void LinearHashTable<T>::resize() {
	d = 1;
	while ((1 << d) < 3 * n)//2^d>=3n. total number of position is 3 times more than the elements in the array
		d++;
	Array<T> t_new(1 << d, null);
	q = n;//reset q, because the new array doesnt have any del values yet
	//insert everything into t_new
	for (int k = 0; k < t.size; k++) {
		if (t[k] != null && t[k] != del) {
			int i = hash(t[k]);//cannot straight deep copy the array, because since the length of this array is different, the hash(x) will ouput a different value for same x
			while (t_new[i] != null)
				i = (i < t_new.size - 1) ? 0 : i + 1;
			t_new[i] = t[k];
		}
	}
	t = t_new;
}

template<class T>
T LinearHashTable<T>::find(T x) {
	int i = hash(x);
	while (t[i] != null) {//until is not found a null value: no data was set so also the x value was not set, meaning that is not in the array
		if (t[i] != del && t[i] == x)//check for the value x 
			return t[i];
		i = (i == t.size - 1) ? 0 : i + 1;//increment i. in case it was at the last position, wrap around
	}
}

template<class T>
bool LinearHashTable<T>::add(T x) {
	if (find(x) != null) //check that no value x is stored
		return false;
	if (2 * (q + 1) > t.size) 
		resize();//in case mumber of deleted + values is more than half of total postion, resize the array
	int i = hash(x);
	while (t[i] != null && t[i] != del)
		i = (i == t.size - 1) ? 0 : i + 1;//increment 1 if not at the end of the array, otherwise wrap around
	if (t[i] == null)
		q++;
	n++;
	t[i] = x;
	return true;
}

//search for x, if found delete it and set value = del. otherwise return null
template<class T>
T LinearHashTable<T>::remove(T x) {
	int i = hash(x);
	while (t[i] != null && t[i] != del) {
		if (t[i] == x && t[i] != del) {
			T y = t[i];
			t[i] = del;
			n--;
			if (8 * n < t.size)//minimum data value is 12.5% occupancy
				resize();
			return y;
		}
		i = (i == t.size - 1) ? 0 : i + i;
	}
	return null;
}
