#pragma once

#include "keeper.hpp"
#include "type_config.hpp"

#include <iostream>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

namespace db {

	// todo �����ַ���(ɾ������ѯ��ɾ��)Ҫ������󳤶�

	using str = std::string;

	constexpr int BUFFSIZE = 1024; // �ڵ�buffer��С
	constexpr int MAXSTRSIZE = 20; // �ַ�����󳤶�
	constexpr address NULLADDR = 0; // NULL�����ݿ��ַ�еı�ʾ
	constexpr int N = (BUFFSIZE - 16) / 12; // �ڵ��ܷ��µ�����key��
	constexpr int MINLF = (N + 1) / 2; // Ҷ�ڵ���С����key��
	constexpr int MINNLF = MINLF - 1; // ��Ҷ�ڵ���С����key��
	constexpr int HALFSTR = (BUFFSIZE - 16) / 2; // �ڵ���С�ַ���ռ��

	constexpr static page_address FLAG_POS = 0;
	constexpr static page_address FLAG_NUM = 4;
	constexpr static page_address FLAG_NEXT = 8;
	constexpr static page_address FLAG_VECTOR = 16;

	/*
	4[flag]+4[num]+4*n[key]+8*(n+1)[addr]=BUFFSIZE
	*/

	template <typename T>
	class Node : virtual_page
	{
	public:
		int flag;
		// 0 δʹ�� 1 Ҷ�ڵ� 2 ָ��Ҷ�ڵ� 3 ָ���Ҷ�ڵ� 
		int n;
		std::vector<T> k;
		std::vector<address> a;
		address next;

		virtual void load() {
			reactivate();
			while (!pin()) {
			}
			flag = read<int>(FLAG_POS);
			if (flag != 0) {
				n = read<int>(FLAG_NUM);
				next = read<address>(FLAG_NEXT);
				page_address cur = FLAG_VECTOR;
				resize();
				for (int i = 0;i < n;i++) {
					k[i] = read<T>(cur);
					cur += sizeof(T);
					a[i] = read<address>(cur);
					cur += sizeof(address);
				}
				if (flag != 1) {
					a[n] = next;
				}
			}
			else {
				n = 0;
				a.resize(1, NULLADDR);
				next = NULLADDR;
			}
			unpin();
		}

		inline std::vector<char> debug() {
			return std::vector<char>(begin(), end());
		}

		virtual void dump() {
			reactivate();
			while (!pin()) {
			}
			
			write(flag, FLAG_POS);
			write(n, FLAG_NUM);
			if (flag == 1) write(next, FLAG_NEXT);
			else write(a[n], FLAG_NEXT);
			page_address cur = FLAG_VECTOR;
			for (int i = 0;i < n;i++) {
				write(k[i], cur);
				cur += sizeof(T);
				write(a[i], cur);
				cur += sizeof(address);
			}
			auto d = debug();
			unpin();
		}

		void close() {
			dump();
		}

		Node(virtual_page &&origin) : virtual_page(std::move(origin)) {

		}

		/*node(void) {
			flag = 0;
			n = 0;
			a.resize(1, nulladdr);
			next = nulladdr;
		}*/

		int isleaf() {
			int s = flag == 1 ? 0 : 1;
			return s;
		}

		void resize() {
			int s = isleaf();
			k.resize(n);
			a.resize(n + 1);//n+s
		}

		int size() {
			return n;
		}

		bool full(T key) {
			return n + 1 > N;
		}

		int split(T key) {
			int s = isleaf();
			return MINLF - s;
		}

		bool half() {
			int s = isleaf();
			return n >= MINLF - s;
		}

		bool half(T key) {
			int s = isleaf();
			return n - 1 >= MINLF - s;
		}

		bool merge(int len) {
			return n + len > N;
		}

		bool merge(int len, T key) {
			return n + len + 1 > N;
		}

		int move(bool direct) {
			int s = isleaf();
			return n - MINLF + s;
		}

		int move(bool direct, T key) {
			int s = isleaf();
			return n - MINLF + s;
		}
	};

	//template <typename T, std::enable_if<>>
	template<>
	class Node<str> : virtual_page {
	public:
		int flag;
		int n;
		std::vector<str> k;
		std::vector<address> a;
		address next;

		virtual void load() {
			reactivate();
			while (!pin()) {
			}
			flag = read<int>(FLAG_POS);
			if (flag != 0) {
				n = read<int>(FLAG_NUM);
				next = read<address>(FLAG_NEXT);
				page_address cur = FLAG_VECTOR;
				page_address last = BUFFSIZE - 1;
				resize();
				for (int i = 0;i < n;i++) {
					str key = read<str>(cur, last);
					k[i] = key;
					cur += static_cast<page_address>(key.length()) + 1;
					a[i] = read<address>(cur);
					cur += sizeof(address);
				}
				if (flag != 1) {
					a[n] = next;
				}
			}
			else {
				n = 0;
				a.resize(1, NULLADDR);
				next = NULLADDR;
			}
			unpin();
		}

		virtual void dump() {
			reactivate();
			while (!pin()) {
			}
			write(flag, FLAG_POS);
			write(n, FLAG_NUM);
			if (flag == 1) write(next, FLAG_NEXT);
			else write(a[n], FLAG_NEXT);
			page_address cur = FLAG_VECTOR;
			page_address last = BUFFSIZE - 1;
			for (int i = 0;i < n;i++) {
				write(k[i], cur, last);
				cur += static_cast<page_address>(k[i].length()) + 1;
				write(a[i], cur, last);
				cur += sizeof(address);
			}
			unpin();
		}

		void close() {
			dump();
		}

		Node(virtual_page &&origin) : virtual_page(std::move(origin)) {

		}

		/*Node(void) {
			flag = 0;
			n = 0;
			a.resize(1, NULLADDR);
			next = NULLADDR;
		}
		*/
		// leaf-0 nonleaf-1
		int isleaf() {
			int s = flag == 1 ? 0 : 1;
			return s;
		}

		void resize() {
			int s = isleaf();
			k.resize(n);
			a.resize(n + 1);//n+s
		}

		int strsize() {
			int cur = 9 * n;
			for (int i = 0;i < n;i++)
				cur += static_cast<int>(k[i].length());
			return cur;
		}

		int size() {
			int cur = strsize();
			return cur + 16;
		}

		bool full(str key) {
			int cur = size();
			cur += static_cast<int>(key.length()) + 9;
			return cur > BUFFSIZE;
		}

		// ���µ��ַ���ռ��Ҫ����һ��
		int split(str key) {
			int r = n;
			for (int i = 0;i < n;i++) {
				if (key <= k[i]) {
					r = i;
					break;
				}
			}
			int cur = 0;
			for (int i = 0;i < r;i++) {
				cur += 9 + static_cast<int>(k[i].length());
				if (cur > HALFSTR) return n - i; // n + 1 - (i + 1); ���� - ��������Ŀ
			}
			cur += 9 + static_cast<int>(key.length());
			if (cur > HALFSTR) return n - r;
			for (int i = r;i < n;i++) {
				cur += 9 + static_cast<int>(k[i].length());
				if (cur > HALFSTR) return n - 1 - i;
			}
			return 0;
		}

		bool half() {
			int cur = strsize();
			return cur >= HALFSTR;
		}

		bool half(str key) {
			int cur = strsize();
			cur -= static_cast<int>(key.length()) - 9;
			return cur >= HALFSTR;
		}

		bool merge(int len) {
			int cur = strsize();
			return cur + len > BUFFSIZE;
		}

		bool merge(int len, str key) {
			int cur = strsize();
			cur += static_cast<int>(key.length()) + 9;
			return cur + len > BUFFSIZE;
		}

		int move(bool direct) {
			int cur = strsize();
			int o = 0;
			for (int i = 0;i < n;i++) {
				if (direct) cur -= static_cast<int>(k[n - 1 - i].length()) + 9; // �Ӵ�С
				else cur -= static_cast<int>(k[i].length()) + 9;
				if (cur < HALFSTR) {
					o = i; // break��ʱ�� ѭ����i+1���� ����ʱ�Ѿ����������� ��������һ��i
					break;
				}
			}
			return o;
		}

		int move(bool direct, str key) {
			int remain = strsize(); // �ڵ�ʣ���С
			int cur = static_cast<int>(key.length()) + 9; // �½ڵ����Ĵ�С
			int o = 0;
			for (int i = 0;i < n;i++) {
				if (cur >= HALFSTR || remain < HALFSTR) { // �½ڵ㲻�ܼ��볬��һ�� �ɽڵ㲻�ܼ��ٳ���һ��
					o = i;
					break;
				}
				int t;
				if (direct) t = static_cast<int>(k[n - 1 - i].length()) + 9;  // �Ӵ�С
				else  t = static_cast<int>(k[i].length()) + 9;
				cur += t;
				remain -= t;
			}
			return o;
			// i���ڿ�ͷ��ѭ���Ĵ���
			// ѭ��1�κ�break�����ʾֻ������һ���ڵ�
			// ѭ��2�κ�break��֤��ֻ��ѭ��1���Ƿ���Ҫ��ģ��ڵ���ʧ2��key
		}
	};

	template <class T>
	class bptree
	{
	public:

		std::vector<Node<T>*> objlst; // ������нڵ��ָ��
		std::unordered_map<address, int> stb; // �������ݿ��ַ������objlst�е�ƫ�� 
		std::set<int> ftb; // �������objlst�п��е�ƫ�� set�������Զ����� ���ڻ��տռ�
		keeper k;

		address root; // root�ڵ�����ݿ��ַ ��Ϊroot�ڵ�Ҳ��䶯
		address pointroot;

		address sid;
		address getfreeaddr() { // ģ��Կ��е�ַ�Ĳ���
			address r = sid;
			sid++;
			return r;
		}

		// ���ݿ��ַ -> �ڵ�ָ�� ���ܷ���NULL
		Node<T>* getnode(address addr) {
			if (addr == NULLADDR) return NULL;
			return objlst[stb[addr]];
		}

		// �ڵ�ָ�� �����objlst�� -> ��������ݿ��ַ
		void setnode(Node<T>* nd, address addr) {
			int key = 0;
			if (ftb.size() != 0) { // ����п��пռ� ���set�л�ȡƫ��
				key = *(ftb.begin());
				ftb.erase(key);
				objlst[key] = nd;
			}
			else {
				key = static_cast<int>(objlst.size());
				objlst.push_back(nd);
			}
			stb[addr] = key;
			//			return addr;
		}

		void erase_node(address addr) {
			Node<T>* nd = getnode(addr);
			nd->flag = 0;
			nd->close();
			delete nd;
			int i = stb[addr];
			stb.erase(addr);
			objlst[i] = NULL;
			ftb.insert(i);
		}

		// ����˳���ڵ����
		void span_insert(Node<T>* a, Node<T>* b, T k, address v, int o) {
			int s = a->isleaf();
			int i = o - a->n;
			if (i < 0) { // ԭ�ڵ�
				a->k[o] = k;
				a->a[o + s] = v;
			}
			else {		 // �½ڵ�
				b->k[i] = k;
				b->a[i + s] = v;
			}
		}

		// ����k�ڽڵ�ԭ�����е�λ��
		int search_index(Node<T>* nd, T k) {
			int r = nd->n; // Ĭ��ָ�����Ҷ�
			for (int i = 0;i < nd->n;i++) {
				if (k < nd->k[i]) {
					r = i;
					break;
				}
			}
			return r;
		}

		// ���ҷ�Ҷ�ڵ��������Ҷ�ڵ�ĵ�һ��key
		T search_left(Node<T>* nd) {
			Node<T>* r = nd;
			while (r->flag != 1) // ֱ������Ҷ�ڵ�
				r = getnode(r->a[0]);
			return r->k[0];  // �����ѷ�Ҷ�ڵ�������˱�Ȼ��ֵ
		}

		// �ڵ����㹻�Ŀռ������Ԫ��
		void direct_insert(Node<T>* nd, T k, address v) {
			int s = nd->isleaf();
			int r = search_index(nd, k);
			int len = nd->n;

			nd->n++;
			nd->resize();

			for (int i = len;i > r;i--) {
				nd->k[i] = nd->k[i - 1];
				nd->a[i + s] = nd->a[i + s - 1];
			}
			nd->k[r] = k;
			nd->a[r + s] = v;
		}

		// �ڵ����ݳ���N�������½ڵ�ĵ�ַ
		address split_insert(Node<T>* nd, T k, address v) {
			int s = nd->isleaf();
			int r = search_index(nd, k);

			address addr = newnode();
			Node<T>* nnd = getnode(addr);

			nnd->n = nd->split(k);
			nnd->flag = nd->flag; // ���ѽڵ�λ��ͬһ��
			nnd->resize();

			int ln = nd->n;
			nd->n = ln + 1 - nnd->n;

			for (int i = ln;i > r;i--) // ��key�������һλ
				span_insert(nd, nnd, nd->k[i - 1], nd->a[i + s - 1], i);
			span_insert(nd, nnd, k, v, r);
			for (int i = r - 1;i > nd->n - 1;i--) // ��keyС��k����ҪǨ�Ƶ��µĽڵ�
				span_insert(nd, nnd, nd->k[i], nd->a[i + s], i);

			if (s == 0) { // ����ڵ����
				nnd->next = nd->next;
				nd->next = addr;
			}
			else {
				/*
				ԭ����3��������֮��Ϊ2+1����Ϊ�µĽڵ㲻����NULL����Ҫɾ��һ��key���������Ҷ���Ϊ�½ڵ�����
				��ԭ�ڵ����Ҷ˵�keyɾ����p�ŵ��½ڵ������
				*/
				nnd->a[0] = nd->a[nd->n];
				nd->n--;
				nd->resize();
			}

			return addr;
		}

		// ֱ��ɾ������򵥵����
		void direct_delete(Node<T>* nd, T k) {
			int s = nd->isleaf();
			int r = 0;
			for (int i = 0;i < nd->n;i++) {
				if (k == nd->k[i]) {
					r = i;
					break;
				}
			}
			int len = nd->n;
			// r ~ len-2 <- r+1 ~ len-1 
			for (int i = r + 1;i < len;i++) {
				nd->k[i - 1] = nd->k[i];
				nd->a[i - 1 + s] = nd->a[i + s];
			}
			nd->n--;
			nd->resize();
		}

		// b����Ҫɾ���Ľڵ� �����ұ߽ڵ���Сֵ(�ṩ���ϲ��޸�)
		T resize_delete_leaf(Node<T>* a, Node<T>* b) {
			bool direct = a->k[0] < b->k[0] ? true : false;
			int la = a->n;
			int lb = b->n;

			int o = a->move(direct); // b��Ҫ�����Ԫ����Ŀ
			b->n += o;
			b->resize();

			if (direct) { // a -> b 
				// 123->45 == -4 == 123->5 == 12->35
				for (int i = 0;i < lb;i++) { // o ~ lb+o-1(lfmin-1) <- 0 ~ lb-1
					b->k[lb - 1 + o - i] = b->k[lb - 1 - i];
					b->a[lb - 1 + o - i] = b->a[lb - 1 - i];
				}
				for (int i = 0;i < o;i++) { // 0 ~ o-1 <- la-1-o ~ la-1
					b->k[o - 1 - i] = a->k[la - 1 - i];
					b->a[o - 1 - i] = a->a[la - 1 - i];
				}
			}
			else { //  b<-a
				// 12->345 == -2 == 1->345 == 13->45
				for (int i = 0;i < o;i++) { // a��Ԫ����ӵ�b�� lb~lb+o-1 <- 0~o-1
					b->k[lb + i] = a->k[i];
					b->a[lb + i] = a->a[i];
				}
				for (int i = 0;i < la - o;i++) { // a�ڲ����λ 0~la-o-1 <- o~la-1
					a->k[i] = a->k[i + o];
					a->a[i] = a->a[i + o];
				}
			}

			a->n -= o;
			a->resize();

			if (direct) return b->k[0];
			else return a->k[0];
		}

		// �ؼ�������ȷ���������ļ�ֵ �Լ����Ϸ��صļ�ֵ
		T resize_delete_nonleaf(Node<T>* a, Node<T>* b) {
			bool direct = a->k[0] < b->k[0] ? true : false;

			int la = a->n;
			int lb = b->n;

			int o = 0;
			T tp;

			if (direct) { // a->b
				// 10 20 30 -> 40 50 == 10 20 30 -> 50
				// 10 20 30 -> (NULL) 35 50 == 10 -> 30 35 50 (20��ֱ�Ӷ���)
				tp = search_left(getnode(b->a[0]));
				o = a->move(direct, tp);

				b->n += o;
				b->resize();

				for (int i = 0;i < lb;i++) { // bԭ��ֵ����  o~lb+o-1 <- 0~lb-1
					b->k[lb + o - 1 - i] = b->k[lb - 1 - i];
					b->a[lb + o - i] = b->a[lb - i];
				}
				b->k[o - 1] = tp; // ��Ϊ��ߴ����֧����С��ֵ
				b->a[o] = b->a[0];
				for (int i = 0;i < o - 1;i++) { // �ƶ�key 0~o-2 <- la-o+1~la-1
					b->k[o - 2 - i] = a->k[la - 1 - i];
				}
				T res = a->k[la - o];
				for (int i = 0;i < o;i++) {  // �ƶ���ַ 
					b->a[o - 1 - i] = a->a[la - i];
				}

				a->n -= o;
				a->resize();

				return res;
			}
			else { //  b<-a
				// 10 20 -> 30 40 50 == 10 ->30 40 50
				// 10 25 (NULL) -> 30 40 50 == 10 25 30 ->  50 ����(40)  
				tp = search_left(getnode(a->a[0]));
				o = a->move(direct, tp);

				b->n += o;
				b->resize();

				b->k[lb] = tp;
				for (int i = 0;i < o - 1;i++) { // �ƶ�key lb+1~lb+o-1 <- 0~o-2 o-2
					b->k[lb + 1 + i] = a->k[i];
				}
				T res = a->k[o - 1];
				for (int i = 0;i < o;i++) { // �ƶ���ַ  lb+1~lb+o <- 0~o-1 0-1
					b->a[lb + 1 + i] = a->a[i];
				}

				for (int i = 0;i < la - o;i++) { //  0~la-o-1 <-  o~la-1
					a->k[i] = a->k[o + i];
				}
				for (int i = 0;i < la - o + 1;i++) { // 0~la-o < o~la
					a->a[i] = a->a[o + i];
				}

				a->n -= o;
				a->resize();

				return res;
			}
		}

		// ��Delete���ͷŽڵ� delete���� ָ����NULL���޸�ftb��
		bool merge_delete_leaf(Node<T>* a, Node<T>* b) {
			bool direct = a->k[0] < b->k[0] ? true : false;
			if (a->merge(b->size())) return false;
			Node<T> *x, *y;
			if (direct) {
				x = a;
				y = b;
			}
			else {
				x = b;
				y = a;
			}

			int lx = x->n;
			int ly = y->n;
			x->n += ly;
			x->resize();

			for (int i = 0;i < ly;i++) { // yԭ��ֵ���� lx~lx+ly-1 ~ 0~ly-1 
				x->k[lx + i] = y->k[i];
				x->a[lx + i] = y->a[i];
			}

			y->n = 0;
			x->next = y->next;
			return true;
		}

		bool merge_delete_nonleaf(Node<T>* a, Node<T>* b) {
			bool direct = a->k[0] < b->k[0] ? true : false;

			Node<T> *x, *y;
			if (direct) {
				x = a;
				y = b;
			}
			else {
				x = b;
				y = a;
			}
			T st = search_left(getnode(y->a[0]));
			if (a->merge(b->size(), st)) return false;
			// 1 2 -> 4 5 == 1 2 -> 5 ��resize������ͬ ֻ��Ҫȫ���ƶ���
			// 1 2 3 (NULL)->5 ==  1235
			int lx = x->n;
			int ly = y->n;
			x->n += ly + 1;
			x->resize();

			x->k[lx] = st;
			for (int i = 0;i < ly;i++) { // �ƶ�key
				x->k[lx + 1 + i] = y->k[i];
			}
			for (int i = 0;i < ly + 1;i++) { // �ƶ���ַ
				x->a[lx + 1 + i] = y->a[i];
			}

			y->n = 0;
			return true;
		}

		void print_leaf() {
			Node<T>* p = getnode(root);

			if (p->a[0] == NULLADDR) {
				print_leaf(getnode(p->a[1]));
				return;
			}

			while (p->flag != 1) p = getnode(p->a[0]);

			while (p != NULL) {
				print_leaf(p);
				p = getnode(p->next);
			}
		}

		void print_leaf(Node<T>* nd) {
			if (nd != NULL) {
				for (int i = 0;i < nd->n;i++) {
					std::cout << nd->k[i] << "[";
					std::cout << nd->a[i] << "],";
				}
			}
			std::cout << std::endl;
		}


		void print_space(int level, int pd) {
			str st = "";
			for (int i = 1;i < (pd + 3) * level;i++) {
				if (i % (pd + 3) == 0) st.append("|");
				else st.append(" ");
			}
			if (level != 0) st.append("+");
			std::cout << st;
		}

		// ����������ȱ���
		void print_nonleaf(Node<T>* nd, int level, int pd) {
			for (int i = 0;i < nd->n + 1;i++) {
				if (i != 0) print_space(level, pd); // ��һ��Ԫ�ز�������

				if (i != nd->n) std::cout << std::setw(pd) << std::left << nd->k[i] << "--+";
				else {
					str st = "";
					for (int i = 0;i < pd;i++) st.append(" ");
					st.append("--+");
					std::cout << st;
				}

				if (nd->flag == 2) print_leaf(getnode(nd->a[i]));
				else print_nonleaf(getnode(nd->a[i]), level + 1, pd);
			}
		}

		void print_tree(int padding) {
			Node<T>* ndroot = getnode(root);
			if (ndroot->n != 0) print_nonleaf(ndroot, 0, padding);
			std::cout << "-------------------------------------" << std::endl;
		}

		bptree(const char *path, bool sign) : k(path, sign) { // Ĭ���½�b+��
			k.start();
			create();
		}

		bptree(const char *path, bool sign, address addr) : k(path, sign) { // �������ݿ��ַ����ж�ȡ
			k.start();
			if (load(addr)) std::cout << "��ȡ�����ɹ�" << std::endl;
			else {
				create();
				std::cout << "�ṩ��ַ��Ч���½����ݿ�" << std::endl;
			}
		}

		// �½��ڵ㲢�������ݿ��ַ
		address newnode() {
			Node<T>* r = NULL;
			address i = 0;
			for (i = 1;i < SEGMENT_SIZE;i++) { // ��ʱ��δʵ�ֿ��пռ�����ܣ�δ��Ҫʵ��bitmap
				Node<T>* p = new Node<T>(std::move(k.hold(i*PAGE_SIZE + SEGMENT_SIZE)));
				p->load();
				if (p->flag == 0) { // ��ʾpageδʹ��
					p->flag = 1;
					p->dump(); // ������пռ���� ��Ҳ̫�˷���
					r = p;
					setnode(r, i);
					break;
				}
				else {
					delete p;
				}
			}
			if (r == NULL) return SEGMENT_SIZE;
			else return i;
			//return r;
		}

		// ��ȡ�ڵ����ݲ�������ƽṹ
		bool loadnode(address addr) {
			Node<T>* p = new Node<T>(std::move(k.hold(addr*PAGE_SIZE + SEGMENT_SIZE)));
			p->load();
			if (p->flag == 0) return false;
			else {
				setnode(p, addr);
				if (p->flag != 1) {
					for (int i = 0;i < p->n + 1;i++) {
						if (p->a[i] == NULLADDR) continue;
						if (!loadnode(p->a[i])) return false;
					}
				}
			}
			return true;
		}

		bool create() { // pprootʼ�ձ��浱ǰroot�ڵ�ĵ�ַ ��Ϊroot�ڵ��䶯
			pointroot = newnode();
			root = newnode();
			if (pointroot == SEGMENT_SIZE || root == SEGMENT_SIZE) {
				std::cout << "�½�����ʧ�ܣ�û�п��нڵ�" << std::endl;
				return false;
			}
			Node<T>* pproot = getnode(pointroot);
			Node<T>* proot = getnode(root);
			proot->flag = 2;
			pproot->flag = 1;
			pproot->next = root;
			std::cout << "�½������ɹ�" << std::endl;
			return true;
		}

		bool load(address addr) {
			pointroot = addr;
			if (!loadnode(addr)) return false;
			Node<T>* pproot = getnode(pointroot);
			if (!loadnode(pproot->next)) return false;
			return true;
		}

		void close() {
			Node<T>* pproot = getnode(pointroot);
			pproot->next = root;
			for (auto it = objlst.begin();it != objlst.end();++it) {
				if (*it != NULL) (*it)->close();
			}
			k.stop();
			k.close();
		}

		address search(T key) {
			address res = NULLADDR;

			Node<T>* p = getnode(root);
			if (p->n == 0) return res; // root�ڵ����Ϊ��

			while (p->flag != 1) { // ���p����Ҷ�ڵ㣬����������
				int r = search_index(p, key);
				p = getnode(p->a[r]);
				if (p == NULL) break; // ����root�ڵ���ڵ����ΪNUL
			}

			if (p != NULL) {
				for (int i = 0;i < p->n;i++) {
					if (key == p->k[i]) {
						res = (p->a[i]);
						break;
					}
				}
			}
			return res;
		}

		bool insert(T key, address value) {
			if (search(key) != NULLADDR) return false;

			Node<T>* ndroot = getnode(root);

			if (ndroot->n == 0) {	// root�ڵ�Ϊ�վ���Ҫ�½�Ҷ�ڵ�
				address addr = newnode(); // Ŀǰ��ַ��btree�л�ȡ���Ժ�Ӧ�ô�node�л�ȡ���󶨵ĵ�ַ
				Node<T>* nnd = getnode(addr);
				nnd->flag = 1;
				direct_insert(nnd, key, value);


				direct_insert(ndroot, key, addr);
				return true;
			}

			Node<T>* p = ndroot;
			std::stack<Node<T>*> path; // ��Ų�ѯ·��

			do {
				path.push(p);
				int r = search_index(p, key);
				p = getnode(p->a[r]);
			} while (p != NULL && p->flag != 1);

			if (p == NULL) { // ���pΪ��ֻ��������root�ڵ������ �½�Ҷ�ڵ� ��ַ������ڵ���
				address addr = newnode();
				Node<T>* nnd = getnode(addr);
				nnd->flag = 1;
				direct_insert(nnd, key, value);
				ndroot->a[0] = addr;
				nnd->next = ndroot->a[1];
				return true;
			}

			if (!p->full(key)) { // ���ݽڵ��ܷ���
				direct_insert(p, key, value);
				return true;
			}

			address v = split_insert(p, key, value);
			T k = getnode(v)->k[0]; // Ҷ�ڵ��ṩ����һ���key,value

			// ����ͨ�õ�ѭ�� ��k,v����p��
			do {
				p = path.top();
				path.pop();

				if (p == ndroot && ndroot->a[0] == NULLADDR) {
					/*
					 ��������ֵһֱ���� 1,2,3,4
					 ���� NULL [1] 1,2 [3] 3,4
					 ���� 1,2 [3] 3,4
					*/
					ndroot->k[0] = k;
					ndroot->a[0] = ndroot->a[1];
					ndroot->a[1] = v;
					return true;
				}

				if (!p->full(k)) { // �����Ҷ�ڵ�ŵ���
					direct_insert(p, k, v);
					break;
				}

				// �����������������ѷ�Ҷ�ڵ�

				v = split_insert(p, k, v);
				k = search_left(getnode(v));


				if (p == ndroot) { // ���Ҫ���ѵ���root�ڵ� ��Ҫ�½�root�ڵ�
					address addr = newnode();
					Node<T>* nnd = getnode(addr);
					nnd->n = 1;
					nnd->resize();

					nnd->k[0] = k;
					nnd->a[0] = root;
					nnd->a[1] = v;
					nnd->flag = 3;

					root = addr;
				}

			} while (!path.empty());
			return true;
		}

		bool delkey(T key) {
			if (search(key) == NULLADDR) return false; // ���û���ҵ�key�򷵻�û���ҵ�

			Node<T>* ndroot = getnode(root);
			Node<T>* p = ndroot;

			std::stack<Node<T>*> path;
			std::stack<int> poffset; // ��Ҫ��¼�ߵ����ĸ��ӽڵ�

			do {
				int r = search_index(p, key);
				path.push(p); // ��ǰ�ڵ���ջ
				poffset.push(r); // ƫ����ջ
				p = getnode(p->a[r]);
			} while (p->flag != 1);

			// ����Ҷ�ڵ�
			direct_delete(p, key);
			if (p->half()) return true;

			Node<T>* pv = path.top(); //��ǰ�ڵ㸸�ڵ�
			int pov = poffset.top(); //getnode(pv->addr[pov])����ǰ�ڵ�

			if (pv == ndroot) {
				if (pv->a[0] == NULLADDR) { // ���ֻ��һ��Ҷ�ڵ㣬���ӽڵ�����������
					if (p->n == 0) { // ����Ҷ�ڵ�
						erase_node(pv->a[1]);
						pv->n = 0;
					}
					return true;
				}
				else if (pv->n == 1) {
					int sign = 1 - pov;
					Node<T>* other = getnode(pv->a[sign]);
					if (merge_delete_leaf(other, p)) {
						// �����һ���ڵ�key���� ��ϲ� �������ұ� ����ֻ��root����ڵ����ΪNULL
						// ʼ�պϲ�����߽ڵ�
						erase_node(pv->a[1]);
						pv->a[1] = pv->a[0];
						pv->a[0] = NULLADDR;
						pv->k[0] = getnode(pv->a[1])->k[0];
						return true;
					}
				}
			}


			int sign = pov == 0 ? 1 : pov - 1; //��¼���ڽڵ��λ��
			int tp = pov == 0 ? 0 : pov - 1; // ��¼��һ��Ҫɾ��key��λ��
			Node<T>* other = getnode(pv->a[sign]);
			if (merge_delete_leaf(other, p)) {
				address eaddr = pv->a[tp + 1];
				erase_node(eaddr);
				if (pv == ndroot || pv->half(pv->k[tp])) {  // ��һ����root��һ����ֱ��ɾ�� ��Ϊroot����������Ѿ�����
					direct_delete(pv, pv->k[tp]);
					return true;
				}
			}
			else { // resize���ɣ�����ɾ���ڵ㣬�Ƚϰ�ȫ
				pv->k[tp] = resize_delete_leaf(other, p);
				return true;
			}

			// ���򽻸�ѭ������ɾ��
			do {
				int curk = tp; // curk�����һ����Ҫɾ��key��λ��
				p = path.top(); // ��ǰ�ڵ�����
				path.pop();
				poffset.pop();

				pv = path.top();
				pov = poffset.top();

				sign = pov == 0 ? 1 : pov - 1; // ���ڽڵ�λ��
				tp = pov == 0 ? 0 : pov - 1; // ��һ�����Ҫɾ����λ��
				other = getnode(pv->a[sign]);
				direct_delete(p, p->k[curk]);
				if (merge_delete_nonleaf(other, p)) {
					address eaddr = pv->a[tp + 1];
					erase_node(eaddr);
					if ((pv == ndroot && pv->n > 1) || pv->half(pv->k[tp])) { // ��һ����root����Ϊ1 ��������Ϊhalf
						direct_delete(pv, pv->k[tp]);
						return true;
					}
					else if (pv == ndroot && pv->n == 1) { // ���root�ڵ�Ҫɾ�� ��������root
						address eaddr = root;
						root = ndroot->a[0];
						erase_node(eaddr);
						return true;
					}
				}
				else { // resize���ɣ�����ɾ���ڵ㣬�Ƚϰ�ȫ
					pv->k[tp] = resize_delete_nonleaf(other, p);
					return true;
				}


			} while (true);

			return true;
		}
	};
}