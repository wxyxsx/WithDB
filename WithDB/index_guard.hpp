#pragma once

#include "definitions.hpp"
#include "bptree.hpp"

namespace db {
	template<class T>
	struct IndexGuard { // �򵥵İ�װbptree
		bptree<T>* tr;
		address iroot; // ͨ����ȡiroot��ȡaddressλ��

		IndexGuard(Keeper* k) { // �½���
			tr = new bptree<T>(k);
			iroot = tr->pointroot;
		}

		IndexGuard(Keeper* k, address r) { // �������е�����
			tr = new bptree<T>(k, r);
			iroot = r;
		}

		address fetch(T key) {
			return tr->search(T);
		}

		void allocate(T key, address value) {
			tr->insert(key, value);
		}

		void free(T key) {
			tr->delkey(key);
		}

		void reallocate(T key, address value) {
			tr->delkey(key);
			tr->insert(key, value);
		}

		void print(int i) {
			tr->print_tree(i);
		}

		~IndexGuard() {
			tr->close();
		}
		
	};


}