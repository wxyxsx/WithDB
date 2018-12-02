// WithDB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <algorithm>
#include <fstream>
#include <random>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <chrono> 

using namespace std;

const char * path = "C:\\Users\\wxy\\test.db";

std::random_device rd;
std::mt19937 random_engine(rd());

db::address testsaveint(bool sign) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	vector<int> arr;
	for (int i = 1;i < 501;i++) {
		arr.push_back(i);
	}
	shuffle(arr.begin(), arr.end(), default_random_engine(static_cast<unsigned int>(seed)));
	//random_shuffle(arr.begin(), arr.end());
	db::bptree<int>* tr = new db::bptree<int>(path, sign);
	cout << "root节点地址是" << tr->pointroot << endl;
	db::address res = tr->pointroot;
	int v = 1;
	for (vector<int>::iterator it = arr.begin();it != arr.end();++it) {
		tr->insert(*it, v);
		v++;
	}
	tr->print_tree(3);
	//tr->print_leaf();
	tr->close();
	return res;
}

void testloadint(db::address res) {
	db::bptree<int>* tr = new db::bptree<int>(path, false, res);
	tr->print_tree(3);
	//tr->print_leaf();
	tr->close();
}

void testdelint(db::address res) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	vector<int> arr;
	for (int i = 1;i < 501;i++) {
		arr.push_back(i);
	}
	db::bptree<int>* tr = new db::bptree<int>(path, false, res);
	shuffle(arr.begin(), arr.end(), default_random_engine(static_cast<unsigned int>(seed)));
	int v = 1;
	for (vector<int>::iterator it = arr.begin();it != arr.end();++it) {
		tr->delkey(*it);
		v++;
		if (v > 470 || v % 100 == 0) {
			tr->print_tree(3);
		}
	}
	tr->close();
}

db::address testsavestr(bool sign) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	string teststr[334] = { "bbcs","clear","sides","deal","view","delivered","worse","reporters","have","into",
		"border","time","joint","the","thing","brexiteers","policy","might","prominent","proposals","there","regaining",
		"however","that","street","able","britains","end","negotiate","period","deals","result","another","house:","working",
		"sold","editor","customs","tory","donald","allow","kick","labour","event","export","suggesting","given","uk-eu","us",
		"prevent","exactly","no-one","some","prepare","it","uk","on","laying","advantageous","further","from","moment","mark",
		"currently","people","designed","united","largest","brexit","trump","wants","new","same","kingdom","vote","claiming",
		"mps","economy","great","days","jon","billions","withdrawal","sounds","you","seriously","snps","at","been","around",
		"british","legal","line","has","president","concerned","was","mp","get","washington","because","take","both","market",
		"acknowledged","dups","these","posts","its","aspect","now","delayed","sir","look","independent","suggested","did",
		"referendum","wouldnt","lucas","caroline","an","july","dodds","responding","december","countries","be","good",
		"eurosceptics","which","application","insurance","certainty","five","insisted","after","buts","open","later",
		"bilateral","north","needed","or","green","mays","struck","like","term","free-trade","party","theresa","brought",
		"told","not","until","pm","triggered","insisting","eu","if","again","home","tied","he","specify","dont","more",
		"through","basis","francois","trumps","sign","we","host","far","fought","had","members","may","appear","agreed",
		"2021","trade","including","before","pounds","absolutely","return","dem","being","businesses","as","hours","iain",
		"knew","visit","will","carry","between","vince","whether","single","parliament","fear","transition","fishermen",
		"could","over","unveiled","post-brexit","botched","force","of","way","2020","least","blackford","backstop","scottish",
		"meant","states","spokesman","while","leader","said","aims","prime","commons","were","provocative","unable","all","leave",
		"determine","bad","control","jeremy","for","to","with","doing","urge","met","senior","groups","her","forging","written",
		"times","lib","added","sopel","remarks","dodo","mrs","cable","strike","mr","put","downing","faced","allowed","criticism",
		"heavy","us-uk","rules","by","sunday","irish","much","administration","laws","money","full","very","world","can","america",
		"communication","in","nigel","his","under","flows","ifs","but","right","this","11","dead","threaten","sustained","others",
		"come","our","they","agreement","no","and","think","him","came","comments","what","white","called","january","formed","out",
		"is","long","outside","use","already","10","britain","so","groundwork","monday","during","possible","off","among","continue",
		"backbencher","she","corbyn","borders","ambitious","brussels","would","minister","absolute" };
	vector<string> data;
	for (int i = 0;i < 334;i++) {
		data.push_back(teststr[i]);
	}
	shuffle(data.begin(), data.end(), default_random_engine(static_cast<unsigned int>(seed)));
	db::bptree<std::string>* tr = new db::bptree<std::string>(path,sign);
	cout << "root节点地址是" << tr->pointroot << endl;
	db::address res = tr->pointroot;
	int v = 1;
	for (vector<string>::iterator it = data.begin();it != data.end();++it) {
		tr->insert(*it, v);
		v++;
	}
	tr->print_tree(15);
	//tr->print_leaf();
	tr->close();
	return res;
}

void testloadstr(db::address res) {
	db::bptree<std::string>* tr = new db::bptree<std::string>(path, false, res);
	tr->print_tree(15);
	//tr->print_leaf();
	tr->close();
}

void testdelstr(db::address res) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	string teststr[334] = { "bbcs","clear","sides","deal","view","delivered","worse","reporters","have","into",
		"border","time","joint","the","thing","brexiteers","policy","might","prominent","proposals","there","regaining",
		"however","that","street","able","britains","end","negotiate","period","deals","result","another","house:","working",
		"sold","editor","customs","tory","donald","allow","kick","labour","event","export","suggesting","given","uk-eu","us",
		"prevent","exactly","no-one","some","prepare","it","uk","on","laying","advantageous","further","from","moment","mark",
		"currently","people","designed","united","largest","brexit","trump","wants","new","same","kingdom","vote","claiming",
		"mps","economy","great","days","jon","billions","withdrawal","sounds","you","seriously","snps","at","been","around",
		"british","legal","line","has","president","concerned","was","mp","get","washington","because","take","both","market",
		"acknowledged","dups","these","posts","its","aspect","now","delayed","sir","look","independent","suggested","did",
		"referendum","wouldnt","lucas","caroline","an","july","dodds","responding","december","countries","be","good",
		"eurosceptics","which","application","insurance","certainty","five","insisted","after","buts","open","later",
		"bilateral","north","needed","or","green","mays","struck","like","term","free-trade","party","theresa","brought",
		"told","not","until","pm","triggered","insisting","eu","if","again","home","tied","he","specify","dont","more",
		"through","basis","francois","trumps","sign","we","host","far","fought","had","members","may","appear","agreed",
		"2021","trade","including","before","pounds","absolutely","return","dem","being","businesses","as","hours","iain",
		"knew","visit","will","carry","between","vince","whether","single","parliament","fear","transition","fishermen",
		"could","over","unveiled","post-brexit","botched","force","of","way","2020","least","blackford","backstop","scottish",
		"meant","states","spokesman","while","leader","said","aims","prime","commons","were","provocative","unable","all","leave",
		"determine","bad","control","jeremy","for","to","with","doing","urge","met","senior","groups","her","forging","written",
		"times","lib","added","sopel","remarks","dodo","mrs","cable","strike","mr","put","downing","faced","allowed","criticism",
		"heavy","us-uk","rules","by","sunday","irish","much","administration","laws","money","full","very","world","can","america",
		"communication","in","nigel","his","under","flows","ifs","but","right","this","11","dead","threaten","sustained","others",
		"come","our","they","agreement","no","and","think","him","came","comments","what","white","called","january","formed","out",
		"is","long","outside","use","already","10","britain","so","groundwork","monday","during","possible","off","among","continue",
		"backbencher","she","corbyn","borders","ambitious","brussels","would","minister","absolute" };
	vector<string> data;
	for (int i = 0;i < 334;i++) {
		data.push_back(teststr[i]);
	}
	shuffle(data.begin(), data.end(), default_random_engine(static_cast<unsigned int>(seed)));
	db::bptree<std::string>* tr = new db::bptree<std::string>(path, false, res);
	int v = 1;
	for (vector<string>::iterator it = data.begin();it != data.end();++it) {
		tr->delkey(*it);
		v++;
		if (v > 300 || v % 50 == 0) {
			tr->print_tree(15);
		}
	}
	tr->close();
}

void testindex() {
	db::address r1, r2, r3, r4;
	r1 = testsavestr(true);
	r4 = testsaveint(false);
	testloadstr(r1);
	testloadint(r4);
	testdelint(r4);
	testdelstr(r1);
	r3 = testsaveint(false);
	r2 = testsavestr(false);
	testloadint(r3);
	testloadstr(r2);
	testdelstr(r2);
	testdelint(r3);
}

void test1() {
	vector<char> buffer(db::PAGE_SIZE * 10);
	auto x = buffer.begin(), y = buffer.end();
	db::page p(x, x + db::PAGE_SIZE);

	db::fpage_wrapper f(path);
	cout << f.is_open() << endl;
	for (auto i = 0; i < 10; ++i) {
		p.write((long long)i + 123456789, 0);
		f.put(p, i * db::PAGE_SIZE);
	}
	for (auto i = 9; i >= 0; --i) {
		f.get(p, i * db::PAGE_SIZE);
		cout << p.read<long long>(0) << endl;
	}
}

void test2() {
	db::drive ctrl(path, true);
	vector<db::drive_address> addrs;
	cout << std::hex;
	for (int i = 0x100; i > 0; --i) {
		auto ret = ctrl.allocate(i * db::PAGE_SIZE, true);
		cout << ret << endl;
		addrs.push_back(ret);
	}
	for (int i = 0x100 - 1; i >= 0; --i) {
		ctrl.free(addrs[i]);
	}
	for (int i = 0x100; i > 0; --i) {
		auto ret = ctrl.allocate(i * db::PAGE_SIZE, true);
		cout << ret << endl;
		addrs.push_back(ret);
	}
	for (int i = 0x100 - 1; i >= 0; --i) {
		ctrl.free(addrs[i]);
	}
}

void test3() {
	struct test_handler : db::cache_handler<db::address, db::page> {
		virtual bool cache_insert(db::address addr, db::page &value) {
			cout << addr << " insert with writing" << endl;
			value.write(0x123456789LL, 0);
			return true;
		}
		virtual bool cache_erase(db::address addr, db::page &value) {
			cout << addr << " erase with reading: ";
			cout << "value = " << value.read<long long>(0) << endl;
			return true;
		}
	};
	cout << hex;
	test_handler handler;
	db::cache<db::address, db::page> test(4, handler);
	test.get(0x50);
	test.get(0x10);
	test.pin(0x10);
	test.get(0x50);
	test.get(0x20);
	test.pin(0x20);
	test.get(0x30);
	test.get(0x60);
	test.get(0x70);
	test.pin(0x70);
	test.get(0x80);
	test.unpin(0x70);
	test.get(0x90);
}

void test4() {

	db::drive io(path, true);
	db::translator trans(io);
	std::size_t data_segment = db::default_segment_address(db::DATA_SEG);
	trans.link(data_segment, io.allocate());
	cout << hex;
	for (int i = 0; i < 0x100; ++i) {
		auto x = data_segment + i * db::PAGE_SIZE;
		auto y = io.allocate();
		trans.link(x, y);
		cout << "link " << x << " with " << y << endl;
	}
	for (int i = 0; i < 0x100; ++i) {
		std::uniform_int_distribution<> dis(0, 0xff);
		auto x = data_segment + dis(random_engine) * db::PAGE_SIZE;
		cout << "get " << x << " with " << trans(x) << endl;
	}
	for (int i = 0; i < 0x100; ++i) {
		auto x = data_segment + i * db::PAGE_SIZE;
		trans.unlink(x);
		cout << "unlink " << x << endl;
	}
	for (int i = 0; i < 0x100; ++i) {
		auto x = data_segment + i * db::PAGE_SIZE;
		auto y = io.allocate();
		trans.link(x, y);
		cout << "link " << x << " with " << y << endl;
	}
	for (int i = 0; i < 0x100; ++i) {
		std::uniform_int_distribution<> dis(0, 0xff);
		auto x = data_segment + dis(random_engine) * db::PAGE_SIZE;
		cout << "get " << x << " with " << trans(x) << endl;
	}
	for (int i = 0; i < 0x100; ++i) {
		auto x = data_segment + i * db::PAGE_SIZE;
		trans.unlink(x);
		cout << "unlink " << x << endl;
	}
}

void test5() {
	db::keeper k(path, true);
	k.start();
	cout << hex;
	for (int i = 0; i < 0x20; ++i) {
		auto x = i * db::PAGE_SIZE;
		auto y = k.hold(x);
		cout << "get " << x << " with " << y.addr << endl;
		y.unpin();
	}
	for (int i = 0; i < 0x20; ++i) {
		auto x = i * db::PAGE_SIZE;
		auto y = k.loosen(i);
		cout << "loose " << x << " with " << y.addr << endl;
	}
	k.stop();
	k.close();
}

void test6() {
	db::keeper k(path, false);
	k.start();
	cout << hex;
	db::tuple_page x(std::move(k.hold(0)));
	cout << x.addr << endl;
	cout << x.get_free_space() << endl;
	auto i = x.allocate(600);
	cout << i << endl;
	auto p = x.get(i);
	cout << p.first << "  " << p.second << endl;
	char s[] = "1234567890", r[20] = {};
	x.copy_from(s, p.first, p.first + 10);
	x.copy_to(r, p.first, p.first + 10);
	cout << r << endl;
	k.stop();
	k.close();
}

void test7() {
	db::tuple_table table{
		db::tuple_entry(db::INT_T),
		db::tuple_entry(db::CHAR_T, 18),
		db::tuple_entry(db::VARCHAR_T),
		db::tuple_entry(db::INT_T),
		db::tuple_entry(db::CHAR_T, 15),
		db::tuple_entry(db::DOUBLE_T),
		db::tuple_entry(db::VARCHAR_T),
	};
	db::tuple_builder builder;
	builder.set_table(make_shared<db::tuple_table>(table));
	db::keeper k(path, true);
	k.start();
	for (auto i = 0; i < 0x100; ++i) {
		builder.start();
		builder.set(1, 0);
		builder.set(string("Supplier#000000001"), 1);
		builder.set(string("N kD4on9OM Ipw3, gf0JBoQDd7tgrzrddZ"), 2);
		builder.set(17, 3);
		builder.set(string("27-918-335-1736"), 4);
		builder.set(5755.94, 5);
		builder.set(string("each slyly above the careful"), 6);
		auto out = builder.get();
		builder.reset();
		for (db::address addr = 0; addr >= 0; addr += db::PAGE_SIZE) {
			db::tuple_page p(std::move(k.hold(addr)));
			try {
				p.load();
			}
			catch (out_of_range e) {
				p.init();
			}
			try {
				auto result = p.allocate(static_cast<db::page_address>(out->size()));
				auto pa = p.get(result);
				p.copy_from(out->begin(), pa.first, pa.second);
				p.dump();
				cout << i << " -- " << p.addr << ":" << result << endl;
				break;
			}
			catch (out_of_range e) {
				// cout << e.what() << endl;
			}
		}
	}
	int t = 0;
	for (db::address addr = 0; addr >= 0; addr += db::PAGE_SIZE) {
		db::tuple_page p(std::move(k.hold(addr)));
		try {
			p.load();
		}
		catch (out_of_range e) {
			break;
		}
		for (auto &entry : p.piece_table) {
			auto pa = p.get(entry.index);
			if (pa.second == 0) {
				continue;
			}
			db::tuple tmp(pa.second - pa.first);
			p.copy_to(tmp.begin(), pa.first, pa.second);
			cout << table.get<int>(tmp, 0) << endl;
			cout << table.get<string>(tmp, 1) << endl;
			cout << table.get<string>(tmp, 2) << endl;
			cout << table.get<int>(tmp, 3) << endl;
			cout << table.get<string>(tmp, 4) << endl;
			cout << table.get<double>(tmp, 5) << endl;
			cout << table.get<string>(tmp, 6) << endl;
			cout << t++ << " -- " << p.addr << ":" << entry.index << endl;
			p.free(entry.index);
		}
	}
	for (auto i = 0; i < 0x100; ++i) {
		builder.start();
		builder.set(1, 0);
		builder.set(string("Supplier#000000001"), 1);
		builder.set(string("N kD4on9OM Ipw3, gf0JBoQDd7tgrzrddZ"), 2);
		builder.set(17, 3);
		builder.set(string("27-918-335-1736"), 4);
		builder.set(5755.94, 5);
		builder.set(string("each slyly above the careful"), 6);
		auto out = builder.get();
		builder.reset();
		for (db::address addr = 0; addr >= 0; addr += db::PAGE_SIZE) {
			db::tuple_page p(std::move(k.hold(addr)));
			try {
				p.load();
			}
			catch (out_of_range e) {
				p.init();
			}
			try {
				auto result = p.allocate(static_cast<db::page_address>(out->size()));
				auto pa = p.get(result);
				p.copy_from(out->begin(), pa.first, pa.second);
				cout << i << " -- " << p.addr << ":" << result << endl;
				break;
			}
			catch (out_of_range e) {
				// cout << e.what() << endl;
			}
		}
	}
	for (auto i = 0; i < 0x100; ++i) {

		builder.start();
		builder.set(1, 0);
		builder.set(string("Supplier#000000001"), 1);
		builder.set(string("N kD4on9OM Ipw3, gf0JBoQDd7tgrzrddZ"), 2);
		builder.set(17, 3);
		builder.set(string("27-918-335-1736"), 4);
		builder.set(5755.94, 5);
		builder.set(string("each slyly above the careful"), 6);
		auto out = builder.get();
		builder.reset();
		for (db::address addr = 0; addr >= 0; addr += db::PAGE_SIZE) {
			db::tuple_page p(std::move(k.hold(addr)));
			try {
				p.load();
			}
			catch (out_of_range e) {
				p.init();
			}
			try {
				auto result = p.allocate(static_cast<db::page_address>(out->size()), false);
				auto pa = p.get(result);
				p.copy_from(out->begin(), pa.first, pa.second);
				cout << i << " -- " << p.addr << ":" << result << endl;
				break;
			}
			catch (out_of_range e) {
				cout << e.what() << endl;
			}
		}
	}

	k.stop();
	k.close();
}
// for temporary use to save strange file

int main()
{
	
	//cout << hex;
	ios::sync_with_stdio(false);
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	
	testindex();
	
	/*{
		db::controller c(path);
		c.put_from_file("C:/Users/wxy/Documents/supplier.tbl", false);
	}
	{
		db::controller c(path);
		c.get_all(10);
	}*/

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
